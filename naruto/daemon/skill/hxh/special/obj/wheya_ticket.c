#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
    set_name(HIR"[輝夜]"HIW"借貸券"NOR, ({ "wheya ticket" }));
    if( !clonep() ) {
        set("unit", "張");
        set("value", 0);
        set("base_value", 0);
        set("base_weight", 1);
        set("no_box", 1);
        set("long","一張奇怪的卡片，上面散發出與眾不同的念力\n\n"
                   "技能名稱：輝夜忍者技巧"HIY"["HIR"早蕨之舞"HIY"]\n"NOR
                   "使用條件：特質系程度(special) 100 級以上、借貸券 100 級以上\n"
                   "技能效果：一般傷害 借貸券等級 + (自)生命 - random(200)\n"
                   "命中條件：(自)命中能力 > (敵)迴避能力\n"
                   "額外條件：每次使用扣除自己的生命 借貸券等級 + random(100) 點\n"
                   "使用需求：每次使用需要 借貸券等級/4 點魔力值\n\n");
    }
    setup();
}

void do_use(object me, string arg)
{
    mapping cnd = ([]);
    int sk;

    if( me->query("level") < 30 ) {
        write("等級必須要有 30 級才能使用輝夜的借貸券。\n");
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

    cnd["name"] = HIR"借[輝夜]"NOR;
    cnd["duration"] = sk*3/2;
    cnd["ability"] = "wheya";
    me->start_busy(2);
    me->set_condition("ticket", cnd);
    me->set_temp("ticket_card/wheya", 1);

    // 個數減少
    this_object()->add_amount(-1);
    if( !this_object()->query_amount() )
        destruct(this_object());
}
