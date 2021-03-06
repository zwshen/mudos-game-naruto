#include <ansi.h>
#define SKILL_NAME "outfit kick"
#define SKILL_NAME_C "踢技全餐"
#define SKILL_CLASS "spurn"

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
    return ability + me->query_skill(SKILL_NAME)/10;
}

int defend(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/5;
}

// 計算是否命中
int isHit(object me, object target)
{
    int hit, raiseHit;

    raiseHit = me->query_skill(SKILL_NAME, 1)/2;

    me->add_temp("apply/exact", raiseHit);
    hit = COMBAT_D->isHit(me, target);
    me->add_temp("apply/exact", -raiseHit);

    return hit;
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    int damage;
    object wp;

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    if( sk < 100 ) return damage*30/100;       // 30%
    else if( sk < 120 ) return damage*40/100;  // 40%
    else if( sk < 150 ) return damage*50/100;  // 50%
    else if( sk < 180 ) return damage*57/100;  // 57%
    else if( sk < 199 ) return damage*63/100;  // 63%
    else return damage*75/100;                 // 75%
}

int autoCasting(object me, object target, object weapon)
{
    string *name = ({ "頭", "首", "肩", "肩里肌", "頸", "油炸頸", "胸", "腰",
                      "大腿", "上部大腿", "背", "後肋", "尾", "鞍下", "腹",
                      "燉胸", "里肌", "脛骨", "三級絞", "二級絞", "一級絞", });

    int damage, sk;
    mapping cnd = ([]);

    sk = me->query_skill(SKILL_NAME, 1);

    // 判斷是否啟動
    if( target->is_busy() ) return 1;
    if( me->query_stat("mp") < sk/20 ) return 1;
    if( me->query_skill("spurn", 1) < 20 ) return 1;
    if( sk < 20 ) return 1;

    if( sk < 80 ) {
        if( random(sk) < sk*9/10 ) return 1; // 20~80 級 10%
    } else if( sk < 150 ) {
        if( random(sk) < sk*8/10 ) return 1; // 81~150 級 20%
    } else {
        if( random(sk) < sk*7/10 ) return 1; // 151~200 級 30%
    }

    cnd["name"] = YEL+"燙傷狀態"+NOR;
    cnd["duration"] = 5;
    cnd["damage"] = sk/3;
    cnd["from"] = me;

    // 傷害固定
    damage = getDamage(me, target, sk);

    // 判斷是否為惡魔風腳狀態
    if( me->query_condition("diabo") ) message_vision("$N朝著$n跳了起來，一招"HIW"『"HIR"惡魔風腳•" + name[random(sizeof(name))] + "肉"HIW"』"NOR"踢向$n！\n", me, target);
    else message_vision("$N朝著$n跳了起來，一招"HIW"『"HIY"" + name[random(sizeof(name))] + "肉"HIW"』"NOR"踢向$n！\n", me, target);

    if( !isHit(me, target) ) {
        if( me->query_condition("diabo") ) message_vision("四周發出強烈的閃光，但是卻沒打到$N...\n", target, me);
        else message_vision("$N身子一歪避過了這次的攻擊...\n", target);
    } else {
        if( me->query_condition("diabo") ) {
            target->set_condition("burn", cnd);
            message_vision( sprintf("「碰」地一聲，$n身上發出強烈的閃光，還不停發出滋滋聲(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);
        } else message_vision( sprintf("$n閃避不及，被踢的眼冒金星...(%d)%s\n", damage, COMBAT_D->report_status(target) ), me, target);

        // 判斷定人效果
        if( me->query_skill("spurn", 1) >= 40 ) {
            target->start_busy(1);
        }
        target->receive_damage(damage, me);
    }
    me->damage_stat("mp", sk/20, me);
    me->improve_skill(SKILL_NAME, 1);
}