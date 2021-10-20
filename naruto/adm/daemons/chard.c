/*  chard.c - protected character operation daemon
 
    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>
 
    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.
 
    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

// #pragma save_binary

#include <login.h>
#include <ansi.h>
#include <statistic.h>

inherit F_CLEAN_UP;

private void create()
{
    seteuid(getuid());
}

// setup_char()
//
// This function is called when characters need setup (after create() is
// called). The major task of this function is to keep consistency of
// user data and NPCs. Because the game system may change with development
// of mudlib, there might be minor or major changes in creating character
// objects. Also, this function serves as default creation function of
// NPCs that saves wizards' work on initializing NPCs.

/*  setup()
 *
 *  �@��ʪ��H���]�w��ơC�o�Ө�ƥΨӹ�H�����󰵤@�Ǫ�l�ƪ��]�w�C
 */
void setup_char(object ob)
{
    mapping apply;

    // �p�G�H���S���]�w�رڡB¾�~�B���šA���@�ӹw�]��
    if( !ob->query_race() ) ob->set_race("human");
    if( !ob->query_class() ) ob->set_class("commoner");
    if( !ob->query_level() ) ob->set_level(1);

    ob->init_statistic();
    ob->init_attribute();

    // ��l�ƤH�����Ȯɪ��A
    if( mapp(apply = ob->query("perm_apply") ) )
        ob->set_temp("apply", copy(apply));
    else
        ob->set_temp("apply", ([]));

    /*
        �w��H�����ͩR���A(life_form)�A����t�ιw�]���]�w
        TYPE_STATIC        �o���򥻼ƭȬO���|�۰ʧ�s��
        TYPE_HEALTH     �o���򥻼ƭȬO�|�H�ɶ��۰ʫ�_��
        TYPE_WASTING    �o���򥻼ƭȬO�|�H�ɶ��C�C��֪�
    */
    ob->set_stat_regenerate("ap", TYPE_HEALTH);
    ob->set_stat_regenerate("hp", TYPE_HEALTH);
    ob->set_stat_regenerate("mp", TYPE_HEALTH);

    // ����رڤ�¾�~����l�ơA�رکM¾�~����i�H�ק�e����l�ƹL���ݩʡC
    RACE_D(ob->query_race())->setup(ob);
    CLASS_D(ob->query_class())->setup(ob);
    ob->add_path("/daemon/race/" + ob->query_race() + "/");
    ob->add_path("/daemon/class/" + ob->query_class() + "/");
}

varargs object make_corpse(object victim, object killer)
{
    int amount;
    mapping bounty;
    object corpse, inv, env;
    string score, corpse_ob;

    // �Ův���ݭn���ͫ���
    if( wizardp(victim) ) return 0;

    if( !objectp(env=environment(victim)) ) return 0;

    // Notify inventory item to save data if nessessary.
    all_inventory(victim)->owner_is_killed(killer);

    // Check if using custom corpse object.
    corpse_ob = victim->query("corpse_ob");
    if( !corpse_ob ) corpse_ob = CORPSE_OB;

    seteuid(MUDLIB_UID);
    catch(corpse = new(corpse_ob));
    seteuid(getuid());

    corpse->set_name( victim->name(1) + "������", "corpse of " + capitalize(victim->query("id")), "corpse" );
    corpse->set("long", "�@��" + victim->name(1) + "������A�ݰ_�Ӭn�C��K���B���_���o�X�c��C\n");
    corpse->set("age", victim->query("age"));
    corpse->set("gender", victim->query("gender"));
    corpse->set("victim_name", victim->name(1));
    corpse->set("level", victim->query_level());
    corpse->set("userp", userp(victim));

    corpse->set_weight( victim->query_weight() );
    corpse->set_max_encumbrance( victim->query_max_encumbrance() );
    corpse->start_decay( userp(victim) ? 120 : 60 );

    if( env->is_area() ) {
        if( !area_move(env, corpse, victim->query("area_info/x_axis"), victim->query("area_info/y_axis")) ) {
            destruct(corpse);
            return 0;
        }
    } else {
        if( !corpse->move(env) ) {
            destruct(corpse);
            return 0;
        }
    }

    // ���W�Ҧ����~�ಾ�����W
    //    foreach(inv in all_inventory(victim)) inv->move(corpse);
    // �{�b���ξ߫ͤF.... by Acme

    // npc������
    if( !userp(victim) ) {
        // �������~�O�� /adm/daemons/itemd.c ��X���󴣨�
        // �]�w���������c�G (���l/����) �O�������v
        // ({ ([ "type":���O, "id":�s��, "amount":�ƶq, "p1":���l, "p2":���� ]),
        //    ([ ... ]), ([ ... ]), ... })
        mixed drop;
        if( arrayp(drop = victim->query("set_drop")) ) {
            mapping dd, record;
            object item;
            foreach( dd in drop ) {
                if( !mapp(dd) || random(dd["p2"]) > dd["p1"] ) continue; // ���]�������v
                record = 0;
                switch( dd["type"] ) {
                    case "eq":   record = ITEM_D->do_query("eq", dd["id"]); break;
                    case "wp":   record = ITEM_D->do_query("wp", dd["id"]); break;
                    case "food": record = ITEM_D->do_query("food", dd["id"]); break;
                    case "obj": record = ITEM_D->do_query("obj", dd["id"]); break;
                    default: record = 0;
                }

                if( !mapp(record) ) continue;

                // �L�k�إ߸ӱ�����
                if( !objectp(item = new(record["file_name"])) ) break;

                // �ӱ������O�X�֪���A�i�H�]�w�ƶq
                if( function_exists("set_amount", item) && dd["amount"] > 1 )
                    item->set_amount(dd["amount"]);

                if( !item->move(corpse) ) {
                    destruct(item);
                    continue;
                }
            }
        }
    } else {
        // ���}���`����
        if( !killer ) killer = victim->last_damage_giver();
        if( objectp(killer) ) {
            if( killer == victim ) { // �۱�
                shout( sprintf( HIR "�i���|�s�D�j%s(%s)�G���b�ۤw����W�F�I�I\n" NOR, victim->name(), victim->query_id() ) );
                tell_object(victim, sprintf( HIR "�i���|�s�D�j%s(%s)�G���ۤw����W�F�I�I\n" NOR, victim->name(), victim->query_id() ) );

            } else { // �L��
                shout( sprintf( HIR "�i���|�s�D�j%s(%s)�G���b%s(%s)����W�F�I�I\n" NOR, victim->name(), victim->query_id(), killer->name(), killer->query_id() ) );
                tell_object( victim, sprintf( HIR "�i���|�s�D�j%s(%s)�G���b%s(%s)����W�F�I�I\n" NOR, victim->name(), victim->query_id(), killer->name(), killer->query_id() ) );
            }
        } else {
            shout( sprintf( HIR "�i���|�s�D�j%s(%s)���W�_���N���ŤF�I�I\n" NOR, victim->name(), victim->query_id() ) );
            tell_object(victim, sprintf( HIR "�i���|�s�D�j%s(%s)���W�_���N���ŤF�I�I\n" NOR, victim->name(), victim->query_id() ) );
        }
    }


    victim->set_temp("corpse", corpse);

    return corpse;
}
