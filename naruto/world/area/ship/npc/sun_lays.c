#include <ansi.h>
#include <npc.h>

inherit F_SEABANDIT;

void create()
{
    set_name("樂事", ({ "lays" }) );
    set_race("human");
    set_level(25);
    set("title",HIR"三日月"NOR);
    set("nickname", "祭師");
    set("gender", "male");
    set("class","thief_sea");
    set("camp", "robber");
    set("age", 25);
    set("long", "口中亂唸一通，手杖胡亂比劃，應該是個啥都不會的冒牌祭師。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        (: command, "say 嗯？我的聖經掉哪去了？" :),
        (: command, "say 糟糕...桃符紙又快用光拉..." :),
        (: command, "say 不知道這句阿獼猴頭是什麼意思..." :),
    }));
    set("set_drop", ({
        ([ "type":"wp", "id":9, "amount":1, "p1":79, "p2":100 ]),         // 蘿蔔
        ([ "type":"wp", "id":21, "amount":1, "p1":1, "p2":1500 ]),        // 神木杖
        ([ "type":"wp", "id":43, "amount":1, "p1":10, "p2":100 ]),        // 刺木棒
    }) );
    setup();
    carry_object("/world/wp/pairrod.c")->wield();
}
