#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

void to_do_say()
{
    do_chat( ({
        (: command, "say 這些蒼之梟真是太猖狂了。" :),
        (: command, "say 真不知道該怎麼對付牠們。" :),
        (: command, "sigh" :),
    }) );
}
void create()
{
    set_name("豹頭", ({ "bow head", "head", "_BOW_HEAD_" }));
    set_race("human");
    set_level(60);
    set("title","豹人族長");
    set("long", "豹族長老，在悠閒中眼神卻帶著一種悲痛。\n");
    set("age", 80);
    set("gender", "male");
    set("chat_chance", 5);
    set("chat_msg", ({
        (: to_do_say :),
        CYN"搖椅發出聲響...「喀..」\n"NOR,
    }) );
    setup();
}
int relay_say(object me, string arg)
{
    if( !objectp(me) || !stringp(arg) ) return 0;

    if( arg == "高手高手高高手" ) {
        if( this_player()->query_temp("quest/gogogood") == 1) {
            do_chat( ({
               (: command, "ack" :),
               (: command, "say 沒想到"+this_player()->query("name")+"真的對這個稱呼有興趣阿！" :),
               (: command, "say 那就給你吧！哈哈∼後繼有人了。" :),
            }) );
            this_player()->add_temp("quest/gogogood", 1);
            this_player()->set("nickname",HIW"高手"HIY"高手"HIC"高高手"NOR);
        } else
        if( this_player()->query_temp("quest/gogogood") > 1) {
            do_chat( ({
               (: command, "say 怎麼把那麼貴重的稱號弄丟了呢！" :),
               (: command, "say 再給"+this_player()->query("name")+"一次吧！" :),
               (: command, "say 再弄丟我可不管了！" :),
            }) );
            this_player()->delete_temp("quest/gogogood");
            this_player()->set("nickname",HIW"高手"HIY"高手"HIC"高高手"NOR);
        } else {
            do_chat( ({
               (: command, "cac" :),
               (: command, "say 那可是我年輕時大家給我的稱呼呢！" :),
               (: command, "say 只要能「對付」蒼之梟，這稱呼給你也罷！" :),
               (: command, "nomatch _BOW_HEAD_" :),
            }) );
        }
        return 1;
    }
    if( arg == "蒼之梟" || arg == "猖狂" ) {
        do_chat( ({
           (: command, "say 提到牠就讓我生氣。" :),
           (: command, "angry" :),
           (: command, "say 我年輕的時候就有一隻蒼之梟來過轟天瀑。" :),
           (: command, "say 結果被人稱「高手高手高高手」的我給打跑了。" :),
           (: command, "cac" :),
           (: command, "eh _BOW_HEAD_" :),
           (: command, "say 不對..不是要說這個。" :),
           (: command, "say 是牠們最近居然又跑來佔領轟天瀑。" :),
           (: command, "say 已經殺死我們不少去轟天瀑修練的族人了！" :),
           (: command, "say 加上我年事已高..." :),
           (: command, "ah" :),
           (: command, "say 最近我們在找人「對付」這些蒼之梟。" :),
           (: command, "say 有興趣可以找我洽談阿。" :),
           (: command, "wink "+this_player()->query("id") :),
        }) );
        return 1;
    }
    if( arg == "對付" || arg == "有興趣" || arg == "恰談" || arg == "興趣" ) {
        if( this_player()->query_temp("quest/owleyes") == 1) {
            do_chat( ({
               (: command, "say 加油加油！" :),
               (: command, "laddoil "+this_player()->query("id") :),
               (: command, "say 如果成功可以把高手高手高高手的名號給你喔！" :),
            }) );
        } else {
            do_chat( ({
               (: command, "say 太好了！終於找到人能對付啦！" :),
               (: command, "goodboy "+this_player()->query("id") :),
               (: command, "say 只要給我梟之眼就能證明你打死牠了！" :),
               (: command, "say 加油吧！" :),
            }) );
        this_player()->add_temp("quest/owleyes", 1);
        }
        return 1;
    }
    return 1;
}

int give_check(object ob)
{
    if( ob->id("_OWL_EYE_") ) return 1;    // 梟之眼
    else return 0;
}
int accept_object(object me, object ob)
{
    int amount;
    object item;

    if( is_busy() ) {
        tell_object(me, "正在忙碌中，等等吧。\n");
        return 0;
    }
    if( is_fighting() ) {
        do_chat((: command, "say 沒看到高手正在打架嗎！" :));
        return 0;
    }
    me->start_busy(1);
    this_object()->start_busy(1);

    switch( give_check(ob) ) {
        case 1:
            if( this_player()->query_temp("quest/owleyes") < 1 ) {
                do_chat((: command, "say 我沒有拜託你對付牠們吧！" :));
                return 0;
            }
            amount = ob->query_amount();
            message_vision("$N看著$n高興的從木椅上跳了起來。\n"NOR, this_object(), ob);
            do_chat( ({
               (: command, "say 幹的好阿！" :),
               (: command, "spank " + this_player()->query("id") :),
               (: command, "say 這"+amount*50000+"兩銀子是我自己多給的！" :),
               ( : destruct , ob : ),
            }) );
            tell_object(me, "( "HIY+amount*50000+HIG" 兩銀子已經自動存在銀行裡。"NOR")\n");
            tell_object(me, HIY"Ｃ級任務"NOR"增加了("HIY+amount*5+NOR")點。\n");

            me->add("bank", amount*50000);

            // 加c級任務
            me->gain_score("clevel", amount*5);

            // 增加高手nick
            me->add_temp("quest/gogogood", 1);

            // 移除暫存的資料
            me->delete_temp("quest/owleyes");
            break;
        default:
            do_chat((: command, "say 你以為我老糊塗了嗎！" :));
            return 0;
            break;
    }
    return 1;
}
