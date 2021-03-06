#include <ansi.h>
#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("土著戰士", ({ "aborigines warrior", "warrior" }));
    set_race("human");
    set("gender", "male");
    set("age", 10+random(50));
    set_level(26);
    set("long", "土著的保衛戰士，手持刺槍驅逐外人進入。\n");
    set("attitude", "aggressive");
    set("set_drop", ({
        ([ "type":"food", "id":40, "amount":1+random(5), "p1":50, "p2":100 ]),  // 乾果
        ([ "type":"food", "id":38, "amount":1+random(2), "p1":30, "p2":100 ]),  // 樹果
        ([ "type":"food", "id":39, "amount":1+random(1), "p1":20, "p2":100 ]),  // 水果
        ([ "type":"food", "id":41, "amount":1, "p1":10, "p2":100 ]),            // 水果王
        ([ "type":"eq", "id":71, "amount":1, "p1":30, "p2":100 ]),              // 樹葉
        ([ "type":"wp", "id":20, "amount":1, "p1":5, "p2":200 ]),               // 刺槍
    }) );
    setup();

    // 減弱閃躲, 增加攻擊、防禦, 增強體力  就是皮厚打痛不會閃.
    delete_skill("dodge");
    add_temp("apply/hp", 1500);
    add_temp("apply/armor", 40);
    add_temp("apply/attack", 60);
    add_temp("apply/intimidate", 20);
    
    // 有調整過 ap, hp, mp 的要 do_heal(), 才能讓狀態補滿
    do_heal();
}
