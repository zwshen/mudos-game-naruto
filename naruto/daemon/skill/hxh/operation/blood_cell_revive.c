/* 操作術：血球再生(blood-cell revive) */
// 增加附加能力 by mouse 2007/7/25

#include <ansi.h>
#define SKILL_NAME   "blood-cell revive"
#define SKILL_NAME_C "血球再生"
#define SKILL_CLASS  "operation"

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

// 防禦技巧影響
int wittiness(object me, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/10;
}

// 防禦力量影響
int defend(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)*3/40;
}

void do_perform(object me, object target)
{
    int sk;
    mapping cnd = ([]);
    
    sk = me->query_skill( SKILL_NAME, 1);
        
    if( sk < 20 || me->query_skill("operation", 1) < 40 ) {
        write("你的能力不足以使用這個技能。\n");
        return;
    }
    if( objectp(target) ) {
        if( sk < 60 ) {
            write("你還無法對他人使用這個技能。\n");
            return;
        }
    } else target = me;

    if( target->query_condition("blood_cell_revive_cond") != 0 ) {
        write(target->query("name")+"已經被施過血球再生了。\n");
        return;
    }
    if( me->query_stat("mp") < sk*3/2 ) {
        write("你目前沒有足夠的念能力來使用血球再生。\n");
        return;
    }
    me->damage_stat("mp", sk*3/2, me);

    message_vision("$N將念力一掌拍進去$n的延腦上，施展了"HIR"血球再生"NOR"！！\n", me, target);

    cnd["name"] = HIR"血球再生"NOR;
    cnd["duration"] = 60;
    cnd["heal"] = sk/10;

    target->set_condition("blood_cell_revive_cond", cnd);

    // 增加技能經驗
    me->improve_skill(SKILL_NAME, 1);
}

int perform_action(object me, string act, object target)
{
    if( !objectp(me) ) return 0;
    if( me->is_busy() ) return notify_fail("你現在沒有空使用血球再生。\n");

    switch( act ) {
        case "revive": do_perform(me, target); break;
        default: return notify_fail("目前血球再生有 revive 這個功\能。\n"); break;
    }
    return 1;
}
