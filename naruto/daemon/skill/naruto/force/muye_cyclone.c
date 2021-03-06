/* 增加一般傷害公式 by mouse 2007/8/14 */

#include <ansi.h>
#define SKILL_NAME "muye cyclone"
#define SKILL_NAME_C "木之葉旋風"
#define SKILL_CLASS "force"

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
    if( me->query_skill("force", 1) < 60 ) return ability;
    return ability + me->query_skill(SKILL_NAME)*33/200;
}

int sock(object me, object target, int ability, int type)
{
    if( me->query_skill("force", 1) >= 150 ) {
        if( me->query_skill(SKILL_NAME, 1) >= 200 ) return ability+2;
        else if( me->query_skill(SKILL_NAME, 1) >= 100 ) return ability+1;
    }
    return ability;
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
    int damage, raiseDamage;
    object wp;

    if( wp = me->query_temp("weapon/twohanded") ) raiseDamage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) raiseDamage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) raiseDamage = COMBAT_D->isDamage(me, target, wp);
    else raiseDamage = COMBAT_D->isDamage(me, target, 0);

    // 自動技沒辦法用 cd 判斷
    // 讓效果比其他打上限的 sk 還要差一些
    if( sk >= 181 ) {
        damage = target->query_stat_maximum("hp")*3/100;
        if( damage > 750 ) damage = 750;
    } else if( sk >= 101 ) {
        damage = target->query_stat_maximum("hp")*2/100;
        if( damage > 500 ) damage = 500;
    } else {
        damage = target->query_stat_maximum("hp")/100;
        if( damage > 500 ) damage = 250;
    }

    // 基本傷害公式就不受影響
    damage += raiseDamage/4;

    return damage;
}

// 自動施展技，判斷是否要多打一下
int autoCasting(object me, object target, object weapon)
{
    int hit, damage, sk, bsk;

    bsk = me->query_skill("force", 1);
    sk = me->query_skill(SKILL_NAME,1);

    // 判斷是否成功發動
    if( me->query_stat("mp") < sk/10 ) return 1;
    if( bsk < 80 ) return 1;
    if( sk < 30 ) return 1;

    if( sk < 80 ) {
        if( random(sk) < sk*9/10 ) return 1;     // 20~80 級 10%
    } else if( sk < 150 ) {
        if( random(sk) < sk*8/10 ) return 1;     // 81~150 級 20%
    } else if( random(sk) < sk*7/10 ) return 1;  // 151~200 級 30%

    message_vision("$N腳步快速的圍繞者$n，突然一招"HIW"『"HIG + SKILL_NAME_C + HIW"』"NOR"朝$n擊落...\n", me, target);

    // 是否命中
    hit = isHit(me, target);

    if( !hit ) {
        message_vision("$N有驚無險的閃過了這一招...\n", target);
    } else {
        damage = getDamage(me, target, sk);
        target->receive_damage(damage, me);
        message_vision( sprintf("$n沒辦沒躲開，被打得吐出一口鮮血...(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);
    }
    me->damage_stat("mp", sk/5, me);
    me->improve_skill(SKILL_NAME, 1);

    return 1;
}