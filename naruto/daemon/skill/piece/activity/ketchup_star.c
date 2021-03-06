#include <ansi.h>
#define SKILL_NAME "ketchup star"
#define SKILL_NAME_C "蕃茄醬星"
#define SKILL_CLASS "activity"

inherit SKILL;

void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon(SKILL_NAME);
}

string query_class() { return SKILL_CLASS; }

void skill_advanced(object me, string skill)
{
    int lv = me->query_skill(skill, 1);
    switch( lv ) {
        case 189: me->set_skill_require(skill, 1500000); break; // 關卡3 : 189升190
        case 149: me->set_skill_require(skill, 1000000); break; // 關卡2 : 149升150
        case  99: me->set_skill_require(skill, 500000);  break; // 關卡1 :  99升100
        default:  me->set_skill_require(skill, lv*lv*5); break;
    }
}

// 檢查是否能使用技能
int isCast(object me, string act, int sk)
{
    if( !objectp(me) ) return 0;

    if( !me->is_fighting() ) {
        tell_object(me, "沒事不要亂裝死。\n");
        return 0;
    }

    if( me->is_busy() ) {
        tell_object(me, "你動彈不得沒辦法裝死。\n");
        return 0;
    }

    if( act != "die" ) {
        tell_object(me, "目前" + SKILL_NAME_C + "只有 die 這個功\能。\n");
        return 0;
    }

    if( me->query_skill("activity", 1) < 50 || sk < 50 ) {
        tell_object(me, "你的能力不足以使用這一招。\n");
        return 0;
    }

    if( me->query_stat("mp") < sk/2 ) {
        tell_object(me, "你的狀態無法使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    return 1;
}

void do_perform(object me, int sk)
{
    write("你使出絕學『"HIR+SKILL_NAME_C+NOR"』開始倒在地上裝死。\n\n");
    message_vision(HIR"$N「阿」的慘叫一聲，身體噴出大量鮮血，最後失血過多倒在地上。\n"NOR, me);
    if( sk/4 > random(100) ) {
        message_vision("$n見$N已經死去，便罷手不鬥了。\n"NOR, me, me->query_opponent());
        me->remove_all_killer();
    } else {
        message_vision("結果一隻蒼蠅飛到$N的鼻頭讓$N打了個大噴涕，原來是在裝死！\n"NOR, me);
        me->start_busy(5);
    }
    me->damage_stat("mp", 10, me);
    me->improve_skill(SKILL_NAME, 1);
    return;
}
int perform_action(object me, string act)
{
    int sk;

    sk = me->query_skill(SKILL_NAME, 1);

    if( !objectp(me) ) return 0;

    // 檢查是否能使用技能
    if( !isCast(me, act, sk) ) return 1;

    do_perform(me, sk);
    return 1;
}