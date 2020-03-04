inherit ITEM;
#include <ansi.h>

string *unk_msg = ({
        YEL"大吉"NOR, HIY"吉"NOR, HIY"小吉"NOR, HIW"中"NOR, 
        HIK"小兇"NOR, HIR"兇"NOR, RED"大兇"NOR,
});

void create()
{
        set_name(HIW"命運骰子"NOR, ({ "dice"}));
        set_weight(1);
        if( !clonep() ) {
                set("unit", "粒");
                set("value", 5);
                set("long","一粒骰子，可以用 roll 擲骰子玩。\n");
        }
        setup();
}
void init()
{
        add_action("do_roll", ({ "roll", "throw" }));
}
int do_roll(string arg)
{
        string msg;
        if( !id(arg) ) return 0;
        msg = unk_msg[random(sizeof(unk_msg))];
        message_vision("$N拿出骰子一擲，骰子滾了滾停下來，結果是"+msg+"！\n", this_player());
        return 1;
}
