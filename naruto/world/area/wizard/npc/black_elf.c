#include <ansi.h>
#include <npc.h>

void create()
{
    set_name(HIK"黑精靈"NOR, ({ "black elf", "elf" }));
    set_level(1);
    set_race("beast");
    set("verbs", ({ "bite" }) );
    set("long", "嬌小的黑色精靈，一臉邪惡的樣子到處設陷阱。\n");
    set("limbs", ({ "頭部", "身體", "腿部", "翅膀", "衣服" }) );
    // 隨機移動
    set("chat_chance", 30);
    set("chat_msg", ({
        (: random_move :),
    }));
    setup();
    add_temp("apply/hp", 300);
    add_temp("apply/ap", 300);
    add_temp("apply/mp", 300);
    do_heal();
}
void die()
{
    object enemy, item;
    int i;
    enemy = this_object()->last_damage_giver();
    if( !enemy ) {
        destruct(this_object());
        return;
    }
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) {
            destruct(this_object());
            return;
        } else
        if( environment(enemy) != environment(this_object()) ) {
            destruct(this_object());
            return;
        }
    }
    i = enemy->query_level()*20 + random(160);
    item = new("/obj/money/silver.c");

    // 限制一下可以打的等級吧，免得新手被搶怪
    if( i > 360 ) i = 360;
    if( enemy->query_level() > 15 ) i = 1;
    else if( enemy->query("bank") > 500000 ) i = 1;

    item->set_amount(i);

    enemy->add_temp("ELF_HOUSE", 1);
    if( environment(enemy)->is_area() ) {
        if( !area_move(environment(enemy), item, enemy->query("area_info/x_axis"), enemy->query("area_info/y_axis")) ) {
            tell_object(enemy,HIK"\n黑精靈邪惡的笑了幾聲，直接消失不見了。\n\n"NOR);
        } else tell_object(enemy,HIK"\n黑精靈咚地一聲掉在地上，化為"HIR"["HIY+chinese_number(i)+HIR"]"HIK"兩銀子。\n\n"NOR);
    } else if( item->move(environment(enemy)) ) {
        tell_object(enemy,HIK"\n黑精靈咚地一聲掉在地上，化為"HIR"["HIY+chinese_number(i)+HIR"]"HIK"兩銀子。\n\n"NOR);
    } else {
        tell_object(enemy,HIK"\n黑精靈邪惡的笑了幾聲，直接消失不見了。\n\n"NOR);
    }
    if( enemy->query_temp("ELF_HOUSE") >= 20 ) {
        message_vision(CYN"精靈們對$N感到害怕，將$N趕出精靈之門了。\n"NOR, enemy);
        enemy->move("/world/area/wizard/elf_door.c");
    }
    destruct(this_object());
    return;
}
