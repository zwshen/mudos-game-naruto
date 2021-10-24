/*  logind.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

// #pragma save_binary

#include <ansi.h>
#include <command.h>
#include <login.h>

inherit F_CLEAN_UP;
inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;

/*
string *user_race = ({
    "human",
});
*/

string *banned_name = ({
    "�A", "�p", "��", "�L", "�o", "�e", "��",
});

string *banned_rude_name = ({
    "�F", "��", "�Q", "��", "�x", "�Y", "��", "��", "��",
});

string *banned_ip = ({
// �Ȯɨ���, �O�����d��, �Y�O���p���ۦP�A�Ҽ{�ä[ban�� -dragoon
//	"163.19.7.%*s", 	// mutli, dragoon
//	"140.96.148.%*s",	// mutli, dragoon
});

string *banned_hostname = ({
//	"%*s.Dorm2.nsysu.edu.tw",	// mutli, rude words, dragoon
});

#ifdef ENABLE_ANTISPAM
mapping spammer_player = ([]);
mapping spammer_ip = ([]);
string *penalty_attr = ({
	"str", "dex", "int", "con"
});
#endif	/* ENABLE_ANTISPAM */

private void get_id(string arg, object ob);
private void confirm_id(string yn, object ob);
private void get_email(string email, object ob);
object make_body(object ob);
private void init_new_body(object link, object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string arg);
private int list_user_race(object link);
private void increment_visitor_count();
private int check_ip(object link);

private void create() 
{
    seteuid(getuid());
    set("channel_id", "�s�u���F");
}

private void reset()
{
    object room, ob;

#if 0
    /* �M�Ŧb void �̪��_�u���a�C */
    room = find_object(VOID_OB);
    seteuid(getuid());
    if( objectp(room) )
	foreach(ob in all_inventory(room)) {
#ifdef	SAVE_USER
	    if( userp(ob) ) ob->save();
#endif
	    destruct(ob);
	}
#endif

    /* �O���u�W�ϥΪ̤H�� */
    log_file("USRGRAPH", sprintf("[%s] %d users\n",
	ctime(time()), sizeof(users())));

#ifdef ENABLE_ANTISPAM
    spammer_player = ([]);
    spammer_ip = ([]);
#endif
}

void logon(object ob)
{
    object *usr;
    int i, wiz_cnt, ppl_cnt, login_cnt;

#ifdef ENABLE_ANTISPAM
    if( spammer_ip[query_ip_number(ob)] >= 10 ) {
        write("�q�z�s�u���D���гy���H���Ӧh�F�M�z���D���N�Q�ڵ����Ӥ@�q�ɶ��C\n");
        destruct(ob);
        return;
    }
#endif

    seteuid(getuid());
    
    if( random(2) == 1 ) efun::write(read_file(WELCOME_N) + "");
    else efun::write(read_file(WELCOME_H) + "");
//    UPTIME_CMD->main();
    VISITOR_CMD->main();

    usr = users();
    wiz_cnt = 0;
    ppl_cnt = 0;
    login_cnt = 0;
    // invis wizard count in ppl in stead of wiz, by grain (03/25/1998)
    for(i=0; i<sizeof(usr); i++) {
        if( !environment(usr[i]) ) login_cnt++;
        else if( wizardp(usr[i]) ) {
            if( !usr[i]->link()->query("invis") ) wiz_cnt++;
        }
        else ppl_cnt++;
    }
    printf("�y���v�Ԫ̤H�w�g����F" + CHINESE_D->chinese_period(uptime()) + "�C\n");
    printf("�ثe�@�� %d ��Ův�B%d �쪱�a�b�u�W�M�H�� %d ��ϥΪ̹��ճs�u���C\n\n",
        wiz_cnt, ppl_cnt, login_cnt );

    write("�z���ϥΪ̥N���G");
    input_to( "get_id", ob );
}

