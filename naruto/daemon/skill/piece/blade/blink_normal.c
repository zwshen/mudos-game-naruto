#include <ansi.h>
#define SKILL_NAME "blink normal"
#define SKILL_NAME_C "直角閃光"
#define SKILL_CLASS "blade"

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
    int hit, raiseHit;

    raiseHit = me->query_skill(SKILL_NAME, 1);

    me->add_temp("apply/exact", raiseHit);
    hit = COMBAT_D->isHit(me, target);
    me->add_temp("apply/exact", -raiseHit);

    return hit;
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    int damage, raiseSK;
    object wp;

    raiseSK = sk + me->query_skill("blade");

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    if( raiseSK < 150 ) return damage*2/5;        // 40%
    else if( raiseSK < 200 ) return damage*3/5;   // 60%
    else if( raiseSK < 250 ) return damage*4/5;   // 80%
    else if( raiseSK < 300 ) return damage;       // 100%
    else if( raiseSK < 360 ) return damage*11/10; // 110%
    else return damage*125/100;              // 125%
}

// 技能使用後 
void setEffect(object me, int sk, int hit)
{
    if( !hit ) {
        me->damage_stat("mp", sk/40, me);
    } else {
        me->damage_stat("mp", sk/20, me);
    }
    me->improve_skill(SKILL_NAME, 1);
}

int autoCasting(object me, object target, object weapon)
{
    int damage, sk, hit;

    sk = me->query_skill(SKILL_NAME, 1);

    // 判斷是否啟動
    if( !me->query_temp("weapon/righthand") && !me->query_temp("weapon/lefthand") && !me->query_temp("weapon/twohanded")) return 1;
    if( me->query_stat("mp") < sk/20 ) return 1;
    if( me->query_skill("blade", 1) < 20 ) return 1;
    if( sk < 20 ) return 1;

    if( sk < 80 ) {                          
        if( random(sk) < sk*9/10 ) return 1; // 20~80 級 10%
    } else if( sk < 150 ) {                  
        if( random(sk) < sk*8/10 ) return 1; // 81~150 級 20%
    } else {                                 
        if( random(sk) < sk*7/10 ) return 1; // 151~200 級 30%
    }
    // 命中
    hit = isHit(me, target);

    message_vision("\n$N說道﹕"HIG"我非常討厭不正經的刀法！看我的「"+me->query("name")+HIG"空割」！\n\n"NOR, me, target);
    message_vision("$N舉起武器朝著$n發出一道九十度直角刀氣"HIC"『"HIW"直角閃光"HIC"』"NOR"撲向$n！\n", me, target);

    if( !hit ) {
        message_vision("$N稍微往旁邊跑開一些，光束便直線飛走了...\n", target);
    } else {
        damage = getDamage(me, target, sk);

        // 傷害盾吸收
        damage = COMBAT_D->receive_damage(target, me, damage);

        target->receive_damage(damage, me);
        message_vision( sprintf("「刷」$n被光束擊中，沿路的地面都被刀氣切開(%d) %s\n", damage, COMBAT_D->report_status(target) ), me, target);
    }
    setEffect(me, sk, hit);
    return 1;
}