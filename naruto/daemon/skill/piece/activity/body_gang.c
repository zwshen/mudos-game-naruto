#include <ansi.h>
#define SKILL_NAME "body gang"
#define SKILL_NAME_C "鐵塊•剛"
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

string *defend_message = ({
    HIW"$N雖然被攻擊所擊中，但是毫髮無傷。\n"NOR,
    HIW"「咚」地一聲，$n反而痛的哇哇大叫，似乎擊中什麼硬物。\n"NOR,
    HIW"$N直接用自己的身子硬接攻擊，結果完全沒有受傷\n"NOR,
});

// target 受到傷害前，讓技能先跑過 receive_damage 
// 如何便可以製作 "暫時無敵技" 或是 "傷害吸收盾" 之類的技能
int receiveDamage(object me, object target, int damage)
{
    int sk;
    string msg;

    sk = me->query_skill(SKILL_NAME);

    if( me->query_skill("body iron") < 50 && me->query_skill(SKILL_NAME) < 40 ) return damage;

    if( me->query_condition("gang", 1) != 0) {
        msg = defend_message[random(sizeof(defend_message))];
        message_vision(msg, me, target);
        // 增加技能經驗
        me->improve_skill(SKILL_NAME, 1);
        return 0;
    }
    return damage;
}

// 檢查是否能使用技能
int isCast(object me, string act, int sk)
{
    if( !objectp(me) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( act != "defence" ) {
        tell_object(me, "目前" + SKILL_NAME_C + "有 defence 這個功\能。\n");
        return 0;
    }

    if( me->query_skill("body iron", 1) < 50 || sk < 40 ) {
        tell_object(me, "你的能力不足以使用這一招。\n");
        return 0;
    }

    if( me->query_stat("mp") < sk/2 ) {
        tell_object(me, "你的狀態無法使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( me->query_condition("gang_busy", 1) != 0) {
        tell_object(me, "身體硬化太久將會無法回復！再等一等吧。\n");
        return 0;
    }

    return 1;
}

// 取得冷卻時間
int check_cd(object me, int sk)
{
    if( sk < 80 ) return 240;
    else if( sk < 120 ) return 210;
    else if( sk < 160 ) return 180;
    else if( sk < 200 ) return 150;
    else return 120;
}

void do_perform(object me, int sk)
{
    int busy;
    mapping cnd = ([]);

    me->damage_stat("mp", sk/2, me);
    message_vision("$N發動了鐵塊最強防禦狀態"HIW"『"+SKILL_NAME_C+"』"NOR"！\n"NOR, me);

    cnd["name"] = HIW+SKILL_NAME_C+NOR;
    cnd["duration"] = sk/20;

    me->set_condition("gang", cnd);

    busy = check_cd(me, sk);

    cnd["name"] = HIW"(軟化)"NOR;
    cnd["duration"] = busy;

    me->set_condition("gang_busy", cnd);

    // 增加技能經驗
    me->improve_skill(SKILL_NAME, 1);
}

int perform_action(object me, string act)
{
    int sk;

    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, sk) ) return 1;

    do_perform(me, sk);
    return 1;
}
