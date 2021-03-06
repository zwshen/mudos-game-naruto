#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
    set_name("機關紙", ({ "paper" }));
    if( !clonep() ) {
        set("base_unit", "張");
        set("unit", "張");
        set("base_value", 2);
        set("base_weight", 200);
        set("long","一張神秘的機關紙，可以用(look 機關紙)來觀看。");
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
    if( arg == "機關紙" ) {
        string line;
        line  = "　\n";
        line += "從林北的僵屍身上拿到的機關開法，可信度多高就不知道了\n";
        line += "　\n";
        line += "    １─２  158        酒窖(開)   ◎連開158打開酒窖，注意與畫室衝突\n";
        line += "    │  │  851        酒窖(關)   ◎關閉後才能開啟畫室\n";
        line += "    ３─４  623        畫室(開)   ◎連開623打開畫室，注意與酒窖衝突\n";
        line += "    │  │  326        畫室(關)   ◎關閉後才能開啟酒窖\n";
        line += "    ５─６  6461587    寶藏間(開) ◎開啟酒窖6啟動內藏齒輪4，開啟畫室158打開寶藏間7\n";
        line += "    │  │  857162426  寶藏間(關) ◎關閉畫室85關閉寶藏間7，開啟酒窖62關閉內藏齒輪4\n";
        line += "    ７─８             註：酒窖寶藏間藏於王座之中，畫室則在小朋友畫室之下\n";
        line += "　\n";
        line += "　\n";
        write(line);
        return 1;
    }
}
