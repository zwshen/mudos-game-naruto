#include <ansi.h>
#define SKILL_NAME "fire wall"
#define SKILL_NAME_C "火牆"
#define SKILL_CLASS "variation"

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

// 攻擊技巧影響
int intimidate(object me, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)*3/40;
}

// 能在傷害前跑出，用於製作無敵或盾防禦
int receiveDamage(object me, object target, int damage)
{
    int raiseDamage, i;
    object wp;

    raiseDamage = me->query_skill(SKILL_NAME) + me->query_skill("variation")/2 + me->query_skill("fire variation")/2;

    if( me->query_condition("firewall", 1) != 0) {

        if( wp = me->query_temp("weapon/twohanded") ) i = COMBAT_D->isDamage(me, target, wp);
        else if( wp = me->query_temp("weapon/righthand") ) i = COMBAT_D->isDamage(me, target, wp);
        else if( wp = me->query_temp("weapon/lefthand") ) i = COMBAT_D->isDamage(me, target, wp);
        else i = COMBAT_D->isDamage(me, target, 0);

        i = (i*(100+(me->query_skill(SKILL_NAME)/4)))/(500-raiseDamage);

        target->receive_damage(i, me);
        message_vision("\n$n"RED"為了使攻擊命中$N不慎被火焰燒傷了"HIR"("+i+")\n"NOR, me, target);
    }
    return damage;
}

// 檢查是否能使用技能
int isCast(object me, string act, object target, int sk)
{
    if( !objectp(me) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( act != "fire" ) {
        tell_object(me, "目前" + SKILL_NAME_C + "只有 fire 功\能。\n");
        return 0;
    }

    if( !me->is_fighting() ) {
        tell_object(me, "必須在戰鬥中才能施展" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_skill("variation", 1) < 60 || sk < 60 ) {
        tell_object(me, "你的能力不足以使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_stat("mp") < 100 ) {
        tell_object(me, "你身體狀況不佳，不能使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_condition("firewall", 1) != 0) {
        tell_object(me, "你已經用" + SKILL_NAME_C + "包圍四周了。\n");
        return 0;
    }

    return 1;
}

void do_perform(object me, int sk)
{
    mapping cnd = ([]);

    message_vision("\n$N運起念力兩手朝地面一拍，只見大片"HIR"火海衝天形成"NOR+RED"「火牆」"NOR"將$N包覆其中！\n\n"NOR, me);

    cnd["name"] = RED+"火牆"+NOR;
    cnd["duration"] = sk;
    cnd["from"] = me;

    me->set_condition("firewall", cnd);

    // 增加技能經驗
    me->damage_stat("mp", 100, me);
    me->start_busy(3);
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
