#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;

void create()
{
    set_name("蛇守", ({ "snake so", "so" }) );
    set_level(26);
    set_race("human");
    set("gender", "male");
    set("age", 25);
    set("limbs", ({ "蛇頭", "蛇尾", "腹部", "胸口", "腳部", "肩膀", "腰部" }) );
    set("title",HIG"蛇族戰士"NOR);
    set("long", "頭上長了一塊大肉瘤的蛇人，正站在這一動也不動。\n");
    set("guard_exit", ({ "north" })); // 守著出口
    set("set_drop", ({
        ([ "type":"eq", "id":87, "amount":1, "p1":1, "p2":150 ]),     // 蛇神項鍊
        ([ "type":"food", "id":29, "amount":1, "p1":35, "p2":100 ]),  // 蛇蛋
        ([ "type":"food", "id":30, "amount":1, "p1":25, "p2":100 ]),  // 蛇膽
        ([ "type":"obj", "id":24, "amount":1, "p1":25, "p2":100 ]),   // 蛇皮
        ([ "type":"wp", "id":14, "amount":1, "p1":20, "p2":100 ]),    // 蛇牙
    }) );
    setup();
    set_temp("apply/attack", 100);
    carry_object("/world/area/thorn_pine/npc/wp/thorn_blade")->wield("righthand");
}
int do_guard_exit(int x, int y, string exit)
{
    message_vision("$n伸出手擋住$N的去路。\n", this_player(), this_object());
    do_chat((: command, "say 上面是活祭品神壇，你這外人滾一邊去。":));
    return 1;
}
void init()
{
    if( this_object() == this_player() ) return;

    // 若 this_player() 看不見這個人物，則不引發戰鬥。
    if( !this_object()->visible(this_player()) ) return;

    // 區域設定
    if( environment()->is_area() && !area_environment(this_object(), this_player()) ) return;

    // 若雙方正互相仇視中，開始戰鬥。
    if( this_player()->is_killing(query("id")) ) {
        COMBAT_D->auto_fight(this_player(), this_object(), "hatred");
        return;
    }
    if( is_killing(this_player()->query("id")) ) {
        COMBAT_D->auto_fight(this_object(), this_player(), "hatred");
        return;
    }
    // 看到老張女兒便開打
    if( this_player()->id("_HELP_GIRL_") && !this_player()->is_fighting(this_player()) ) {
        message_vision(HIR"$N一見到$n便大聲喊著：「活祭品跑了！快去抓回來！」\n\n"NOR, this_object(), this_player());
        this_object()->kill_ob(this_player());
    }
}
