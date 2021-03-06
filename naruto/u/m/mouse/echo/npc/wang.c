#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

void to_do_say()
{
    do_chat( ({
        (: command, "angry" :),
        (: command, "say 麵！快給我麵！" :),
    }) );
}
void create()
{
    set_name("王百萬", ({ "wang by one", "wang", "one" }));
    set_race("human");
    set_level(40);
    set("title",HIC"麵食家"NOR);
    set("long", "肥肥胖胖的麵食家，家財萬貫全都拿去買麵吃。\n");
    set("age", 40);
    set("gender", "male");
    set("chat_chance", 5);
    set("chat_msg", ({
        (: to_do_say :),
    }) );
    setup();
}
int relay_say(object me, string arg)
{
    if( arg == "麵" ) {
        do_chat( ({
           (: command, "say 你是拿老張牛肉麵來給我的嗎！？" :),
        }) );
        return 1;
    }
    if( arg == "老張" || arg == "牛肉麵" || arg == "老張牛肉麵" ) {
        do_chat( ({
           (: command, "stare" :),
           (: command, "say 那碗麵改變了我的一生。" :),
           (: command, "say 原本我是個什麼都吃，完全不懂得享受。" :),
           (: command, "say 吃過了那碗麵，才真的知道什麼叫人間美味！" :),
           (: command, "sigh" :),
           (: command, "say 不過後來我再也找不到老張的麵攤了。" :),
           (: command, "say 只聽說有人在咆哮墓林看過老張在那裡哭。" :),
           (: command, "say 不過這怎麼可能呢！那種高手幹麻跑到墓林去！" :),
           (: command, "say 如果有空能幫忙我找找他嗎？" :),
           (: command, "say 錢絕對不是問題！" :),
        }) );
    }
    if( arg == "幫忙" || arg == "找他" ) {
        if( this_player()->query_temp("quest/noodle_help") == 1) {
            do_chat( ({
               (: command, "glare" :),
               (: command, "say 好餓阿，你快點好嗎。" :),
            }) );
        }
        this_player()->add_temp("quest/noodle_help", 1);
        do_chat( ({
           (: command, "ya" :),
           (: command, "say 交給你摟！" :),
        }) );
        return 1;
    }
    return 1;
}
int give_check(object ob)
{
    if( ob->id("_BEEF_NOODLES_") ) return 1;    // 牛肉麵
    if( ob->id("_GOOD_FOOD_") ) return 2;       // 一堆麵
    else return 0;
}
int accept_object(object me, object ob)
{
    int amount;
    object item;

    if( is_busy() ) {
        tell_object(me, "他正在吃麵中，請稍等。\n");
        return 0;
    }
    if( is_fighting() ) {
        do_chat((: command, "say 偶爾運動一下也不錯！" :));
        return 0;
    }
    me->start_busy(1);
    this_object()->start_busy(1);

    switch( give_check(ob) ) {
        case 1:
            if( this_player()->query_temp("quest/noodle_help") < 1 ) {
                do_chat((: command, "say 你故意拿麵來氣我嗎！" :));
                return 0;
            }
            amount = ob->query_amount();
            message_vision("$N接過$n感動的流下眼淚。\n"NOR, this_object(), ob);
            do_chat( ({
               (: command, "say 這...實在太棒了！" :),
               (: command, "spank " + this_player()->query("id") :),
               (: command, "say 這"+amount*100000+"兩銀子就拿去吧！我要好好享受這麵了。" :),
               ( : destruct , ob : ),
            }) );
            tell_object(me, "( "HIY+amount*100000+HIG" 兩銀子已經自動存在銀行裡。"NOR")\n");
            me->add("bank", amount*100000);
            me->delete_temp("quest/noodle_help");
            break;
        case 2:
            if( this_player()->query_temp("quest/noodle_help") < 1 ) {
                do_chat((: command, "say 蟹黃生蠔鮑魚龜頭水果拉麵？等等也去買一碗。" :));
                return 0;
            }
            amount = ob->query_amount();
            message_vision("$N接過$n聞聞香味。\n"NOR, this_object(), ob);
            do_chat( ({
               (: command, "say 嗯，確定是真品，不過不是牛肉麵真可惜！" :),
               (: command, "say 這"+amount*1000+"兩銀子給你當跑路費吧。" :),
               ( : destruct , ob : ),
            }) );
            tell_object(me, "( "HIY+amount*1000+HIG" 兩銀子已經自動存在銀行裡。"NOR")\n");
            me->add("bank", amount*1000);
            me->delete_temp("quest/noodle_help");
            break;
        default:
            do_chat((: command, "say 這是什麼阿！能吃嗎！" :));
            return 0;
            break;
    }
    return 1;
}
