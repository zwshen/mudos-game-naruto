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

    tell_object(this_object(), HIY + ob->name() + HIY"�}�l�O�@�A�C\n" NOR);
    guarded += ({ ob });
}

void remove_guard(object ob)
{
    if( member_array(ob, guarded) < 0 ) return;

    guarded -= ({ ob, 0 });
    tell_object(this_object(), HIY + ob->name() + HIY"���A�O�@�A�F�C\n"+ NOR);
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

    // �W�[area �P�_ by -Acme-
    if( environment()->is_area() && !area_environment(ob, this_object()) ) return;

    if( ob==guarding ) guard_ob(0);

    set_heart_beat(1);

    if( member_array(ob, enemy)==-1 ) enemy += ({ ob });

    guard = ob->wake_guard(this_object());
    if( sizeof(guard) ) {
        message("system", HIY + ob->name() + HIY"���D�������I�A�W�e�U�ԡI\n" NOR, guard);
        guard->activate_guard(this_object());
        enemy += guard;
    }

    // �D�� fight �� kill �۰ʩI�s���禡, ��K�]�p�@�� NPC �ܤ�
    if( function_exists( "start_fighting", this_object() ) )
        this_object()->start_fighting(ob);
}

void kill_ob(object ob)
{
    if( userp(ob) ) {
        if( living(ob) && undefinedp(killer[ob->query("id")]) )
            tell_object(ob, HIR "�ݰ_��" + this_object()->name() + HIR"�Q�����A�T\n" NOR);
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
    tell_object(this_object(), HIY "�A�}�l�N" + ob->name() + HIY"�����n�����ؼСI\n" NOR);
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
 * �o�Ө�ƥΨӱN�w�g�S���԰���O���ĤH�۾԰���H���簣�A�Ǧ^�Ȧp�G�j�� 0
 * ��ܩ|���ĤH�C
 */
int clean_up_enemy() {
    enemy = filter(enemy, (:
        objectp($1) && (environment($1)==environment()) && (living($1) || is_killing($1)) && (environment()->is_area() ? area_environment(this_object(), $1) : 1 )
    :) );
    return sizeof(enemy);
}

/* select_opponent()
 *
 * �o�Ө�ƥΨӬ��H����ܤ@�ӧ�����H�C
 */
private object select_opponent()
{
    object opp;
    int which, intimidate, wittiness, chance;

    if( !arrayp(enemy) || !sizeof(enemy) ) return 0;

    /* �����ɦV = ��յ��� + ���ݫY�� */
    intimidate = COMBAT_D->intimidate(this_object()) + attack_patience;

    /* �p�G�����n�����ؼСA�u���Ҽ{�o�ӥؼ� */
    if( charge_target && member_array(charge_target, enemy) >= 0 ) {
        intimidate += intimidate / 5;// charge �������ĪG
        opp = charge_target;
    } else opp = enemy[random(sizeof(enemy))];

    /* �u�յ��� */
    if( living(opp) ) {
        wittiness = COMBAT_D->wittiness(opp);
        if( opp->query_charging() )
            wittiness -= wittiness / 3;// charge ���t���ĪG
    } else wittiness = 0;

    if( !wittiness ) return opp;
    chance = 50 + (intimidate - wittiness) * 2;

    /* �N�o�ʧ��������|���w�b 20% �� 80% ���� */
    if( chance < 20 ) chance = 20;
    else if( chance > 80 ) chance = 80;

    /* �o�ʧ����I�M�����ݫY�� */
    if( random(100) < chance ) {
        attack_patience = 0;
        return opp;
    }

    /* ��դ����A�֥[���ݫY�� */
    attack_patience += intimidate / 10;

    return 0;
}

/* attack()
 *
 * �o�Ө�O�Ψӱ���H���C�^�X���԰��G�ϥΪZ���ޯ�ή{��i���ޯ�����C
 */

varargs int attack(object opponent)
{
    mapping wielded_weapon;

    if( !living(this_object()) ) return 0;

    /* �Y�S�����w�ؼСA�h��w�@�ӥؼСC�@��Ө����w�ؼЪ��I�s�覡�O��
     * �S��ޯ�Ϊ��A�S�����w�ؼЪ��覡�O�� heart_beat �Ϊ��C
     */
    if( !objectp(opponent) ) opponent = select_opponent();
    if( opponent ) current_target = opponent;

    // �����Z��
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

    /* �Y this_player() �ݤ����o�ӤH���A�h���޵o�԰��C */
    if( ! this_object()->visible(this_player()) ) return;

    /* �W�[area�P�_ add by -Acme- */
    if( environment()->is_area() && !area_environment(this_object(), this_player()) ) return;

    /* �Y���西���ۤ������A�}�l�԰��C */
    if( this_player()->is_killing(query("id")) ) {
        COMBAT_D->auto_fight(this_player(), this_object(), "hatred");
        return;
    }

    if( is_killing(this_player()->query("id")) ) {
        COMBAT_D->auto_fight(this_object(), this_player(), "hatred");
        return;
    }

    /* �Y���観�a�ڤ���A�h�}�l�԰��C */
    if( this_player()->query("vendetta/" + query("vendetta_mark")) ) {
        COMBAT_D->auto_fight(this_player(), this_object(), "vendetta");
        return;
    }

    switch( query("attitude") ) {
        case "aggressive":
            /* �D�ʧ������ͪ� */
            COMBAT_D->auto_fight(this_object(), this_player(), "aggressive");
            break;
    }

    if( this_object()->is_fighting(this_player()) ) return;

    // �}�礧�����R�뱡��
    if( this_object()->query("camp") ) {
        string c, camp_dir;
        
        c = this_object()->query("camp");
        
        camp_dir = CAMP_DIR + c + ".c";
        if( file_size(camp_dir) == -1 || file_size(camp_dir) == -2 ) return;
        
        // ���a���ܡA�h�P�_�Ĺ�}��b�Ӫ��a���n��
        if( userp(this_player()) ) {
            int score;
            string camp, *camps;
            
            // ���ˬd�Ӱ}�窺�n��O�_�|�Qauto kill
            score = this_player()->getCampScore(c);
            if( score <= camp_dir->getHate() ) {
                COMBAT_D->camp_auto_kill(this_object(), this_player(), camp_dir->getHateMsg());
                return;
            }
            
            // �A�ˬd�Ĺ諸�}��Ӫ��a���n��O�_�|�Q auto kill
            camps = camp_dir->getAdversely();
            foreach( camp in camps ) {
                score = this_player()->getCampScore(camp);
                if( score >= camp_dir->getAdvHate() ) {
                    COMBAT_D->camp_auto_kill(this_object(), this_player(), camp_dir->getAdvHateMsg());
                    return;
                }
            }
            
        // npc���ܡA�h�P�_�O���O���ݪ��Ĺ�}��
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
