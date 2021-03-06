/* 四腳術(four foot) by mouse 2007/8/13 */

#include <ansi.h>
#define SKILL_NAME "four foot"
#define SKILL_NAME_C "四腳術"
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

// 命中能力影響
int exact(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/8;
}

// 檢查是否能使用技能
int isCast(object me, string act, int sk)
{
    if( !objectp(me) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( act != "beast" ) {
        tell_object(me, "目前" + SKILL_NAME_C + "只有 beast 這個功\能。\n");
        return 0;
    }

    if( me->query_skill("ninja") < 60 || sk < 40 ) {
        tell_object(me, "你的能力不足以使用這一招。\n");
        return 0;
    }

    if( me->query_stat("mp") < 200 ) {
        tell_object(me, "你的狀態無法使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_condition("four_foot", 1) != 0) {
        tell_object(me, "你已經在" + SKILL_NAME_C + "狀態了。\n");
        return 0;
    }

    return 1;
}

void do_perform(object me, int sk)
{
    mapping cnd = ([]), weapons;
    string skill;
    object ob;

    message_vision("$N結印後將雙手觸碰地面，發動"HIW"『"HIR"四腳之術"HIW"』"NOR"全身浮現野獸般的紋路！\n\n"NOR, me);

/*  武器部分暫時拿掉
    if( mapp(weapons = me->query_temp("weapon")) && sizeof(weapons) ) {
        foreach(skill, ob in weapons) ob->unequip();
        write("因為你發動四腳之術，所以暫時不能使用武器了。\n");
    }
*/

    cnd["name"] = HIR+ SKILL_NAME_C +NOR;
    cnd["duration"] = sk*3/4;
    cnd["attack"] = sk/2;
    cnd["evade"] = sk/2;
    cnd["ap"] = sk*2;

    me->set_condition("four_foot", cnd);
    me->damage_stat("mp", 200, me);
    me->improve_skill(SKILL_NAME, 1);
}

// 使用絕招
int perform_action(object me, string act, object target)
{
    int sk;
    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, sk) ) return 1;

    do_perform(me, sk);
    return 1;
}
