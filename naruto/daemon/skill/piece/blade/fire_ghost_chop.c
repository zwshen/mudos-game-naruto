#include <ansi.h>
#define SKILL_NAME "fire ghost chop"
#define SKILL_NAME_C "燒鬼斬"
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

int sock(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/40;
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

    if( me->query_skill("blade", 1) < 40 || sk < 60 ) {
        tell_object(me, "你的能力不足以使用這一招。\n");
        return 0;
    }

    if( me->query_stat("mp") < sk/8 ) {
        tell_object(me, "你身體狀況不佳，不能使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    return 1;
}

// 計算是否命中
int isHit(object me, object target)
{
    int i, j;

    i = COMBAT_D->intimidate(me, 1);
    j = COMBAT_D->wittiness(target, 1);

    if( COMBAT_D->SkillHit(me, target, i, j) ) return 1;
    else return 0;
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    int damage, raiseDamage;
    object wp;

    if( me->query_attr("str") < 300 ) raiseDamage = me->query_attr("str")/3 + sk*2;
    else raiseDamage = 100 + sk*2;

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
    me->damage_stat("mp", sk/8, me);
    me->start_busy(3);
    me->improve_skill(SKILL_NAME, 1);
}

int perform_action(object me, string act, object target)
{
    int damage, sk, i = 0;
    object *inv, item;
    mapping cnd = ([]);

    sk = me->query_skill(SKILL_NAME, 1);
    inv = all_inventory(me);

    // 檢查是否能使用技能
    if( !isCast(me, act, target, sk) ) return 1;

    foreach(item in inv) {
        if( item->is_weapon() ) {
            i++;
        }
    }
    if( !me->query_temp("weapon/righthand") || !me->query_temp("weapon/lefthand") || i < 3 ) 
        return notify_fail("三刀流必須裝備兩把武器並攜帶第三把武器才能使用。\n");

    message_vision("\n$N使出"HIR"『"RED"燒鬼斬"HIR"』"NOR"身體噴出雄雄烈火，將三把刀力量聚於一點衝向$n！\n", me, target);

    // 傷害計算
    damage = getDamage(me, target, sk);

    cnd["name"] = HIR+"著火狀態"+NOR;
    cnd["duration"] = sk/20;
    cnd["from"] = me;

    if( !isHit(me, target) ) {
        message_vision("結果火燄只在地上燒出一條火線...\n\n", target);
    } else {
        // 判斷有沒有著火，已經著火就不再中特殊狀態
        if( target->query_condition("firedamage") ) {
            target->receive_damage(damage, me);
            message_vision( sprintf("$n被三刀貫穿而過，衝擊力使身子飛了起來，在空中噴出大量鮮血(%d) %s\n\n", damage, COMBAT_D->report_status(target) ), me, target);
        } else {
            target->receive_damage(damage, me);
            message_vision( sprintf("火燄順著$n的身子劃出一道長長的火線，噴出的鮮血早已被火烤乾(%d) %s\n\n", damage, COMBAT_D->report_status(target) ), me, target);
            target->set_condition("firedamage", cnd);
        }
    }
    setEffect(me, sk);
    return 1;
}