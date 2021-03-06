/* 體術─八卦掌回天 */

#include <ansi.h>
#define SKILL_NAME "sky palm"
#define SKILL_NAME_C "八卦回天"
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

// 能在傷害前跑出，用於製作無敵或盾防禦
int receiveDamage(object me, object target, int damage)
{
    int i, raiseDamage, exact, evade;
    object wp;

    if( !me->query_condition("sky_palm") ) return damage;

    exact = random(me->query_ability("exact") + me->query_ability("intimidate"));
    evade = random(target->query_ability("evade"));

    me->damage_stat("mp", 20, me);
    message_vision(HIG"\n$N看準了攻勢，立刻使用白眼查出"NOR"$n"HIG"的弱點與攻擊路境施展『"HIW"八卦掌回天"HIG"』！\n"NOR, me, target);
    if( exact < evade ) {
        message_vision(HIY"但是"NOR"$n"HIY"居然看破了回天掌法，直接從$N視角盲點反擊！\n\n"NOR, me, target);
    } else {
        if( exact - evade < 100 ) {
            message_vision(YEL"結果$n"YEL"的攻擊居然被回天掌法全數化解，只能黯然避開$N的反擊！\n\n"NOR, me, target);
        } else {
            raiseDamage = me->query_skill(SKILL_NAME) + me->query_skill("force")/2 + me->query_skill("soft fist") + me->query_skill("white eyes");

            me->add_temp("apply/attack", raiseDamage);

            if( wp = me->query_temp("weapon/twohanded") ) i = COMBAT_D->isDamage(me, target, wp);
            else if( wp = me->query_temp("weapon/righthand") ) i = COMBAT_D->isDamage(me, target, wp);
            else if( wp = me->query_temp("weapon/lefthand") ) i = COMBAT_D->isDamage(me, target, wp);
            else i = COMBAT_D->isDamage(me, target, 0);

            me->add_temp("apply/attack", -raiseDamage);

            target->receive_damage(i, me);
            message_vision( sprintf(HIR"$N不但將攻擊全部化解，更使用回天掌法擊中$n"HIR"身體關節處，重創了$n(%d) %s\n\n", i, report_status(target) ), me, target);
        }
        return 0;
    }
    return damage;
}

// 檢查是否能使用技能
int isCast(object me, string act, object target, int sk)
{
    if( !objectp(me) ) return 0;

    if( me->is_busy() ) {
        write("你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( act != "attack" ) {
        write("目前" + SKILL_NAME_C + "只有 attack 功\能。\n");
        return 0;
    }

    if( !me->is_fighting() ) {
        write("必須在戰鬥中才能施展" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_condition("sky_palm_cd", 1) ) {
        write("你目前注意力不佳，無法使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_condition("sky_palm", 1) ) {
        write("你目前已經在使用" + SKILL_NAME_C + "中。\n");
        return 0;
    }

    if( !me->query_condition("white_eyes") ) {
        write("只有在白眼的狀態中才能使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_skill("force", 1) < 160 || sk < 60 || me->query_skill("soft fist", 1) < 80 ) {
        write("你的能力不足以使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_stat("mp") < 50 ) {
        write("你身體狀況不佳，不能使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    return 1;
}

void do_perform(object me, int sk)
{
    mapping cnd = ([]);

    message_vision(HIG"\n$N配合白眼開始施展『"HIW"八卦回天掌"HIG"』拳風剛中帶柔，柔中帶勁，守勢密不透風！\n\n"NOR, me);

    cnd["name"] = HIG+"回天"+NOR;
    cnd["duration"] = sk;
    cnd["from"] = me;

    me->set_condition("sky_palm", cnd);

    cnd["name"] = HIG+"(CD)回天"+NOR;
    cnd["duration"] = sk*3/2;

    me->set_condition("sky_palm_cd", cnd);

    // 增加技能經驗
    me->damage_stat("mp", 50, me);
    me->start_busy(2);
    me->improve_skill(SKILL_NAME, 1);
    return;
}

int perform_action(object me, string act, object target)
{
    int sk;

    sk = me->query_skill(SKILL_NAME, 1);

    if( !isCast(me, act, target, sk) ) return 1;

    do_perform(me, sk);
    return 1;
}
