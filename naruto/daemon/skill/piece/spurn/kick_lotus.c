#include <ansi.h>
#define SKILL_NAME "kick lotus"
#define SKILL_NAME_C "嵐腳•蓮華"
#define SKILL_CLASS "spurn"

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

int exact(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/10;
}

// 檢查是否能使用技能
int isCast(object me, string act, object target, int sk)
{
    if( !objectp(me) || !objectp(target) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( act != "kick" ) {
        tell_object(me, "目前" + SKILL_NAME_C + "只有 kick 功\能。\n");
        return 0;
    }

    if( !me->is_fighting(target) ) {
        tell_object(me, "你並未和對方在戰鬥中...\n");
        return 0;
    }

    if( me->query_condition("lotus_cd") ) {
        tell_object(me, "你感覺詩意不夠濃厚，不想出招。\n");
        return 0;
    }

    if( me->query_skill("spurn", 1) < 50 || sk < 60 ) {
        tell_object(me, "你的能力不足以使用這一招。\n");
        return 0;
    }

    if( me->query_stat("mp") < 50 ) {
        tell_object(me, "你身體狀況不佳，不能使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    return 1;
}

// 命中部份(1)
int attackHit(object me, object target)
{
    int i, j;

    i = COMBAT_D->intimidate(me, 1)*1.8;
    j = COMBAT_D->wittiness(target, 1)*1.5;

    if( COMBAT_D->SkillHit(me, target, i, j) ) return 1;
    else return 0;
}

// 命中部份(2)
int buffHit(object me, object target)
{
    int i, j;

    i = COMBAT_D->intimidate(me, 1)*2 + COMBAT_D->exact(me, target, 1)/2;
    j = COMBAT_D->wittiness(target, 1) + COMBAT_D->evade(target, me, 1);

    if( COMBAT_D->SkillHit(me, target, i, j) ) return 1;
    else return 0;
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    int damage, raiseDamage;
    object wp;

    raiseDamage = sk;

    me->add_temp("apply/attack", raiseDamage);

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    me->add_temp("apply/attack", -raiseDamage);

    return damage;
}

// 技能使用後 
void setEffect(object me, int sk, int hit)
{
    mapping cnd = ([]);

    if( !hit ) {
        me->damage_stat("mp", 15, me);
    } else {
        me->damage_stat("mp", 30, me);
    }
    cnd["name"] = HIM+"(CD)蓮花"+NOR;
    cnd["duration"] = 6;

    me->set_condition("lotus_cd", cnd);
    me->start_busy(1);
    me->improve_skill(SKILL_NAME, 1);
}

int perform_action(object me, string act, object target)
{
    int damage, sk, hit;
    mapping cnd = ([]);

    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, target, sk) ) return 1;

    message_vision("\n$N左腳劃出一些斬擊，右腳忽然踢出嵐腳將斬擊捲起，型成一朵"HIW"『"HIM"嵐腳•蓮華"HIW"』"NOR"飛向$n。\n", me, target);

    hit = attackHit(me, target);

    if( !hit ) {
        message_vision("$N反踢一腳瞬間將蓮花踢成破碎花瓣四散...\n\n", target);
    } else {
        damage = getDamage(me, target, sk);
        target->receive_damage(damage, me);
        message_vision( sprintf("蓮花斬擊擊中了$n，衝散的花瓣在空中形成一遍美景(%d) %s\n\n", damage, COMBAT_D->report_status(target) ), me, target);
        if( sk > 70 && target->query_condition("firelotus", 1) == 0) {
            message_vision("$N忽然大喊"HIM"「春•情•吟」"NOR"手上武器一揮使出"HIR"『獅子樺蕪』"NOR"一顆大火球砸向$n！\n", me, target);
            if( !buffHit(me, target) ) {
                message_vision("但是火球的方向打偏了，只在地上爆出一陣火花。\n\n", target);
            } else {
                message_vision("火球擊中空中的花瓣，連鎖效應將$n的四周燒成一片火海。\n\n", me, target);

                cnd["name"] = HIM+"蓮花火海"+NOR;
                cnd["duration"] = sk/20;
                cnd["from"] = me;

                target->set_condition("firelotus", cnd);
            }
        }
    }
    setEffect(me, sk, hit);
    return 1;
}
