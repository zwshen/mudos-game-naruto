#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

string *name1 = ({ "威古力", "善醇", "酉露安", "運功\閃", "行氣閃", "麵速立打母",
                   "雞肋", "阿蓋\", "司思", "諾德", "貼利康", "悠呦", "異可伕", });

void do_exit()
{
    if( environment(this_object())->query("SAND_WAR") == 1 ) {
        do_chat((: random_move :));
    } else {
        message_vision("$N收到了沙穴回召的命令，開始撤退了。\n"NOR, this_object());
        destruct(this_object());
    }
    return;
}
void do_fight()
{
    if( this_object()->query_stat("hp") < query_stat_maximum("hp")/2 ) {
        message_vision("$N"HIW"用精湛的手法為自己療傷，只見$N身上的傷口快速回復中...\n"NOR, this_object());
        this_object()->heal_stat("hp", query_stat_maximum("hp")/5);
        this_object()->heal_stat("ap", query_stat_maximum("ap")/5);
        this_object()->heal_stat("mp", query_stat_maximum("mp")/5);
        this_object()->start_busy(1);
    }
    return;
}
void create()
{
    set_name(name1[random(sizeof(name1))], ({ "doctor" }) );
    set_level(40);
    set_race("human");
    if( random(2) == 1) {
        set("gender", "male");
    } else {
        set("gender", "female");
    }
    set("chat_chance", 20);
    set("chat_msg", ({
        (: do_exit :),
    }));
    set("chat_chance_combat", 20);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("age", 15+random(41));
    set("title",YEL"沙穴密醫"NOR);
    set("long", "臉上帶著口罩，頭上帶著手術用的帽子，看起來像哪裡的外科醫生。\n");
    set("set_drop", ({
        ([ "type":"wp", "id":27, "amount":1, "p1":1, "p2":300 ]),       // 手術刀
        ([ "type":"eq", "id":111, "amount":1, "p1":1, "p2":300 ]),      // 威骨力
        ([ "type":"eq", "id":36, "amount":1, "p1":1, "p2":150 ]),       // 阿蓋
        ([ "type":"obj", "id":58, "amount":1, "p1":10, "p2":100 ]),     // 精神急救
        ([ "type":"obj", "id":65, "amount":1, "p1":10, "p2":100 ]),     // 體力急救
        ([ "type":"obj", "id":66, "amount":1, "p1":10, "p2":100 ]),     // 念查急救
    }) );
    setup();
    carry_object("/world/wp/scalpel.c")->wield("righthand");
    add_temp("apply/evade", 200);
}
void die()
{
    object enemy, room, killer;
    int i;

    enemy = this_object()->last_damage_giver();
    room = load_object(query("SAND_KILL"));
    i = random(2);

    if( !enemy ) {
        room->delete("SAND_HOLE");
        ::die();
        return;
    }
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) {
            room->delete("SAND_HOLE");
            ::die();
            return;
        } else
        if( environment(enemy) != environment(this_object()) ) {
            room->delete("SAND_HOLE");
            ::die();
            return;
        }
    }
    // 寵物殺死算主人的
    if( !userp(enemy) && objectp(enemy->query_owner()) ) {
        killer = enemy->query_owner();
    } else {
        killer = enemy;
    }
    killer->add("exchange", i);
    message("system", "\n\n"HIW+this_object()->query("name")+"說道："+enemy->query("name")+"這傢伙下手太狠了！兄弟們快撤退阿！\n\n"NOR, users());
    if( i != 0 ) tell_object(killer, HIY"(因為你殺死"+this_object()->query("name")+"獲得了 "+i+" 點兌換點數。)\n"NOR);
    WAR_D->doEndWar(this_object(), "/world/war/sand_hole.c");
    ::die();
    return;
}
