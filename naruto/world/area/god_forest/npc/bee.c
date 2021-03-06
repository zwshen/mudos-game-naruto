#include <ansi.h>
#include <npc.h>

inherit F_SOLDIER;

void do_fight()
{
    mapping cnd = ([]);
    object enemy;
    int exact, evade;

    // 沒有敵人
    enemy = this_object()->query_opponent();

    if( !enemy ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( enemy->query_condition("vp") != 0 ) return;
    exact = COMBAT_D->intimidate(this_object(), 1)*1.5;
    evade = COMBAT_D->wittiness(enemy, 1);

    message_vision("\n$N"YEL"露出屁股上的尖針，拍了幾下翅膀快速刺向$n的要害！\n"NOR, this_object(), enemy);
    if( !COMBAT_D->SkillHit(this_object(), enemy, exact, evade) ) {
       message_vision("結果$N飛錯了方向，完全沒有碰到$n！\n\n"NOR, enemy, this_object());
    } else {
        cnd["name"] = GRN"中毒"NOR;
        cnd["duration"] = 20;

        this_object()->damage_stat("mp", 20, this_object());
        enemy->set_condition("vp", cnd);
        message_vision("$N唉吆一聲慘叫，原來是被$n蟄到了。\n\n"NOR, enemy, this_object());
    }
    return;
}
void create()
{
    set_name("玄蜂", ({ "god monster bee", "bee" }));
    set_level(50);
    set_race("beast");
    set("limbs", ({ "蜂頭", "蜂翅", "肥尾", "蜂刺", "觸鬚", "肚子" }) );
    set("long", "其實就是巨蜂，腹大如壺，蟄人，有毒，能殺人。 \n");
    set("nickname",YEL"巨蜂"NOR);
    set("set_drop", ({

    }) );
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"food", "id":79, "amount":1, "p1":10, "p2":100 ]),     // 神仙果
        ([ "type":"food", "id":16, "amount":1, "p1":20, "p2":100 ]),     // 大精力丸
        ([ "type":"food", "id":15, "amount":1, "p1":30, "p2":100 ]),     // 精力丸
    }) );
    setup();
}