private void get_id(string arg, object ob)
{
    object ppl;

    arg = lower_case(arg);
    if( !check_legal_id(arg)) {
	write("�z���ϥΪ̥N���G");
	input_to("get_id", ob);
	return;
    }

    /* �]�w�s�u�����v������ */
    seteuid(arg);
    export_uid(ob);
    seteuid(getuid());
    ob->set("id", arg);

#ifdef MAX_USERS
    if( wizhood(arg)=="(player)" && sizeof(users()) >= MAX_USERS )
    {
	ppl = find_body(arg);
	// Only allow reconnect an interactive player when MAX_USERS exceeded.
	if( !ppl || !interactive(ppl) ) {
	    write("�藍�_�M" + MUD_NAME + "���ϥΪ̤w�g�Ӧh�F�M�Ыݷ|�A�ӡC\n");
	    destruct(ob);
	    return;
	}
    }
#endif

#ifdef ENABLE_BAN_SITE
    // Rework by Annihilator (11/10/1999), support IP address and hostname
    if( wizhood(arg)=="(player)" )
    {
	string ip, pattern;

	ip = query_ip_number(ob);
	foreach(pattern in banned_ip)
	    if( ip==pattern || sscanf(ip, pattern) ) {
		write("�藍�_�A�z���s�u��m�ثe�������ϥΪ̵n�J�C\n");
		destruct(ob);
		return;
	    }
	ip = query_ip_name(ob);
	foreach(pattern in banned_hostname)
	    if( ip==pattern || sscanf(ip, pattern) ) {
		write("�藍�_�A�z���s�u��m�ثe�������ϥΪ̵n�J�C\n");
		destruct(ob);
		return;
	    }
    }
#endif	/* ENABLE_BAN_SITE */

#ifdef WIZ_LOCK_LEVEL
    if( (int)wiz_level(arg) < (int)wiz_lock_level ) {
        write("�藍�_�M" + MUD_NAME + "�ثe����Ův���� " + WIZ_LOCK_LEVEL
            + " �H�W���H�~��s�u�C\n");
        destruct(ob);
        return;
    }
#endif

    if( arg=="guest" ) {
        // If guest, let them create the character.
        get_email( "guest@" + query_ip_name(ob), ob);
        return;
    }

    if( file_size(login_data(arg)) != -1 ) {
        if( ob->restore() ) {
            write("�п�J�K�X�R");
            input_to("get_passwd", 1, ob);
            return;
        }
        write("�藍�_�M�z���H���x�s�ץX�F�@�ǰ��D�M�ЧQ�� guest �H���q���Ův�B�z�C\n");
        destruct(ob);
        return;
    }

    write("�ϥ� " + (string)ob->query("id") + " �o�ӦW�r�N�|�гy�@�ӷs���H���M�z�T�w��(y/n)�S");
    input_to("confirm_id", ob);
}

private void get_passwd(string pass, object ob)
{
    string my_pass;
    object user;

    write("\n");

    if( !check_ip(ob) ) {
	write("�藍�_�A�z���s�u��m�����T�C\n");
	destruct(ob);
	return;
    }

    my_pass = ob->query("password");
    if( crypt(pass, my_pass) != my_pass ) {
        write("�K�X���~�I\n");
        destruct(ob);
        return;
    }

    user = find_body(ob->query("id"));
    if (user) {
	/* �_�u���ϥΪ̭��s�s�u */
        if( !user->link() ) {
            reconnect(ob, user);
            return;
        }
        write("�z�n�N�t�@�ӳs�u�����ۦP�H�����X�h�M���ӥN���ܡS(y/n)");
        input_to("confirm_relogin", ob, user);
        return;
    }

    user = make_body(ob);
    if( ! user ) {
	/* �p�G�S����k�s�y�ϥΪ̪���A�������_�s�u */
	destruct(ob);
	return;
    }

    if( user->restore() )
    {
	log_file( "USAGE", sprintf("[%s] %s login from %s\n",
	    ctime(time()), (string)user->query("id"), query_ip_name(ob) ) );
/*
	if( wizhood(ob)=="(admin)") {
	    if( (query_ip_name(ob) != "localhost") && (query_ip_number(ob) != "127.0.0.1") ) {
			write("�w���ˬd����....�۰ʵn�X�C\n");
			destruct(user);
			destruct(ob);
			return;
	    }
	    write("�w���ˬd�q�L�C\n");
	}
*/	enter_world(ob, user);
	return;
    } else {
	if( file_size(user->query_save_file())==-1 ) {
	    write(@NOTICE
�t�Χ䤣��z���H����ơA�i�઺��]�]�A�z�b�гy�H���ΤH���b��L��@��
�_�u�A�Ϊ̦]���H�ϳW�w�z���H����ƳQ�R���F�C�p�G�z�T�w�o�ӤH���èS��
�W�z�o�Ǳ��p�A�Х� guest �b�����u�W�Ův�d�ߡC

NOTICE
	    );
	    destruct(user);
	    write(HIY "�z�n���s�гy�o�ӤH���ܡH(y/n) " NOR);
	    input_to("confirm_reincarnate", ob);
	} else {
	    write(@NOTICE
�t�Υثe�L�kŪ���z���H����ơA�i�઺��]�]�A�t�Υ��b�Ƥ��ξ�z�ϥΪ�
��ơA�еy�ԦA�աC
NOTICE
	    );
	    destruct(user);
	    destruct(ob);
	}
    }
}

