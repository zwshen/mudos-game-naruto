#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;

void create()
{
    set_name("步忍過", ({ "bu ren guo", "guo" , "__GUARD__" }) );

    set_class("superior");  // 上忍
    set_level(55);

    set("title", "神獸之森守衛");

    set("long", "一個守護的神獸之森的上忍，防止不知情的人誤闖進去，也保護人們\n"
                "不受神獸之森裡的野獸攻擊。\n");

    // 守著出口
    set("guard_exit", ({"east", "northeast", "southeast"}));

    // 世仇：神界
    set("vendetta_mark", "wizard");

    setup();

    // 人物本身的技能設定
    set_skill("dodge", 200);               // 基本： 迴避技巧
    set_skill("parry", 200);               // 基本： 防禦技巧
    set_skill("combat", 200);              // 基本： 格鬥技巧
    set_skill("savage hit", 200);          // 基本： 暴擊
    set_skill("heavy hit", 200);           // 基本： 重擊
    set_skill("force", 10);                // 基本： 體術
    set_skill("ninja", 200);               // 基本： 忍術
    set_skill("magic", 10);                // 基本： 幻術
}

int do_guard_exit(int x, int y, string exit)
{
    object me, area;
    string area_file = "/world/area/god_forest/god_1.c";

    me = this_player();

    if( !objectp(area = load_object(area_file)) ) return 0;
    if( !area->is_area() ) return 0;
    if( !userp(me) || me->query_level() < 35 ) {
        message_vision("$n伸手將$N攔住。\n", me, this_object());
        do_chat((: command, "say 神獸森林裡的野獸兇惡得很，你最好別進去。":));
    } else {
        message_vision("$n說道﹕"HIG"既然$N已經有如此能力，我也不阻止$N進入了。\n"NOR, me, this_object());
        message_vision(CYN"\n$n雙手發出藍光，將$N輕輕送進了神獸森林。\n\n", me, this_object());
        if( !area_move(area, me, 1, 29) ) return 0;
    }
    return 1;
}

int accept_fight(object ob)
{
    do_chat((: command, "say 比武？我可沒空，你去找別人試試吧。":));
    return 0;
}
