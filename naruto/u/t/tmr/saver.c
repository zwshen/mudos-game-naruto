#include <armor.h>

inherit F_NECK_EQ;

void create()
{
        set_name("全玩家存檔", ({ "players saver","saver"}));
        set_weight(3);
            setup_neck_eq();
        if( !clonep() ) {
                set("wear_as", "neck_eq");
                set("unit", "株");
                set("value", 5);
                set("long",
                        "使用指令：saveall\n");
        }
        setup();
}

void init()
{
        if( wizardp(this_player() ) )
         add_action("do_saveall", "saveall");
}

int do_saveall(string arg)
{
        users()->save();
    write("ok\n");
        return 1;
}
