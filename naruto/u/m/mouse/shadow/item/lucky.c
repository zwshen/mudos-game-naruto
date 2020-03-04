inherit ITEM;
#include <ansi.h>

string *unk_msg = ({
        YEL"大吉"NOR, HIY"吉"NOR, HIY"小吉"NOR, HIW"中"NOR, 
        HIK"小兇"NOR, HIR"兇"NOR, RED"大兇"NOR,
});

void create()
{
    set_name(HIY"幸運輪"NOR, ({ "lucky"}));
    set_weight(1);
    if( !clonep() ) {
        set("unit", "臺");
        set("value", 0);
        set("no_get", 1);
        set("long","一臺巨大的幸運輪，可以轉動(pull)看看會掉出什麼。\n");
    }
    setup();
}
void init()
{
    add_action("do_pull", "pull" );
}
int do_pull(string arg)
{
    string msg;
    int i;
    msg = unk_msg[random(sizeof(unk_msg))];
    if( !id(arg) ) return notify_fail("你想轉動什麼？\n");
    message_vision("$N投了("HIY"100"NOR")元，用力的轉動$n。\n", this_player(), this_object());
    this_player()->add("bank", -100);
    message_vision("$n"HIW"中掉出一捲紙，$N打開掉出的紙張，上面寫著「"NOR+msg+HIW"」\n"NOR, this_player(), this_object());
    return 1;
}
