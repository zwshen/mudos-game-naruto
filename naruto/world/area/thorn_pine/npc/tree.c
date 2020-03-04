#include <npc.h>
#include <ansi.h>

string *name1 = ({ "¨ë¾ð", "¨ëªK", "¨ë¤ì", "¨ë¸­", "¨ë®Ú", "¨ë²ô",
                   "ªQ¾ð", "ªQªK", "ªQ¤ì", "ªQ¸­", "ªQ®Ú", "ªQ²ô",
                   "¬f¾ð", "¬fªK", "¬f¤ì", "¬f¸­", "¬f®Ú", "¬f²ô",
                   "ÅK¾ð", "ÅKªK", "ÅK¤ì", "ÅK¸­", "ÅK®Ú", "ÅK²ô", });

string *name2 = ({ "Å]", "§¯", "©Ç", "ºë", "°­", "¥P", "ÂÎ" });

void do_fight()
{
    int damage, raiseDamage;
    object enemy;

    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    // µ¥¯Å¤Ó§C¤£©ñ perform, ¤w¸g³Q©w´N¤£©ñ perform
    if( enemy->query_level() < 5 ) return;
    if( enemy->is_busy() ) return;

    message_vision("\n$N"HIG"ªK¸­¤@±i¡A¦p¦P±Û­·¯ëªº§Ö³t´Â"NOR"$n"HIG"±½¥h¡I\n"NOR, this_object(), enemy);
    if( random(5) > 2) {
        message_vision("$nÃÛ§C¨­¤l°{¹L¤F§ðÀ»¡I\n\n", this_object(), enemy);
        this_object()->start_busy(1);
        return;
    }
    damage = 100;

    add_temp("apply/attack", raiseDamage); 
    damage = COMBAT_D->isDamage(this_object(), enemy, 0);
    add_temp("apply/attack", -raiseDamage);

    // ¶Ë®`¬Þ§l¦¬
    damage = COMBAT_D->receive_damage(enemy, this_object(), damage);
    enemy->damage_stat("hp", damage, this_object());
    message_vision( sprintf("$n¡u°Ô¡I¡v¦a¤@Án³Q¥´Â½¦b¦a¤W(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    enemy->start_busy(3);
    return;
}
void create()
{
    set_name( name1[random(sizeof(name1))] + name2[random(sizeof(name2))], ({ "thorn tree", "tree" }));
    set_race("beast");
    set_level(25+random(6));
    set("long", "¨ëªQªL¤¤ªº¾ð±Ú¡A·|¦Û°Ê§ðÀ»¥~¨ÓªÌ¡C\n");
    set("limbs", ({ "¸­¤ù", "¾ð·F", "¾ð®Ú", "¾ð²ô", "¾ð¥Ö", "¾ð±é", "ªKÀY" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // ¥D°Ê§ðÀ»
    // ÀH¾÷²¾°Ê
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    switch( random(101) ) {
        case 0..15:
            set("set_drop", ({
                ([ "type":"obj", "id":60, "amount":1, "p1":50, "p2":100 ]),  // ¾ð®Ú
                ([ "type":"obj", "id":61, "amount":1, "p1":35, "p2":100 ]),  // ¾ð¥Ö
                ([ "type":"obj", "id":70, "amount":1, "p1":20, "p2":100 ]),  // ¾ð¯×
                ([ "type":"obj", "id":73, "amount":1, "p1":60, "p2":100 ]),  // ¬õ¦â¾ð²G
            }) );
            break;
        case 16..34:
            set("set_drop", ({
                ([ "type":"obj", "id":60, "amount":1, "p1":50, "p2":100 ]),  // ¾ð®Ú
                ([ "type":"obj", "id":61, "amount":1, "p1":35, "p2":100 ]),  // ¾ð¥Ö
                ([ "type":"obj", "id":70, "amount":1, "p1":20, "p2":100 ]),  // ¾ð¯×
                ([ "type":"obj", "id":72, "amount":1, "p1":60, "p2":100 ]),  // µµ¦â¾ð²G
            }) );
            break;
        case 35..94:
            set("set_drop", ({
                ([ "type":"obj", "id":60, "amount":1, "p1":50, "p2":100 ]),  // ¾ð®Ú
                ([ "type":"obj", "id":61, "amount":1, "p1":35, "p2":100 ]),  // ¾ð¥Ö
                ([ "type":"obj", "id":70, "amount":1, "p1":20, "p2":100 ]),  // ¾ð¯×
                ([ "type":"obj", "id":71, "amount":1, "p1":60, "p2":100 ]),  // ºñ¦â¾ð²G
            }) );
            break;
        default:
            set("set_drop", ({
                ([ "type":"obj", "id":60, "amount":1, "p1":50, "p2":100 ]),  // ¾ð®Ú
                ([ "type":"obj", "id":61, "amount":1, "p1":35, "p2":100 ]),  // ¾ð¥Ö
                ([ "type":"obj", "id":70, "amount":1, "p1":20, "p2":100 ]),  // ¾ð¯×
                ([ "type":"obj", "id":74, "amount":1, "p1":60, "p2":100 ]),  // ¶Àª÷¾ð²G
            }) );
            break;
    }
    setup();
}