private void confirm_reincarnate(string yn, object ob)
{
    if( yn=="" ) {
        write(HIY "�z�n���s�гy�o�ӤH���ܡH(y/n) " NOR);
        input_to("confirm_reincarnate", ob);
        return;
    }

    if( yn[0]!='y' && yn[0]!='Y' ) {
        write("�n�a�M�w��U���A�ӡC\n");
        destruct(ob);
        return;
    }

    if( !list_user_race(ob) ) {
	/*  �~�O�����A�L�k��L��@�����p�C */
#ifdef	SAVE_USER
	rm(ob->query_save_file());
#endif
        destruct(ob);
        return;
    }

    input_to("get_race", ob);
}

private void confirm_relogin(string yn, object ob, object user)
{
    object old_link;

    if( yn=="" ) {
        write("�z�n�N�t�@�ӳs�u�����ۦP�H�����X�h�M���ӥN���ܡS(y/n)");
        input_to("confirm_relogin", ob, user);
        return;
    }       

    if( yn[0]!='y' && yn[0]!='Y' ) {
        write("�n�a�M�w��U���A�ӡC\n");
        destruct(ob);
        return;
    } else {
        tell_object(user, "���H�q�O�B( " + query_ip_number(ob)
            + " )�s�u���N�z�ұ���H���C\n");
        log_file( "USAGE", sprintf("[%s] %12s replaced @ %s\n",
            ctime(time()),
            (string)user->query("id"),
            query_ip_name(ob),  ) );
    }

    // Kick out tho old player.
    old_link = user->link();
    if( old_link ) {
	seteuid(getuid());
	if( interactive(user) ) exec(old_link, user);
        destruct(old_link);
    }

    reconnect(ob, user);    
}

private void confirm_id(string yn, object ob)
{
    if( yn=="" ) {
        write("�ϥγo�ӦW�r�N�|�гy�@�ӷs���H���M�z�T�w��(y/n)�S");
        input_to("confirm_id", ob);
        return;
    }       

    if( yn[0]!='y' && yn[0]!='Y' ) {
        write("�n�a�M����Э��s��J�z���^��W�r�R");
        input_to("get_id", ob);
        return;
    }

#ifdef ENABLE_ANTISPAM
    if( spammer_player[ob->query("id")] ) spammer_player[ob->query("id")]++;
    else spammer_player[ob->query("id")] = 1;
    if( spammer_ip[query_ip_number(ob)] ) spammer_ip[query_ip_number(ob)]++;
    else spammer_ip[query_ip_number(ob)] = 1;
#endif
    write("�г]�w�z���K�X�R");
    input_to("new_password", 1, ob);
}

private void new_password(string pass, object ob)
{
    write("\n");
    if( strlen(pass)<5 ) {
        write("�K�X�����צܤ֭n���Ӧr���M�Э��]�z���K�X�R");
        input_to("new_password", 1, ob);
        return;
    }
#ifdef	ENABLE_MD5_PASSWORD
    ob->set("password", crypt(pass, sprintf("$1$%d", random(99999999))));
#else
    ob->set("password", crypt(pass, 0) );
#endif
    write("�ЦA��J�@���z���K�X�M�H�T�{�z�S�O���R");
    input_to("confirm_password", 1, ob);
}

private void
confirm_password(string pass, object ob)
{
    string old_pass;

    write("\n");
    old_pass = ob->query("password");
    if( crypt(pass, old_pass)!=old_pass ) {
        write("�z�⦸��J���K�X�ä��@�ˡM�Э��s�]�w�@���K�X�R");
        input_to("new_password", 1, ob);
        return;
    }

    write(@TEXT
���F�קK�z���H���D�H�s�ΡANaruto �N�ĥ� email �{�Ҥ覡�O�@
�H���Ҧ��v�A�ҥH�бz��J�@�ӥi�ѱ����{�ҥιq�l�l�󪺦a�}�C
�o�ӹq�l�l��a�}���F�Ův�H�~�A���|�Q��L�ϥΪ̬ݨ�C
TEXT
    );
    write("�z���q�l�l��a�}�G");
    input_to("get_email",  ob);
}

