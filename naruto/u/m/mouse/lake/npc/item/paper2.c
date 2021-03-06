#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name("信紙", ({ "paper" }));
    if( !clonep() ) {
        set("base_unit", "張");
        set("unit", "張");
        set("base_value", 2);
        set("base_weight", 10);
        set("long","一張信紙，可以用(look 信紙)觀看內容。");
    }
    setup();
}
void init()
{
    add_action("do_look", "look");
}
int do_look(string arg)
{
    if( !arg ) return 0;
    if( arg == "信紙" ) {
        string line;
        line  = "　\n";
        line += "一張不知名的紙，上面寫著：\n";
        line += "　\n";
        line += "父親生前交給我的傳家寶盒和兩卷開啟寶盒的必要卷軸，誰知\n";
        line += "我那天喝醉酒後竟然不小心把其中的一張給弄掉了！誰知居然\n";
        line += "被一位女傭給撿到！她還威脅我如果想要拿回那張卷軸就要把\n";
        line += "我這莊園讓給她！這會讓大家都無家可歸的！早些時候她要找\n";
        line += "我談判，我已經把她約在畫廊的密室裡了，希望林北大總管看\n";
        line += "在工作和友情的份上能幫我這個忙，在談判前就將那卷軸給拿\n";
        line += "回來！我在酒窖內等候總管的好消息！\n";
        line += "　\n";
        line += "　\n";
        write(line);
        return 1;
    }
}
