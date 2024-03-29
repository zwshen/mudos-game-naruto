/* combatd.c 戰鬥精靈
   create by Acme 2007.03.15
    修正拿武器 + enable 會找不到敘述的問題 by mouse 2007/7/25
*/

// #pragma save_binary
#include <ansi.h>

#define PI 3.14159265359

void create() { seteuid(getuid()); }

string *combat_actions = ({
    "$N用手中的$w往$n$l揮去",
    "$N揮動$w，往$n$l打去",
    "$N將手中$w對準$n$l揮去",
    "$N揮動手中$w，攻向$n$l",
    "$N尋著空隙，一個箭步上前手中$w便往$n$l擊落",
});

string *dodge_msg = ({
    "但是和$p$l偏了幾寸",
    "但是被$p機靈地躲開了",
    "但是$n身子一側，閃了開去",
    "但是被$p及時避開",
    "但是$n已有準備，不慌不忙的躲開",
    "但是沒中",
});

string *parry_msg = ({
    "但是被$n格開了",
    "但是被$n擋住了",
});

// 依傷害程度，取得受傷訊息
string getDamageMessage(int damage)
{
    if( damage < 20 ) return "結果只是勉強造成一處輕微傷害！";
    if( damage < 40 ) return "結果造成輕微的傷害！";
    if( damage < 80 ) return "結果造成一處傷害！";
    if( damage < 160 ) return "結果造成一處嚴重傷害！";
    if( damage < 320 ) return "結果造成頗為嚴重的傷害！";
    if( damage < 640 ) return "結果造成相當嚴重的傷害！";
    if( damage < 1280 ) return "結果造成十分嚴重的傷害！";
    if( damage < 2560 ) return "結果造成極其嚴重的傷害！";
    return "結果造成非常可怕的嚴重傷害！";
}

// 取得人物的體力值回報
string report_status(object me)
{
    int hp_max, ratio;
    
    if( !(hp_max = me->query_stat_maximum("hp")) ) return "";
    ratio = me->query_stat("hp")*100/hp_max;
    
    if( ratio >= 80 ) return HIK"["HIG + me->name() + HIG + ratio + "%" + HIK"]"NOR;
    else if( ratio >= 30 ) return HIK"["HIY + me->name() + HIY + ratio + "%" + HIK"]"NOR;
    else return HIK"["HIR + me->name() + HIR + ratio + "%" + HIK"]"NOR;
}

private int do_fight(object me, object target)
{
    if( !me || !target ) return 0;
    if( !living(me) || (userp(target) && !interactive(target)) ) return 0;
    if( !environment(me)  || !environment(target) ) return 0;

    if( environment(me)->is_area() ) {
        if( !area_environment(me, target) ) return 0;
    } else {
        if( environment(me) != environment(target) ) return 0;
        if( environment(me)->query("no_fight") ) return 0;
    }

    if( me->is_fighting(target) && target->is_fighting(me) ) return 0;
    
    me->kill_ob(target);
    if( userp(target) ) target->fight_ob(me);
    else target->kill_ob(me);
    
    return 1;
}

// 結仇
void start_hatred(object me, object obj)
{
    if( do_fight(me, obj) )
        message_vision( HIW"$N"HIW"和$n"HIW"仇人相見分外眼紅，立刻打了起來！\n"NOR, me, obj);
}

// 世仇
void start_vendetta(object me, object obj)
{
    if( do_fight(me, obj) )

        message_vision( HIW"$N"HIW"和$n"HIW"仇人相見分外眼紅，立刻打了起來！\n"NOR, me, obj);
}

// 侵略
void start_aggressive(object me, object obj)
{
    if( do_fight(me, obj) )
        message_vision( HIW"$N"HIW"一見到$n"HIW"二話不說，立刻就打了起來！\n" NOR, me, obj);
}

void auto_fight(object me, object obj, string type)
{
    if( !userp(me) && !userp(obj) ) return;
    call_out( "start_" + type, 0, me, obj);
}

void start_camp_kill(object me, object obj, string msg)
{
    if( do_fight(me, obj) )
    
    message_vision(msg, me, obj);
}

void camp_auto_kill(object me, object obj, string msg)

{
    call_out("start_camp_kill", 0, me, obj, msg);
}

