/*  inventory.c

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

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    int i;
    string msg;
    object *inv, ob;

//    if( wizardp(me) && arg ) {
    if( arg ) {
    if( arg == "_MY_PET_" ) {
    ob = me->query_temp("pet");
    if( !ob ) return notify_fail("你沒有寵物。\n");
    } else {
    ob = present(arg, environment(me));
            if( !ob ) ob = find_player(arg);
            if( !ob ) ob = find_living(arg);
            if( !ob ) ob = present(arg, environment(me));
            if( !ob ) return notify_fail("你要看誰的物品？\n");
            if( ob->query_owner() != me && !wizardp(me) )
            return notify_fail("你不能查對方身上的物品。\n");
        }
    }
    else ob = me;

    inv = all_inventory(ob);
    if( !sizeof(inv) ) {
        write((ob==me)? "目前" + gender_self(me) + "身上沒有任何東西。\n"
            : ob->name() + "身上沒有攜帶任何東西。\n");
        return 1;
    }
    
    msg = sprintf("%-45s [空間] %-4s %-13s\n",
            ((ob==me)? gender_self(me) : ob->name()) + "身上帶著下列這些東西",
            sizeof(inv)*100/40 + "%",
            sizeof(inv) + "/40" );
    
    msg += sprintf("============================================= [負重] %-4s %-13s\n",
        ob->query_encumbrance() * 100 / (ob->query_ability("carriage")+1) + "%",
           ob->query_encumbrance() + "/" + ob->query_ability("carriage") );
    
    msg += implode(map_array(inv, "inventory_desc", this_object()), "\n") + "\n";
    tell_object(me, msg);
    return 1;
}

string inventory_desc(object ob)
{
    string desc = ob->short();

    if( ob->query("equipped") ) {
        if( ob->query("keep_this") ) desc = HIK"◎"NOR + desc;
        else desc = HIK"○"NOR + desc;
    } else {
        if( ob->query("keep_this") ) desc = HIK"ｏ"NOR + desc;
        else desc = "  " + desc;
    }

    if( wizardp(this_player()) ) desc += " " + BLU+base_name(ob)+NOR;

    return desc;
}

int help (object me)
{
    write(@HELP
指令格式: inventory
 
可列出你目前身上所攜帶的所有物品。

○  表示你已經裝備該物品
ｏ  表示該物品已經 keep
◎  表示該物品已裝備且 keep

註 : 此指令可以 " i " 代替。

可以查詢自已寵身上的的物品
ex: i acme's dog 或 i _MY_PET_
HELP);
    return 1;
}
