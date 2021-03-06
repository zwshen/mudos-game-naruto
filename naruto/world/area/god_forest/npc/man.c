#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("青年男子", ({ "man" }));
    set_race("human");
    set_level(1);
    set("age", 21);
    set("long", "書香氣息的男子，只見他一臉輕鬆的研究棋盤，並沒發現你的到來。\n");
    set("gender", "male");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: command, "think" :),
        CYN"青年男子拿起白子放在棋盤上，又搖搖頭把白子收回。\n"NOR,
        CYN"青年男子拿起黑子放在棋盤上，又搖搖頭把黑子收回。\n"NOR,
        (: command, "ah" :),
    }));
    setup();
}
int relay_say(object me, string arg)
{
    if( !objectp(me) || !stringp(arg) ) return 0;

    if( arg == "三魂" ) {
        do_chat(({
            (: command, "say 三魂七魄這個字詞應該有聽過吧。" :),
            (: command, "say 一個人的心臟都是由三魂七魄所組成。" :),
            (: command, "say 魄因為凝聚力較強，數量也比較多，所以有所損失會自動修補。" :),
            (: command, "say 魂無法自我修補，又容易失去。" :),
            (: command, "say 所以常常人會說「魂都嚇飛了」、「失魂失魂」都是這樣來的。" :),
            (: command, "say 三魂中以心魂為重，另外兩魂只是輔助。" :),
            (: command, "say 也只有心魂不能替換成其他魂魄。" :),
            (: command, "say 一些行屍走肉的生物，大多都是失去了心魂。" :),
        }));
    }
    if( arg == "龍空大王" ) {
        do_chat(({
            (: command, "say 龍空大王是一隻偽龍。" :),
            (: command, "say 原本的牠只是一隻妖蛇罷了。" :),
            (: command, "say 不過因為修道有成，被指派管理這神獸森林第一層。" :),
            (: command, "say 之前管理得當，但是最近好像聽說森林有點失控..." :),
        }));
    }
    if( arg == "魂玉" ) {
        do_chat(({
            (: command, "say 這是一種類魂的晶體。" :),
            (: command, "say 可以用來驅使低程度的鬼魂。" :),
            (: command, "say 有種叫「奪心魔」的妖怪非常喜歡這樣東西。" :),
        }));
    }
    if( arg == "奪心魔" ) {
        do_chat(({
            (: command, "say 專門偷人魂魄的妖怪。" :),
            (: command, "say 據說魔法能力非常之高，喜歡待在充滿靈魂的地方。" :),
            (: command, "say 之前曾經聽說有人在死亡碉堡中看過牠。" :),
        }));
    }
    return 1;
}