void announce(object me, string event)
{
    switch(event) {
        case "dead":
            message_vision("\n$N呻吟了幾聲，咳出一口鮮血，便斷了氣。\n\n", me);
            break;
        case "unconcious":
            message_vision("\n$N腳下一個不穩﹐跌在地上一動也不動了。\n\n", me);
            break;
        case "revive":
            message_vision("\n$N慢慢睜開眼睛﹐清醒了過來。\n\n", me);
            break;
    }
}

// 攻擊技巧
int intimidate(object me, int type)
{
    int ability;

    string sk, *skills;
    
    if( !me ) return 0;
    
    ability = me->query_ability("intimidate");

    // 拿雙手武器，技巧要降低
    if( me->query_temp("weapon/twohanded") )
        ability = ability*7/10;

    skills = keys(me->query_skills());

    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("intimidate", SKILL_D(sk)) )
                ability = SKILL_D(sk)->intimidate(me, ability, type);
    }

    return ability;
}

// 防禦技巧
int wittiness(object me, int type)

{
    int ability;
    string sk, *skills;
    
    if( !me ) return 0;
    
    ability = me->query_ability("wittiness");
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("wittiness", SKILL_D(sk)) )
                ability = SKILL_D(sk)->wittiness(me, ability, type);
    }
    
    return ability;
}

// 命中率
int exact(object me, object target, int type)
{
    int ability;
    string sk, *skills;

    
    if( !me || !target ) return 0;
    
    ability = me->query_ability("exact");
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("exact", SKILL_D(sk)) )
                ability = SKILL_D(sk)->exact(me, target, ability, type);
    }
    
    return ability;
}

// 迴避率
int evade(object me, object target, int type)
{
    int ability;
    string sk, *skills;
    
    if( !me || !target ) return 0;
    

    // 被設定沒辦法迴避
    if( me->query("no_evade") ) return 0;
    
    ability = me->query_ability("evade");
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
       if( me->skill_mapped(sk) )
           if( function_exists("evade", SKILL_D(sk)) )
               ability = SKILL_D(sk)->evade(me, target, ability, type);
    }
    
    return ability;
}

// 武器攻擊力
int weapon_attack(object weapon, int damage, int use)
{
    int ability = damage;
    string type;

    if( stringp(type = weapon->query("equipped")) && type[0..6] == "weapon/" ) {
        mapping dam;

        type = type[7..];
        if( mapp(dam = weapon->query("damage/" + type)) ) {
            // 武器殺傷力
            if( use ) ability = damage + dam["lower"] + random( dam["upper"] - dam["lower"] );
            else ability = damage + dam["lower"] + (dam["upper"]-dam["lower"])/2;
            // 加乘殺傷力
            ability = ability * dam["bonus"] / 100;
        }
    }
    return ability - damage;
}

// 攻擊力
int attack(object me, object target, int type, object weapon)
{
    int ability;
    string sk, *skills;
    
    if( !me || !target ) return 0;
    
    // 人物本身攻擊力 (除2主要是要讓重擊(heavy hit)補足另一半的攻擊力)
    ability = me->query_ability("attack") / 2;

    // 武器加乘
    if( weapon && weapon->is_weapon() )
        ability += weapon_attack(weapon, ability, type);
    
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("attack", SKILL_D(sk)) )
                ability = SKILL_D(sk)->attack(me, target, ability, type);
    }
    
    return ability;
}

// 防禦力
int defend(object me, object target, int type)
{
    int ability;
    string sk, *skills;
    
    if( !me || !target ) return 0;
    

    // 被設定沒辦法防禦
    if( me->query("no_defend") ) return 0;
    
    ability = me->query_ability("defend");
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("defend", SKILL_D(sk)) )
                ability = SKILL_D(sk)->defend(me, target, ability, type);
    }
    
    return ability;
}

// 致命一擊
int sock(object me, object target, int type)
{
    int ability;
    string sk, *skills;
    
    if( !me || !target ) return 0;
    
    ability = me->query_ability("sock");
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("sock", SKILL_D(sk)) )
                ability = SKILL_D(sk)->sock(me, target, ability, type);
    }
    
    return ability;
}

// 致命一擊傷害提升%, 原始為(150%)
int sockPower(object me, object target, int type)
{
    int ability = 150;
    string sk, *skills;
    if( !me || !target) return ability;
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("sockPower", SKILL_D(sk)) )

                ability = SKILL_D(sk)->sockPower(me, target, ability, type);
    }
    
    return ability;
}

