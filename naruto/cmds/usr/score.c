/* score.c
*/

// #pragma save_binary

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

string hp_bar = "__________________________________________________";
string display_attr(int gift, int value);
string status_color(int value, int color_kind);
string show_score(object ob);
string show_bar(object ob, string entry);

int main(object me, string arg)
{
    object ob, eq;
    mapping wielded_weapon, buffering;
    string line, tmp, sk, buf;
    string wp1=HIK"--"NOR, wp1_c=HIK"--"NOR, wp2=HIK"--"NOR, wp2_c=HIK"--"NOR;
    string eq1="", eq1_c="", eq2="", eq2_c="";
    int exp;

    if( !arg ) ob = me;
    else {
    if( arg == "_MY_PET_" ) {
        if( !objectp(ob = me->query_temp("pet")) ) 
                return notify_fail("你似乎沒有忍犬...\n");
    } else ob = present(arg, environment(me));
        if(!ob) ob = find_player(arg);
        if(!ob) ob = find_living(arg);
        if( !ob ) ob = LOGIN_D->find_body(arg);
        if(!ob) return notify_fail("你要察看誰的狀態﹖\n");
        if(!living(ob)) return notify_fail("你只能察看生物的狀態。\n");
        if( !wizardp(me) && (object)ob->query_owner() != me )
            return notify_fail("只有巫師能察看別人的狀態。\n");
    }
    seteuid(getuid(ob));

    line = sprintf(NOR"╭──────────────────────────────────╮\n");
    line = sprintf("%s│"HIW"【%|8s】"NOR" %-55s│\n",line, ob->rank(), ob->short(1) );
    line = sprintf("%s├──────────────────────────────────╯\n",line);
    line = sprintf("%s│%-68s\n",line,
    "等級 " + HIC+ob->query("level")+NOR + " 級  " +
    "年齡 " + HIM+ob->query("age")+NOR + " 歲  " +
    "種族 " + HIY+to_chinese(ob->query_race())+NOR + "  " +
    "性別 " + HIG+((tmp = ob->query("gender")) ? to_chinese(tmp) : "？？")+NOR );

    line = sprintf("%s├────────┬─────────────────────────╮\n",line);

    // 攻擊力量
    exp = 0;
    exp = COMBAT_D->attack(ob, ob, 0, ob);
    
    wielded_weapon = ob->query_temp("weapon");
    if( mapp(wielded_weapon) && sizeof(wielded_weapon) ) {
        object weapon;
        string skill;
        foreach(skill, weapon in wielded_weapon) {
        if( skill[0..8] == "twohanded")      // 雙手武器
        wp1 = wp1_c = wp2 = wp2_c = weapon->name();
        else if( skill[0..9] == "lefthand" )   // 左手武器
        wp2 = wp2_c = weapon->name();
        else wp1 = wp1_c = weapon->name();       // 右手武器
            exp += COMBAT_D->weapon_attack(weapon, 0, 0);
        }
    }

    line = sprintf("%s│力量  %-10s│ 攻擊力量 %-5d  防禦力量 %-5d  學習點數 %-8d│\n",line,
        display_attr(ob->query_attr("str",1), ob->query_attr("str")),
        exp, COMBAT_D->defend(ob, ob, 0), ob->query_point("learn")
        );

    line = sprintf("%s│體格  %-10s│ 攻擊技巧 %-5d  防禦技巧 %-5d  屬性點數 %-8d│\n",line,
        display_attr(ob->query_attr("con",1), ob->query_attr("con")),
        COMBAT_D->intimidate(ob, 0),
        COMBAT_D->wittiness(ob, 0),
        ob->query_point("attribute")
    );
    
    line = sprintf("%s│敏捷  %-10s│ 命中能力 %-5d  迴避能力 %-5d  技能點數 %-8d│\n",line,
        display_attr(ob->query_attr("dex",1), ob->query_attr("dex")),
        COMBAT_D->exact(ob, ob, 0),
        COMBAT_D->evade(ob, ob, 0),
        ob->query_point("skill")
    );
    

    line = sprintf("%s│智慧  %-10s│ 致命一擊 %-5s  致命傷害 %-5s  潛能點數 %-8d│\n",line,
        display_attr(ob->query_attr("int",1), ob->query_attr("int")),
        COMBAT_D->sock(ob, ob, 0) + "%",
        COMBAT_D->sockPower(ob, ob, 0) + "%", 
        ob->query_point("score") );
    
    line = sprintf("%s├────────┴─────────────────────────╯\n",line);

    if( ob->query_stat_maximum("ap") ) {
        line = sprintf("%s│精力值%s%5d/%5d"NOR" %s\n",line,
            status_color(ob->query_stat_current("ap")*100/ob->query_stat_maximum("ap"), 0),
            ob->query_stat("ap"),
            ob->query_stat_maximum("ap"),
            show_bar(ob, "ap")
        );
    }

    if( ob->query_stat_maximum("hp") ) {
        line = sprintf("%s│體力值%s%5d/%5d"NOR" %s\n",line,
            status_color(ob->query_stat_current("hp")*100/ob->query_stat_maximum("hp"), 0),
            ob->query_stat("hp"),
            ob->query_stat_maximum("hp"),
            show_bar(ob, "hp")
        );
    }

    if( ob->query_stat_maximum("mp") ) {
          line = sprintf("%s│能量值%s%5d/%5d"NOR" %s\n",line,
            status_color(ob->query_stat_current("mp")*100/ob->query_stat_maximum("mp"), 0),
            ob->query_stat("mp"),
            ob->query_stat_maximum("mp"),
            show_bar(ob, "mp") );
    }

    line = sprintf("%s├──────────────────────────────────╮\n",line);
    
    if( objectp(eq = ob->query_temp("armor/head_eq")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    wp1 = uncolor(wp1);
    // 先用無顏色的做排列(如此色碼才不會被算進去導致亂掉)
    tmp = sprintf("│%19s "HIK"[頭部]__"NOR+BLU"   ███   "HIK"__[右手]"NOR" %-19s│\n", eq1, wp1);
    // 將無顏色的置換成有顏色的
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, wp1, wp1_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/face_eq")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    if( objectp(eq = ob->query_temp("armor/wrist_eq")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    eq2 = uncolor(eq2);    
    // 先用無顏色的做排列(如此色碼才不會被算進去導致亂掉)
//    tmp = sprintf("│%19s "HIK"[臉部]__"NOR+BLU"   ███   "HIK"__[手腕]"NOR" %-19s│\n", eq1, eq2);
    tmp = sprintf("│%19s "HIK"[臉部]__"NOR+BLU"   "NOR+BBLU" o"BLU"█"NOR+BBLU"o "NOR"   "HIK"__[手腕]"NOR" %-19s│\n", eq1, eq2);
    // 將無顏色的置換成有顏色的
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, eq2, eq2_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/neck_eq")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    if( objectp(eq = ob->query_temp("armor/hand_eq")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    eq2 = uncolor(eq2);    
    // 先用無顏色的做排列(如此色碼才不會被算進去導致亂掉)
    tmp = sprintf("│%19s "HIK"[頸部]__"NOR+BLU"   "BLK+BBLU"▂"WHT"﹀"BLK"▂"NOR+BLU" ▌"HIK"__[手部]"NOR" %-19s│\n", eq1, eq2);
    // 將無顏色的置換成有顏色的
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, eq2, eq2_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/cloth")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    if( objectp(eq = ob->query_temp("armor/armor")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    eq2 = uncolor(eq2);    
    // 先用無顏色的做排列(如此色碼才不會被算進去導致亂掉)
    tmp = sprintf("│%19s "HIK"[衣服]__"NOR+BLU" ▅███"BLK+BBLU"▂"NOR+HIK" __[鎧甲]"NOR" %-19s│\n", eq1, eq2);
    // 將無顏色的置換成有顏色的
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, eq2, eq2_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/finger_eq")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    if( objectp(eq = ob->query_temp("armor/waist_eq")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    eq2 = uncolor(eq2);    
    // 先用無顏色的做排列(如此色碼才不會被算進去導致亂掉)
    tmp = sprintf("│%19s "HIK"[手指]__"NOR+BLU" ▌  █     "HIK"__[腰部]"NOR" %-19s│\n", eq1, eq2);
    // 將無顏色的置換成有顏色的
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, eq2, eq2_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/pants")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq2 = uncolor(eq2);
    wp2 = uncolor(wp2);    
    // 先用無顏色的做排列(如此色碼才不會被算進去導致亂掉)
    tmp = sprintf("│%19s "HIK"[左手]__"NOR"   "BLK+BBLU"▌"HIR+BBLU"禁"NOR+BLU"▌   "HIK"__[褲子]"NOR" %-19s│\n", wp2, eq2);
    // 將無顏色的置換成有顏色的
    tmp = replace_string(tmp, eq2, eq2_c);
    tmp = replace_string(tmp, wp2, wp2_c);
    line += tmp;

    if( objectp(eq = ob->query_temp("armor/leg_eq")) ) eq1 = eq1_c = eq->name();
    else eq1 = eq1_c = HIK"--"NOR;
    if( objectp(eq = ob->query_temp("armor/feet_eq")) ) eq2 = eq2_c = eq->name();
    else eq2 = eq2_c = HIK"--"NOR;
    eq1 = uncolor(eq1);
    eq2 = uncolor(eq2);    
    // 先用無顏色的做排列(如此色碼才不會被算進去導致亂掉)
    tmp = sprintf("│%19s "HIK"[腿部]__"NOR+BLU" ▄█  █▄ "HIK"__[足部]"NOR" %-19s│\n", eq1, eq2);
    // 將無顏色的置換成有顏色的
    tmp = replace_string(tmp, eq1, eq1_c);
    tmp = replace_string(tmp, eq2, eq2_c);
    line += tmp;

    line = sprintf("%s├──────────────────────────────────╯\n",line);
    
    exp = 0;
    buffering = ob->query_all_conditions();
    if( sizeof(buffering) ) {
    foreach(buf in keys(buffering) ) {
    tmp = "";
        if( undefinedp(buffering[buf]) ) continue;
        exp++;
        sk = uncolor(buffering[buf]["name"]);
        if( exp == 1 ) tmp += "│";
        tmp += sprintf("%-23s", sk + "("+ buffering[buf]["duration"]/30 + ":" + (buffering[buf]["duration"]*2)%60 + ")");
        tmp = replace_string(tmp, sk, buffering[buf]["name"]);
        if( exp%3 == 0 ) {
        exp = 0;
        tmp += "\n";
        }
        line += tmp;
    }
    if( exp%4 != 0 ) line += "\n";
    }
    line = sprintf("%s╰──────────────────────────────────╯\n",line);
    write(line);
    return 1;
}

string show_score(object ob)
{
    string msg;
    msg = to_chinese(ob->query("life_form"));
    if( ob->query_all_condition() ) {
        string condition;
        foreach( condition in keys(ob->query_all_condition()) ) {
            msg+=to_chinese(condition);
        }
    }
    return msg;
}

string display_attr(int gift, int value)
{
if( value > gift )
return sprintf( HIC "%3d%-7s" NOR, value, " (+" + (value - gift) + ")" );
else if( value < gift )
return sprintf( HIB "%3d%-7s" NOR, value, " (" + (value - gift) + ")" );
else
return sprintf( CYN "%3d       " NOR, value);
}

string show_bar(object ob, string entry)
{
    int cur, eff, max;
    cur = ob->query_stat_current(entry);
    max = ob->query_stat_maximum(entry);
    return sprintf("%s%s"NOR,
               status_color((cur*100/max), 1) + hp_bar[0..(cur*50/max)] + NOR,
               HIK + hp_bar[(cur*50/max)+1..49]);
}

string status_color(int value, int color_kind)
{       
    if( color_kind ) {
        switch( value ) {
            case  0..30: return BRED;
            case 31..80: return BYEL;
            case 81..100: return BGRN;
            default: return BCYN;
        }
    } else {
        switch( value ) {
                case  0..30: return HIR;
                case 31..80: return HIY;
                case 81..100: return HIG;
                default: return HIC;
        }
    }
}

int help(object me)
{
    write(@HELP
指令格式 : score 或 sc
           score <對象名稱>

這個指令可以顯示你(妳)或指定對象(含怪物)的基本資料，如果你的對象
不是你的忍犬你無法使用這個指令，你也可以利用 score _MY_PET_ 來進
行查詢。
HELP
);
    return 1;
}
