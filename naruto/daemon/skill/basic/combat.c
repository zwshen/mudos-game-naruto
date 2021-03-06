#include <ansi.h>
#define SKILL_NAME  "combat"
#define SKILL_CLASS "basic"

inherit SKILL;

// 要求 DEMON_D 登錄技能
void create()
{
	seteuid(getuid());
    DAEMON_D->register_skill_daemon(SKILL_NAME);
}

// 技能種類
string query_class() { return SKILL_CLASS; }

// 不需要 enable 
// int valid_enable(string base_skill) { return base_skill == SKILL_BASE; }

// 技能升級後會呼叫的函式，通常用來設定升下一級所需的經驗
void skill_advanced(object me, string skill)
{
    int lv = me->query_skill(skill, 1);
    switch( lv ) {
    	case 189: me->set_skill_require(skill, 1500000); break; // 關卡3 : 189升190
    	case 149: me->set_skill_require(skill, 1000000); break; // 關卡2 : 149升150
    	case  99: me->set_skill_require(skill, 500000);  break; // 關卡1 :  99升100
    	default:  me->set_skill_require(skill, lv*lv*5); break;
    }
}

// 命中率影響
int exact(object me, object target, int ability, int type)
{
    // 格鬥技巧 (combat) 會影響命中率
    int value = ability + me->query_skill(SKILL_NAME)/2;
    if( !type ) return value;
    
    // 使用一次便會增加經驗
    me->improve_skill(SKILL_NAME, 1);
    return value;
}

/*
int receiveDamage(object me, object target, int damage)
{
    if( userp(me) ) {
        message_vision(HIY"大神的神力讓$N刀槍不入，絲毫不受$n"HIY"的攻擊影響！ (傷害吸收：" + damage + ")\n"NOR, me, target);
        return 0;
    }
    return damage;
}
*/
