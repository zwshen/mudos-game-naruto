#include <ansi.h>
#define SKILL_NAME "body skill"
#define SKILL_NAME_C "鐵塊拳法"
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

// 取得傷害
int getDamage(object me, object target, int sk, int i)
{
    int damage, raiseDamage;
    object wp;

    raiseDamage = sk*8 + me->query_skill("body iron")*3;

    if( i == 1 ) raiseDamage += me->query_skill("gun finger")*3;
    else if( i == 2 ) raiseDamage += me->query_skill("kick haze wolf")*3;
    else if( i == 3 ) raiseDamage += me->query_skill("heavy hit")*2 + me->query("savage hit");

    me->add_temp("apply/attack", raiseDamage); 

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    me->add_temp("apply/attack", -raiseDamage);

    return damage;
}

int autoCasting(object me, object target, object weapon)
{
    string msgin, msgout;
    int damage, sk, i;

    sk = me->query_skill(SKILL_NAME, 1);

    // 判斷是否啟動
    if( me->query_stat("mp") < sk/5 ) return 1;
    if( me->query_skill("body iron", 1) < 200 ) return 1;
    if( sk < 40 ) return 1;

    if( sk < 80 ) {                          
        if( random(sk) < sk*9/10 ) return 1;  // 20~80 級 10%
    } else if( sk < 150 ) {                  
        if( random(sk) < sk*17/20 ) return 1; // 81~150 級 15%
    } else {                                 
        if( random(sk) < sk*8/10 ) return 1;  // 151~200 級 20%
    }
    i = random(3) + 1;

    switch( i ) {
        case 1:
            msgin = "$N右手食指忽然朝$n一彈，露出尖銳的指甲"RED"『"HIC"鐵塊拳法•狼牙式"NOR+RED"』"NOR"！\n";
            msgout = "「啪」地一聲，$n被攻擊所彈中，整個人飛了出去(%d)%s\n";
            break;
        case 2:
            msgin = "$N狼吼一聲發動"RED"『"HIY"鐵塊拳法•狼狩"NOR+RED"』"NOR"以極快的速度逼近$n準備進行狩獵！\n";
            msgout = "$n尚未反應過來，$N馬上出招「四面八方之手」瞬間擊傷了$n(%d)%s\n";
            break;
        case 3:
            msgin = "$N踢出多道斬擊，身子使起"RED"『"HIM"鐵塊拳法•重步狼"NOR+RED"』"NOR"藏於斬擊中直奔$n！\n";
            msgout = "$n光顧著抵禦斬擊，誰知$N突然出現以給予$n致命一擊(%d)%s\n";
            break;
        default:
            msgin = "公式有算錯...快找巫師來修理吧。\n";
            msgout = "這個招式沒有傷害，因為公式算錯了。\n";
            break;
    }
    message_vision(msgin, me, target);
    if( !COMBAT_D->isHit(me, target) ) {
        message_vision("$N好像被狼給同化了，攻擊到一半忽然蹲在原地嗷嗚嗷嗚的叫...\n", me, target);
        me->start_busy(2);
    } else {
        damage = getDamage(me, target, sk, i);
        target->receive_damage(damage, me);
        message_vision( sprintf(msgout, damage, COMBAT_D->report_status(target) ), me, target);
    }
    me->damage_stat("mp", sk/2, me);
    me->improve_skill(SKILL_NAME, 1);
    return 1;
}