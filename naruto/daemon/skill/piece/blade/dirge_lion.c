#include <ansi.h>
#define SKILL_NAME "dirge lion"
#define SKILL_NAME_C "獅子輓歌"
#define SKILL_CLASS "blade"

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

    if( !me->query_temp("weapon/righthand") && !me->query_temp("weapon/lefthand") && !me->query_temp("weapon/twohanded")) {
        tell_object(me, "這是一刀流技能，必須拿一把武器才能使用。\n");
        return 0;
    }

    if( me->query_condition("lion_cd") ) {
        tell_object(me, "目前心神無法專注。\n");
        return 0;
    }

    if( me->query_skill("blade", 1) < 200 || sk < 60 ) {
        tell_object(me, "你的能力不足以使用這一招。\n");
        return 0;
    }

    if( me->query_stat("mp") < sk/3 ) {
        tell_object(me, "你身體狀況不佳，不能使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    return 1;
}

// 計算是否命中
int isHit(object me, object target)
{
    int i, j;

    i = COMBAT_D->intimidate(me, 1)*1.5;
    j = COMBAT_D->wittiness(target, 1);

    if( COMBAT_D->SkillHit(me, target, i, j) ) return 1;
    else return 0;
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    int damage, raiseDamage;
    object wp;

    raiseDamage = sk*5 + me->query_skill("savage hit")*2 + me->query_skill("blade");

    if( me->query_attr("str") < 300 ) raiseDamage += me->query_attr("str")*5;
    else raiseDamage += 1500;

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
        me->start_busy(3);
    } else {
        me->start_busy(1);
    }
    cnd["name"] = YEL+"(CD)獅子"+NOR;
    cnd["duration"] = 10;

    me->set_condition("lion_cd", cnd);
    me->damage_stat("mp", sk/3, me);
    me->improve_skill(SKILL_NAME, 1);
}

int perform_action(object me, string act, object target)
{
    int damage, sk, hit;

    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, target, sk) ) return 1;

    message_vision("\n$N"HIW"深深吸了一口氣，閉目將刀還入鞘中「"HIM"一刀流•居合"HIW"」心神全神灌注在刀意之中！\n"NOR, me, target);

    // 判斷命中
    hit = isHit(me, target);

    if( !hit ) {
        message_vision(HIK"$n"HIK"看破了招式的威力，立刻出招將$N"HIK"的攻擊攔了下來。\n\n"NOR, me, target);
    } else {
        damage = getDamage(me, target, sk);
        target->receive_damage(damage, me);
        message_vision( sprintf(HIR"$N眼神一亮，瞬間拔刀穿過$n"HIR"要害"NOR+YEL"『獅子輓歌』"HIR"$n"HIR"噴出大量鮮血！！"NOR"(%d) %s\n\n", damage, COMBAT_D->report_status(target) ), me, target);
    }
    setEffect(me, sk, hit);
    return 1;
}
