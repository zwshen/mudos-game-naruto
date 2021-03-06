/* 掌仙術(hand heal) by mouse 2007/8/13 */

#include <ansi.h>
#define SKILL_NAME "hand heal"
#define SKILL_NAME_C "掌仙術"
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

int get_bonus(int lv)
{
    if(lv < 60 ) return 50;
    if(lv < 100 ) return 60;
    if(lv < 120 ) return 70;
    if(lv < 160 ) return 80;
    if(lv < 200 ) return 90;
    return 100;
}

// 檢查是否能使用技能
int isCast(object me, string act, int sk, string one, string two)
{
    if( !objectp(me) ) return 0;

    if( one == two ) {
        tell_object(me, "這兩種體能是同一種阿？轉來轉去很好玩？\n");
        return 0;
    }

    if( one != "hp" && one != "ap" && one != "mp" ) {
        tell_object(me, "" + SKILL_NAME_C + "只能轉換精力(ap)、體力(hp)、魔力(mp)。\n");
        return 0;
    }

    if( two != "hp" && two != "ap" && two != "mp" ) {
        tell_object(me, "" + SKILL_NAME_C + "只能轉換精力(ap)、體力(hp)、魔力(mp)。\n");
        return 0;
    }

    if( me->query_skill("ninja", 1) < 100 || sk < 20 ) {
        tell_object(me, "你目前的忍術造詣還不足已使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    // 借用惡魔風腳冷卻時間
    if( me->query_condition("diabo_busy", 1) != 0) {
        tell_object(me, SKILL_NAME_C + "正在冷卻中，請過一會再使用。\n");
        return 0;
    }

    if( me->query_stat_maximum(two) <= me->query_stat(two) ) {
        tell_object(me, "你的身體狀況十分良好，不需使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    return 1;
}

void do_perform(object me, string one, string two, int number, int sk)
{
    int heal, bonus, i;
    mapping cnd = ([]);

    heal = me->query_stat_maximum(two) - me->query_stat(two);
    bonus = get_bonus(sk);

    if( number >= 1 ) {
        if( me->query_stat(one) < number + 1 ) {
            write("你沒有那麼多的 "RED+one+NOR" 去補充 "RED+two+NOR"。\n");
            return;
        }
    } else {
        if( me->query_stat(one) < heal + 1) {
            write("你沒有那麼多的 "RED+one+NOR" 去補充 "RED+two+NOR"。\n");
            return;
        }
    }
    message_vision("$N以奇特的手式快速結印，接著將手中出現的藍色光球「"HIC"掌仙丹"NOR"」打入自己的胸口...\n"NOR, me);
    if( number >= 1 ) {
        i = number*bonus/100;
        me->damage_stat(one, number, me);
        me->heal_stat(two, i);
        tell_object(me,HIC"你花費了 "NOR+HIR+number+HIC" 點 "NOR+one+HIC" 補充了 "HIY+i+HIC" 點 "NOR+two+HIC"。\n"NOR);
    } else {
        i = heal*bonus/100;
        me->damage_stat(one, heal, me);
        me->heal_stat(two, i);
        tell_object(me,HIC"你花費了 "NOR+HIR+heal+HIC" 點 "NOR+one+HIC" 補充了 "HIY+i+HIC" 點 "NOR+two+HIC"。\n"NOR);
    }
    me->improve_skill(SKILL_NAME, 1);

    cnd["name"] = HIC"(CD)掌仙"NOR;
    cnd["duration"] = 10;

    me->set_condition("diabo_busy", cnd);

    return;
}

int perform_action(object me, string act, object target)
{
    int sk, number;
    string one, two;

    sk = me->query_skill(SKILL_NAME, 1);

    if( !objectp(me) ) return 0;

    if( !act || sscanf(act, "%s to %s %d", one, two, number) != 3 ) {
        if( !act || sscanf(act, "%s to %s", one, two) != 2 ) return notify_fail("指令格式﹕perform hand heal.<1> to <2> <轉換值>\n");
    }
    // 檢查是否能使用技能
    if( !isCast(me, act, sk, one, two) ) return 1;

    do_perform(me, one, two, number, sk);
    return 1;
}
