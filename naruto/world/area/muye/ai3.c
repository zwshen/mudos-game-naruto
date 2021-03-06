/* write by -Acme- */
inherit ROOM;

void create()
{
    set("short", "愛子家-後院");

    set("long", @long
這裡是木葉村的愛子家的後院，雜草叢生相當嚇人。
long);

    set("detail", ([
        "雜草" : "這裡的雜草很多，好像拔(weed)不完一樣...",
    ]));

    set("exits", ([
        "east" : __DIR__"ai2.c",
    ]));

    setup();
}

void init()
{
    add_action("do_weed", "weed");
}

int do_weed(string arg)
{
    if( this_player()->is_busy() ) return notify_fail("你上一個動作還沒完成。\n");
    message_vision("$N哈著腰開始拔起地上的雜草...\n", this_player());

    if( this_player()->query_temp("ai_herb") ) {
        this_player()->add_temp("ai_herb", 1);
    } else {
        this_player()->set_temp("ai_herb", 1);
    }
    this_player()->start_busy(2);
    return 1;
}
