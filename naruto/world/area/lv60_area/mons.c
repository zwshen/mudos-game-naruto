#include <ansi.h>
inherit ROOM;

void create()
{
    set("short", "火山洞口");
    set("long", @long
悶熱的火山洞中，只有一條容納一人的小徑，徑頭的底端是個地
下道，但是入口堆滿了火山中的岩石，可能稍微一動就會影響到整個
火山的架構，如果想要動這些岩石，可要好好考慮清楚了。
long);
    set("exits", ([
        "south" : ([ "filename": __DIR__"fire_isle.c",
                      "x_axis": 10,
                      "y_axis": 6,
                 ]),
    ]));
    set("detail", ([
        "岩石": "應該可以挖(dig)開吧...不過會有什麼後果呢...",
    ]));
    setup();
}
void init()
{
    add_action("do_push", "dig");
}
int do_push(string arg)
{
    object mob, area;
    string area_file = "/world/area/lv60_area/fire.c";

    if( query("FIRE_WAR") != 0 ) return notify_fail("火山洞內已經崩塌了。\n");
    if( this_player()->query_level() < 21 ) return notify_fail("你根本沒膽子去挖這片岩石。\n");
    if( arg == "岩石" ) {
        message_vision("$N將大石頭搬開後，用力朝岩石部份挖掘！\n", this_player());
        message_vision(HIK"只見岩石忽然鬆動了，$N整個人掉進洞裡去啦...\n"NOR, this_player());

        if( !objectp(area = load_object(area_file)) ) return 0;
        if( !area->is_area() ) return 0;
        if( !area_move(area, this_player(), 1+random(19), 1+random(19)) ) return 0;

        this_player()->start_busy(1);
        set("FIRE_WAR", 1);
        WAR_D->doStartWar(this_player(), "/world/war/fire_die.c");
        call_out("push_1", 600, this_object());
        return 1;
    }
    return notify_fail("你想挖什麼東西？\n");
}
void push_1(object ob)
{
    delete("FIRE_WAR");
    message_vision("火山經過爆發與重新堆積，似乎又回到飽和狀態了。\n"NOR, ob);
    return;
}
