#include <ansi.h>
#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("看門狗", ({ "guard door dog", "dog" }));
    set_race("beast");
    set_level(22);

    // 守著出口
    set("guard_exit", ({ "west" }));

    set("set_drop", ({
        ([ "type":"eq", "id":5, "amount":1, "p1":70, "p2":100 ]),     // 繩子
        ([ "type":"eq", "id":32, "amount":1, "p1":10, "p2":100 ]),     // 大便帽
    }) );

    setup();
}
int do_guard_exit(int x, int y, string exit)
{
    if( userp(this_player()) ) {
        message_vision("$n伸出狗腳將$N攔住。\n", this_player(), this_object());
        do_chat((: command, "say 嘖嘖嘖！你可別亂闖啊。":));
        return 1;
    }
}
