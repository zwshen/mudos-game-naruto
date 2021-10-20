/* npc.c
*/

#include <ansi.h>
#include <dbase.h>
#include <localtime.h>
#include <command.h>
#include <skill.h>
#include <type.h>

inherit CHARACTER;
inherit F_CLEAN_UP;     // Only to clean up master copy of NPCs.

nosave mixed next_chat;
nosave int last_scheduled_time_tag = 0;

int chat();

protected void heart_beat()
{
    ::heart_beat();

    if( !this_object() || !living(this_object()) ) return;
    if( !is_busy() ) chat();
}

private void gain_bonus(object killer)
{
    int point, kLV;
    mapping bounty;

    // �n���@���аO
    if( query("vendetta_mark") )
        killer->add("vendetta/" + query("vendetta_mark"), 1);
    
    // �p�G�����O�H�����ܥ[���~ 1
    if( query("humanoid") ) killer->gain_score("kills", 1);
    
    // ��o�g�� (�p�Gvictim���]�wbounty����)
    if( mapp(bounty = query("bounty")) ) {
        string score;
        int amount;
        foreach(score, amount in bounty) {
            killer->gain_score(score, amount);
            tell_object(killer, "�A��o�F " + HIY+amount+NOR + " �I��" + to_chinese(score) + "�C\n");
        }
    }

    // ����
    QUEST_D->doKilled(this_object(), killer);

    point = query_level();

    // �W�[���Ůt�Z�W�[��־��I���P�_
    kLV = killer->query_level();

    // ���t�� 10 �ŤU���A�W�L�C�Ŷ}�l��־��I 0.1
    // �W���O�W�L 5 �ŴN 2 ���A��L�C�ŦU�[ 0.2
    if( kLV >= point + 20 ) point = 1;
    else if( kLV > point + 10 ) point = point * (20 - (kLV - point))/10;
    else if( kLV + 5 < point ) point *= 2;
    else if( kLV <= point ) point += point * (point - kLV)/5;

    // �ܤ֤]���@�I���I
    if( point <= 1 ) point = 1;

    // �W�[���I, �������I���P�_
    if( mapp(killer->query_condition("double-learn")) ) point *= 2;
    killer->add_point("learn", point);
    tell_object(killer, "�A��o�F " + HIY+point+NOR + " �I���ǲ��I�ơC\n");
    
    // �}��
    if( query("camp") ) {
        int value = query_level() / 10;
        string c = query("camp");
        if( value <= 0 ) value = 1;
        value = -value;
        if( !killer->hasCamp(c) ) killer->addCamp(c);
        killer->updateCamp(c, value);
    }
}

void die()
{
    object killer, *team;

    if( !objectp(killer = last_damage_giver()) || killer == this_object() ) {
        ::die();
        return;
    }

    // ���H�̬Onpc�B�O�Y�H�Ҿ֦��A�����H�̧Y�O�Y�H�A�p�Q�v�����άO�Ԥ������A�����H�̬O��D�H
    if( !userp(killer) && objectp(killer->query_owner()) )
        killer = killer->query_owner();

    if( !environment(killer) ) {
        ::die();
        return;
    }

    // �������
    team = killer->query_team();
    if( team ) {
        object ob;
        foreach(ob in team) {
            if( !ob->is_fighting(this_object()) ) continue;
            
            if( environment(killer)->is_area() )  {
                if( !area_environment(killer, ob) ) continue;
            } else if( environment(killer) != environment(ob) ) continue;
            
            if( (killer->query_level() - ob->query_level()) > 5 ||
                (killer->query_level() - ob->query_level()) < -5 ) continue;
            
            gain_bonus(ob);
        }
    } else gain_bonus(killer);

    ::die();
}

mixed carry_object(string file)
{
    object ob;

    // Don't let master copy clone equips
    if( !clonep() ) return VOID_OB;

    if( !objectp(ob = new(file)) ) return 0;

    // Support of uniqueness.
    if( ob->violate_unique() ) ob = ob->create_replica();
        if( !ob ) return VOID_OB;

    ob->varify_template(this_object());
    ob->move(this_object());

    return ob;
}

object carry_money(string type, int amount)
{
    object ob;

    ob = carry_object("/obj/money/" + type);
    if( !ob ) return 0;
    ob->set_amount(amount);
}

int is_chatting() { return functionp(next_chat) != 0; }

int is_npc() { return 1; }

void do_chat(mixed c) { next_chat = c; }

mixed eval_chat(mixed chat)
{
    mixed ret;

    chat = evaluate(chat);
    switch(typeof(chat)) {
        case STRING:
            say(CYN + chat + NOR); return 0;
        case ARRAY:
            if( !sizeof(chat) ) return 0;
            chat[0] =  eval_chat(chat[0]);
            return chat - ({ 0 });
        case FUNCTION: return chat;
        default: return 0;
    }
}

