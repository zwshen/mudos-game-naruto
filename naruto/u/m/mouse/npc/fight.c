#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("測試戰神", ({ "fight man", "man" }));
    set_race("human");
    set("long", "一位專門用來測試的複製人。\n");
    setup();
}
void relay_say(object ob, string arg)
{
    string adv;
    int i;
    if( !arg || sscanf(arg, "%s %d", adv, i) != 2 ) return 0;
    if( wizardp(this_player()) ) {
        if( adv == "攻力" ) {
            this_object()->add_temp("apply/attack", i);
            message_vision("$N說道："HIG"增加"+adv+"能力("HIW+i+HIG")點完成。\n"NOR, this_object());
        } else
        if( adv == "防力" ) {
            this_object()->add_temp("apply/armor", i);
            message_vision("$N說道："HIG"增加"+adv+"能力("HIW+i+HIG")點完成。\n"NOR, this_object());
        } else
        if( adv == "命中" ) {
            this_object()->add_temp("apply/exact", i);
            message_vision("$N說道："HIG"增加"+adv+"能力("HIW+i+HIG")點完成。\n"NOR, this_object());
        } else
        if( adv == "迴避" ) {
            this_object()->add_temp("apply/evade", i);
            message_vision("$N說道："HIG"增加"+adv+"能力("HIW+i+HIG")點完成。\n"NOR, this_object());
        } else
        if( adv == "攻技" ) {
            this_object()->add_temp("apply/intimidate", i);
            message_vision("$N說道："HIG"增加"+adv+"能力("HIW+i+HIG")點完成。\n"NOR, this_object());
        } else
        if( adv == "防技" ) {
            this_object()->add_temp("apply/wittiness", i);
            message_vision("$N說道："HIG"增加"+adv+"能力("HIW+i+HIG")點完成。\n"NOR, this_object());
        } else
        if( adv == "移動" ) {
            this_object()->add_temp("apply/move", i);
            message_vision("$N說道："HIG"增加"+adv+"能力("HIW+i+HIG")點完成。\n"NOR, this_object());
        } else
        if( adv == "負重" ) {
            this_object()->add_temp("apply/carriage", i);
            message_vision("$N說道："HIG"增加"+adv+"能力("HIW+i+HIG")點完成。\n"NOR, this_object());
        }
    }
}
void unconcious()
{
    this_object()->die();
    return;
}
void die()
{
    message_vision(HIW"\n$N白光一閃，忽然地就消失在你眼前了。\n"NOR, this_object());
    destruct(this_object());
    return;
}
