/* skills.c */

#include <ansi.h>
#include <skill.h>

inherit F_CLEAN_UP;

string *skill_level_desc = ({
    "初學乍練",
    "粗通皮毛",
    "漸有所悟",
    "半生不熟",
    "馬馬虎虎",
    "已有小成",
    "熟練如意",
    "揮灑自如",
    "駕輕就熟",
    "出類拔萃",
    "技藝不凡",
    "神乎其技",
    "爐火純青",
    "出神入化",
    "登峰造極",
    "超今絕古",
    "超凡入聖",
    "返璞歸真",
    "深不可測"
});

string *knowledge_level_desc = ({
    "新學乍用",
    "初窺門徑",
    "略知一二",
    "馬馬虎虎",
    "已有小成",
    "得心應手",
    "卓然有成",
    "心領神會",
    "名滿天下",
    "一代宗師",
    "深不可測"
});

string skill_level(string, int);

mapping _skill;
object ob;

string skill_class(string sk)
{
    switch( SKILL_D(sk)->query_class() ) {
        // naruto
        case "force": return BRED"體術"NOR; break;
        case "ninja": return BBLU"忍術"NOR; break;

        // hunter
        case "psychical": return BWHT+BLK"念技"NOR; break;
        case "concrete":  return BRED"具現"NOR; break;
        case "emit":      return BGRN"放出"NOR; break;
        case "operation": return BYEL"操作"NOR; break;
        case "special":   return BBLU"特質"NOR; break;
        case "strength":  return BMAG"強化"NOR; break;
        case "variation": return BCYN"變化"NOR; break;

        // piece
        case "fruit":    return HIY"果實"NOR; break;
        case "blade":    return BGRN"刀術"NOR; break;
        case "spurn":    return BYEL"踢技"NOR; break;
        case "martial":  return BRED"武術"NOR; break;
        case "activity": return REV"特殊"NOR; break;

        case "basic": return HIW"基本"NOR; break;
        default: return HIK"其它"NOR; break;
    }
}

string skill_ability(int i)
{
    switch( i ) {
        case 10: return HIW"[S]"NOR; break;
        case  9:
        case  8: return HIY+"["+i+"]"+NOR;break;
        case  7:
        case  6: return HIC+"["+i+"]"+NOR;break;
        case  5:
        case  4: return HIG+"["+i+"]"+NOR;break;
        case  3: 
        case  2:
        default: return HIK+"["+i+"]"+NOR;break;
}
}

int sk_sort(string sk1, string sk2)
{
    if( !SKILL_D(sk2)->query_class() || !SKILL_D(sk1)->query_class() )
        return ob->query_skill(sk2) - ob->query_skill(sk1);
    if( strcmp(SKILL_D(sk2)->query_class(), SKILL_D(sk1)->query_class()) == 0)
        return ob->query_skill(sk2) - ob->query_skill(sk1);
    else return strcmp(SKILL_D(sk2)->query_class(), SKILL_D(sk1)->query_class());
}

int main(object me, string arg)
{
//    object ob;
    mapping skl, lrn, map, flag, ability, require;
    string *sname, *mapped, s, old_s, line, option;
    int show_all = 0;

    seteuid(getuid());

    if( !arg )  ob = me;
    else {
        if( arg == "-clear" ) {
            me->clear_flags();
            write("ok\n");
            return 1;
        }
        
        ob = present(arg, environment(me));
        if (!ob) ob = find_player(arg);
        if (!ob) ob = find_living(arg);
        if (!ob) return notify_fail("你要察看誰的技能﹖\n");
        if( !wizardp(me)
         && !ob->is_apprentice_of(me)
         && !me->is_apprentice_of(ob)
         && !ob->accept_info(me, "skills") )
                return notify_fail("只有巫師或有師徒關係的人能察看他人的技能。\n");
    }

    flag = ob->query_skill_flags();
    if( !mapp(flag) ) flag = ([]);

    skl = ob->query_skills();
    if( !mapp(skl) ) skl = ([]);

    lrn = ob->query_learned();
    if( !mapp(lrn) ) lrn = ([]);

    ability = ob->query_skills_ability();
    if( !mapp(ability) ) ability = ([]);

    require = ob->query_skills_require();
    if( !mapp(require) ) require = ([]);

    if(!sizeof(skl) && !sizeof(lrn)) {
        write( (ob==me ? "你" : ob->name()) + "目前並沒有學會任何技能。\n");
        return 1;
    }

    line = "╭────────────────────────────────────╮\n";
    line += sprintf("│%-72s│\n", (ob==me ? "你" : ob->name()) + "目前所習得的技能列表");

    // This is a very tricky code that setup a mapping of effective skill
    // level and an array of skill names (>0).
    _skill = ([]);
    sname = filter_array(keys(skl) + keys(lrn), (: undefinedp($3[$1]) ? $3[$1] = $2->query_skill($1) : 0 :), ob, _skill );

    map = ob->query_skill_map();

    if( mapp(map) ) mapped = values(map);
    else mapped = ({});

    sname = sort_array( keys(_skill), (: sk_sort :) );
//    sname = sort_array( keys(_skill) , (: _skill[$2] - _skill[$1] :));

    line += "├────────────────────────────────────┤\n";
    foreach(s in sname ) {
    line += sprintf("│%s%s %-37s %s %3s %-6s%7s│\n",
                        skill_class(s),
                        skill_ability(ability[s]),
                        to_chinese(s) + "(" + s + ")",
                        skill_level(SKILL_D(s)->type(), skl[s]),
                        ob->skill_mapped(s) ?  ""+_skill[s] : HIK"---"NOR,
                        ( ob->skill_mapped(s) && _skill[s] != skl[s]) ? (sprintf("(%+d)", _skill[s] - skl[s])) : "",
                        (( flag[s] & SKILL_FLAG_ABANDONED ) ? HIK" ------"NOR : 
                            ( !require[s] ? "00.00%" : sprintf("%2.2f",lrn[s]*100.0/require[s]) +"%" )) );
                
    }
    line += "╰────────────────────────────────────╯";
    this_player()->start_more(line);
    return 1;
}

string skill_level(string type, int level)
{
    int grade;

      grade = level/10;

    switch(type) {
        case "knowledge":
            if( grade >= sizeof(knowledge_level_desc) )
                grade = sizeof(knowledge_level_desc)-1;
            return knowledge_level_desc[grade];
        default:
            if( grade >= sizeof(skill_level_desc) )
                grade = sizeof(skill_level_desc)-1;
            return skill_level_desc[grade];
    }
}

int help(object me)
{
    write(@HELP
指令格式 : skills [<某人>]

這個指令可以讓你查詢學過的技能及經驗值，亦可查知和你有師徒關係的對象之技
能狀況。

巫師可以查詢任何人或 NPC 的技能狀況。

disable 的技能在技能等級的部分以 --- 顯示
abandon 的技能在技能經驗的部分以 --- 顯示

如果你的技能因為 disable 或是 abandon 要還原時發生問題
你可以試著用指令 skills -clear 來清除 disable 及 abandon 的標記
這個指令不會影響你的技能等級或是經驗，只是清除標記用

相關指令：enable、disable、abandon
HELP
    );
    return 1;
}

