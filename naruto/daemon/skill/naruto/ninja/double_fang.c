/* 牙通牙(double fang) by mouse 2007/8/13 */

#include <ansi.h>
#define SKILL_NAME "double fang"
#define SKILL_NAME_C "牙通牙"
#define SKILL_CLASS "ninja"

inherit SKILL;

object pet;

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

// 命中能力影響
int exact(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/20;
}

// 迴避能力影響
int evade(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)*3/100;
}

// 檢查是否能使用技能
int isCast(object me, string act, object target, int sk)
{
    if( !objectp(me) || !objectp(target) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用通牙。\n");
        return 0;
    }

    if( act != "atwirl" ) {
        tell_object(me, "目前通牙只有 atwirl 功\能。\n");
        return 0;
    }

    if( !me->is_fighting(target) ) {
        tell_object(me, "你並未和對方在戰鬥中...\n");
        return 0;
    }

    if( me->query_skill("ninja") < 100 || sk < 60 ) {
        tell_object(me, "你的能力不足以使用這一招。\n");
        return 0;
    }

    if( me->query_stat("mp") < sk/5 ) {
        tell_object(me, "你身體狀況不佳，不能使用通牙。\n");
        return 0;
    }

    if( me->query_condition("four_foot", 1) == 0) {
        tell_object(me, "你必須要在四腳術的狀態下才能使用通牙。\n");
        return 0;
    }

    if( me->query_condition("fang_cd") ) {
        tell_object(me, SKILL_NAME_C + "前置準備尚未結束。\n");
        return 0;
    }

    return 1;
}

// 判斷寵物用
int check_pet(object me, object target)
{
    // 寵物不在身旁或是暈倒，或根本沒寵物都不使用
    // 戰鬥開始才召寵，等寵物醒了繼續放技，都是不行的
    if( !objectp(pet = me->query_temp("pet")) || !present("_MY_PET_", environment(me)) ) return 0;
    else if( !living(pet) ) return 0;
    else if( !pet->is_fighting(target) ) return 0;
    else return 1;
}

// 取得命中
int getHit(object me, object target, int dog)
{
    int hit, meHit, targetHit;

    meHit = COMBAT_D->exact(me, target, 1)*1.5;
    targetHit = COMBAT_D->evade(target, me, 1)*1.2;

    // 有無寵物的判斷不同
    if( !dog ) {
        target->add_temp("apply/evade", targetHit);
        hit = COMBAT_D->isHit(me, target);
        target->add_temp("apply/evade", -targetHit);
    } else {
        me->add_temp("apply/exact", meHit);
        target->add_temp("apply/evade", targetHit);
        hit = COMBAT_D->isHit(me, target);
        me->add_temp("apply/exact", -meHit);
        target->add_temp("apply/evade", -targetHit);
    }
    return hit;
}

// 取得傷害
int getDamage(object me, object target, int sk, int dog)
{
    int damage, raiseDamage;
    object wp;

    raiseDamage = sk*2 + me->query_skill("ninja") + me->query_skill("four foot");

    if( dog ) {
        if( pet->query("level") < 50 ) raiseDamage += pet->query("level")*8;
        else raiseDamage += 400;
    }
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
        me->start_busy(2);
    } else {
        me->start_busy(1);
    }
    cnd["name"] = HIW+"(CD)通牙"+NOR;
    cnd["duration"] = 6;

    // 有沒有配狗都應該cd，時間也一樣
    me->set_condition("fang_cd", cnd);

    me->damage_stat("mp", sk/5, me);
    me->improve_skill(SKILL_NAME, 1);
}

void do_perform(object me, object target, int sk)
{
    int hit, damage, dog;

    dog = check_pet(me, target);
    hit = getHit(me, target, dog);
    damage = getDamage(me, target, sk, dog);

    // 沒寵物時
    if( !dog ) {
        message_vision("\n$N大吼一聲，忽然跳躍至空中，一式"HIC"「通牙」"NOR"身子有如龍卷風般旋轉撞向$n！\n", me, target);
        if( hit ) {
            target->receive_damage(damage, me);
            message_vision(sprintf("「碰」地一聲，$n被龍卷風撞飛了出去，受到一些傷害(%d) %s\n\n", damage, report_status(target) ), me, target);
        } else {
            message_vision("但是四周氣流變化太大，龍卷風脫離了$N的範圍。\n\n", target);
        }
    } else {
        message_vision("\n$N喊道："HIG"上阿！"+pet->query("name")+"！"NOR"\n\n只見"+pet->query("name")+"飛躍至空中，與$N同時形成"HIC"兩道龍卷風『"HIB+BLINK"牙通牙"NOR+HIC"』"NOR"快速撞向$n！\n", me, target);
        if( hit ) {
            target->receive_damage(damage, me);
            message_vision(sprintf("兩道龍卷風互相衝擊，將$n卷了上去，在不斷的衝擊下摔落地面，變成一團肉泥(%d) %s\n\n", damage, report_status(target) ), me, target);
        } else {
            damage = damage/10;
            target->receive_damage(damage, me);
            message_vision(sprintf("$n十分僥倖的逃過一劫沒被卷入龍卷風中，但還是受到一些傷害(%d) %s\n\n", damage, report_status(target) ), me, target);
        }
    }
    // 使用這招應該扣忍犬的食物量與魔力，不能無條件使用
    if( dog ) {
        pet->do_check_food();
        pet->damage_stat("mp", sk/5, pet);

        // 寵物狀態太差就直接死吧
        if( pet->query_food() < 10 || pet->query_stat("mp") < sk/5 || pet->query_stat("hp") < 100 || pet->query_stat("ap") < 100 ) {
            message_vision(HIR"\n$n在身體不佳的情況下硬配合$N攻擊，身體承受不了而昏死過去。\n"NOR, me, pet);
            pet->die();
        }
    }
    // 使用後扣除
    setEffect(me, sk, hit);
}

// 手動攻擊
int perform_action(object me, string act, object target)
{
    int sk;

    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, target, sk) ) return 1;

    // 使用技能
    do_perform(me, target, sk);

    return 1;
}
