#include <ansi.h>
#include <npc.h>

inherit F_SEABANDIT;

void create()
{
    set_name("螺騎", ({ "royce" }) );
    set_race("human");
    set_level(22);
    set("title", HIR"三日月"NOR);
    set("nickname", HIM"巧克力"NOR);
    set("gender", "male");
    set("class", "little_sea");
    set("camp", "robber");
    set("age", 42);
    set("long", "愁眉苦臉的海賊，似乎正在煩惱什麼事情。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: command, "say 「船長」你們跑哪去了！不要丟下我阿！" :),
        (: command, "say 這裡都是殭屍骷髏...嚇死我了 Q__Q" :),
    }));
    set("set_drop", ({
        ([ "type":"obj", "id":127, "amount":1, "p1":10, "p2":100 ]),   // 石灰
    }) );
    setup();
    carry_object("/world/area/thorn_pine/npc/wp/long_hook.c")->wield();
    carry_object("/world/area/thorn_pine/npc/wp/long_hook.c")->wield("lefthand");
}

void relay_say(object ob, string arg)
{
    if( arg == "船長" )  {
        do_chat(({
            (: command, "cry" :),
            (: command, "say 那天跟船長找寶藏來到這裡。" :),
            (: command, "say 看到這個天枰我們就確信寶藏一定在裡面。" :),
            (: command, "say 不過天枰上的數字...一般物品根本放不下。" :),
            (: command, "say 所以我們將食物磨成粉...或是找各地的沙子來試..." :),
            (: command, "say 結果這附近風太強了...不管放什麼東西都被吹走..." :),
            (: command, "say 直到船長拿出一包灰粉秤重，居然沒被吹走！" :),
            (: command, "say 船長一興奮起來就帶著大家離開了..." :),
            (: command, "say 我回天枰上幫忙拿那包灰粉，沒想到船長他們已經走了！" :),
            (: command, "say 船長你們在哪裡阿！" :),
            (: command, "cry" :),
        }));
        return;
    }
}