private void get_email(string email, object ob)
{
    int c, delim=0, err=0;

    if( strlen(email) > 64 ) {
		write("�q�l�l��a�}�̦h�i�H�� 64 �Ӧr���C\n");
		write("�z���q�l�l��a�}�G");
		input_to("get_email",  ob);
		return;
    }

    foreach(c in email) {
	if( c=='@' && !delim ) { delim = 1; continue; }
	if( strsrch("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.", c) < 0 )
	    { err = 1; break; }
    }
    if( !delim || err ) {
		write("�z���q�l�l��榡���~�A�п�J���T���q�l�l��a�}�C\n");
		write("�z���q�l�l��a�}�G");
		input_to("get_email",  ob);
		return;
    }

    ob->set("email", email);

//  If ONE_GUEST is defined in /include/login.h, only permit one guest login.
#ifdef ONE_GUEST
    if ((string)ob->query("id") == "guest") {
        write("��p, �u�W�w�g���@�� Guest �F.\n");
        destruct(ob);
        return;            }
#endif /* ONE_GUEST */

    // Complete non-body-specific initialization of new user here.
//    ob->set("karma", 20);
//    list_user_race(ob);
//    input_to("get_race", ob);

    write("�z�n��t�k��(m)������Τk��(f)������S");
    input_to("get_gender", ob, "human");
}

/*
private void get_race(string race, object ob)
{
    int kar;
    string choice;
    if( sscanf(race, "? %s", race) ) {
        write( read_file(HELP_DIR + "help/" + race) );
        // add by ueiren ... 
        // list_user_race(ob);
        input_to("get_race", ob);
        return;
    }
    if( member_array(race, user_race)==-1 ) {
        write("�S���o�غرڡM�бz���s��ܡR");
        input_to("get_race", ob);
        return;
    }

    write("�z�n��t�k��(m)������Τk��(f)������S");
    input_to("get_gender", ob, race);
}
*/

private void get_gender(string gender, object ob, string race)
{
    object body;
    string body_file;

    if( gender=="" ) {
        write("�z�n��t�k��(m)������Τk��(f)������S");
        input_to("get_gender", ob, race);           
        return;
    }

    if( gender[0]=='m' || gender[0]=='M' )      gender = "male";
    else if( gender[0]=='f' || gender[0]=='F' )     gender = "female";
    else {
        write("�藍�_�M�z�u���ܨk��(m)�Τk��(f)������R");
        input_to("get_gender", ob, race);
        return;
    }

    if( !stringp(body_file = RACE_D(race)->query("default_body")) ) body_file = USER_OB;

    ob->set("body", body_file);
    if( !(body = make_body(ob)) ) {
        destruct(ob);
        return;
    }

    body->set("gender", gender);
    body->set_race(race);
    init_new_body(ob, body);

    // Remember it so we can dest it if we go linkdead before finishing
    // chraracter creation.
    ob->set_temp("temp_body", body);

    write("�z������W�r�R");
    input_to("get_name", ob, body);
}

private void get_name(string arg, object ob, object user)
{
    if( !check_legal_name(arg) ) {
        write("�z������W�r�R");
        input_to("get_name", ob, user);
        return;
    }

    ob->set("name", arg);
    user->set("name", arg);
    if( !ob->query("creation_time") ) {
        log_file( "USAGE", sprintf("[%s] %12s created  @ %s\n",
            ctime(time()),
            user->query("id"),
            query_ip_name(ob), ) );
            ob->set("creation_time", time());
            // default open chat and rumor channel -- by dragoon
            ob->set("channels", ({"chat","rumor"}));
    }
    
    // �s���� lv1 �i��o�@�ǯ�O�I��
    user->add_point("learn", 100);
    user->add_point("score", 50);
    user->add_point("attribute", 2);
    user->add_point("skill", 2);
    
    user->init_attribute((["str": 20, "con": 20, "dex": 20, "int": 20, ]));
    user->init_statistic((["ap": 80, "hp": 80, "mp": 80, ]));

    enter_world(ob, user);
}

object make_body(object link_ob)
{
    string err;
    object user;
    int n;

