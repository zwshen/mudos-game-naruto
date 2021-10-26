#include <ansi.h>
inherit ITEM;

void create()
{
    set_name(HIB"[���z]"NOR+RED"��"HIW"��"HIK"���n"NOR, ({ "INT capsule", "capsule" }));
    set("unit", "��");
    set("value", -1);
    set("no_box", 1);
    set("no_sell", 1);
    set("no_drop", 1);
    set("attr","int");
    set("long", "���n�����p�ĤY�A���o�����@�뽦�n�u�O�N�ĩ�J�H�C��Ϥ������C\n"
                "���ĥ~�ߪ��C��z���ਣ�䤤�A�Ĥ��b��q���A�b�䳷�աC�����a��\n"
                "���H�g�b���y���m���A�ո̫o�O�@���ťաA�u���ǳ\���į��b����C\n"
                "����C��\����G�����O���A���O�o�Q�W��H��k�X�����ġC\n"
             HIY"�ϥΤ�k��(use capsule)�A"NOR+BLINK+HIR"�`�N�G"NOR+HIR"�Y�U��|�N���ݩʦ^�k��1�šI"NOR);
    setup();
}

void do_use(object me)
{
    int attr;
    object ob = query("attr");
    if( me->query_attr(ob, 1) <= 20 ) {
        write("�A�{�b�����p���ݭn�Y�o���ġC\n");
        return;
    }
    if( me->is_busy() ) {
        write("�A�����ۡA�S���ŦY�ġC\n");
        return;
    }
    if( me->is_fighting() ) {
        write("�԰����ٶæY�ġA����`���C\n");
        return;
    }
    message_vision("\n$N���_$n���L�̤@��A�ܤF�f����$n�]�i�{���C\n\n", me, this_object());

    attr = me->query_attr(ob, 1) - 20;

    message_vision(HIW"$N���M�}�U�@�Ӥ�í�A�����@�դf�R�ժj�˦b�a�W�C\n\n"NOR, me);

    me->add_point("attribute", attr);
    me->set_attr(ob, 20);

    me->unconcious();
    destruct(this_object());
}
