/*  attack.c - the attack routines
 
    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>
 
    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.
 
    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <ansi.h>
#include <dbase.h>
#include <name.h>
#include <origin.h>
#include <skill.h>

#define CAMP_DIR "/world/camp/"
#define MAX_OPPONENT    4

nosave object charge_target = 0;
nosave object guarding = 0, *guarded = ({});
nosave object *enemy = ({});
nosave mapping killer = ([]);
nosave int attack_patience = 0;
nosave object current_target;


void fight_ob(object ob);
void kill_ob(object ob);

void add_guard(object who);
void remove_guard(object who);
object* wake_guard(object enemy);
void activate_guard(object enemy);
void guard_ob(object target);

object *query_enemy()
{
    return enemy;
}
mapping query_killer()
{
    return killer;
}
object query_charging()
{
    return charge_target;
}
object query_guarding()
{
    return guarding;
}
object query_opponent()
{
    return current_target;
}

varargs int is_fighting(object ob)
{
    return ob ? (member_array(ob, enemy) >= 0) : sizeof(enemy);
}

varargs int is_killing(mixed id)
{
    if( !killer ) return 0;
    if( !id ) return sizeof(killer);

    if( objectp(id) && userp(id) )
        id = id->query("id");

    if( stringp(id) || objectp(id) )
        return !undefinedp(killer[id]);

    return 0;
}

void add_guard(object ob)
{
    if( member_array(ob, guarded) >= 0 ) return;

    tell_object(this_object(), HIY + ob->name() + HIY"開始保護你。\n" NOR);
    guarded += ({ ob });
}

void remove_guard(object ob)
{
    if( member_array(ob, guarded) < 0 ) return;

    guarded -= ({ ob, 0 });
    tell_object(this_object(), HIY + ob->name() + HIY"不再保護你了。\n"+ NOR);
}

object *wake_guard(object target)
{
    return filter(guarded, (:
        objectp($1) && living($1) && environment($1)==environment() &&
        (!$1->is_fighting($(target))) && (environment()->is_area() ? area_environment($(target), $1) : 1 ) && $(target)->visible($1)
    :) );
}

void activate_guard(object target)
{
    fight_ob(target);
}

void guard_ob(object ob)
{
    if( objectp(guarding) && (guarding != ob) ) {
        guarding->remove_guard(this_object());
    }

    guarding = ob;
    if( objectp(ob) ) ob->add_guard(this_object());
}

void fight_ob(object ob)
{
    object *guard;

    if( !objectp(ob) || ob==this_object() || environment(ob) != environment() ) return ;

    // 增加area 判斷 by -Acme-
    if( environment()->is_area() && !area_environment(ob, this_object()) ) return;

    if( ob==guarding ) guard_ob(0);

    set_heart_beat(1);

    if( member_array(ob, enemy)==-1 ) enemy += ({ ob });

    guard = ob->wake_guard(this_object());
    if( sizeof(guard) ) {
        message("system", HIY + ob->name() + HIY"正遭受攻擊！你上前助戰！\n" NOR, guard);
        guard->activate_guard(this_object());
        enemy += guard;
    }

    // 遭受 fight 或 kill 自動呼叫此函式, 方便設計一些 NPC 變化
    if( function_exists( "start_fighting", this_object() ) )
        this_object()->start_fighting(ob);
}

void kill_ob(object ob)
{
    if( userp(ob) ) {
        if( living(ob) && undefinedp(killer[ob->query("id")]) )
            tell_object(ob, HIR "看起來" + this_object()->name() + HIR"想殺死你﹗\n" NOR);
        killer[ob->query("id")] = time();
    } else killer[ob] = time();

    killer = filter(killer, (: stringp($1) || objectp($1) :));

    fight_ob(ob);
}

void charge_ob(object ob)
{
    if( ! ob ) {
        charge_target = 0;
        return;
    }

    if( member_array(ob, enemy) < 0 ) enemy += ({ ob });
    tell_object(this_object(), HIY "你開始將" + ob->name() + HIY"當成首要攻擊目標！\n" NOR);
    charge_target = ob;
}

int remove_enemy(object ob)
{
    if( is_killing(ob) )
        return 0;
    enemy -= ({ ob });
    return 1;
}

void remove_killer(object ob)
{
    map_delete(killer, userp(ob) ? ob->query("id") : ob);
    remove_enemy(ob);
}

int remove_charge()
{
    charge_target = 0;
}

void remove_all_enemy()
{
    enemy = filter(enemy, (: objectp($1) && $1->remove_enemy($(this_object()))==0 :));
}

void remove_all_killer()
{
    object ob;
    killer = ([]);
    enemy->remove_killer(this_object());
    enemy = ({});
}

/* clean_up_enemy()
 *
 * 這個函數用來將已經沒有戰鬥能力的敵人自戰鬥對象中剔除，傳回值如果大於 0
 * 表示尚有敵人。
 */
int clean_up_enemy() {
    enemy = filter(enemy, (:
        objectp($1) && (environment($1)==environment()) && (living($1) || is_killing($1)) && (environment()->is_area() ? area_environment(this_object(), $1) : 1 )
    :) );
    return sizeof(enemy);
}

