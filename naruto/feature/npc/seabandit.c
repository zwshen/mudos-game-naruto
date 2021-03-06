/*  seabandit.c
    by mouse 2007/7/26
*/
#include <ansi.h>

mixed do_chat(mixed chat);
varargs string name(int raw);
int is_fighting(object);
void kill_ob(object);

int accept_fight(object ob)
{
    switch(random(5)) {
        case 0: do_chat((: command, "grin" :));                         break;
        case 1: do_chat((: command, "say 痛痛快快打一架！" :));         break;
        case 2: do_chat((: command, "say 大海男兒可是很有毅力的！" :)); break;
    }
}

void accept_kill(object ob)
{
    if( is_fighting(ob) ) return;
    do_chat((: command, "say 老子不打你到動起手來了...！" :));
    
    // 增加區域判斷 by -Acme-
    if( environment()->is_area() ) {
        mapping info;
        info = this_object()->query("area_info");
        if( !info ) return;
        environment()->query_inventory(info["x_axis"], info["y_axis"])->soldier_assist(this_object(), ob);
    }
    else all_inventory(environment())->soldier_assist(this_object(), ob);
}