    seteuid(getuid());
    err = catch(user = new(USER_OB));
    if(err || !user) {
        write("�{�b�i�঳�Ův���b�ק�ϥΪ̪��󪺵{���M�еy�ԦA�աC\n");
        return 0;
    }

    /* �]�w�ϥΪ̪��v�� */
    seteuid(getuid(link_ob));
    export_uid(user);
    seteuid(getuid());

    user->set("id", link_ob->query("id"));
    user->set_name( link_ob->query("name"), link_ob->query("id") );

    return user;
}

private int check_ip(object link)
{
    string okip, cur_ip, cur_ip_num, ip_part, num_part, be_checked;
    int len, ed;

    cur_ip = query_ip_name(link);
    cur_ip_num = query_ip_number(link);

    okip = link->query("okip");
    if( !arrayp(okip) || !sizeof(okip) ) return 1;

    foreach(string ip in explode(okip, ":") - ({ "" })) {
		if (sscanf(ip, "%s*", be_checked) && be_checked!="") {
		    len = strlen(be_checked);
		    ip_part = cur_ip[0..len-1];
	    	num_part = cur_ip_num[0..len-1];
		} else if (sscanf(ip, "*%s", be_checked) && be_checked!="") {
		    len = strlen(be_checked);
		    ed = strlen(cur_ip);
	    	ip_part = cur_ip[ed-len..<1];
		    num_part = cur_ip_num[ed-len..<1];
		} else {
		    be_checked = ip;
		    ip_part = cur_ip;
	    	num_part = cur_ip_num;
		}
       
		if (lower_case(be_checked) == lower_case(ip_part) || lower_case(be_checked) == lower_case(num_part)) {
	    	write(HIW "�ˬd�q�L�C\n" NOR);
	    	return 1;
		}
    }

    return 0;
}

private void init_new_body(object link, object user)
{
#ifdef ENABLE_ANTISPAM
    int penalty;
    string a;
#endif

    user->set("birthday", time() );
    user->set_class("commoner");
    user->set_level(1);

    CHAR_D->setup_char(user);
}

varargs void enter_world(object ob, object user, int silent)
{
    object room;
//    string startroom, err, mot;
    string err, mot;

    /* �N�ϥΪ̱q�s�u���� exec ��ϥΪ̪���W */
    user->set_link(ob);
    ob->set_body(user);
    exec(user, ob);

    if( !silent ) write("�ثe�v���R" + wizhood(user) + "\n");

    user->setup();
    increment_visitor_count();

#ifdef SAVE_USER
    /* �b�o���x�s�A���s�гy���H���Q�s�U�� */
    user->save();
#endif

    if( silent ) return;

    if( !mot = read_file(MOTD) ) mot = "";
    user->start_more(mot);
    // cat(MOTD);

    // IDENT_D->query_userid((string)user->query("id"));

    /* �H�w������k���J�ϥΪ̵n�J���ж� */
   	err = catch(room=load_object(user->query("startroom")));
   	if( !room || !room->is_area() ||
   		!area_move(room, user, user->query("area_info/x_axis"), user->query("area_info/y_axis") ) )
    {
    	err = catch(room = load_object(user->query("recoverroom")));
    	if( !room || !user->move(room) ) {
	        if( !room ) err = catch(room = load_object(START_ROOM));
	        if( !room ) err = catch(room = load_object(VOID_OB));
  		
    	    if( !room || !user->move(room) ) {
        	    write("�藍�_�A�ثe�t�Υ��b��פ@�ǵn�J�a�I���{���A�еy�ԦA�աC\n");
			    destruct(ob);
			    destruct(user);
	 	    }
	 	}
  	}

    /* �ˬd�ϥΪ̬O�_����Ū���H�� */
    if( ob->query("new_mail") ) {
		write( HIW "\n���z���H�I�Ш��毸�Ӥ@�� ...\n\n" NOR);
		ob->delete("new_mail");
    }
 
    // if detect mark: pker, set the time mark -dragoon
    if( user->query("pker") ) {
		user->set("last_pk_time", time());
		user->delete("pker");
    }

    /* �ŧi�ϥΪ̵n�J������ */
//    if( !wizardp(user) && !user->query("invis") ) {
		message_vision("$N�s�u�i�J�o�ӥ@�ɡC\n", user);
		CHANNEL_D->do_channel( this_object(), "sys",
			sprintf("%s(%s)��%s�s�u�i�J�C",
			user->name(1),
			user->query("id"),
			query_ip_name(user)) );
//    }
}