int chat()
{
    string *msg;
    mixed ret;
    int chance, rnd;

    if( !environment() ) return 0;

    // Evaluate programmed chat first.
    if( next_chat ) {
        next_chat = eval_chat(next_chat);
        return 1;
    }

    // Else, do random chat if any.
    if( ! (chance = (int)query(is_fighting()? "chat_chance_combat": "chat_chance")) )
        return 0;

    if( arrayp(msg = query(is_fighting()? "chat_msg_combat": "chat_msg")) && sizeof(msg) ) {
        if( random(100) > chance ) return 0;

        rnd = random(sizeof(msg));

        if( stringp(msg[rnd]) ) say(CYN + msg[rnd] + NOR);
        else if( functionp(msg[rnd]) )

        evaluate(msg[rnd]);
        return 1;
    }
}

int random_move()
{
    mapping exits;
    string *dirs;

    if( environment()->is_area() ) {
        if( !(dirs = environment()->query_exits(this_object()->query("area_info/x_axis"), this_object()->query("area_info/y_axis")) ) ) return 0;
    } else {
        if( !mapp(exits = environment()->query("exits")) ) return 0;
            dirs = keys(exits);
    }
    GO_CMD->main(this_object(), dirs[random(sizeof(dirs))]);
}

void perform_skill(string skill, string action)
{
    if( stringp(skill) && stringp(action) )
        SKILL_D(skill)->perform_action(this_object(), action, query_opponent());
}

// This overrides default activate_guard() in F_ATTACK.
void activate_guard(object target)
{
    kill_ob(target);
}

void do_heal()
{
    heal_stat("ap", 9999);
    heal_stat("hp", 9999);
    heal_stat("mp", 9999);
}

// ���w�q����������ơA�H�`�٨t�θ귽
varargs void improve_skill(string skill, int amount) {}

// ���w�q����������ơA�H�`�٨t�θ귽
void gain_score(string term, int amount) {}

