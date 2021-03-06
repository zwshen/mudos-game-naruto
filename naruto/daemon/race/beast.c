// beast.c

#define BASE_WEIGHT 10000

#include <ansi.h>
#include <statistic.h>
#include <race.h>

inherit HUMANOID;

string *combat_actions = ({
    "$N撲上來張嘴往$n$l咬去",
    "$N往$n$l撲了過去，張嘴便咬",
    "$N用爪子往$n$l狠狠一抓",
    "$N齜牙裂嘴，奮不顧身地往$n$l狠狠一咬",
});

string query_action()
{
    return combat_actions[random(sizeof(combat_actions))];
}

void create()
{
    ::create();

    seteuid(getuid());

    set("unit", "隻");

    set("gender", "male-animal");

    set("limbs", ({ "頭部", "身體" }) );

    set("default_actions", (: call_other, __FILE__, "query_action" :) );

    DAEMON_D->register_race_daemon("beast");
}

void setup(object ob)
{
    ::setup(ob);

	ob->set_default_object(__FILE__);
	
	if( !ob->query_weight() ) ob->set_weight(BASE_WEIGHT);
}

void initialize(object ob)
{
    seteuid(geteuid(ob));

    if( !ob->query("age") )
	ob->set("age", 1);
    ob->set_default_object(__FILE__);
}
/*
// 野獸是不會拿武器的
int valid_wield(object me, object ob, string skill) { return 1; }

// 野獸是不會穿防具的
int valid_wear(object me, object ob, string part) {	return 1; }
*/
