#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

void to_do_say()
{
    do_chat( ({
        (: command, "say 想要「參加」有照獵人考試嗎！？" :),
        (: command, "say 歡迎有實力的無照獵人報名參加！" :),
    }) );
}
void create()
{
    set_name("薩茨", ({ "saze" }));
    set_race("human");
    set_level(60);
    set_class("hxh_intermediate");
    set("title","獵人試驗主考官");
    set("long", "臉上沒什麼表情，但就能讓人感覺親切。\n");
    set("camp", "hunter");
    set("age", 35);
    set("gender", "male");
    // 一般時動作
    set("chat_chance", 3);
    set("chat_msg", ({
        (: to_do_say :),
    }) );
    setup();
}
int relay_say(object me, string arg)
{
    if( !objectp(me) || !stringp(arg) ) return 0;

    if( arg == "參加" || arg == "參加考試" ) {
        if( me->query_level() < 20 ) {
            do_chat((: command, "say "+me->query("name")+"實力還太差了，不能參加有照獵人考試。" :));
            return 1;
        }
        if( me->query_class() != "hxh_initial") {
            do_chat((: command, "say "+me->query("name")+"，只有無照獵人才能參加考試。" :));
            return 1;
        }
        if( me->query_temp("inter_test") ) {
            do_chat((: command, "say "+me->query("name")+"已經參加有照獵人考試了喔。" :));
            return 1;
        }
        do_chat(({
            (: command, "say 好吧！"+me->query("name")+"聽著考試題目。" :),
            (: command, "say 去試煉洞窟中打敗其他無照獵人拿號碼牌。" :),
            (: command, "say 只要能拿到三張號碼牌給我，你就成為有照獵人了！" :),
        }));
        me->set_temp("inter_test", 1);
    }
    return 1;
}
int accept_object(object me, object item)
{
    int pass=0;

    if( !objectp(me) || !objectp(item) ) return 0;
    if( !item->query("inter_test") ) return 0;

    if( me->query_level() < 20 ) {
        do_chat((: command, "say "+me->query("name")+"實力還太差了，不能參加有照獵人考試。" :));
        return 0;
    }
    if( me->query_class() != "hxh_initial") {
        do_chat((: command, "say "+me->query("name")+"，只有無照獵人才能參加考試。" :));
        return 0;
    }
    if( !me->query_temp("inter_test") ) {
        do_chat((: command, "say "+me->query("name")+"沒有參加有照獵人考試了喔。" :));
        return 0;
    }
    message_vision("$N接過$n給的"+item->query("name")+"說道："HIG"很好！繼續努力吧！\n"NOR, this_object(), me);

    if( item->query("inter_test") == 1 ) me->add_temp("inter_test_b1", 1);

    if( me->query_temp("inter_test_b1") >= 3 ) pass = 1;

    if( pass ) {
        me->delete_temp("inter_test");
        me->delete_temp("inter_test_b1");
        me->set_class("hxh_intermediate");
        do_chat(({
            (: command, "say "+me->name()+"已經通過有照獵人考試了！恭喜！" :),
            (: command, "cong "+me->query_id() :),
            (: destruct, item :),
        }));
        return 1;
    }
    do_chat(((: destruct, item :)));
    return 1;
}
