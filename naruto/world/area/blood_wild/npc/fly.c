#include <npc.h>
#include <ansi.h>

void create()
{
    if( random(100) > 5 ) {
        set_name(HIK"小碳蠅"NOR, ({ "little coal fly", "fly" }) );
        set_level(10);
        set("long", "如同鳥禽般大小的碳化魔物，擁有一對蝙蝠翅膀卻被稱為蠅。\n");
        set("set_drop", ({ ([ "type":"obj", "id":122, "amount":1+random(2), "p1":60, "p2":100 ]), }) );
    } else {
        set_name(HIK"飛碳蝠"NOR, ({ "fly coal bat", "bat", "fly" }) );
        set_level(55);
        set("long", "小碳蠅的進化型，翅膀部份強化成一對巨翼，有如古代的翼手龍。\n");
        set("set_drop", ({ ([ "type":"obj", "id":122, "amount":5+random(15), "p1":100, "p2":100 ]), }) );
    }
    set_race("beast");
    set("age", 100+random(5000));
    set("limbs", ({ "頭部", "觸手", "翅膀", "細腳", "翼葉", "碳軀" }) );
    set("chat_chance", 30);
    set("chat_msg", ({
        (: random_move :)
    }));
    setup();
    add_temp("apply/hp", query_level()*10);
    add_temp("apply/evade", query_level()*3);
    do_heal();
}
void die()
{
    object enemy;
    int i;
    enemy = this_object()->last_damage_giver();
    if( !enemy ) {
        ::die();
        return;
    }
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) {
            ::die();
            return;
        } else
        if( environment(enemy) != environment(this_object()) ) {
            ::die();
            return;
        }
    }
    i = query_level()*5 - random(query_level());
    if( enemy->query_point("learn") > 1000000 ) {
        i = i*-2;
        tell_object(enemy,HIR"\n因為殺死"NOR+this_object()->query("name")+HIR"你被扣除了"HIY"["HIK+chinese_number(i)+HIY"]"HIR"點學點。\n\n"NOR);
    } else {
        tell_object(enemy,"\n因為殺死"NOR+this_object()->query("name")+"你額外獲得了"HIM"["HIC+chinese_number(i)+HIM"]"NOR"點學點。\n\n"NOR);
    }
    enemy->add_point("learn", i);
    ::die();
    return;
}
