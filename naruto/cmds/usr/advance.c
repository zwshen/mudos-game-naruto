/* advance */

#include <ansi.h>
#include <attribute.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int add_attribute(object me, string attr, int amount)
{
    if( me->query_point("attribute") < amount ) {
        write("你的屬性點數不足，無法提升人物屬性。\n");
        return 1;
    }
    
    if( me->query_attr(attr, 1) + amount > ATTRVAL_MAX ) {
        write("你的屬性 " + attr + " 無法提升這麼多，上限為"+ chinese_number(ATTRVAL_MAX) +"。\n");
        return 1;
    }
    
    me->add_point("attribute", -amount);
    me->set_attr(attr, me->query_attr(attr, 1) + amount);
    
    write(HIY"你的屬性 " + attr + " 提升" + chinese_number(amount) + "點了！\n"NOR);
    
    return 1;
}

int add_state(object me, string state, int amount)
{
    if( me->query_point("score") < amount ) {
        write("你的潛能點數不足，無法提升人物狀態。\n");
        return 1;
    }
    
    if( me->query_stat_maximum(state) + amount > 9999 ) {
        write("你的狀態 " + state + " 無法提升這麼多，上限為九千九百九十九。\n");
        return 1;
    }
    
    me->add_point("score", -amount);
    me->advance_stat(state, amount);
    me->heal_stat(state, amount);

    write(HIY"你的狀態 " + state + " 提升"+ chinese_number(amount) +"點了！\n"NOR);

    return 1;
}

int add_skill(object me, string skill, int amount)
{
    int i;
    if( me->query_point("skill") < amount ) {
        write("你的技能點數不足，無法提升人物技能上限。\n");
        return 1;
    }

    if( me->query_skill_ability(skill) + amount > 10 ) {
        write("你的技能 " + skill + " 無法提升這麼多，技能投點最高為十點。\n");
        return 1;
    }
    
    me->add_point("skill", -amount);

    for(i=1;i<=amount;i++) me->add_skill_ability(skill);
    
    write(HIY"你的技能 " + skill + " 上限提升" + chinese_number(amount*20) + "級了！\n"NOR);
    
    return 1;
}


void add_level(object me)
{
	if( me->query_level() >= CLASS_D(me->query_class())->getMaxLV() ) {
		write("你的等級已經達到該職業的上限了。\n");
		return;
	}
	
	if( me->query_point("learn") <  CLASS_D(me->query_class())->getLvUpExp(me) ) {
		write("你的學習點數不足 " + CLASS_D(me->query_class())->getLvUpExp(me) + " 無法提升等級。\n");
		return;
	}
	
    me->add_point("learn", -CLASS_D(me->query_class())->getLvUpExp(me));
    me->add("level",1);
	CLASS_D(me->query_class())->advance_level(me);
    RACE_D(me->query_race())->advance_level(me);
    
	write(HIY"你的等級提升至 " + me->query_level() + " 級。\n"NOR);
}

int main(object me, string arg)
{
    int amount;

    if( !arg ) return notify_fail("你想提升人物的什麼能力？\n");
    
    if( sscanf(arg, "%s for %d", arg, amount) != 2 ) amount = 1;

    if( amount < 0 ) return notify_fail("你想降低人物的能力？\n");

    // 提升人物等級
    if( arg == "level" ) {
    	add_level(me);
    	return 1;
    }
    
    if( arg == "check" )  {
	    if( me->query_level() >= CLASS_D(me->query_class())->getMaxLV() )
		    return notify_fail("你的等級已經達到該職業的上限了。\n");
		
        write("等級提升至 " + (me->query_level()+1) + " 級，需要 " + CLASS_D(me->query_class())->getLvUpExp(me) + " 點學習點數。\n");
    	return 1;
    }
    
    // 提升人物屬性
    if( arg == "str" || arg == "con" || arg == "dex" || arg == "int" ) {
        add_attribute(me, arg, amount);
        return 1;
    }
    
    // 提升人物狀態
    if( arg == "ap" || arg == "hp" || arg == "mp" ) {
        add_state(me, arg, amount);
        return 1;
    }
    
    // 提升人物技能
    if( me->query_skill(arg, 1) ) {
        add_skill(me, arg, amount);
        return 1;
    }
    
    write("沒有 " + arg + " 這種屬性、狀態或技能，你無法提升任何能力。\n");

    return 1;
}

int help()
{
    write(@TEXT
指令格式： advance <屬性、狀態或技能> [for <點數>]

這個指令可以提升人物的能力。

例：
advance level        提升人物的等級
advance check        檢視人物提升等級需要的學習點數
advance str          提升人物的力量屬性1點，使用後扣除一點屬性點數
advance con for 3    提升人物的體格屬性3點，使用後扣除三點屬性點數
advance dex          提升人物的敏捷屬性1點，使用後扣除一點屬性點數
advance int for 2    提升人物的智慧屬性2點，使用後扣除二點屬性點數

advance ap           提升人物精神值狀態1點，使用後扣除一點潛能點數
advance hp for 50    提升人物體力值狀態50點，使用後扣除五十點潛能點數
advance mp           提升人物查克拉狀態1點，使用後扣除一點潛能點數

advance combat      技能combat投一點，技能上限提升20級
advance dodge for 3 技能dodge投三點，技能上限提升60級
TEXT);
    return 1;
}