// 受到傷害前，讓技能先跑過 receive_damage 
// 如何便可以製作 "暫時無敵技" 或是 "傷害吸收盾" 之類的技能
int receive_damage(object me, object target, int damage)
{
    string sk, *skills;
    
    if( !me || !target ) return 0;
    
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("receiveDamage", SKILL_D(sk)) )
                damage = SKILL_D(sk)->receiveDamage(me, target, damage);
    }
    
    return damage;
}

// 取得攻擊訊息
// 攻擊訊息由 enable 在 combat 技能上的技能提供
// 若沒 enable 則由戰鬥系統提供
private string getCombatActions(object me, object weapon)
{
    string skill = me->skill_mapped("combat");
    // 沒有 enable 任何技能
    if( !skill || skill == "combat" ) {
        if( weapon->query("have_mag") ) {
            if( weapon->is_weapon() ) return weapon->getCombatAction(me, weapon);
        }
        if( weapon->is_weapon() ) return combat_actions[random(sizeof(combat_actions))];
        else return RACE_D(me->query_race())->query_action();
    } else {
        if( weapon->query("have_mag") ) {
            if( weapon->is_weapon() ) return weapon->getCombatAction(me, weapon);
        }
        if( weapon->is_weapon() ) return combat_actions[random(sizeof(combat_actions))];
        else return SKILL_D(skill)->getCombatAction(me, weapon);
    }
}


// 取得閃躲訊息
// 攻擊訊息由 enable 在 dodge 技能上的技能提供
// 若沒 enable 則由戰鬥系統提供
private string getEvadeActions(object me)
{
    string skill = me->skill_mapped("dodge");

    // 沒有 enable 任何技能
    if( !skill || skill == "dodge" )
        return dodge_msg[random(sizeof(dodge_msg))];
    else return SKILL_D(skill)->getEvadeAction(me);
}

// 取得防禦訊息
// 攻擊訊息由 enable 在 parry 技能上的技能提供
// 若沒 enable 則由戰鬥系統提供
private string getDefendActions(object me)
{
    string skill = me->skill_mapped("parry");

    // 沒有 enable 任何技能
    if( !skill || skill == "parry" )
        return parry_msg[random(sizeof(parry_msg))];

    else return SKILL_D(skill)->getDefendAction(me);
}

// 送出戰鬥訊息
private void printMessage(string msg, object me, object target, object weapon)
{
    if( msg && stringp(msg) ) {
        string *limbs = target->query("limbs");
        if( !arrayp(limbs) || !sizeof(limbs) )
            msg = replace_string(msg, "$l", "身上");
        else
            msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
        if( weapon->is_weapon() )
            msg = replace_string(msg, "$w", weapon->name());
        message_vision(msg, me, target);
    }
}

// 常態分佈(Normal distribution) or 高斯分佈(Gaussian distribution)
// 【閒聊】力可(Rick)：我寫下來 x=原本的參照點    x*(sqrt(-2*log(rand))*cos(2*pi*rand)+2.5)
float normalDistribution(int value)
{
    float v, rand, result = 0;

    // int 轉成 float
    v = value;

    // random 0~1
    rand = random(1000000.0)/1000000.0;
    
    // 有可能random到0, 取log會錯, 設成極小值
    if( rand <= 0.0 ) rand = 0.0000001;

    result = v * (sqrt(-2*log(rand)) * cos(2*PI*rand) +2.5);

    return result;
}

// 命中處理:  0. 沒命中, 1. 命中
int isHit(object me, object target)
{
    int chance, exact, evade;

    if( !living(target) ) return 1;
    if( target->query_stat("ap") < 1 ) return 1;
    
    exact = exact(me, target, 1);
    evade = evade(target, me, 1);
    
    // 被打的人是玩家，則判斷其敵人數量，過多會降低迴避率
    if( userp(target) ) {
        int move, amount;
        move = 4;
        amount = sizeof(target->query_enemy());
        if( amount > move ) evade -= (evade/10)*(amount-move);
    }
    
    // 高斯分佈
    return normalDistribution(exact) > normalDistribution(evade);
}

// 給不需要看命中的 sk 使用
int SkillHit(object me, object target, int meHit, int targetHit)
{
    int chance, exact, evade;

    if( !living(target) ) return 1;
    if( target->query_stat("ap") < 1 ) return 1;

    // 高斯分佈
    exact = normalDistribution(meHit);
    evade = normalDistribution(targetHit);

    if( exact > evade ) return 1;
    else return 0;
}

