#include <npc.h>
#include <ansi.h>

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
    // 沒有敵人
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    message_vision("$N"CYN"汪汪叫了幾聲，從嘴裡伸出一把"HIY"來福槍"NOR+CYN"對準"NOR"$n"CYN"一槍轟去！\n"NOR, this_object(), enemy);
    damage = this_object()->query_ability("attack");
    damage += random(50);
    if( random(enemy->query_ability("evade")) > 100) {
        message_vision("        $n快速從一旁避開！(0)"+report_status(enemy)+"", this_object(), enemy);
        this_object()->start_busy(3);
        return;
    }
    enemy->damage_stat("hp", damage, enemy);
    message_vision("        $n被子彈打中，好像受了點傷！("+damage+")"+report_status(enemy)+"", this_object(), enemy);
    enemy->start_busy(2);
    return;
}
void do_drop()
{
    object enemy;
    // 沒有敵人
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    message_vision("$N"HIR"趴了下來，背上打開機關，慢慢從裡面出現一顆小型飛彈！\n"NOR, this_object(), enemy);
    this_object()->start_busy(5);
    call_out("drop_1",10,this_object(),enemy);
}
void drop_1()
{
    int damage;
    object enemy;
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    damage = 100 + random(300);
    message_vision(HIG"「目標校正」"HIR"飛彈呼！的一聲朝"NOR"$n"HIR"疾射而去！\n"NOR, this_object(), enemy);
    if( random(enemy->query_ability("evade")) > 200) {
        message_vision("        「轟隆」一聲巨響，$n離開了爆炸範圍！(0)"+report_status(enemy)+"\n"NOR, this_object(), enemy);
        enemy->start_busy(3);
        return;
    }
    enemy->damage_stat("hp", damage, enemy);
    message_vision("        「轟隆」一聲巨響，$n被炸成焦炭了！("+damage+")"+report_status(enemy)+"", this_object(), enemy);
    enemy->start_busy(6);
    return;
}
void create()
{
    set_name("來福", ({ "rifle", "dog" }));
    set_race("beast");
    set_level(40);
    set("title",HIY"大家的狗"NOR);
    set("age", 10);
    set("long", "你好阿來福∼一隻機器狗與木葉村的故事。\n");
    set("limbs", ({ "狗頭", "身體", "腹部", "狗腿", "尾巴", "耳朵" }) );
    set("verbs", ({ "bite" }) );
    set("chat_chance", 5);
    set("chat_msg", ({
        (: command, "dog" :),
    }) );
    // 戰鬥動作
    set("chat_chance_combat", 20);
    set("chat_msg_combat", ({
        (: do_fight :),
        (: do_fight :),
        (: do_fight :),
        (: do_drop :),
    }) );
    setup();
    add_temp("apply", (["hp":7799, "attack":-100 ]) );
    do_heal();
}
int give_check(object ob)
{
    if( ob->id("_BOW_LU_") ) return 1;           // 寶路
    else return 0;
}
int accept_object(object me, object ob)
{
    object item;
    if( is_busy() ) {
        do_chat((: command, "say 我正忙著。" :));
        return 0;
    }
    if( is_fighting() ) {
        do_chat((: command, "say 戰鬥中。" :));
        return 0;
    }
    me->start_busy(1);
    this_object()->start_busy(1);
    switch( give_check(ob) ) {
        case 1:
            if( ob->query_amount() > 1 ) {
                return 0;
            }
            do_chat(({
               (: command, "dog" :),
               (: command, "follow " + this_player()->query("id") :),
               (: command, "guard " + this_player()->query("id") :),
            }));
            break;
        default:
            do_chat((: command, "dog" :));
            return 0;
            break;
    }
    return 1;
}
