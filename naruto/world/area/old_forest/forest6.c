#include <ansi.h>
inherit ROOM;

void create()
{
    set("short",GRN"遠古叢林"NOR);
    set("long", @long
茂密的叢林，每棵樹少說都高數百公尺，枝葉茂盛將天上的太陽
蓋個無光，底下枝脈盤根錯節，看來這些大樹少說也有幾千年的生命
了，有的樹枝更是像有生命般的活動著，似乎還會撥開它的枝葉讓根
部也能照到少許的陽光，也因為這樣整片森林中視野還算清晰。
long);
    set("exits", ([
        "north" : __DIR__"forest6.c",
        "south" : __DIR__"forest6.c",
        "west" : __DIR__"forest6.c",
        "east" : __DIR__"forest6.c",
    ]));
    set("no_recall", 1);
    setup();
}
int valid_leave(object me, string dir)
{
    string area = __DIR__"forest"+random(20)+".c";
    object mob;
    if( !me ) return 0;
    if( userp(me) && (dir == "west" || dir == "east" || dir == "south" || dir == "north" ) ) {
        me->move(area);
        switch( random(500) ) {
            case 50..105: message_vision(HIR"$N走著走著，四周忽然傳出一陣野獸的暴怒聲！\n"NOR, me);
                          mob = new(__DIR__"npc/sacrier.c");
                          mob->move(environment(me));
                          break;
            case 260..315: message_vision(HIW"嘹亮的號角聲中，白光從茂密的枝葉上破空而下！\n"NOR, me);
                          mob = new(__DIR__"npc/sworder.c");
                          mob->move(environment(me));
                          break;
            case 420..475: message_vision(HIG"綠樹在瞬間變的更加茂盛！但卻伴隨著詭異的笑聲...\n"NOR, me);
                          mob = new(__DIR__"npc/doctor.c");
                          mob->move(environment(me));
                          break;
        }
    }
    return notify_fail("");
}
