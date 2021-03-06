// forst_closed_ball.c 變化系 lv2 - 冰封球
// 2006/06/04 -Tmr
// 新增特殊技能 by mouse 2007/7/25

#include <ansi.h>
#define SKILL_NAME   "frost closed ball"
#define SKILL_NAME_C "冰封球"
#define SKILL_CLASS  "variation"

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

/*
|       技能影響：
|                技能： 0------50------100------150---175---200
|            冰住時間：     1               2            3
|            傷害系數： 100% -----------------------------> 300%
|
*/

/*
|       修改後的技能影響 2007/7/25
|       擊中後判定hit數，達到條件後造成狀態值，狀態為0時產生傷害
|
|       技能：0------------------100--------------150----------200
|       時間：sk*2                sk/5             sk/20
*/       

// 檢查是否能使用技能
int isCast(object me, string act, object target, int sk)
{
    if( !objectp(me) || !objectp(target) ) return 0;

    if( act != "ball" ) {
        tell_object(me, SKILL_NAME_C + "目前只有 ball 功\能。\n");
        return 0;
    }

    if( me->is_busy() ) {
        tell_object(me, "你正忙著，沒有空使用這個技能。\n");
        return 0;
    }

    if( target->is_busy() && target->query_condition("iceball") != 0 ) {
        tell_object(me, "對方已經不能動了，不需要再用冰封球去阻止行動。\n");
        return 0;
    }

    if( !me->is_fighting(target) ) {
        tell_object(me, "你並未和對方在戰鬥中...\n");
        return 0;
    }

    if( me->query_skill("variation", 1) < 50 ) {
        tell_object(me, "你的變化系程度還沒達到 50 級，無法使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_skill("ice variation", 1) < 80 ) {
        tell_object(me, "你的冰念力變化還沒達到 80 級，無法使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_stat("mp") < 100 ) {
        tell_object(me, "你的念能力不足 100 點。\n");
        return 0;
    }

    if( me->query_condition("iceball_cd") ) {
        tell_object(me, "你目前還無法使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    return 1;
}

int get_times(int lv)
{
    if( lv <= 100 ) return 1;
    if( lv <= 150 ) return 2;
    return 3;
}

int get_bonus(int lv)
{
    if(lv < 1 ) return 100;
    return lv + 100;
}

int ice_time(int sk)
{
    if( sk < 100 ) return sk/2;
    else if( sk < 150 ) return sk/10;
    else return sk/20;
}

// 取得傷害
int getDamage(object me, object target, int sk, int bonus)
{
    int raiseDamage, damage;
    object wp;

    raiseDamage = sk*3 + bonus*2 + me->query_skill("ice variation")*2;

    me->add_temp("apply/attack", raiseDamage);

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    me->add_temp("apply/attack", -raiseDamage);

    damage = damage/4;
    return damage;
}

void do_attack(object me, object target, int sk)
{
    int bonus, hit, times, icetime, damage;
    mapping cnd = ([]);

    times = get_times(sk);
    bonus = get_bonus(me->query_skill("variation"));
    icetime = ice_time(sk);

    // 命中率
    hit = COMBAT_D->isHit(me, target);

    // 傷害計算
    damage = getDamage(me, target, sk, bonus);

    if( hit ) {
        // 傷害盾吸收
        damage = COMBAT_D->receive_damage(target, me, damage);

        target->receive_damage(damage, me);
        message_vision( sprintf(HIB"\t$n"HIB"被冰封球擊個正著，猶如置身冰窖，$n"HIB"全身上下都慢慢凝結成冰了..."NOR"(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);

        cnd["name"] = HIB+"冰封球"+NOR;
        cnd["duration"] = icetime;
        cnd["from"] = me;
        cnd["damage"] = damage*4;

        // 已經冰到就不冰了，避免 buff 一直存在
        if( target->query_condition("iceball") == 0 ) target->set_condition("iceball", cnd);

        // 定人部份
        target->start_busy(times);
    } else {
        // 傷害再減弱
        damage = damage/4;

        // 傷害盾吸收
        damage = COMBAT_D->receive_damage(target, me, damage);

        target->receive_damage(damage, me);
        message_vision( sprintf(HIB"\t$n"HIB"被冰封球擴散的餘威擊中，身子打了個冷顫"NOR"(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);
    }

    cnd["name"] = HIB+"(CD)冰球"+NOR;
    cnd["duration"] = 10;

    // 不管是否擊中都應該有cd
    me->set_condition("iceball_cd", cnd);
}

void do_shoot(object me, object target, int sk)
{
    message_vision(HIW"一粒由無數冰錐組成的"HIC"冰封球"HIW"從$N手中出現，咻地一聲就往$n"HIW"擲去！！！\n"NOR, me, target);
    do_attack(me, target, sk);
    me->damage_stat("mp", 50, me);
}

// 使用絕招
int perform_action(object me, string act, object target)
{
    int sk;

    sk = me->query_skill(SKILL_NAME, 1);

    if( !isCast(me, act, target, sk) ) return 1;

    do_shoot(me, target, sk);
    me->improve_skill( SKILL_NAME, 1);
    me->start_busy(2);

    return 1;
}
