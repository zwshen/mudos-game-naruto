inherit ITEM;

void create()
{
        set_name("骰子", ({ "dice" }));
        set_weight(3);
        if( !clonep() ) {
                set("unit", "粒");
                set("value", 5);
                set("long","剛好寫區域要用到，就借來改一改。\n");
        }
        setup();
}
void init()
{
        add_action("do_roll", ({ "roll", "throw" }));
}
int do_roll(string arg)
{
        if( !id(arg) ) return 0;
        message_vision("$N拿出骰子一擲，骰子滾了滾停下來，結果是個" + (random(14)) + "點。\n", this_player());
        return 1;
}
