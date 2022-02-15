// write by -Acme-
/* pet.c �d���G�Ԥ� */
// #pragma save_binary

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;
inherit F_SAVE;
//inherit F_AUTOLOAD;

inherit "/feature/user/autoload.c";

object owner;

//int food_maximum = 999; // �����q�W��
//int food = 0;           // �ثe�����q
//int exp = 0;            // �g���

int query_food_maximum() { return 999; }
int query_food() { return query("food"); }
int query_exp() { return query("exp"); }
void add_food(int value) { add("food", value); }
void add_exp(int value) { add("exp", value); }

// �����q�W��
int food_gain(int fo)
{
    if( query_food() + fo > query_food_maximum() ) return 0;
    add_food(fo);
    return 1;
}

// level up
void level_up()
{
    // �̵��Ŵ��ɯ�O
    this_object()->set_attr("str", this_object()->query_level()*150/100);
    this_object()->set_attr("con", this_object()->query_level()*150/100);
    this_object()->set_attr("dex", this_object()->query_level()*150/100);
    this_object()->set_attr("int", this_object()->query_level()*150/100);
    this_object()->set_stat_maximum("ap", this_object()->query_level()*50);
    this_object()->set_stat_maximum("hp", this_object()->query_level()*50);
    this_object()->set_stat_maximum("mp", this_object()->query_level()*50);
    this_object()->set_stat_current("ap", this_object()->query_level()*50);
    this_object()->set_stat_current("hp", this_object()->query_level()*50);
    this_object()->set_stat_current("mp", this_object()->query_level()*50);
    this_object()->set_skill("combat", this_object()->query_level()*3);
    this_object()->set_skill("parry", this_object()->query_level()*3);
    this_object()->set_skill("dodge", this_object()->query_level()*3);
    this_object()->set_skill("heavy hit", this_object()->query_level()*3);
    this_object()->set_skill("savage hit", this_object()->query_level()*3);
    this_object()->set_skill("continual hit", this_object()->query_level()*3);
}

// �g�����o
void exp_gain(int ex)
{
/*
    if( query_exp() >= 100000) {
        return;
    }
*/
    add_exp(ex);

    if( !objectp(owner) ) return;
    if( this_object()->query_level() >= owner->query_level() ) return;

    // �ɯ��ˬd
    if( this_object()->query_level() * this_object()->query_level() * 10 <= query_exp() ) {
        add_exp(-query_exp());
        this_object()->set_level(this_object()->query_level()+1);
        level_up();
        this_object()->save();
        tell_object(owner, HIY"�A���Ԥ� " + this_object()->query("name") + " �����Ŵ��ɦ� " + this_object()->query_level() + " �šC\n"NOR);
    }

    return;
}

// �]�w�D�H
int set_owner(object obj)
{
    if( !objectp(obj) ) return 0;
    owner = obj;
}

// �d�ߥD�H
object query_owner()
{
    if( !objectp(owner) ) return 0;
    return owner;
}

// �R���Ԥ�
void do_destruct()
{
    // �o�{�d���l��L�h���|�o�ͫO�@���~
    // �]�����}�ɨS���R���d���O�@
    // �ҥH�ֿn�F�L�h�� guard ��T  by mouse 2009/2/16
    this_object()->guard_ob(0);
    
    // �w�g�n�������d���N���Τ@���ۭn�����F
//   if( query("WILL_DELETE") ) return;
    message_vision("$N�@�ȷϪ��N�]�o�L�v�L�ܤF...\n", this_object());
    set("WILL_DELETE", 1);
    save_autoload();
    save();

    // �������@�ǰʧ@���]�L
    do_chat( ({ (: destruct, this_object() :) }) );
    return;
}

// �d�����ŤU��
void level_down()
{


    // �w�g�n�������d���N���Τ@���ۭn�����F
    if( query("WILL_DELETE") ) return;

    // ���d�����ŭ��C�ɤ~�|���}�A���M�d���O���|������
    tell_object(owner, HIR"�]���A�S���������U�ۤv���d���A�ϱo�e�����ŭ��C�F�C\n"NOR);

    // �쥻�N�O�g�礣�����~���šA�ҥHexp�����k0
    add_exp(-query_exp());

    // ���i��O�]�����������`�A���K�g���ҥH�����᭹���|�۰ʼW�[�@�I
    add_food(20);

    // ���Ťp��ε���@�ŮɴN���|�A���ŤF
    if( this_object()->query_level() > 1 ) {
        this_object()->set_level(this_object()->query_level() - 1);
        level_up();
    }

    do_destruct();
    return;
}

