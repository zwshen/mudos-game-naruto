
/*  fingerd.c */

// #pragma save_binary

#include <origin.h>
#include <ansi.h>

inherit F_CLEAN_UP;

string *hide_ip = ({ "acme", "tmr" });

private object acquire_login_ob(string id);

private void create()
{
    seteuid(getuid());
}

// ���� ip -Tmr 2002/04/12
string reverse_ip(string ipstr)
{
        string ip1,ip2,ip3,ip4,okips;
        int i;
        if(!stringp(ipstr))
                return "NULL_IP_STRING";
        if(!sscanf(ipstr,"%s.%s.%s.%s",ip1,ip2,ip3,ip4) )
                return "NULL_IP_STRING";
        okips=sprintf("%3s.%3s.%3s.%3s",ip4,ip3,ip2,ip1);
        return okips;
}

// ����ip -By Tmr
string query_ip_name2(object ob)
{
        return reverse_ip(query_ip_name(ob) );
}

string age_string(int time)
{
    int month, day, hour;

    time /= 3600;
    hour = time % 24;
    time /= 24;
    day = time % 30;
    month = time / 30;
    return (month ? month + "m" : "") + (day ? day + "d" : "") + hour + "h";
}

string finger_all()
{
    object *ob;
    string msg;
    int i;

//      ob = sort_array( users(), (: strcmp(query_ip_number($1), query_ip_number($2)) :) );
        ob = sort_array( users(), (: strcmp(query_ip_name2($1), query_ip_name2($2)) :) );

    msg  = "�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    msg += "�x"BBLU"        �W��(ID)        "NOR" "BGRN"               DNS             "NOR" "BYEL"�o�b"NOR" "BMAG" �s�u�ɼ� "NOR"�x\n";
    for(i=0; i<sizeof(ob); i++)
    {
        if( this_player() && !ob[i]->visible(this_player()) )
            continue;
        
        // ignore the user who want to hide ip
        if( member_array(ob[i]->query_id(), hide_ip) != -1 ) 
                continue;
        
        msg += sprintf("�x%12s%-12s %|31s %|4d %|10s�x\n",
                       ob[i]->query("name"),
                       "("+ ob[i]->query("id") + ")",
//                        (member_array(ob[i]->query_id(), hide_ip) != -1 ) ? "127.0.0.1" : query_ip_name(ob[i]),
                        query_ip_name2(ob[i]),

                       (int)query_idle(ob[i])/60,
                       ob[i]->link() ? age_string(ob[i]->link()->query("time_aged")) : "n/a"
                      );
    }
    msg += "���w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��";
    return msg;
}

string finger_user(string name)
{
    object ob, body;
    string msg, mud;
    int invis, age, wiz_mode = 0;

    ob = acquire_login_ob(name);
    if( !ob )
        return "�S���o��ϥΪ̡C\n";
    body = find_player(name);

    if( this_player(1) && (wizardp(this_player(1)) || body==this_player(1)) )
        wiz_mode = 1;

    age = ob->query("time_aged");
    invis = ob->query("invis") && (!body || !this_player() || wiz_level(body) > wiz_level(this_player()));

    msg  = "�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    msg += sprintf("�x"BBLU"�m    �W�G%-24s  �v�����šG%-12s"NOR"�x\n",
                   ob->query("name") + "(" + capitalize(ob->query("id")) + ")",
                   wizhood(name) );
    msg += "�x                                                          �x\n";
    msg += sprintf("�x�q�l�l��G%-48s"NOR"�x\n", wiz_mode ? ob->query("email") : "<���K>" );
    if( wiz_mode )
    {
        if( member_array(ob->query("id"), hide_ip) != -1 )
            msg += sprintf("�x�W���s�u�G%-48s"NOR"�x\n", "127.0.0.1" + " (" + CHINESE_D->chinese_date((int)ob->query("last_on")) + ")");
        else
            msg += sprintf("�x�W���s�u�G%-48s"NOR"�x\n", ob->query("last_from") + " (" + CHINESE_D->chinese_date((int)ob->query("last_on")) + ")" );
    }
    else
        msg += sprintf("�x�W���s�u�G%-48s"NOR"�x\n", "<���K>" + " (" + CHINESE_D->chinese_date((int)ob->query("last_on")) + ")");
    msg += sprintf("�x�ɼ��`�X�G%-48s"NOR"�x\n", chinese_period(age) );
    msg += "�x                                                          �x\n";
    if( objectp(body) )
    {
        if( interactive(body) )
        {
            if( wiz_mode )
            {
                if( member_array(ob->query("id"), hide_ip) != -1 )
                      msg += sprintf("�x�s�u�עޡG"HIG"<�s�u��>"NOR" %-39s�x\n", "You.Never.Know.It");
                else
                      msg += sprintf("�x�s�u�עޡG"HIG"<�s�u��>"NOR" %-39s�x\n", query_ip_name2(body));
            }
            else
                msg += sprintf("�x�s�u�עޡG"HIG"<�s�u��>"NOR" %-39s�x\n", "<���K>");
            msg += sprintf("�x�s�u�ɼơG%-48s"NOR"�x\n", chinese_period(time() - ob->query_temp("login_time")) );
        }
        else
            msg += sprintf("�x�s�u�עޡG"HIR"<�_�u��>"NOR" %-39s�x\n", "");
    }
    msg += "�r�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�r\n";

    if( ob->query("profile") )
        msg += ob->query("profile");

    msg += "�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w\n";

    if( !ob->body() )
        destruct(ob);

    return msg;
}

object acquire_login_ob(string id)
{
    object ob;

    if( origin()==ORIGIN_CALL_OTHER )
    {
        if( geteuid(previous_object())!=ROOT_UID
                &&  base_name(previous_object())!=MAILBOX_OB )
            return 0;
    }

    if( ob = find_player(id) )
    {
        // Check if the player is linkdead
        if( ob->link() )
            return ob->link();
    }

    ob = new(LOGIN_OB);
    ob->set
    ("id", id);
    return ob->restore() ? ob : 0;
}

