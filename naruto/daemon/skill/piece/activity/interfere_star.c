#include <ansi.h>
#define SKILL_NAME "interfere star"
#define SKILL_NAME_C "干擾星"
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

int evade(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/20;
}

// 計算是否命中
int isHit(object me, object target, int sk)
{
    int hit, meHit, targetHit;

    if( sk > 100 ) meHit = me->query_skill(SKILL_NAME, 1)/2 + me->query_ability("intimidate");
    else meHit = me->query_ability("intimidate");

    targetHit = target->query_ability("evade");

    me->add_temp("apply/exact", meHit);
    target->add_temp("apply/evade", targetHit);
    hit = COMBAT_D->isHit(me, target);
    me->add_temp("apply/exact", -meHit);
    target->add_temp("apply/evade", -targetHit);

    return hit;
}

// 攻擊人數判斷
int check_number(object me, int sk)
{
    int number;

    number = (sk/100) - 1;
    if( number <= 0 ) number = 0;

    return number;
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

    if( sk < 100 ) return damage*3/20;            // 15%
    else if( sk < 120 ) return damage*9/50;       // 18%
    else if( sk < 150 ) return damage*23/100;     // 23%
    else if( sk < 180 ) return damage*13/50;      // 26%
    else if( sk < 199 ) return damage*3/10;       // 30%
    else return damage*2/5;                       // 40%

    return damage;
}

int autoCasting(object me, object target, object weapon)
{
    string msgin, msgout;
    int damage, sk, check, i, number, hit;
    object *targets, staff;

    sk = me->query_skill(SKILL_NAME, 1);
    targets = me->query_enemy();

    // 先偵測身上有沒有彈弓
    if( !objectp(staff = present("_CATAPULT_", me)) ) return 1;

    // 判斷是否啟動
    if( me->query_stat("mp") < sk/20 ) return 1;
    if( me->query_skill("activity", 1) < 40 ) return 1;
    if( sk < 20 ) return 1;

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

    // 攻擊人數
    number = check_number(me, sk);

    // 敘述統一寫在這裡，減少程式
    switch( check ) {
        case 1:
            msgin = "$N拿出腰間彈弓，隨手摸出一顆"HIW"雞蛋"NOR"射向$n！\n";
            msgout = "「啪」地一聲雞蛋砸中$n，四周傳出一陣腥臭味...(%d) %s\n";
            break;
        case 2:
            msgin = "$N拿出腰間彈弓，抓了一把子彈射向$n！"HIW"後面還牽了一長串白煙...\n"NOR;
            msgout = "「碰」地一聲子彈爆開...四周濃煙密佈，嗆的$n拼命咳嗽(%d) %s\n";
            break;
        case 3:
            msgin = "$N拉起彈弓大喊"HIY"『"HIG"向日葵星"HIY"』"NOR"射出的子彈忽然爆開噴向四面八方！\n";
            msgout = "「答答」數聲無數的子彈打擊在$n身上，痛的$n哇哇大叫(%d) %s\n";
            break;
        case 4:
            msgin = "$N邪笑一下射出"HIB"『"HIM"鐵蒺藜地獄"HIB"』"NOR"只見地上插滿了鐵蒺藜！\n";
            msgout = "忽然傳出「唉呦」一聲，原來是$n誤踩到地上的陷阱了(%d) %s\n";
            break;
        default: return notify_fail("判斷有問題喔。\n"); break;
    }
    message_vision(msgin, me, target);
    for(i=0;i<sizeof(targets);i++) {
        if( i > number ) break;   // 最多攻擊兩人
        if( !hit ) {
            message_vision("但是$N的攻擊失去了準頭，不知道射到哪去了。\n", me, targets[i]);
        } else {
            damage = getDamage(me, targets[i], sk, staff);

            // 傷害盾吸收
            damage = COMBAT_D->receive_damage(target, me, damage);

            targets[i]->receive_damage(damage, me);

            // 沒有被定才能定人
            if( !targets[i]->is_busy() ) targets[i]->start_busy(1);
            message_vision( sprintf(msgout, damage, COMBAT_D->report_status(targets[i])), me, targets[i]);
        }
    }
    me->damage_stat("mp", sk/20*i, me);
    me->improve_skill(SKILL_NAME, 1);
    return 1;
}