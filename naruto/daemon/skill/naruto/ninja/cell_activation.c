/* 忍術：細胞活化(cell activation)
   修改 buff 時效、將 buff 分離 by mouse 2007/8/14
*/

#include <ansi.h>
#define SKILL_NAME "cell activation"
#define SKILL_NAME_C "細胞活化"
#define SKILL_CLASS "ninja"

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
int isCast(object me, string act, int sk)
{
    if( !objectp(me) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( act != "ca" ) {
        tell_object(me, "目前" + SKILL_NAME_C + "有 ca 這個功\能。\n");
        return 0;
    }

    if( sk < 20 || me->query_skill("ninja") < 20 ) {
        tell_object(me, "你的能力不足以使用這個技能。\n");
        return 0;
    }

    if( me->query_stat("mp") < sk*3/2) {
        tell_object(me, "你目前沒有足夠的查克拉來使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_condition("ca") && me->query_condition("ca2") ) {
        tell_object(me, "你目前仍然在使用" + SKILL_NAME_C + "中。\n");
        return 0;
    }

    if( me->query_condition("ca2") &&
        me->query_stat("hp") >= me->query_stat_maximum("hp") &&
        me->query_stat("ap") >= me->query_stat_maximum("ap") ) {

        tell_object(me, "你現在的狀況十分良好，不需要活血。\n");
        return 0;
    }

    return 1;
}

void do_perform(object me, int sk)
{

    mapping cnd = ([]);

    message_vision("$N雙手緩慢的結印後在額頭處輕點了一下，施展了"HIG+SKILL_NAME_C+NOR"！！\n", me);

    cnd["name"] = HIR"活血"NOR;
    cnd["duration"] = 30;
    cnd["heal"] = sk/10;

    if( me->query_condition("ca") == 0 ) {
        write(HIR"(你的血液受到查克拉的鼓動，加速了新陳代謝。)\n"NOR);
        me->set_condition("ca", cnd);
    }

    cnd["name"] = HIG+SKILL_NAME_C+NOR;
    cnd["duration"] = sk;
    cnd["str"] = sk/20;
    cnd["dex"] = sk/20;

    if( me->query_condition("ca2") == 0 ) {
        write(HIG"(細胞開始產生變化，你感覺部分能力提高了。)\n"NOR);
        me->set_condition("ca2", cnd);
    }

    if( me->is_fighting() ) {
        tell_object(me, HIG"(因為強行在戰鬥中施展細胞活化，暫時無法行動)\n");
        me->start_busy(2);
    }

    me->damage_stat("mp", sk*3/2, me);
    me->improve_skill(SKILL_NAME, 1);
}

int perform_action(object me, string act, object target)
{
    int sk;

    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, sk) ) return 1;

    do_perform(me, sk);
    return 1;
}
