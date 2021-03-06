#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;

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
    this_object()->damage_stat("mp", 15, this_object());
    message_vision("\n$N"HIW"拿起長槍一抖，如靈蛇般的戳向"NOR"$n"HIW"四肢關節處！\n"NOR, this_object(), enemy);
    if( !COMBAT_D->isHit(this_object(), enemy) ) {
        message_vision("長槍就像蓄勢待發的蛇，「呼」地一聲撲向空氣...\n\n", this_object(), enemy);
        this_object()->start_busy(1);
        return;
    }
    raiseDamage = 800;

    add_temp("apply/attack", raiseDamage); 
    damage = COMBAT_D->isDamage(this_object(), enemy, query_temp("weapon/twohanded"));
    add_temp("apply/attack", -raiseDamage);

    if( damage < 400 ) damage = 250 + random(150);

    enemy->receive_damage(damage, this_object());
    message_vision( sprintf("長槍就像蓄勢待發的蛇，「呼」地一聲咬住了$n，刺出了一個拳頭大的血洞(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
    enemy->start_busy(1);
    return;
}
void create()
{
    set_name("蛇皇", ({ "snake king", "snake", "king" }) );
    set_race("human");
    set("gender", "male");
    set("camp", "snaker");
    set_level(45);
    set("age", 35);
    set("limbs", ({ "蛇頭", "蛇尾", "腹部", "胸口", "腳部", "肩膀", "腰部" }) );
    set("title",HIW"蛇族皇帝"NOR);
    set("long", "身穿一件長披風，手上拿著一把白色的長槍，看起來很威風。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: command, "say 蛇族是最偉大的種族！" :),
        (: command, "nomatch" :),
        (: command, "say 總有一天天下會以蛇族為尊！" :),
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"eq", "id":87, "amount":1, "p1":5, "p2":100 ]),     // 蛇神項鍊
        ([ "type":"wp", "id":47, "amount":1, "p1":1, "p2":800 ]),     // 白皇蛇槍
        ([ "type":"wp", "id":49, "amount":1, "p1":15, "p2":100 ]),    // 彎刀
        ([ "type":"wp", "id":48, "amount":1, "p1":20, "p2":100 ]),    // 盾劍
        ([ "type":"food", "id":30, "amount":1, "p1":35, "p2":100 ]),  // 蛇膽
        ([ "type":"obj", "id":24, "amount":1, "p1":35, "p2":100 ]),   // 蛇皮
        ([ "type":"wp", "id":14, "amount":1, "p1":30, "p2":100 ]),    // 蛇牙
        ([ "type":"obj", "id":82, "amount":1, "p1":20, "p2":100 ]),   // 蛇毒
    }) );
    setup();
    carry_object(_DIR_AREA_"thorn_pine/npc/wp/soft_lance.c")->wield("twohanded");
}
void die()
{
    object enemy, killer;
    string msg;

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
    // 寵物殺死算主人的
    if( !userp(enemy) && objectp(enemy->query_owner()) ) {
        killer = enemy->query_owner();
    } else {
        killer = enemy;
    }
    msg = "\n\n\t"NOR+this_object()->query("name")+HIW"臨死前大喊道：人類真是潛能無限的生物！我失算了！\n"NOR;
    msg += HIR"\n\t不論是竹取一族或是"+enemy->query("name")+"！！蛇族都不會放過你們的！\n"NOR;
    msg += HIW"\n\t蛇人族之皇被"HIR+enemy->query("name")+HIW"殺死了！蛇人們哀傷萬分...\n\n\n"NOR;

    killer->add("exchange", 1);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死"+this_object()->query("name")+"獲得了 1 點兌換點數。)\n"NOR);
    ::die();
    return;
}