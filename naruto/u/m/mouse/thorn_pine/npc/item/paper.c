#include <ansi.h>

inherit ITEM;

void create()
{
    set_name("號碼牌("HIW+random(406)+NOR")", ({ "paper" }));
    set_weight(1);
    if( !clonep() ) {
        set("inter_test", 1);
        set("unit", "張");
        set("value", 0);
        set("long", "獵人考試的號碼牌，好像沒什麼用");
    }
    setup();
}
