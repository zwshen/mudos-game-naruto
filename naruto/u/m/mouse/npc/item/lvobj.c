#include <ansi.h>

inherit ITEM;

void create()
{
    set_name(HIY"修補"HIW"工具組"NOR, ({ "the wizard's object", "object" }));
    if( !clonep() ) {
        set("unit", "箱");
        set("value", 0);
        set("weight", 1);
        set("long", "修補 lv41 升級沒加能力用的工具，請勿隨意使用。"NOR);
    }
    setup();
}
void init()
{
    add_action("do_add", "addd");
}
int do_add(string arg)
{
    string npc;
    object ob;

    if( this_player()->query_id() != "mouse" || !wizardp(this_player()) )  return notify_fail("你沒有權利使用這樣物品。\n");
    if( !arg ) return notify_fail("指令格式: addd on <某人> \n");
    if( sscanf(arg, "on %s", npc) !=1 ) return notify_fail("指令格式: addd on <某人> \n");

    ob = LOGIN_D->find_body(npc);
    if(!ob) return notify_fail("線上沒有 "HIY+npc+NOR" 這號人物。\n"NOR);

    message_vision("$N"CYN"從"NOR"$n"CYN"中拿出一堆有的沒的工具，對著"NOR+ob->query("name")+CYN"不停地敲敲打打...\n"NOR, this_player(), this_object());
    if( !ob->is_character() || ob->is_corpse() || !userp(ob)) {
        message_vision(HIR"不過並沒有發生任何事情。\n"NOR, this_object());
        tell_object(this_player(),HIR"\n謎之聲：我不能修復非生命的東西。\n"NOR);
        return 1;
    }
    message_vision(CYN"沒多久"NOR+ob->query("name")+CYN"就變的煥然一新了！\n"NOR, this_player(), this_object());
    ob->add_point("score", 150);
    ob->add_point("attribute", 4);
    ob->add_point("skill", 2);

    log_file("lv41update", sprintf("[%s] %s(%s) 修正 %s(%s) 等級提升未增加的能力。\n", ctime(time())[0..15], this_player()->query("name"), this_player()->query_id(), ob->query("name"), ob->query_id()) );

    return 1;
}
