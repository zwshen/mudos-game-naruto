#include <ansi.h>
#define SKILL_NAME "change face shot"
#define SKILL_NAME_C "整型ＳＨＯＴ"
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
    return ability + me->query_skill(SKILL_NAME)/5;
}

// 計算是否命中
int isHit(object me, object target)
{
    int hit, meHit, targetHit;

    meHit = me->query_ability("exact");
    targetHit = target->query_ability("evade")/2;

    me->add_temp("apply/exact", meHit);
    target->add_temp("apply/evade",  targetHit);
    hit = COMBAT_D->isHit(me, target);
    me->add_temp("apply/exact", -meHit);
    target->add_temp("apply/evade", - targetHit);

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

    if( sk < 100 ) return damage*2/5;        // 40%
    else if( sk < 120 ) return damage*3/5;   // 60%
    else if( sk < 150 ) return damage*4/5;   // 80%
    else if( sk < 180 ) return damage;       // 100%
    else if( sk < 199 ) return damage*11/10; // 110%
    else return damage*125/100;              // 125%
}

// 技能使用後 
void setEffect(object me, int sk, int hit)
{
    if( !hit ) {
        me->damage_stat("mp", 10, me);
    } else {
        me->damage_stat("mp", sk/10, me);
    }
    me->improve_skill(SKILL_NAME, 1);
}

int autoCasting(object me, object target, object weapon)
{
    string *name1 = ({ "肩肉", "腹肉", "大腿肉", "頰肉", "羊肉", "小牛肉",
                       "整型", "切肉", "豬肉鍋", });

    string *name2 = ({ "眼睛", "鼻子", "嘴巴", "耳朵", });

    int damage, sk, hit;
    mapping cnd = ([]);

    sk = me->query_skill(SKILL_NAME, 1);

    // 判斷是否啟動
    if( me->query_stat("mp") < sk/10 ) return 1;
    if( me->query_skill("spurn", 1) < 60 ) return 1;
    if( sk < 40 ) return 1;

    if( sk < 80 ) {
        if( random(sk) < sk*9/10 ) return 1; // 20~80 級 10%
    } else if( sk < 150 ) {
        if( random(sk) < sk*3/4 ) return 1;  // 81~150 級 25%
    } else {
        if( random(sk) < sk*3/5 ) return 1;  // 151~200 級 40%
    }

    // 傷害固定
    damage = getDamage(me, target, sk);

    // 命中
    hit = isHit(me, target);

    // 判斷是否為惡魔風腳狀態
    if( me->query_condition("diabo", 1) ) {
        message_vision("$N倒掛金勾使出"HIY"『"HIR"惡魔風腳•畫龍點睛ＳＨＯＴ"HIY"』"NOR"踢向$n！\n", me, target);
        if( !hit ) {
            message_vision("結果招式在地上踢出了一個大洞...\n", target, me);
        } else {
            target->receive_damage(damage, me);
            message_vision( sprintf("「磅」地一聲，$n像太陽般發出強烈光芒後墜落到地面(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);

            cnd["name"] = YEL+"燙傷狀態"+NOR;
            cnd["duration"] = 5;
            cnd["damage"] = sk/5;
            cnd["from"] = me;

            target->set_condition("burn", cnd);
        }
    } else {
        message_vision("$N雙腳一蹬衝向$n，踢出"HIW"『"YEL + name1[random(sizeof(name1))] + "ＳＨＯＴ"HIW"』"NOR"！\n", me, target);

        if( !hit ) {
            message_vision("但是被$N不慌不忙的閃開了...\n", target);
        } else {
            // 傷害盾吸收
            damage = COMBAT_D->receive_damage(target, me, damage);

            target->receive_damage(damage, me);
            message_vision( sprintf("$n閃避不及，" + name2[random(sizeof(name2))] + "部位被$N踢中，整個凹了進去...(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);
        }
    }
    setEffect(me, sk, hit);
    return 1;
}