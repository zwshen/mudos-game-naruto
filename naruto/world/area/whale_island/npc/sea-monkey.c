#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("海猴", ({ "sea monkey", "monkey" }) );
    set_race("beast");
    set("title", HIC"小型海王類" NOR);
    set_level(45);
    set("age", 150);
    set("long", @long
一隻長的比抹香鯨還大的海猴，正在不停地玩弄海水，都快要到引起
海嘯的程度了。想要攻擊牠，似乎不是一般人能做到的事。
long
);
    set("limbs", ({ "猴頭", "身體", "肚子", "猴臂", "魚尾巴", "猴背", "猴腿" }) );
    set("verbs", ({ "bite" }) );
    set("set_drop", ({
          ([ "type":"wp", "id":25, "amount":1, "p1":1, "p2":800 ]),  // 香蕉
    }) );
    setup();
    add_temp("apply/attack", 40);
    set_skill("combat", 150);
    set_skill("dodge", 150);
    set_skill("parry", 150);
    set_skill("savage hit", 150);
    set_skill("heavy hit", 150);
    set_skill("continual hit", 150);
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
    msg = "\n\n\t"HIC"當"+this_object()->query("name")+"倒下時，鯨魚島島民歡呼聲四起∼∼∼\n"NOR;
    msg += HIW"\n鯨魚島村長當眾宣佈："+enemy->query("name")+"("+enemy->query("id")+")為我鯨魚島民除盡一害！真是大快人心！\n\n"NOR;

    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    if( random(100) < 26 ) {
        killer->add("exchange", 1);
        tell_object(killer, HIY"(因為你殺死"+this_object()->query("name")+"獲得了 1 點兌換點數。)\n"NOR);
    }
    ::die();
    return;
}