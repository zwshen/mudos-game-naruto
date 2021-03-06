#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("張潁", ({ "zhang ying", "ying" }) );
    set_race("human");
    set_level(5);
    set("gender", "female");
    set("nickname", HIG"隔空抓藥"NOR);
    set("age", 27);
    set("long", "自稱擁有道法之力的人，隨便伸手一抓就能拿到靈藥。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        CYN"張穎閉著眼睛隨手往空中一揮，忽然多出一顆黑色藥丸在她手中。\n"NOR,
        (: command, "say 我的技術可不是隨便就能施展的。" :),
        CYN"張穎正吹噓著她的藥有多神奇。\n"NOR,
    }));
    setup();
}
