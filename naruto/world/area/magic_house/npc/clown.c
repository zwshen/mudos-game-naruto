#include <ansi.h>
#include <npc.h>
#include "skill.h"

void create()
{
    set_name("馬戲團小丑", ({ "clown" }));
    set_race("human");
    set_level(40);
    set("age", 5+random(40));

    // 隨機移動
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));

    // 戰鬥動作
    set("chat_chance_combat", 15);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );

    set("set_drop", ({
        ([ "type":"eq", "id":109, "amount":1, "p1":1, "p2":100 ]),    // 大紅鼻子
        ([ "type":"eq", "id":107, "amount":1, "p1":1, "p2":400 ]),    // 魔術手腕
        ([ "type":"obj", "id":107, "amount":1, "p1":1, "p2":1000 ]),  // 極光飛天滑板
    }) );

    set("sktree", random(5)+1);

    setup();
    switch( query("sktree") ) {
        case 1: // 雜耍小丑
            set("nickname",HIC"雜耍表演"NOR);
            set("long", "手拿五把鋼刀不停丟擲的小丑，臉上帶著小丑招牌的微笑。\n");
            break;
        case 2: // 魔術小丑
            set("nickname",HIM"魔術表演"NOR);
            set("long", "不停從帽子裡變出兔子的小丑，臉上帶著小丑招牌的微笑。\n");
            break;
        case 3: // 空中飛人
            set("nickname",HIW"空中飛人"NOR);
            set("long", "穿著白色緊身衣的小丑，不停地向四周的客人打招呼。\n");
            break;
        case 4: // 踩球小丑
            set("nickname",HIG"踩大球"NOR);
            set("long", "踩在一顆圓球上卻不會掉下來，臉上帶著小丑招牌的微笑。\n");
            break;
        case 5: // 火圈小丑
            set("nickname",HIR"跳火圈"NOR);
            set("long", "不停在火圈間穿來穿去都沒被燒著，讓四周客人拍手叫好。\n");
            break;
    }
    // 增強
    add_temp("apply/attack", -50);         // 攻擊力量
    add_temp("apply/armor", 100);          // 防禦力量
    add_temp("apply/evade", 50);          // 迴避率
    add_temp("apply/int", 20);             // 智慧
    add_temp("apply/dex", 20);             // 敏捷
}
