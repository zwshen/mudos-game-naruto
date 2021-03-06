/* machine_gun.c
   雙手機關槍 放出 rank 2 技能
   會影響念彈連發次數
  -Tmr 2006/06/04
  update by Acme 2007.03.16
*/

#include <ansi.h>
#define SKILL_NAME   "machine gun"
#define SKILL_NAME_C "雙手機關槍"
#define SKILL_CLASS  "emit"

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