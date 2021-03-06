#include <ansi.h>
#define SKILL_NAME "chop two"
#define SKILL_NAME_C "二斬"
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

int attack(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/10;
}

int sock(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/40;
}

// 檢查是否能使用技能
int isCast(object me, string act, object target, int sk)
{
    if( !objectp(me) || !objectp(target) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( act != "attack" ) {
        tell_object(me, "目前" + SKILL_NAME_C + "只有 attack 功\能。\n");
        return 0;
    }

    if( !me->is_fighting(target) ) {
        tell_object(me, "你並未和對方在戰鬥中...\n");
        return 0;
    }

    if( !me->query_temp("weapon/righthand") || !me->query_temp("weapon/lefthand") ) {
        tell_object(me, "這是二刀流技能，必須拿二把武器才能使用。\n");
        return 0;
    }

    if( me->query_skill("blade", 1) < 60 || sk < 50 ) {
        tell_object(me, "你的能力不足以使用這一招。\n");
        return 0;
    }

    if( me->query_stat("mp") < 120 ) {
        tell_object(me, "你身體狀況不佳，不能使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    return 1;
}

// 計算是否命中
int isHit(object me, object target)
{
    int i, j;

    i = COMBAT_D->intimidate(me, 1);
    j = COMBAT_D->wittiness(target, 1);

    if( COMBAT_D->SkillHit(me, target, i, j) ) return 1;
    else return 0;
}

// 取得傷害
int getDamage(object me, object target, int sk)
{
    int damage, raiseDamage;
    object wp;

    raiseDamage = sk + me->query_skill("blade")/2;

    if( wp = me->query_temp("weapon/twohanded") ) raiseDamage -= COMBAT_D->isDamage(me, target, wp)*3/4;
    else if( wp = me->query_temp("weapon/righthand") ) raiseDamage -= COMBAT_D->isDamage(me, target, wp)*3/4;
    else if( wp = me->query_temp("weapon/lefthand") ) raiseDamage -= COMBAT_D->isDamage(me, target, wp)*3/4;
    else raiseDamage -= COMBAT_D->isDamage(me, target, 0)*3/4;

    me->add_temp("apply/attack", raiseDamage);

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    me->add_temp("apply/attack", -raiseDamage);

    return damage;
}

// 技能使用後 
void setEffect(object me, int sk, int number)
{
    // 空行msg
    message_vision("\n", me);

    // 判斷前面的攻擊是否命中造成自定, 超過三招沒中多定2回
    if( me->query_temp("busy_temp") > 2 ) {
        me->start_busy(6);
        me->delete_temp("busy_temp");
    } else {
        me->start_busy(3);
        me->delete_temp("busy_temp");
    }
    me->damage_stat("mp", 20*number, me);
    me->improve_skill(SKILL_NAME, 1);
}

int perform_action(object me, string act, object target)
{
    string msgin, msgout;
    int number, damage, hit, sk, i;
    object wp;

    sk = me->query_skill(SKILL_NAME, 1);

    // 檢查是否能使用技能
    if( !isCast(me, act, target, sk) ) return 1;

    message_vision("\n$N將手中雙刀平舉，擺\出「二」的字樣...『"HIC"二斬"NOR"』\n", me, target);

    // 刀術影響與連擊判斷
    if( me->query_skill("blade", 1) < 100 ) number = 0;
    else number = sk/50;

    for(i=0;i<number;i++) {

        // 命中、傷害每擊都要判斷一次
        hit = isHit(me, target); 
        damage = getDamage(me, target, sk);

        switch( i ) {
            case 0: 
                msgin = "$N反手拿雙刀朝空中一跳使出『"HIM"登樓"NOR"』$n沒有閃開受到了傷害(%d) %s\n";
                msgout = "$N反手拿雙刀朝空中一劈使出『"HIM"登樓"NOR"』但是被$n閃過了...\n";
                break;
            case 1:
                msgin = "$N在空中換回正手拿刀朝下發出『"HIC"應登樓"NOR"』斬擊，砍傷了$n(%d) %s\n";
                msgout = "$N在空中換回正手拿刀朝下發出『"HIC"應登樓"NOR"』斬擊，但是被$n閃過了...\n";
                break;
            case 2:
                msgin = "$N順勢將雙刀橫揮向$n『"HIG"閃"NOR"』強大的衝擊砍傷了$n(%d) %s\n";
                msgout = "$N順勢將雙刀橫揮向$n『"HIG"閃"NOR"』，但是被$n閃過了...\n";
                break;
            case 3:
                msgin = "$N身子一轉，又側身朝$n一劈『"HIY"沙紋"NOR"』$n無法閃躲硬是吃了這招(%d) %s\n";
                msgout = "$N身子一轉，又側身朝$n一劈『"HIY"沙紋"NOR"』，但是被$n閃過了...\n";
                break;
            default: return notify_fail("判斷有問題喔。\n"); break;
        }
        if( hit ) {
            target->receive_damage(damage, me);
            message_vision(sprintf(msgin, damage, COMBAT_D->report_status(target) ), me, target);
        } else {
            message_vision(msgout, me, target);
            me->add_temp("busy_temp",1);
        }
    }
    setEffect(me, sk, number);
    return 1;
}