/* select_opponent()
 *
 * 這個函數用來為人物選擇一個攻擊對象。
 */
private object select_opponent()
{
    object opp;
    int which, intimidate, wittiness, chance;

    if( !arrayp(enemy) || !sizeof(enemy) ) return 0;

    /* 攻擊傾向 = 攻勢等級 + 等待係數 */
    intimidate = COMBAT_D->intimidate(this_object()) + attack_patience;

    /* 如果有首要攻擊目標，優先考慮這個目標 */
    if( charge_target && member_array(charge_target, enemy) >= 0 ) {
        intimidate += intimidate / 5;// charge 的正面效果
        opp = charge_target;
    } else opp = enemy[random(sizeof(enemy))];

    /* 守勢等級 */
    if( living(opp) ) {
        wittiness = COMBAT_D->wittiness(opp);
        if( opp->query_charging() )
            wittiness -= wittiness / 3;// charge 的負面效果
    } else wittiness = 0;

    if( !wittiness ) return opp;
    chance = 50 + (intimidate - wittiness) * 2;

    /* 將發動攻擊的機會限定在 20% 到 80% 之間 */
    if( chance < 20 ) chance = 20;
    else if( chance > 80 ) chance = 80;

    /* 發動攻擊！清除等待係數 */
    if( random(100) < chance ) {
        attack_patience = 0;
        return opp;
    }

    /* 攻勢不足，累加等待係數 */
    attack_patience += intimidate / 10;

    return 0;
}

/* attack()
 *
 * 這個函是用來控制人物每回合的戰鬥：使用武器技能或徒手搏鬥技能攻擊。
 */

varargs int attack(object opponent)
{
    mapping wielded_weapon;

    if( !living(this_object()) ) return 0;

    /* 若沒有指定目標，則選定一個目標。一般而言指定目標的呼叫方式是給
     * 特殊技能用的，沒有指定目標的方式是給 heart_beat 用的。
     */
    if( !objectp(opponent) ) opponent = select_opponent();
    if( opponent ) current_target = opponent;

    // 有拿武器
    wielded_weapon = query_temp("weapon");
    if( mapp(wielded_weapon) && sizeof(wielded_weapon) ) {
        string type;
        object weapon;
        foreach(type, weapon in wielded_weapon)
            COMBAT_D->fight(this_object(), opponent, weapon);
    } else COMBAT_D->fight(this_object(), opponent, this_object());
    return 1;
}

void init()
{
    if( this_object() == this_player() ) return;

    /* 若 this_player() 看不見這個人物，則不引發戰鬥。 */
    if( ! this_object()->visible(this_player()) ) return;

    /* 增加area判斷 add by -Acme- */
    if( environment()->is_area() && !area_environment(this_object(), this_player()) ) return;

    /* 若雙方正互相仇視中，開始戰鬥。 */
    if( this_player()->is_killing(query("id")) ) {
        COMBAT_D->auto_fight(this_player(), this_object(), "hatred");
        return;
    }

    if( is_killing(this_player()->query("id")) ) {
        COMBAT_D->auto_fight(this_object(), this_player(), "hatred");
        return;
    }

    /* 若雙方有家族仇恨，則開始戰鬥。 */
    if( this_player()->query("vendetta/" + query("vendetta_mark")) ) {
        COMBAT_D->auto_fight(this_player(), this_object(), "vendetta");
        return;
    }

    switch( query("attitude") ) {
        case "aggressive":
            /* 主動攻擊的生物 */
            COMBAT_D->auto_fight(this_object(), this_player(), "aggressive");
            break;
    }

    if( this_object()->is_fighting(this_player()) ) return;

    // 陣營之間的愛恨情仇
    if( this_object()->query("camp") ) {
        string c, camp_dir;
        
        c = this_object()->query("camp");
        
        camp_dir = CAMP_DIR + c + ".c";
        if( file_size(camp_dir) == -1 || file_size(camp_dir) == -2 ) return;
        
        // 玩家的話，則判斷敵對陣營在該玩家的聲望
        if( userp(this_player()) ) {
            int score;
            string camp, *camps;
            
            // 先檢查該陣營的聲望是否會被auto kill
            score = this_player()->getCampScore(c);
            if( score <= camp_dir->getHate() ) {
                COMBAT_D->camp_auto_kill(this_object(), this_player(), camp_dir->getHateMsg());
                return;
            }
            
            // 再檢查敵對的陣營該玩家的聲望是否會被 auto kill
            camps = camp_dir->getAdversely();
            foreach( camp in camps ) {
                score = this_player()->getCampScore(camp);
                if( score >= camp_dir->getAdvHate() ) {
                    COMBAT_D->camp_auto_kill(this_object(), this_player(), camp_dir->getAdvHateMsg());
                    return;
                }
            }
            
        // npc的話，則判斷是不是所屬的敵對陣營
        } else {
            string *camps;
            if( !this_player()->query("camp") ) return;
            camps = camp_dir->getAdversely();
            if( member_array(this_player()->query("camp"), camps) != -1 ) {
                COMBAT_D->camp_auto_kill(this_object(), this_player(), camp_dir->getAdvHateMsg());
                return;
            }

        }
    }
}
