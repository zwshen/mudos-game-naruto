#include <ansi.h>
#define SKILL_NAME "destory fist"
#define SKILL_NAME_C "破壞拳"
#define SKILL_CLASS "strength"

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

    if( me->query_skill("strength", 1) < 80 || sk < 40 ) {
        tell_object(me, "你還無法負擔破壞拳的強大念力。\n");
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

    i = COMBAT_D->intimidate(me, 1);
    j = COMBAT_D->wittiness(target, 1);

    if( COMBAT_D->SkillHit(me, target, i, j) ) return 1;
    else return 0;
}

// 計算是否出現致命一擊
int isSock(object me, object target)
{
    // 超過 59 級才有致命一擊的影響
    if( me->query_skill("body strength", 1) < 60 ) return 0;

    // 加致命一擊機率
    return (COMBAT_D->sock(me, target, 1) > random(100));
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    int damage, raiseDamage;
    object wp;

    // 攻擊力量影響最高 800 傷害
    if( me->query_ability("attack") < 400 ) raiseDamage = sk*4 + me->query_skill("strength") + me->query_skill("body strength") + me->query_ability("attack")*2;
    else raiseDamage = sk*4 + me->query_skill("strength") + me->query_skill("body strength") + 800;

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
    me->damage_stat("mp", sk/4, me);
    me->start_busy(4);
    me->improve_skill(SKILL_NAME, 1);
}

int perform_action(object me, string act, object target)
{
    int hit, sock, sk, damage;

    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, target, sk) ) return 1;

    // 是否致命一擊
    sock = isSock(me, target);

    // 是否命中
    hit = isHit(me, target);

    // 攻擊訊息
    if( sock ) message_vision(HIR"\n(致命一擊) "NOR"$N"HIY"全身念力爆漲，右拳一記「"HIR"超"NOR"•"HIY+BLINK"破壞拳"NOR+HIY"」朝著"NOR"$n"HIY"重重擊去！"NOR"\n", me, target);
    else message_vision("\n$N全身念力爆漲朝$n打出一記「"HIY"破壞拳"NOR"」！"NOR"\n", me, target);

    // 未命中
    if( !hit ) {
        // 如果出現致命一擊，還是會有傷害
        if( sock ) {
            // 增加1/10的傷害
            damage = getDamage(me, target, sk)/10;
            target->receive_damage(damage, me);
            message_vision( sprintf("$N一拳揮空擊中地面，卻仍發出核彈般的爆炸威力炸傷了$n(%d) %s\n\n", damage, COMBAT_D->report_status(target) ), me, target);

        // 否則攻擊失敗
        } else message_vision("$N一拳揮空擊中地面，打出了一個大洞。\n\n", me, target);

    // 命中
    } else {
        // 致命一擊
        if( sock ) {
            // 增加傷害
            damage = getDamage(me, target, sk);
            target->receive_damage(damage, me);
            message_vision( sprintf("$n被右拳正面擊中，因為強大的力道貫穿頭部直接身首分離(%d) %s\n\n", damage, COMBAT_D->report_status(target) ), me, target);

        // 未致命一擊
        } else {
           damage = getDamage(me, target, sk)/2;
           target->receive_damage(damage, me);
           message_vision( sprintf("$n被右拳正面擊中，慘嚎一聲似乎是鼻樑被打斷了(%d) %s\n\n", damage, COMBAT_D->report_status(target) ), me, target);
        }
    }
    setEffect(me, sk);
    return 1;
}