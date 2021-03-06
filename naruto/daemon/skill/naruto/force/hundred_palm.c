/* 重新開放 & 修改傷害公式 by mouse 2007/8/14 */

#include <ansi.h>
#define SKILL_NAME "hundred palm"
#define SKILL_NAME_C "百烈掌"
#define SKILL_CLASS "force"

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

// 攻擊力量影響
int attack(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/5;
}

// 檢查是否能使用技能
int isCast(object me, string act, object target, int sk)
{
    if( !objectp(me) || !objectp(target) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( act != "attack" ) {
        tell_object(me, "目前" + SKILL_NAME_C + "只有 attack 功\能。\n");
        return 0;
    }

    if( !me->is_fighting(target) ) {
        tell_object(me, "你並未和對方在戰鬥中...\n");
        return 0;
    }

    if( me->query_condition("hundred_cd") ) {
        tell_object(me, "你似乎還無法靈活地正常使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( sk < 30 || me->query_skill("force") < 20 ) {
        tell_object(me, "你的能力不足以使用這一招。\n");
        return 0;
    }

    if( me->query_stat("mp") < sk/4 ) {
        tell_object(me, "你身體狀況不佳，不能使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    return 1;
}

// 計算是否命中
int isHit(object me, object target)
{
    int i, j;

    i = COMBAT_D->intimidate(me, 1)*2;
    j = COMBAT_D->wittiness(target, 1) + COMBAT_D->evade(target, me, 1)/2;

    if( COMBAT_D->SkillHit(me, target, i, j) ) return 1;
    else return 0;
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    object wp;
    int damage, raiseDamage, white, str;

    white = me->query_skill("white eyes", 1);

    if( me->query_condition("white_eyes") && white > 70 ) {
        if( me->query_attr("str") > 300 ) str = 600;
        else str = me->query_attr("str")*2;
    } else {
        if( me->query_attr("str") > 300 ) str = 300;
        else str = me->query_attr("str");
    }
    raiseDamage = str + sk*3 + me->query_skill("force");

    me->add_temp("apply/attack", raiseDamage);

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    me->add_temp("apply/attack", -raiseDamage);

    return damage;
}

// 技能使用後 
void setEffect(object me, int sk)
{
    mapping cnd = ([]);

    cnd["name"] = HIW+"(CD)百烈"+NOR;
    cnd["duration"] = 5;

    me->set_condition("hundred_cd", cnd);
    me->damage_stat("mp", sk/6, me);
    me->improve_skill(SKILL_NAME, 1);
}

// 手動攻擊
int perform_action(object me, string act, object target)
{
    int damage, sk, hit;

    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, target, sk) ) return 1;

    // 是否命中
    hit = isHit(me, target);

    message_vision("\n$N將查克拉團聚於右掌中，一招"HIW"『"HIC + SKILL_NAME_C + HIW"』"NOR"對著$n狠狠擊落...\n", me, target);
    if( hit ) {
        damage = getDamage(me, target, sk);

        // 傷害盾吸收
        damage = COMBAT_D->receive_damage(target, me, damage);

        target->receive_damage(damage, me);
        message_vision( sprintf("$n閃避不及，硬生生中了這招飛跌了數尺...(%d) %s\n\n", damage, report_status(target) ), me, target);
        me->start_busy(1);
    } else {
        message_vision("$N有險無驚的閃過了這一招...\n\n", target);
        me->start_busy(3);
    }
    setEffect(me, sk);
    return 1;
}
