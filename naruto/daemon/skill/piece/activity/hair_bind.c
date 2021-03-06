#include <ansi.h>
#define SKILL_NAME "hair bind"
#define SKILL_NAME_C "毛髮束縛"
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

int exact(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)*43/200;
}

// 檢查是否能使用技能
int isCast(object me, string act, object target, int sk)
{
    if( !objectp(me) || !objectp(target) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( target->is_busy() ) {
        tell_object(me, "你已經定住" + target->query("name") + "了。\n");
        return 0;
    }

    if( act != "tie" ) {
        tell_object(me, "目前" + SKILL_NAME_C + "只有 tie 功\能。\n");
        return 0;
    }

    if( !me->is_fighting(target) ) {
        tell_object(me, "你並未和對方在戰鬥中...\n");
        return 0;
    }

    if( me->query_condition("hair_cd") ) {
        tell_object(me, "想再次控制頭髮需集中精神。\n");
        return 0;
    }

    if( sk < 100 ) {
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
    int hit, raiseHit;

    raiseHit = me->query_skill(SKILL_NAME, 1)/4;

    me->add_temp("apply/exact", raiseHit);
    hit = COMBAT_D->isHit(me, target);
    me->add_temp("apply/exact", -raiseHit);

    return hit;
}

// 技能使用後 
void setEffect(object me, int sk, int hit)
{
    mapping cnd = ([]);

    if( !hit ) {
        me->damage_stat("mp", sk/10, me);
    } else {
        me->damage_stat("mp", sk/8, me);
    }
    cnd["name"] = HIW+"(CD)髮束"+NOR;
    cnd["duration"] = 10;

    me->set_condition("hair_cd", cnd);
    me->improve_skill(SKILL_NAME, 1);
}

int perform_action(object me, string act, object target)
{
    int damage, sk, hit;

    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, target, sk) ) return 1;

    message_vision("\n$N將武器插在地上，閉目冥想"HIK"『"BRED+HIW"生命歸返•毛髮束縛"NOR+HIK"』"NOR"只見$N的頭髮緩緩地生長！\n", me, target);

    // 是否命中
    hit = isHit(me, target);

    if( !hit ) {
        message_vision("但是頭髮生長速度很慢，似乎沒達到$N預期的效果。\n\n", me, target);
        me->start_busy(2);
    } else {
        message_vision("忽然$N頭髮快速生長，一瞬間將$n纏住，使$n暫時無法行動！\n\n", me, target);
        target->start_busy(sk/50);
    }
    setEffect(me, sk, hit);
    return 1;
}
