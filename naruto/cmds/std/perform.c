// cast.c

#include <skill.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string martial_skill, act, trg;
    object target;

    if( !arg ) return notify_fail("指令格式﹕perform <技能.絕招> on <目標>\n");
    
    if( me->query_condition("weak") ) return notify_fail("你太虛弱了，沒辦法使用技能。\n");

    if( sscanf( arg, "%s.%s on %s", martial_skill, act, trg ) == 3 ) {
        if( !me->skill_mapped(martial_skill) )
        	return notify_fail("請先用 enable 指令選擇你要使用的技能。\n");
        
        // 有些 mob 因為 id 問題
        // 在 area 中會判斷不到，像分身之類的
        // 所以另外給 mob 一個判斷式，如果找不到對方就隨機打敵人
        if( userp(me) ) {
            if( !(target = present(trg, environment(me))) || !target->is_character() || target->is_corpse() ) return notify_fail("這裡沒有這個人。\n");
        } else {
            if( !(target = present(trg, environment(me))) ) target = me->query_opponent();
            if( !target ) target = me;
            if( !target || !target->is_character() || target->is_corpse() ) return notify_fail("這裡沒有這個人。\n");
        }
        
//        martial_skill = me->skill_mapped(martial_skill);
        
        return SKILL_D(me->skill_mapped(martial_skill))->perform_action(me, act, target);

    } else if( sscanf( arg, "%s.%s", martial_skill, act ) == 2 ) {
        if( !me->skill_mapped(martial_skill) )
        	return notify_fail("請先用 enable 指令選擇你要使用的技能。\n");

//        martial_skill = me->skill_mapped(martial_skill);

        return SKILL_D(me->skill_mapped(martial_skill))->perform_action(me, act, target);

    } else return notify_fail("指令格式﹕perform <技能.絕招> [on <目標>]\n");

    return 0;
}

int help (object me)
{
    write(@HELP
指令格式﹕perform <技能.絕招> [on <施招對象>]

在戰鬥中使用所學技能的絕招來和施招對象對戰，絕招可以參考
個別的技能所提供的HELP。
HELP);
    return 1;
}