varargs void reconnect(object ob, object user, int silent)
{
    /* �N�ϥΪ̱q�s�u���� exec ��ϥΪ̪���W */
    user->set_link(ob);
    ob->set_body(user);
    exec(user, ob);

    user->reconnect();
    // IDENT_D->query_userid((string)user->query("id"));   

    if( silent ) return;

    // if detect pking, reset time mark to now -dragoon
    if( time() - (int)user->query("last_pk_time") < 60 * 60 )
	user->set("last_pk_time", time());

    /* �ŧi�ϥΪ̭��s�s�u������ */
    if( !wizardp(user) && !user->query("invis") ) {
		message_vision("$N���s�s�u�^��o�ӥ@�ɡC\n", user);
		CHANNEL_D->do_channel( this_object(), "sys",
			sprintf("%s(%s)��%s���s�s�u�i�J�C",
			user->name(1),
			user->query("id"),
			query_ip_name(user))
		);
    }
}

void net_dead(object ob)
{
    CHANNEL_D->do_channel( this_object(), "sys", sprintf("%s(%s)�_�u�F�C", ob->name(1), ob->query("id")));
    ob->move("/obj/void");
}

int check_legal_id(string id)
{
    int i;

    i = strlen(id);
    if( (strlen(id) < 3) || (strlen(id) > 10 ) ) {
        write("�藍�_�M�z���^��W�r�����O 3 �� 10 �ӭ^��r���C\n");
        return 0;
    }
    while(i--)
        if( id[i]<'a' || id[i]>'z' ) {
            write("�藍�_�M�z���^��W�r�u��έ^��r���C\n");
            return 0;
        }

    return 1;
}

int check_legal_name(string name)
{
    int i;
    string bname;

    i = strlen(name);

    if( (strlen(name) < 2) || (strlen(name) > 12 ) ) {
        write("�藍�_�A�z������W�r�����O 1 �� 6 �Ӥ���r�C\n");
        return 0;
    }
    while(i--) {
        if( name[i]<=' ' ) {
            write("�藍�_�M�z������W�r����α���r���C\n");
            return 0;
        }
        if( i%2==0 && !is_chinese(name[i..<0]) ) {
            write("�藍�_�M�бz�Ρu����v���W�r�C\n");
            return 0;
        }
        if( name[i..i+1]=="�@" ) {
            write("�藍�_�M�Ф��n�Ϊťզr�����W�r�C\n");
            return 0;
        }
    }
    if( member_array(name, banned_name)!=-1 ) {
        write("�藍�_�M�o�ئW�r�|�y����L�H���x�Z�C\n");
        return 0;
    }
    foreach(bname in banned_rude_name)
        if( strsrch( name, bname )>-1 ) {
            write("�藍�_, �o�ئW�l�|�ް_�����n���~�|�C\n");
            return 0;
        }
    return 1;
}

object find_body(string name)
{
    object ob, *body;

    if( objectp(ob = find_player(name)) ) return ob;
    foreach(ob in children(USER_OB))
        if( clonep(ob)
        &&  userp(ob)
        &&  ob->is_character()
        &&  getuid(ob) == name )
            return ob;

    return 0;
}

int set_wizlock(int level)
{
    if( wiz_level(this_player(1)) <= level ) return 0;
    if( geteuid(previous_object()) != ROOT_UID ) return 0;

    wiz_lock_level = level;
    return 1;
}

/*
int list_user_race(object link)
{
    string msg, race;

    msg = "";
    foreach(race in user_race) {
		msg += sprintf("%-25s\n",
			to_chinese(race) + "(" + race + ")" );
    }

    msg += "�z�����(�� '? <�رڦW>' �i�d�\\����)�R";

    write(msg);
    return 1;
}
*/

#define VISITOR_COUNTER_FILE	"/adm/etc/visitor.cnt"

private void increment_visitor_count()
{
    int t, cnt;
    string s = read_file(VISITOR_COUNTER_FILE);

    if( !s ) 
        s = sprintf("%d 1", time());
    else {
        sscanf(s, "%d %d", t, cnt);
        if( ! t ) { t = time(); cnt = 0; }
        s = sprintf("%d %d", t, cnt+1);
    }
    write_file(VISITOR_COUNTER_FILE, s, 1);
}
