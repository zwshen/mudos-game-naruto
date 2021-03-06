// 變化系 lv1：電念力
// -Tmr 2005/10/27

// 2006/06/04 -Tmr
// update by Acme 2007.03.16
// 增加附加能力 by mouse 2007/7/25

#include <ansi.h>
#define SKILL_NAME "electric variation"
#define SKILL_NAME_C "電念力變化"
#define SKILL_CLASS "variation"

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
    return ability + me->query_skill(SKILL_NAME)*3/20;
}

// 攻擊力量影響
int attack(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/40;
}

// 是否命中
int isHit(object me, object target, int sk)
{
    int hit, i;

    i = sk/2;

    me->add_temp("exact", i);
    hit = COMBAT_D->isHit(me, target);
    me->add_temp("exact", -i);

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

    if( sk < 100 ) return damage/4;          // 25%
    else if( sk < 120 ) return damage*7/25;  // 28%
    else if( sk < 150 ) return damage/3;     // 33%
    else if( sk < 180 ) return damage*13/50; // 36%
    else if( sk < 199 ) return damage*2/5;   // 40%
    else return damage*50/100;               // 50%

    return damage;
}

int autoCasting(object me, object target, object weapon)
{
    int hit, damage, i, sk;
    object *targets;

    sk = me->query_skill(SKILL_NAME);
    targets = me->query_enemy();

    // 機率 30%
    if( sk < 30 ) return 1;
    if( me->query_skill("variation") < 30 ) return 1;
    if( random(sk) < sk*7/10 ) return 1;

    // mp 不足不使用
    if( me->query_stat("mp") < 50 ) return 1;

    message_vision("$N身上的念力忽然轉變成"HIC"駭人的電氣"NOR"...\n", me, target);

    for(i=0;i<sizeof(targets);i++) {
        if( i > 2 ) break;                 // 只對三個人有用
        hit = isHit(me, targets[i], sk);   // 命中

        if( !hit ) {
            message_vision("$n避開了攻擊，地上燒出一點焦黑。\n", me, targets[i]);
        } else {
            damage = getDamage(me, targets[i], sk);  // 傷害

            // 傷害盾吸收
            damage = COMBAT_D->receive_damage(targets[i], me, damage);

            targets[i]->receive_damage(damage, me);
            message_vision( sprintf("$n一聲慘叫，身上傳出陣陣焦味...(%d) %s\n", damage, COMBAT_D->report_status(targets[i])), me, targets[i]);
        }
    }
    me->improve_skill(SKILL_NAME, 1);

    if( sk > 150 ) me->damage_stat("mp", 35, me);
    else if( sk > 100 ) me->damage_stat("mp", 25, me);
    else me->damage_stat("mp", 15, me);

    return 1;
}