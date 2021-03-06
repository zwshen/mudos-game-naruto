#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIY"[豹\族]"HIW"借貸券"NOR, ({ "bow ticket" }));
    if( !clonep() ) {
        set("unit", "張");
        set("value", 0);
        set("base_value", 0);
        set("base_weight", 1);
        set("no_box", 1);
        set("long","一張奇怪的卡片，上面散發出與眾不同的念力。\n\n"
                   "技能名稱：豹\族技巧"HIR"[發勁]\n"NOR
                   "使用條件：特質系程度(special) 100 級以上、借貸券 80 級以上\n"
                   "技能效果：提高攻擊力量 借貸券等級/2 點\n"
                   "效果時間：借貸券等級*2\n"
                   "使用需求：每次使用需要 200 點魔力值\n\n");
    }
    setup();
}

void do_use(object me, string arg)
{
    mapping cnd = ([]);
    int sk;

    if( me->query("level") < 25 ) {
        write("等級必須要有 25 級才能使用豹族的借貸券。\n");
        return;
    }
    if( me->query_condition("ticket") != 0 ) {
        write("你已經在使用借貸券了，等時效過去再換吧。\n");
        return;
    }
    sk = me->query_skill("lending ticket");

    if( sk < 20 || me->query_skill("special") < 20 ) {
        write("你的借貸券和特質系程度必須要在 20 級以上。\n");
        return;
    }
    message_vision("\n$N神情專注地帶上耳塞，慢慢將$n撕開，一陣青光灌入$N的身上...\n\n"NOR, me, this_object());

    cnd["name"] = HIY"借[豹\族]"NOR;
    cnd["duration"] = sk*3/2;
    cnd["ability"] = "bow";
    me->start_busy(2);
    me->set_condition("ticket", cnd);
    me->set_temp("ticket_card/bow", 1);

    // 個數減少
    this_object()->add_amount(-1);
    if( !this_object()->query_amount() )
        destruct(this_object());
}
