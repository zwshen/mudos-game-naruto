#include <ansi.h>
#define SKILL_NAME "attack star"
#define SKILL_NAME_C "攻擊星"
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

int intimidate(object me, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/10;
}

// 計算是否命中
int isHit(object me, object target, int sk)
{
    int hit, raiseHit;

    if( sk > 100 ) raiseHit = me->query_skill(SKILL_NAME, 1);
    else raiseHit = me->query_skill(SKILL_NAME, 1)/3;

    me->add_temp("apply/exact", raiseHit);
    hit = COMBAT_D->isHit(me, target);
    me->add_temp("apply/exact", -raiseHit);

    return hit;
}

// 取得傷害
int getDamage(object me, object target, int sk, object staff)
{
    int damage;
    object wp;

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    damage += staff->query("damage/twohanded/upper");

    if( sk < 100 ) return damage/2;          // 50%
    else if( sk < 120 ) return damage*3/5;   // 60%
    else if( sk < 150 ) return damage*7/10;  // 70%
    else if( sk < 180 ) return damage*4/5;   // 80%
    else if( sk < 199 ) return damage*9/10;  // 90%
    else return damage;                      // 100%
}

// 技能使用後 
void setEffect(object me, int sk, int hit)
{
    if( !hit ) {
        me->damage_stat("mp", sk/10, me);
    } else {
        me->damage_stat("mp", sk/5, me);
    }
    me->improve_skill(SKILL_NAME, 1);
}

int autoCasting(object me, object target, object weapon)
{
    string msgin, msgout;
    int damage, sk, check, hit;
    object staff;

    sk = me->query_skill(SKILL_NAME, 1);

    // 先偵測身上有沒有彈弓
    if( !objectp(staff = present("_CATAPULT_", me)) ) return 1;

    // 判斷是否啟動
    if( me->query_stat("mp") < sk/5 ) return 1;
    if( me->query_skill("activity", 1) < 60 ) return 1;
    if( sk < 80 ) return 1;

    if( sk < 80 ) {                          // 20~80 級 10%
        if( random(sk) < sk*9/10 ) return 1;
    } else if( sk < 150 ) {                  // 81~150 級 20%
        if( random(sk) < sk*8/10 ) return 1;
    } else {                                 // 151~200 級 30%
        if( random(sk) < sk*7/10 ) return 1;
    }
    // 判斷敘述用
    if( sk > 100 ) check = 4 - random(2);
    else check = random(2) + 1;

    // 命中判斷
    hit = isHit(me, target, sk);

    // 敘述統一寫在這裡，減少程式
    switch( check ) {
        case 1:
            msgin = "$N使出"HIW"『"NOR"鉛星"HIW"』"NOR"拿出一顆鉛子彈拉弓射向$n！\n";
            msgout = "「咚」地一聲$n的頭上被砸出一個大包...(%d) %s\n";
            break;
        case 2:
            msgin = "$N偷偷笑了一下，拿起一顆平凡無奇的"HIR"子彈"NOR"，快速的射向$n！\n"NOR;
            msgout = "「磅」！子彈命中$n之後忽然發生爆炸，原來是"HIY"『"HIR"火藥星"HIY"』"NOR"！(%d) %s\n";
            break;
        case 3:
            msgin = "$N拿起四顆子彈齊射而出，子彈在高空中爆開宛如"HIC"『"RED"火鳥"HIC"』"NOR"，快速的飛向$n！\n";
            msgout = "「轟」地一聲巨響，$n被爆炸的衝擊力往後面翻了幾圈(%d) %s\n";
            break;
        case 4:
            msgin = "$N朝著$n的方向連續射出幾種重量不同的"HIR"『"HIY"金屬"HIR"』"NOR"！\n";
            msgout = "金屬彈「霹靂啪啦」地打在$n的身上，痛的$n蹲在地上發抖(%d) %s\n";
            break;
        default: return notify_fail("判斷有問題喔。\n"); break;
    }
    // 攻擊敘述、傷害判定
    if( sk > 100 + random(200) ) {
        damage = getDamage(me, target, sk, staff)*2;
        message_vision(HIW"(精準射擊) "NOR+msgin, me, target);
    } else {
        damage = getDamage(me, target, sk, staff);
        message_vision(msgin, me, target);
    }
    if( !hit ) {
        message_vision("但是$N的攻擊失去了準頭，不知道射到哪去了。\n", me, target);
    } else {
        // 傷害盾吸收
        damage = COMBAT_D->receive_damage(target, me, damage);
        target->receive_damage(damage, me);
        message_vision( sprintf(msgout, damage, COMBAT_D->report_status(target)), me, target);
    }
    setEffect(me, sk, hit);
    return 1;
}