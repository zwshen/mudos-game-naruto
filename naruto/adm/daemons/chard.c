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
 *  一般性的人物設定函數。這個函數用來對人物物件做一些初始化的設定。
 */
void setup_char(object ob)
{
    mapping apply;

    // 如果人物沒有設定種族、職業、等級，給一個預設值
    if( !ob->query_race() ) ob->set_race("human");
    if( !ob->query_class() ) ob->set_class("commoner");
    if( !ob->query_level() ) ob->set_level(1);

    ob->init_statistic();
    ob->init_attribute();

    // 初始化人物的暫時狀態
    if( mapp(apply = ob->query("perm_apply") ) )
        ob->set_temp("apply", copy(apply));
    else
        ob->set_temp("apply", ([]));

    /*
        針對人物的生命型態(life_form)，執行系統預設的設定
        TYPE_STATIC        這項基本數值是不會自動更新的
        TYPE_HEALTH     這項基本數值是會隨時間自動恢復的
        TYPE_WASTING    這項基本數值是會隨時間慢慢減少的
    */
    ob->set_stat_regenerate("ap", TYPE_HEALTH);
    ob->set_stat_regenerate("hp", TYPE_HEALTH);
    ob->set_stat_regenerate("mp", TYPE_HEALTH);

    // 執行種族及職業的初始化，種族和職業物件可以修改前面初始化過的屬性。
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

    // 巫師不需要產生屍體
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

    corpse->set_name( victim->name(1) + "的屍體", "corpse of " + capitalize(victim->query("id")), "corpse" );
    corpse->set("long", "一具" + victim->name(1) + "的屍體，看起來歪七扭八的且不斷散發出惡臭。\n");
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

    // 身上所有物品轉移到屍體上
    //    foreach(inv in all_inventory(victim)) inv->move(corpse);
    // 現在不用撿屍了.... by Acme

    // npc掉落物
    if( !userp(victim) ) {
        // 掉落物品是由 /adm/daemons/itemd.c 整合物件提供
        // 設定掉落物結構： (分子/分母) 是掉落機率
        // ({ ([ "type":類別, "id":編號, "amount":數量, "p1":分子, "p2":分母 ]),
        //    ([ ... ]), ([ ... ]), ... })
        mixed drop;
        if( arrayp(drop = victim->query("set_drop")) ) {
            mapping dd, record;
            object item;
            foreach( dd in drop ) {
                if( !mapp(dd) || random(dd["p2"]) > dd["p1"] ) continue; // 先跑掉落機率
                record = 0;
                switch( dd["type"] ) {
                    case "eq":   record = ITEM_D->do_query("eq", dd["id"]); break;
                    case "wp":   record = ITEM_D->do_query("wp", dd["id"]); break;
                    case "food": record = ITEM_D->do_query("food", dd["id"]); break;
                    case "obj": record = ITEM_D->do_query("obj", dd["id"]); break;
                    default: record = 0;
                }

                if( !mapp(record) ) continue;

                // 無法建立該掉落物
                if( !objectp(item = new(record["file_name"])) ) break;

                // 該掉落物是合併物件，可以設定數量
                if( function_exists("set_amount", item) && dd["amount"] > 1 )
                    item->set_amount(dd["amount"]);

                if( !item->move(corpse) ) {
                    destruct(item);
                    continue;
                }
            }
        }
    } else {
        // 公開死亡消息
        if( !killer ) killer = victim->last_damage_giver();
        if( objectp(killer) ) {
            if( killer == victim ) { // 自殺
                shout( sprintf( HIR "【社會新聞】%s(%s)慘死在自已的手上了！！\n" NOR, victim->name(), victim->query_id() ) );
                tell_object(victim, sprintf( HIR "【社會新聞】%s(%s)慘死自已的手上了！！\n" NOR, victim->name(), victim->query_id() ) );

            } else { // 他殺
                shout( sprintf( HIR "【社會新聞】%s(%s)慘死在%s(%s)的手上了！！\n" NOR, victim->name(), victim->query_id(), killer->name(), killer->query_id() ) );
                tell_object( victim, sprintf( HIR "【社會新聞】%s(%s)慘死在%s(%s)的手上了！！\n" NOR, victim->name(), victim->query_id(), killer->name(), killer->query_id() ) );
            }
        } else {
            shout( sprintf( HIR "【社會新聞】%s(%s)莫名奇妙就暴斃了！！\n" NOR, victim->name(), victim->query_id() ) );
            tell_object(victim, sprintf( HIR "【社會新聞】%s(%s)莫名奇妙就暴斃了！！\n" NOR, victim->name(), victim->query_id() ) );
        }
    }


    victim->set_temp("corpse", corpse);

    return corpse;
}