// 傷害處理: 0: 沒有傷害, otherwise: 有傷害
int isDamage(object me, object target, object weapon)
{
    int chance, damage, defend;

    damage = attack(me, target, 1, weapon);

    if( !living(target) ) return damage;

    defend = defend(target, me, 1);

    // 被打的人是玩家，則判斷其敵人數量，過多會降低防禦力
    if( userp(target) ) {
    int move, amount;
        move = 4;
        amount = sizeof(target->query_enemy());
        if( amount > move ) defend -= (defend/10)*(amount-move);
    }

    // 沒有絕對的防禦或不可防禦
    damage -= defend;
    chance = 50 + damage/2;

    if( damage < 0 ) damage = 0;

    if( chance < 10 ) chance = 10;
    else if( chance > 90 ) chance = 90;

    if( damage ) {    // 如果還有攻擊力
        if( random(100) > chance ) return (damage/2)+random(damage/2)+1;  // 防得成功
        else return (damage*2/3) + random(damage/3)+1;                    // 防得不成功
    } else {          // 攻擊力完全被消減掉
        if( random(100) > chance ) return 0;    // 防得很成功
        else return random(5)+1;                // 防得不太成功
    }
}

private int isFight(object me, object target, object weapon)
{
    if( !me || !target ) return 0;
    if( !weapon ) weapon = me;

    if( environment(me)->query("no_fight") && !target->query("unprotect_mark") && !me->query("unprotect_mark") )
        return 0;

    // 戰鬥過程斷線，停止戰鬥
    if( ( userp(me) && !interactive(me) ) || ( userp(target) && !interactive(target) ) )
        return 0;

    // 沒有 ap 沒辦法攻擊
    if( me->query_stat("ap") < 1 ) return 0;

    // 沒有enable戰鬥技能，不會攻擊
    if( !me->skill_mapped("combat") ) return 0;

    // 被設定為不能攻擊
    if( me->query("no_combat") ) return 0;

    return 1;
}

// 正常的攻擊
private int generalAttack(object me, object target, object weapon)
{
    int damage, sock;
    string msg;

    // 是否暴擊
    sock = (sock(me, target, 1) > random(100));

    // 設定攻擊訊息
    msg = (sock ? HIR"(致命一擊) "NOR : "") + getCombatActions(me, weapon) + "，";
    
    // 沒打中
    if( !isHit(me, target) ) {
        // 被攻擊者扣 AP
        if( userp(me) ) target->damage_stat("ap", 1, target);

        // 輸出戰鬥訊息
        msg += getEvadeActions(target) + "。\n";
        printMessage(msg, me, target, weapon);
        return 0;
    }
    
    // 沒產生傷害
    if( !(damage = isDamage(me, target, weapon)) ) {
        // 輸出戰鬥訊息
        msg += getDefendActions(target) + "。\n";
        printMessage(msg, me, target, weapon);
        return 0;
    }

    // 暴擊傷害力計算
    if( sock ) damage = damage * sockPower(me, target, 1) / 100;

    // 攻擊者扣 AP
    if( userp(me) || (me->query_owner() && userp(me->query_owner())) )
        me->damage_stat("ap", random(damage/10) + 1, me);

    // 接受傷害
    damage = receive_damage(target, me, damage);
    target->receive_damage(damage, me);

    // 顯示傷害程度
    msg += getDamageMessage(damage) + "(" + damage + ")";
    // 顯示被攻擊者狀態
    msg += " " + report_status(target) + "\n";
    // 顯示戰鬥訊息
    printMessage(msg, me, target, weapon);

    return 1;
}


// 自動施展的技能處理
private int autoCasting(object me, object target, object weapon)
{
    string sk, *skills;
    
    if( !me || !target ) return 0;

    if( !weapon || !weapon->is_weapon() )
        weapon = 0;
    
    skills = keys(me->query_skills());
    
    foreach(sk in skills) {
        if( me->skill_mapped(sk) )
            if( function_exists("autoCasting", SKILL_D(sk)) )
                SKILL_D(sk)->autoCasting(me, target, weapon);
    }
}

int fight(object me, object target, object weapon)
{
    // 檢查是否能攻擊
    if( !isFight(me, target, weapon) ) return 0;

    // 正常攻擊
    generalAttack(me, target, weapon);

    // 自動施展技
    autoCasting(me, target, weapon);

    return 1;
}
