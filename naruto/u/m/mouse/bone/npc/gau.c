#include <npc.h>
#include <ansi.h>

inherit F_VENDOR;

void create()
{
    set_name("童角", ({ "ton gau", "gau" }) );
    set_level(60);
    set_class("superior");
    set_race("human");
    set("gender", "male");
    set("age", 25);
    set("long","木葉醫療忍者，似乎正在等人來幫助他。");
    set("chat_chance", 15);
    set("chat_msg", ({
        (: command, "say 委託的燈籠任務怎麼都沒人要幫忙呢...":),
    }));
    setup();
}
void relay_say(object ob, string arg)
{
    if( arg == "燈籠" || arg == "燈籠任務" || arg == "委託" )  {
        do_chat(({
            (: command, "nod" :),
            (: command, "say 就是戰事林通倍利所拿的燈籠。" :),
            (: command, "say 聽說據有神奇的療傷效果。" :),
            (: command, "say 所以我想拿回來研究。" :),
            (: command, "say 不過我以前就認識大蛇丸，就這樣跑去一定會被攻擊的。" :),
            (: command, "say 因為這樣我對燈籠的事也是一知半解。" :),
            (: command, "sigh" :),
            (: command, "say 所以必須拜託一些生面孔去拿才行。" :),
            (: command, "say 到附近的『骸骨戰場』找「輝夜一族」" :),
            (: command, "say 他們是大蛇丸旗下的一支族群。" :),
            (: command, "say 大蛇丸就是派他們去拿燈籠的，所以問他們應該會更清楚。" :),
            (: command, "say 你能「幫忙」我嗎？" :),
        }));
        return;
    }
    if( arg == "骸骨戰場" || arg == "輝夜一族" )  {
        do_chat(({
            (: command, "hmm" :),
            (: command, "say 地圖會看吧？" :),
            (: command, "say 就是 help world 啦。" :),
            (: command, "say 骸骨戰場就在左上角。" :),
            (: command, "say 輝夜一族當然就在那邊。" :),
            (: command, "ah" :),
            (: command, "say 對了..." :),
            (: command, "say 千萬別跟輝夜一族的人起衝突阿..." :),
            (: command, "say 他們以前被稱為惡魔一族..是很危險的族群。" :),
        }));
        return;
    }
    if( arg == "惡魔一族" )  {
        do_chat(({
            (: command, "fear" :),
            (: command, "say 別問那麼多，不要跟他們起衝突就對了！" :),
        }));
        return;
    }
    if( arg == "幫忙" ) {
        if( this_player()->query_temp("quest/tonlight") == 1) {
            do_chat(({
                (: command, "say 你已經在幫我了！" :),
                (: command, "say 不想幫就說「不幫」" :),
            }));
            return;
        }
        this_player()->add_temp("quest/tonlight", 1);
        do_chat(({
            (: command, "jump" :),
            (: command, "say 那就麻煩你了。" :),
            (: command, "say 因為大蛇丸也在找這個燈籠。" :),
            (: command, "say 所以村中將這個升格為Ｃ級任務了。" :),
        }));
        return;
    }
    if( arg == "不幫" )  {
        if( this_player()->query_temp("quest/tonlight") < 1) {
            do_chat(({
                (: command, "?" :),
                (: command, "say 你有幫忙我嗎？" :),
            }));
        } else {
        this_player()->delete_temp("quest/tonlight");
            do_chat(({
                (: command, "glare" :),
                (: command, "say 到底誰能拿到這個燈籠呢..." :),
            }));
            return;
        }
    }
}
int give_check(object ob)
{
    if( ob->id("_TONBELI_A_") ) return 1;   // 通倍利燈籠
    else return 0;
}
int accept_object(object me, object ob)
{
    int amount;
    object item;

    amount = ob->query_amount();

    if( is_busy() ) {
        do_chat((: command, "say 等等！等等！" :));
        return 0;
    }
    if( is_fighting() ) {
        do_chat((: command, "say 等我解決他再說！" :));
        return 0;
    }
    me->start_busy(1);
    this_object()->start_busy(1);
    switch( give_check(ob) ) {
        case 1:
            if( me->query_temp("quest/tonlight") != 1) {
                do_chat((: command, "say 你有幫忙我嗎？" :));
                return 0;
            }
            amount = ob->query_amount();
            message_vision("$N接過$n後高興的拍手。\n"NOR, this_object(), ob);
            do_chat( ({
               (: command, "pat" :),
               (: command, "say 太好啦！" :),
               (: command, "say 非常謝謝你的幫忙，這是賞金！" :),
               ( : destruct , ob : ),
            }) );
            tell_object(me, "( "HIY+amount*15000+HIG" 兩銀子已經自動存在銀行裡。"NOR")\n");
            tell_object(me, HIY"Ｃ級任務"NOR"增加了("HIY+amount+NOR")點。\n");

            me->add("bank", amount*15000);

            // 加c級任務
            me->gain_score("clevel", amount);

            // 移除暫存的資料
            me->delete_temp("quest/tonlight");
            break;
        default:
            do_chat((: command, "say 這不是燈籠阿！" :));
            return 0;
            break;
    }
    return 1;
}
