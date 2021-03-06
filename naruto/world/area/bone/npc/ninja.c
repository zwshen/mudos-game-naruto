#include <npc.h>
#include <ansi.h>
#include "skill.h"

string *name1 = ({ "志貴", "琥珀", "翡翠", "瑪瑙", "琉璃", "水晶", "瑾子",
                   "諾立", "桐田", "幽山", "征玲", "天地", "白茫", "黑骨",
                   "風飯", "片瑁", "玳瑁", "紅月", "白月", "黑月", "正月",
                   "琳", "理", "御", "礫", "骸", "骨", "破", "刃", "霧",
                   "燼", "燃", "無", "卯", "巳", "酉", "戌", "亥", "丑",
                   "半兵衛", "中之介", "子午郎", "上之介", "下之介" });

void create()
{
    set_name("竹取"+name1[random(sizeof(name1))], ({ "wheya ninja", "ninja" }) );
    set_level(35);
    set_class("middle");
    set_race("human");

    if( random(2) == 1) set("gender", "male");
    else set("gender", "female");

    set("age", 15+random(41));
    set("title",HIR"血繼限界"NOR);
    set("camp", "wheya");
    set("long",@LONG
竹取一族，在很久以前的一場戰爭後，突然出現的新族群，他們大多
是戰爭過後存活下來的人，也有一些是後代子孫。他們會被人發現的
最大原因，就是他們能夠將骨頭化為利刃，在必要的時刻還能將自己
身上的骨頭拔出做為武器，因太過血腥而被世人認為是惡魔一族，直
到後來被控制音忍的大蛇丸所收留，便定居在他們隨手能拿到武器的
『骸骨戰場』幫助大蛇丸抵制旁邊的蛇人一族。
LONG);
    set("chat_chance", 10);
    set("chat_msg", ({
        (: do_check :),
        (: random_move :),
    }));
    set("chat_chance_combat", 40);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":100+random(200), "p1":60, "p2":100 ]), // 銀子
        ([ "type":"food", "id":16, "amount":1, "p1":3, "p2":100 ]),      // 大精力丸
        ([ "type":"food", "id":18, "amount":1, "p1":5, "p2":100 ]),      // 大體力丸
        ([ "type":"food", "id":20, "amount":1, "p1":3, "p2":100 ]),      // 大查克丸
        ([ "type":"obj", "id":78, "amount":1, "p1":80, "p2":100 ]),      // 輝夜之證
        ([ "type":"wp", "id":50, "amount":1, "p1":1, "p2":700 ]),        // 脊骨劍
        ([ "type":"eq", "id":85, "amount":1, "p1":1, "p2":600 ]),        // 咒印覆面
        ([ "type":"obj", "id":90, "amount":1, "p1":1, "p2":1000 ]),      // 火流星飛天掃帚
    }) );
    setup();
    add_temp("apply", (["hp":1500 ]) );
    // 有調整過 ap, hp, mp 的要 do_heal(), 才能讓狀態補滿
    do_heal();
}
void die()
{
    object ob, *obs;
    obs = all_inventory(this_object());
    if( this_object()->query_temp("quest/psychical") == 1 ) {
        message_vision("因為$N死掉所以"HIW"脊骨劍"NOR"漸漸風化了...。\n"NOR, this_object());
        this_object()->delete_temp("quest/psychical");
        foreach( ob in obs ) destruct(ob);
    }
    ::die();
}
