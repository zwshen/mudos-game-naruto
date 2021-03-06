/* 影分身術(shadow) by mouse 2007/8/12 */

#include <ansi.h>
#define SKILL_NAME "shadow"
#define SKILL_NAME_C "影分身術"
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

// 使用絕招
int perform_action(object me, string act, object target)
{
    string msg;
    if( !objectp(me) ) return 0;
    if( me->is_busy() ) return notify_fail("你現在沒有空使用。\n");
    if( me->query_skill(SKILL_NAME) < 40 ) return notify_fail("你還不能將影分身術應用自如。\n");

    switch( act ) {
        case "defend": me->set_temp("SHADOW_TEMP", 1);
                     msg = "你決定下次要使用"HIB"防禦型"NOR"影分身助戰。\n";
                     break;
        case "attack": me->set_temp("SHADOW_TEMP", 2);
                     msg = "你決定下次要使用"HIR"攻擊型"NOR"影分身助戰。\n";
                     break;
        case "none": me->delete_temp("SHADOW_TEMP");
                     msg = "你決定下次要使用"HIG"平均型"NOR"影分身助戰。\n";
                     break;
        default: return notify_fail("你可以指定要使用哪種型態的影分身。perform shadow.attack|defend|none\n"); break;
    }
    tell_object(me,msg);
    return 1;
}
