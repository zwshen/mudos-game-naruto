/* variation.c
  -Tmr 2005/10/21
*/
#include <ansi.h>
#define SKILL_NAME   "variation"
#define SKILL_NAME_C "變化系基礎"
#define SKILL_CLASS  "variation"

inherit SKILL;

void create()
{
	seteuid(getuid());
    DAEMON_D->register_skill_daemon(SKILL_NAME);
}

string query_class() { return SKILL_CLASS; }

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