void setup()
{
    string msg;
    int lv;

    lv = this_object()->query_level();
    msg = this_object()->query("classify");

    // �S��Ǫ��t�~�A�P�_ hp, ap, mp ����������
    switch( msg ) {
        case "boss":  // ���ũǪ�
            init_statistic( ([ "ap":lv*50000-random(lv*1000), "hp":lv*50000-random(lv*1000), "mp":lv*50000-random(lv*1000) ]) );
            break;
        case "elite": // ��^�Ǫ�
            init_statistic( ([ "ap":lv*6000-random(lv*1000), "hp":lv*6000-random(lv*1000), "mp":lv*6000-random(lv*1000) ]) );
            break;
        case "strengthen": // �j�ƩǪ�
            init_statistic( ([ "ap":lv*500+random(lv*500), "hp":lv*500+random(lv*500), "mp":lv*500+random(lv*500) ]) );
            break;
    }
    // �w�]�� NPC ��O, �̵��ŨӨM�w
    switch( lv ) {
        case 0..5:
            init_attribute( ([ "str":10+lv/2, "con":10+lv/2, "int":10+lv/2, "dex":10+lv/2 ]) );
            set_skills( ([ "combat":5+lv, "dodge":5+lv, "parry":5+lv, "savage hit":5+lv, "heavy hit":5+lv, "continual hit":5+lv ]) );
            init_statistic( ([ "ap":50+lv*5, "hp":50+lv*5, "mp":50+lv*5 ]) );
            set("perm_apply", ([ "armor":-(15+lv*2+random(lv)) ]) );
            break;

        case 6..10:
            init_attribute( ([ "str":15+lv/2, "con":15+lv/2, "int":15+lv/2, "dex":15+lv/2 ]) );
            set_skills( ([ "combat":20+lv*2, "dodge":20+lv*2, "parry":20+lv*2, "savage hit":20+lv*2, "heavy hit":20+lv*2, "continual hit":20+lv*2 ]) );
            init_statistic( ([ "ap":100+lv*10, "hp":100+lv*10, "mp":100+lv*10 ]) );
            set("perm_apply", ([ "attack":lv+random(lv), "armor":lv+random(lv) ]) );
            break;

        case 11..20:
            init_attribute( ([ "str":20+lv/2, "con":20+lv/2, "int":20+lv/2, "dex":20+lv/2 ]) );
            set_skills( ([ "combat":40+lv*2, "dodge":40+lv*2, "parry":40+lv*2, "savage hit":40+lv*2, "heavy hit":40+lv*2, "continual hit":40+lv*2 ]) );
            init_statistic( ([ "ap":300+lv*10, "hp":300+lv*10, "mp":300+lv*10 ]) );
            set("perm_apply", ([ "attack":lv*2+random(lv), "armor":lv*2+random(lv) ]) );
            break;

        case 21..30:
            init_attribute( ([ "str":25+lv/2, "con":25+lv/2, "int":25+lv/2, "dex":25+lv/2 ]) );
            set_skills( ([ "combat":50+lv*2, "dodge":50+lv*2, "parry":50+lv*2, "savage hit":50+lv*2, "heavy hit":50+lv*2, "continual hit":50+lv*2]) );
            init_statistic( ([ "ap":500+lv*20, "hp":500+lv*20, "mp":500+lv*20 ]) );
            set("perm_apply", ([ "attack":lv*2+random(lv), "armor":lv*2+random(lv), "exact":lv/5+random(lv)/2, "evade":lv/5+random(lv)/2, "intimidate":lv/6+random(lv)/2, "wittiness":lv/6+random(lv)/2 ]) );
            break;

        case 31..40:
            init_attribute( ([ "str":30+lv/2, "con":30+lv/2, "int":30+lv/2, "dex":30+lv/2 ]) );
            set_skills( ([ "combat":60+lv*2, "dodge":60+lv*2, "parry":60+lv*2, "savage hit":60+lv*2, "heavy hit":110+((lv-30)*3), "continual hit":110+(((lv-30)/5)*15) ]) );
            init_statistic( ([ "ap":1000+lv*30, "hp":1000+lv*30, "mp":1000+lv*30 ]) );
            set("perm_apply", ([ "attack":lv*2+random(lv), "armor":lv*2+random(lv), "exact":lv/5+random(lv)/2, "evade":lv/5+random(lv)/2, "intimidate":lv/6+random(lv)/2, "wittiness":lv/6+random(lv)/2 ]) );
            break;

        case 41..50:
            init_attribute( ([ "str":40+lv/2, "con":40+lv/2, "int":40+lv/2, "dex":40+lv/2 ]) );
            set_skills( ([ "combat":80+lv*2, "dodge":80+lv*2, "parry":80+lv*2, "savage hit":80+lv*2, "heavy hit":110+((lv-30)*3), "continual hit":110+(((lv-30)/5)*15) ]) );
            init_statistic( ([ "ap":2000+lv*40, "hp":2000+lv*40, "mp":2000+lv*40 ]) );
            set("perm_apply", ([ "attack":lv*2+random(lv), "armor":lv*3+random(lv), "exact":lv/4+random(lv)/2, "evade":lv/4+random(lv)/2, "intimidate":lv/5+random(lv)/2, "wittiness":lv/5+random(lv)/2 ]) );
            break;

        case 51..60:
            init_attribute( ([ "str":50+lv/2, "con":50+lv/2, "int":50+lv/2, "dex":50+lv/2 ]) );
            set_skills( ([ "combat":200, "dodge":200, "parry":200, "savage hit":200, "heavy hit":110+((lv-30)*3), "continual hit":110+(((lv-30)/5)*15) ]) );
            init_statistic( ([ "ap":4000+lv*60, "hp":4000+lv*60, "mp":4000+lv*60 ]) );
            set("perm_apply", ([ "attack":lv*2+random(lv), "armor":lv*3+random(lv), "exact":lv/4+random(lv)/2, "evade":lv/4+random(lv)/2, "intimidate":lv/5+random(lv)/2, "wittiness":lv/5+random(lv)/2 ]) );
            break;

        case 61..80:
            init_attribute( ([ "str":60+lv/2, "con":60+lv/2, "int":60+lv/2, "dex":60+lv/2 ]) );
            set_skills( ([ "combat":200, "dodge":200, "parry":200, "savage hit":200, "heavy hit":200, "continual hit":200 ]) );
            init_statistic( ([ "ap":7000+lv*80, "hp":7000+lv*80, "mp":7000+lv*80 ]) );
            set("perm_apply", ([ "attack":lv*2+random(lv), "armor":lv*3+random(lv), "exact":lv/3+random(lv), "evade":lv/3+random(lv), "intimidate":lv/4+random(lv), "wittiness":lv/4+random(lv) ]) );
            break;

        case 81..100:
            init_attribute( ([ "str":70+lv/2, "con":70+lv/2, "int":70+lv/2, "dex":70+lv/2 ]) );
            set_skills( ([ "combat":200, "dodge":200, "parry":200, "savage hit":200, "heavy hit":200, "continual hit":200 ]) );
            init_statistic( ([ "ap":10000+lv*100, "hp":10000+lv*100, "mp":10000+lv*100 ]) );
            set("perm_apply", ([ "attack":lv*3+random(lv), "armor":lv*4+random(lv), "exact":lv/2+random(lv), "evade":lv/2+random(lv), "intimidate":lv/3+random(lv), "wittiness":lv/3+random(lv) ]) );
            break;
    }
    ::setup();
}