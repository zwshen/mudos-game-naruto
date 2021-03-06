inherit ITEM;
#include <ansi.h>

int i;

string report_status(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$n" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$n" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$n" + HIR + ratio + "%" + HIK"]\n"NOR;
}
string report_statusa(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$N" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$N" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$N" + HIR + ratio + "%" + HIK"]\n"NOR;
}

void create()
{
    set_name(HIW"風險骰子"NOR, ({ "dice"}));
    set_weight(1);
    if( !clonep() ) {
        set("unit", "粒");
        set("value", 0);
        set("long","可以用 roll 擲骰子，不過會發生什麼事呢...\n");
    }
    setup();
}
void init()
{
        add_action("do_roll", ({ "roll", "throw" }));
}
int do_roll(string arg)
{
    object me;
    me = this_player();
    if( !id(arg) ) return 0;
    if( me->query_temp("quest/rolldice") == 1) {
    return notify_fail(CYN"已經在使用中了。"NOR"\n");
    }
    if( this_player()->is_busy()) {
        write(CYN"忙碌中，沒空丟骰子。"NOR"\n");
        return 1;
    }
    if( !this_player()->is_fighting() ) {
        write(CYN"沒有戰鬥不可使用風險骰子。"NOR"\n");
        return 1;
    }
    i = random(101);
    me->add_temp("quest/rolldice", 1);
    if( i >= 95) {
        message_vision("$N拿出骰子一擲，骰子滾了滾停下來，結果是"YEL"大吉"NOR"！\n", me);
        call_out("risks_1",5,me);
        return 1;
    } else
    if( i < 95 && i >= 81) {
        message_vision("$N拿出骰子一擲，骰子滾了滾停下來，結果是"HIY"吉"NOR"！\n", me);
        call_out("risks_1",5,me);
        return 1;
    } else
    if( i < 81 && i >= 61) {
        message_vision("$N拿出骰子一擲，骰子滾了滾停下來，結果是"HIW"小吉"NOR"！\n", me);
        call_out("risks_1",5,me);
        return 1;
    } else
    if( i < 61 && i >= 40) {
        message_vision("$N拿出骰子一擲，骰子滾了滾停下來，結果是"WHT"中"NOR"！\n", me);
        message_vision(HIW"只見「砰！」地一陣煙霧竄起，但沒發生任何事情。\n"NOR, me);
        me->delete_temp("quest/rolldice");
        destruct(this_object());
        return 1;
    } else
    if( i < 40 && i >= 20) {
        message_vision("$N拿出骰子一擲，骰子滾了滾停下來，結果是"HIM"小兇"NOR"！\n", me);
        call_out("risks_1",5,me);
        return 1;
    } else
    if( i < 20 && i >= 6) {
        message_vision("$N拿出骰子一擲，骰子滾了滾停下來，結果是"HIR"兇"NOR"！\n", me);
        call_out("risks_1",5,me);
        return 1;
    } else
    if( i < 6) {
        message_vision("$N拿出骰子一擲，骰子滾了滾停下來，結果是"RED"大兇"NOR"！\n", me);
        message_vision(HIR"「碰！」地一聲，一位"HIK"死神"HIR"憑空出現，隨手拿起鐮刀朝$N一劈！\n"NOR, me);
        me->delete_temp("quest/rolldice");
        me->unconcious();
        destruct(this_object());
        return 1;
    }
    return 1;
}
void risks_1()
{
    int damage;
    object enemy, me;
    me = this_player();
    enemy = me->query_opponent();
    me->delete_temp("quest/rolldice");
    if( i < 40 && i >= 20) {
        message_vision("只見一陣煙霧中出現"HIK"妖怪"NOR"的身影，朝$N用力一爪！\n", me);
        damage = me->query_ability("attack");
        me->damage_stat("hp", damage, me);
        message_vision("        $N「刷！」地一聲，身上被劃出數到血痕！("+damage+")"+report_statusa(me)+"", me);
        destruct(this_object());
        return;
    } else
    if( i < 20 && i >= 6) {
        message_vision("只見一陣煙霧中出現"HIR"魔龍"NOR"的身影，朝$N用力一爪！\n"NOR, me, enemy);
        damage = me->query_ability("attack")*3;
        me->damage_stat("hp", damage, me);
        message_vision("        $N胸前鮮血狂噴，向後飛跌了出去！("+damage+")"+report_statusa(me)+"", me);
        destruct(this_object());
        return;
    }
    if( !enemy ) {
        destruct(this_object());
        return;
    }
    // 敵人在不同位置
    if( environment(me)->is_area() ) {
        if( !area_environment(me, enemy) ) {
            destruct(this_object());
            return;
        }
    } else {
        if( environment(enemy) != environment(me) ) {
            destruct(this_object());
            return;
        }
    }
    if( i >= 95) {
        message_vision("只見一陣煙霧中出現"HIG"幽助"NOR"的身影，朝$N發出"HIC"靈丸"NOR"！\n", enemy);
        damage = me->query_ability("attack")*5;
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        $n被"HIC"靈丸"NOR"轟個老遠，受了重傷站不起來！("+damage+")"+report_status(enemy)+"", me, enemy);
        destruct(this_object());
        return;
    } else
    if( i < 95 && i >= 81) {
        message_vision("只見一陣煙霧中出現"HIW"桑原"NOR"的身影，拔出"YEL"靈劍"NOR"朝$N用力一劈！\n", enemy);
        damage = me->query_ability("attack")*2;
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        $n被劃出一道口子，鮮血直流！("+damage+")"+report_status(enemy)+"", me, enemy);
        destruct(this_object());
        return;
    } else
    if( i < 81 && i >= 60) {
        message_vision("只見一陣煙霧中出現$N的身影，朝$n用力一拳！\n", me, enemy);
        damage = me->query_ability("attack");
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        $n被一拳打中退了幾步，嘴角流出鮮血！("+damage+")"+report_status(enemy)+"", me, enemy);
        destruct(this_object());
        return;
    }
    return notify_fail("使用失敗。\n");
}