// �P�_���ө����٬O����
void check_lv()
{
    int lv = this_object()->query_level();

    // �Q�s�����Τ@���s
    if( query("no_say_again") ) return;

    set("no_say_again", 1);
    message_vision("$N�G�s�u�ӡ��ӡ��v��ˤF�U��...\n", this_object());
    if( userp(owner) && owner->query_skill("animal taming") < 180 ) {
        if( query_exp() >= lv*10 ) {
            add_exp(-lv*10);
            tell_object(owner, HIY"�d�����g��ȤU���F�C\n"NOR);
            do_destruct();
        } else {
            level_down();
        }
        return;
    }
    do_destruct();
    return;
}

void unconcious()
{
    die();
    return;
}

// �d���P�_���ܡA�p�G�S���n�n���U�d���A���ťi��|�U��
void die()
{
    check_lv();
    return;
}

// �O�_�����R�O
int accept_order(object who, string cmd)
{
    if( owner != who ) return 0;
    // ���~�N���ݤj��150�šA�~�|������
    if( who->query_skill("animal taming", 1) <= 150 ) return 0;

    // �����R�O�d�����Ǧp�G�d���w���|��������
    // �ҥH�����T��a�R�O�d�����ǡA�D�H�b�@�ǯǲD
    if( cmd == "kill" ) return 0;
    if( cmd == "fight" ) return 0;
    return 1;
}

// �������~�P�_
int accept_object(object me, object ob)
{
    if( me != owner ) {
        tell_object(me, "�u���D�H�~�൹�ۤv���d�����~�C\n");
        return 0;
    }
    
    if( is_busy() ) {
        tell_object(me, "�d�����`���L���A�L�k�����F��C\n");
        return 0;
    }
    
    if( is_fighting() ) {
        tell_object(me, "�԰����L�k�������~�C\n");
        return 0;
    }
    
    if( ob->query("value") <= 0 ) {
        if( ob->query("base_value") <= 0 ) return 0;
    }

    return 1;
}

// �H���ˬd�D�H�O�_�s�b
void do_check_owner()
{
    // �D�H�����A�h�Ԥ��]����
    if( !objectp(owner) ) {
        do_destruct();
        return;
    }

    // �b���P��m�]�|����
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), owner) ) {
            do_destruct();
            return;
        }
    } else {
        if( environment(this_object()) != environment(owner) ) {
            do_destruct();
            return;
        }
    }
    if( query("no_say_again") ) delete("no_say_again");
}

// �����q�ˬd
void do_check_food()
{
    if( !objectp(this_object()) || !objectp(owner) ) return;
    if( query_food() <= 0 ) {
        // �쥻�j�@���u��10�A���ǤH�ڥ����b�N�d���O���O�Ⱦj���A by mouse
        tell_object(owner, HIR"�A���Ԥ� "+this_object()->query("name")+" ���G�{�l�j�o��...\n"NOR);
        this_object()->damage_stat("ap", this_object()->query_stat_maximum("ap")/20, this_object());    // ���믫
        this_object()->receive_damage(this_object()->query_stat_maximum("hp")/20, this_object());       // ����O
        this_object()->damage_stat("mp", this_object()->query_stat_maximum("mp")/20, this_object());    // ���d�J��
        return;
    }

    // ��֭����q
    add_food(-(random(3) + 1));
}

// �Ԥ���_���A�����
void do_heal_stat()
{
    if( !objectp(this_object()) ) return;
    this_object()->heal_stat("ap", this_object()->query_level());
    this_object()->heal_stat("hp", this_object()->query_level());
    this_object()->heal_stat("mp", this_object()->query_level());
}

void normal_action()
{
    do_check_owner();
    do_check_food();
    do_heal_stat();
    exp_gain(1);
}

void reset_action()
{
    // ���ɰʧ@�G�ˬdowner�٦b���b
    set("chat_chance", 10);
    set("chat_msg", ({
        (: normal_action :),
    }));

    // �԰��ɰʧ@�G�ˬdowner�٦b���b
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: normal_action :),
    }) );
}

void create()
{
    set_name("�Ԥ�", ({ "dog", "_MY_PET_" }));
    set_race("beast");
    set("no_fight", 1);
    setup();
}

// ���i�H�s��
string query_save_file()
{
    if( owner && objectp(owner) )
        return DATA_DIR + "pet/ninja_dog/" + owner->query_id();

    else return DATA_DIR + "pet/ninja_dog/no_owner";
}
