#include <ansi.h>
#include <npc.h>

void create()
{
    set_name(HIK"鼠頭蜘身"NOR, ({ "mouse spider", "spider", "mouse" }) );
    set_race("beast");
    set("title","陰影巢穴");
    set_level(25);

    set("long", "一隻突變的噁心大蜘蛛，想不到長著一個老鼠的頭，身體卻是八隻腳的蜘蛛。\n");

    set("limbs", ({ "鼠頭", "身體", "腹部", "蛛腿" }) );
    set("verbs", ({ "bite" }) );

    set("attitude", "aggressive");         // 主動攻擊
    set("set_drop", ({
        ([ "type":"obj", "id":52, "amount":2, "p1":80, "p2":100 ]),     // 蜘蛛腿
        ([ "type":"obj", "id":54, "amount":1, "p1":5, "p2":100 ]),      // 毒液
        ([ "type":"obj", "id":55, "amount":1, "p1":1, "p2":200 ]),      // 蜘蛛胃袋
        ([ "type":"food", "id":19, "amount":1, "p1":1, "p2":100 ]),     // 查克拉丸
        ([ "type":"eq", "id":81, "amount":1, "p1":1, "p2":500 ]),       // 無縫內褲
        ([ "type":"food", "id":17, "amount":1, "p1":1, "p2":100 ]),     // 體力丸
    }) );
    setup();
    add_temp("apply/attack", 30);
    set_skill("combat", 120);
    set_skill("dodge", 120);
    set_skill("parry", 120);
    set_skill("savage hit", 120);
    set_skill("heavy hit", 120);
    set_skill("continual hit", 120);
}
