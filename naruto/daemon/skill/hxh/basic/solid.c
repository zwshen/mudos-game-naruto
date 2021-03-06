// 獵人念能力：堅(solid)
// create by Tmr
// update by Acme 2007.03.16
// 稍微增強效果 by mouse 2007/7/25

#include <ansi.h>
#define SKILL_NAME "solid"
#define SKILL_NAME_C "堅"
#define SKILL_CLASS "psychical"

inherit SKILL;

// 要求 DEMON_D 登錄技能
void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon(SKILL_NAME);
}

// 技能種類
string query_class() { return SKILL_CLASS; }

// 要 enable 才會有作用
int valid_enable(string base_skill) { return base_skill == "parry"; }

// 技能升級後會呼叫的函式，通常用來設定升下一級所需的經驗
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

string *parry_msg_solid = ({
    HIW"只聽見「碰」的一聲，$N就像是在攻擊硬石牆似的。\n"NOR,
    HIW"$n身體在霎時之間變的堅不可摧，試著削弱$N攻擊的威力。\n"NOR,
    HIW"在千鈞一髮之際，$n大幅地提高身上念力的密度，試抵擋住$N的攻擊。\n"NOR,
});

string *parry_msg = ({
    "但是被$n格開了",
    "但是被$n擋住了",
});

string *parry_enable = ({
    "但是$n運用堅阻擋了$N的攻擊",
    "但是$n使用堅將氣集中在腕部，硬生生地擋住了$N的攻擊",
    "$n立即發動堅將$N攻擊格開了",
});

int receiveDamage(object me, object target, int damage)
{ 
    int lv;

    // enable的判斷好像有誤，parry沒裝堅依然會使用，所以在這也加上判斷
    if( me->skill_mapped("parry") != "solid" ) return damage;
    if( me->query_stat("mp") < 100 ) return damage;

    lv = me->query_skill(SKILL_NAME)*2 + random(me->query_skill("parry"));
    if( random(me->query_skill(SKILL_NAME)) < random(200) ) return damage;

    // 原傷害就已經是 0 了，使用堅卻變成有傷害
    // 應該傷害超過堅一定值以上才會造成傷害
    // 過低就一樣是打 0 滴
    if( damage > lv/2 ) {
        damage -= lv;
        if( damage < 0 ) damage = random(20) + 5;
    } else {
        damage = 0;
    }
    // 成功加強防禦
    message_vision(parry_msg_solid[random(sizeof(parry_msg_solid))], target, me);

    // 消秏一些念力
    me->damage_stat("mp", damage/20+random(10), me);

    // 增加經驗值
    me->improve_skill(SKILL_NAME, 1);

    return damage;
}

string getDefendAction(object me)
{
    string skill = me->skill_mapped("parry");

    // 沒有 enable 任何技能
    if( !skill || skill == "parry" )
        return parry_msg[random(sizeof(parry_msg))];
    else return parry_enable[random(sizeof(parry_enable))];
}
