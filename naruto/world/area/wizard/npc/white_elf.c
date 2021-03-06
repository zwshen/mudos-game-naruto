#include <ansi.h>
#include <npc.h>

void create()
{
    set_name(HIW"白精靈"NOR, ({ "white elf", "elf" }));
    set_level(1);
    set_race("beast");
    set("verbs", ({ "bite" }) );
    set("long", "嬌小的白色精靈，正拍打著翅膀緩緩飛舞。\n");
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
    object enemy;
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
    i = enemy->query_level()*5 + random(20);

    // 限制一下可以打的等級吧，免得新手被搶怪
    if( i > 70 ) i = 70;
    if( enemy->query_level() > 15 ) i = 1;
    else if( enemy->query_point("learn") > 100000 ) {
        tell_object(enemy,RED"\n你的學點超過了十萬點，因此學點只給予一點。\n"NOR);
        i = 1;
    }

    enemy->add_temp("ELF_HOUSE", 1);
    tell_object(enemy,HIW"\n白精靈化為片片雪花，賜給了你"HIY"["HIC+chinese_number(i)+HIY"]"HIW"點學點。\n\n"NOR);
    enemy->add_point("learn", i);
    if( enemy->query_temp("ELF_HOUSE") >= 20 ) {
        message_vision(CYN"精靈們對$N感到害怕，將$N趕出精靈之門了。\n"NOR, enemy);
        enemy->move("/world/area/wizard/elf_door.c");
    }
    destruct(this_object());
    return;
}
