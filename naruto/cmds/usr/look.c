/* look.c write by -Acme-
*/

// #pragma save_binary
#include <ansi.h>

inherit "/adm/daemons/itemd.c";

mapping named_apply = ([
    "head_eq": HIK"["NOR"頭部"HIK"]"NOR,
    "face_eq": HIK"["NOR"臉部"HIK"]"NOR,
    "neck_eq": HIK"["NOR"頸部"HIK"]"NOR,
    "wrist_eq": HIK"["NOR"手腕"HIK"]"NOR,
    "hand_eq": HIK"["NOR"手部"HIK"]"NOR,
    "finger_eq": HIK"["NOR"手指"HIK"]"NOR,
    "cloth": HIK"["NOR"衣服"HIK"]"NOR,
    "armor": HIK"["NOR"鎧甲"HIK"]"NOR,
    "waist_eq": HIK"["NOR"腰部"HIK"]"NOR,
    "pants": HIK"["NOR"褲子"HIK"]"NOR,
    "leg_eq": HIK"["NOR"腿部"HIK"]"NOR,
    "feet_eq": HIK"["NOR"足部"HIK"]"NOR,
    "lefthand": HIK"["NOR"左手"HIK"]"NOR,
    "righthand": HIK"["NOR"右手"HIK"]"NOR,
    "twohanded": HIK"["NOR"雙手"HIK"]"NOR,
]);

string status_msg(string who, int ratio)
{
    switch( ratio ) {
		case    100: return HIG + who + "看起來並沒有受傷。\n" NOR; break;
		case 96..99: return HIG + who + "似乎受了點輕傷，不過光從外表看不大出來。\n" NOR; break;
		case 91..95: return HIG + who + "看起來可能受了點輕傷。\n" NOR; break;
		case 81..90: return HIG + who + "受了幾處傷，不過似乎並不礙事。\n" NOR; break;
		case 61..80: return HIY + who + "受傷不輕，看起來狀況並不太好。\n" NOR; break;
		case 41..60: return HIY + who + "氣息粗重，動作開始散亂，看來所受的傷著實不輕。\n" NOR; break;
		case 31..40: return HIY + who + "已經傷痕累累，正在勉力支撐著不倒下去。\n" NOR; break;
		case 21..30: return HIR + who + "受了相當重的傷，只怕會有生命危險。\n" NOR; break;
		case 11..20: return HIR + who + "傷重之下已經難以支撐，眼看就要倒在地上。\n" NOR; break;
		case  5..10: return HIR + who + "受傷過重，已經奄奄一息，命在旦夕了。\n" NOR; break;
		default:     return HIR + who + "受傷過重，已經有如風中殘燭，隨時都可能斷氣。\n" NOR; break;
    }    
}

string inventory_look(object obj, int flag)
{
    string str, type, sub_type;

    str = obj->short();
    if( type = obj->query("equipped") ) {
        if( sscanf(type, "%s/%s", type, sub_type) == 2 ) {
            str = sprintf("  %s %s",
            	          !undefinedp(named_apply[sub_type]) ? named_apply[sub_type] : sub_type,
            	          str );
        } else str = HIY "  ＊"NOR + str;
    } else if( !flag ) str = "    " + str;
    else return 0;

    return str;
}

int look_living(object me, object obj)
{
    int age;
    string msg, race, pro;
    mixed *inv, drop;

    race = obj->query_race();
    pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));
    age = obj->query("age");

    if( me != obj ) message("vision", me->name() + "正盯著你看﹐不知道打些什麼主意。\n", obj);

    msg = sprintf("%s看起來%s歲。\n", pro, age > 10 ? "約" + chinese_number(age/10*10) + "多" : "不到十" );
    msg += obj->long();
    if( obj->query_stat_maximum("hp") )
        msg += status_msg(pro, obj->query_stat_current("hp")*100/obj->query_stat_maximum("hp"));

    inv = all_inventory(obj);
    if( sizeof(inv) ) {
        inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse() ? 0 : 1 );
        inv -= ({ 0 });
        if( sizeof(inv) )
            msg += sprintf( obj->is_corpse() ? "%s的遺物有﹕\n%s\n" : "%s身上帶著﹕\n%s\n", pro, implode(inv, "\n") );
    }

    // 檢視掉落物
    if( !userp(obj) && arrayp(drop = obj->query("set_drop")) ) {
    	int power = 0;
        mapping dd, record;
        
        if( wizardp(me) ) power = 2;
        else {
            if( mapp(me->query_condition("know1")) ) power = 1;
            if( mapp(me->query_condition("know2")) ) power = 2;
        }
        
        if( power > 0 ) {
            msg += "\n掉落物：\n";
            foreach( dd in drop ) {
                if( !mapp(dd) ) continue;
                record = 0;
                switch( dd["type"] ) {
                    case "eq":   record = ITEM_D->do_query("eq", dd["id"]); break;
                    case "wp":   record = ITEM_D->do_query("wp", dd["id"]); break;
                    case "food": record = ITEM_D->do_query("food", dd["id"]); break;
                    case "obj":  record = ITEM_D->do_query("obj", dd["id"]); break;
                    default: record = 0;
                }
                if( !mapp(record) ) continue;
                msg += "  " + record["name"];
                if( power > 1 ) msg += " [機率：" + dd["p1"] + "/" + dd["p2"] + "]\n";
                else msg += "\n";
            }
        }
    }

    message("vision", msg, me);

    return 1;
}

int look_item(object me, object obj)
{
    mixed *inv;

    me->start_more(obj->long());
    inv = all_inventory(obj);
    if( sizeof(inv) ) {
        if( sizeof(inv) < 30 ) {
            inv = map_array(inv, "inventory_look", this_object() );
            message("vision", sprintf("裡面有﹕\n  %s\n", implode(inv, "\n  ") ), me);
        }
        else tell_object(me, YEL"裡面雜七雜八的放著許多東西..\n"NOR);
    }
    return 1;
}

int main(object me, string arg)
{
    object obj;

    if( !environment(me) )
        return notify_fail("你現在什麼也看不到！\n");

    if( me->query_temp("block_msg/vision") )
        return notify_fail("你現在什麼也看不到！\n");

    if( !arg ) return environment(me)->do_look(me, arg);
    
    if( (obj = present(arg, environment(me))) || (obj = present(arg, me)) ) {
        if( obj->is_character() ) return look_living(me, obj);
            else return look_item(me, obj);
    } else return environment(me)->do_look(me, arg);
    
    return 1;
}

int help (object me)
{
    write(@HELP
指令格式: look [<物品>|<生物>]
 
這個指令讓你查看你所在的環境、某件物品、生物。
 
HELP);
    return 1;
}
