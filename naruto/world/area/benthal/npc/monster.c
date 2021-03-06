#include <npc.h>
#include <ansi.h>

string *name1 = ({ "赫拉", "安多", "拉滋", "伊瓦", "亞修", "迪安",
                   "海", "伊萊", "諾拉", "尼斯", "深海", "沙地", "石像", });

string *name2 = ({ "鐵斯", "拿普", "安格烈夫", "薩卡", "賽巴", "傑魯",
                   "獸", "克頓", "哈姆", "水怪", "牛", "巨蟹", "海魚", });

void create()
{
    set_name( name1[random(sizeof(name1))] + name2[random(sizeof(name2))], ({ "monster" }) );
    set_race("beast");
    set("title", HIC"中型海王類"NOR);
    set_level(55);
    set("age", 100 + random(5000));

    set("long", @LONG
躲在海草堆的沙地中休息的中型海王類，因為體型很大身上常常會留
有一些可供魚蝦等其他海洋生物食用的殘渣，因此捕捉海產的人可能
會一不小心就將這種沙地海王類給吵醒。不過牠們是比較和善的海王
類，不會主動攻擊一般人。
LONG);

    set("limbs", ({ "頭部", "身體", "魚肚", "魚鰭", "魚尾", "背部", "鼻毛", "寄生魚" }) );
    set("verbs", ({ "bite" }) );

    set("chat_chance", 5);
    set("chat_msg", ({
        CYN+this_object()->query("name")+"發出惱人的怪叫...「嗷唬..吼..」\n"NOR,
    }) );

    set("set_drop", ({
          ([ "type":"eq", "id":106, "amount":1, "p1":5, "p2":100 ]),  // 海洋之心
    }) );
    setup();
    call_out("die_1", random(300)+300, this_object());
    add_temp("apply/attack", 100);
    add_temp("apply/intimidate", 100);
    add_temp("apply/wittiness", 100);
}
void die_1()
{
    message_vision(CYN"$N發出低沉的叫聲，又躲回沙中繼續休息了。\n"NOR, this_object());
    destruct(this_object());
    return;
}
void die()
{
    object enemy, killer;
    int i;
    string msg;

    enemy = this_object()->last_damage_giver();
    i = 1 + random(3);

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
    msg = "\n\n"HIC+this_object()->query("name")+"難過的翻起大海，四周的船隻都受到影響！\n\n"NOR;
    msg += HIR"【社會新聞】"+this_object()->query("name")+"("+this_object()->query("id")+")死於"+enemy->rank()+enemy->query("name")+"("+enemy->query("id")+")之手了！\n\n"NOR;

    killer->add("exchange", i);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死"+this_object()->query("name")+"獲得了 "+i+" 點兌換點數。)\n"NOR);
    ::die();
    return;
}