#include <npc.h>
#include <ansi.h>

int i;

string *name1 = ({ "¨ë¾ð", "¨ëªK", "¨ë¤ì", "¨ë¸­", "¨ë®Ú", "¨ë²ô",
                   "ªQ¾ð", "ªQªK", "ªQ¤ì", "ªQ¸­", "ªQ®Ú", "ªQ²ô" });

string *name2 = ({ "Å]", "§¯", "©Ç", "ºë" });

string report_status(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$n" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$n" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$n" + HIR + ratio + "%" + HIK"]\n"NOR;
}
void do_fight()
{
    int damage;
    object enemy;
    string msg;
    // ¨S¦³¼Ä¤H
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // ¼Ä¤H¦b¤£¦P¦ì¸m
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    message_vision("$N"HIG"ªK¸­¤@±i¡A¦p¦P±Û­·¯ëªº§Ö³t´Â"NOR"$n"HIG"±½¥h¡I\n"NOR, this_object(), enemy);
    damage = 10+random(11);
    if( random(5) > 2) {
        message_vision("        $nÃÛ§C¨­¤l°{¹L¤F§ðÀ»¡I(0)"+report_status(enemy)+"", this_object(), enemy);
        this_object()->start_busy(2);
        return;
    }
    enemy->damage_stat("hp", damage, enemy);
    message_vision("        $n¡u°Ô¡I¡v¦a¤@Án³Q¥´Â½¦b¦a¤W¡C("+damage+")"+report_status(enemy)+"", this_object(), enemy);
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
    set("chat_chance_combat", 15);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    i = random(101);
    if( i <= 15 ) {
        set("set_drop", ({
            ([ "type":"obj", "id":66, "amount":1, "p1":50, "p2":100 ]),  // ¾ð®Ú
            ([ "type":"obj", "id":61, "amount":1, "p1":35, "p2":100 ]),  // ¾ð¥Ö
            ([ "type":"obj", "id":70, "amount":1, "p1":20, "p2":100 ]),  // ¾ð¯×
            ([ "type":"obj", "id":73, "amount":1, "p1":100, "p2":100 ]), // ¬õ¦â¾ð²G
        }) );
    } else
    if( i >= 16 && i <= 34 ) {
        set("set_drop", ({
            ([ "type":"obj", "id":66, "amount":1, "p1":50, "p2":100 ]),  // ¾ð®Ú
            ([ "type":"obj", "id":61, "amount":1, "p1":35, "p2":100 ]),  // ¾ð¥Ö
            ([ "type":"obj", "id":70, "amount":1, "p1":20, "p2":100 ]),  // ¾ð¯×
            ([ "type":"obj", "id":72, "amount":1, "p1":100, "p2":100 ]), // µµ¦â¾ð²G
        }) );
    } else
    if( i >= 35 && i <= 94 ) {
        set("set_drop", ({
            ([ "type":"obj", "id":66, "amount":1, "p1":50, "p2":100 ]),  // ¾ð®Ú
            ([ "type":"obj", "id":61, "amount":1, "p1":35, "p2":100 ]),  // ¾ð¥Ö
            ([ "type":"obj", "id":70, "amount":1, "p1":20, "p2":100 ]),  // ¾ð¯×
            ([ "type":"obj", "id":71, "amount":1, "p1":100, "p2":100 ]), // ºñ¦â¾ð²G
        }) );
    } else {
        set("set_drop", ({
            ([ "type":"obj", "id":66, "amount":1, "p1":50, "p2":100 ]),  // ¾ð®Ú
            ([ "type":"obj", "id":61, "amount":1, "p1":35, "p2":100 ]),  // ¾ð¥Ö
            ([ "type":"obj", "id":70, "amount":1, "p1":20, "p2":100 ]),  // ¾ð¯×
            ([ "type":"obj", "id":74, "amount":1, "p1":100, "p2":100 ]), // ¶Àª÷¾ð²G
        }) );
    }
    setup();
}
