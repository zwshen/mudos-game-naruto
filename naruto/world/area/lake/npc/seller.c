#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;
int i;

void create()
{
    set_name("古董商人" , ({ "seller" }));
    set("long", "肥肥胖胖的商人，不時對旁人露出善意的微笑。\n");
    set_level(60);
    set("gender","male");
    set("age",60);
    set("chat_chance", 6);
    set("chat_msg", ({
        (: command, "say 這些雨忍還真慢阿。" :),
        (: command, "say 有興趣和我做點「買賣」嗎？" :),
        CYN"古董商人似乎等的不耐煩了。\n"NOR,
        (: command, "angry" :),
    }) );
    setup();
}
void relay_say(object ob, string arg)
{
    if( arg == "方糖勁" || arg == "廢紙" || 
        arg == "破花瓶" || arg == "奇怪的紙" || arg == "紙") {

        do_chat(({ 
           (: command, "say 方糖勁找你來的嗎？" :),
           (: command, "say 少跟他打交道吧。" :),
           (: command, "shrug" :),
        }));
        return;
    }
    if( arg == "買賣" )  {
        if( this_player()->query_temp("quest/seller") == 1) {
        do_chat(({ 
            (: command, "say 你還沒回答我阿？" :),
            (: command, "say 不想幫忙就說「不幫」" :),
        }));
        return;
        } else
        if( this_player()->query_temp("quest/seller") == 2) {
            do_chat(({ 
                (: command, "say 不想幫我了嗎？" :),
                (: command, "say 那就「停止」和我的交易吧。" :),
            }));
            return;
        }
        this_player()->add_temp("quest/seller", 1);
        do_chat(({ 
            (: command, "say 喔喔！有興趣幫我嗎？" :),
            (: command, "say 傳說在天鵝湖底有個古老的建築物喔。" :),
            (: command, "say 只要你幫我拿裡面的古董出來，我就按價給你傭金！" :),
            (: command, "say 只有我才會給個好價喔！考慮看看吧！" :),
        }));
        return;
    }
    if( arg == "有興趣" || arg == "幫忙" ||
        arg == "好" || arg == "幫你" ) {

        if( this_player()->query_temp("quest/seller") == 2) {
            do_chat(({ 
                (: command, "say 你已經要幫我了不是嗎！" :),
                (: command, "say 快點去吧。" :),
                (: command, "say 再不快點小心被他們搬光了喔！" :),
            }));
            return;
        } else
        if( this_player()->query_temp("quest/seller") == 1) {
            this_player()->add_temp("quest/seller", 1);
            do_chat(({ 
                (: command, "jump" :),
                (: command, "say 那就拜託你啦！" :),
                (: command, "say 只是剛才已經有雨隱村忍者來找過我了。" :),
                (: command, "say 他們太慢了讓我不得不再找人幫忙。" :),
                (: command, "say 再不快點小心被他們搬光了喔！" :),
            }));
            return;
        } else {
            do_chat(({ 
                (: command, "?" :),
                (: command, "say 你在說啥阿？" :),
            }));
            return;
        }
    }
    if( arg == "停止" || arg == "不幫" )  {
        if( this_player()->query_temp("quest/seller") < 1) {
            do_chat(({ 
                (: command, "?" :),
                (: command, "say 做什麼阿，我又沒找你幫忙。" :),
            }));
        } else {
        this_player()->delete_temp("quest/seller");
            do_chat(({ 
                (: command, "sigh" :),
                (: command, "say 好吧！我再另外找人好了。" :),
            }));
            return;
        }
    }
}
int give_check(object ob)
{
    if( ob->id("_OLD_VASE_") ) return 1;           // 古董花瓶
    if( ob->id("_EXQUISITE_DOLL_") ) return 2;     // 精緻娃娃
    if( ob->id("_UNKNOWN_POTTERY_") ) return 3;    // 未知陶壺
    if( ob->id("_WOOD_TREASURY_") ) return 4;      // 木造藏
    if( ob->id("_BAD_BELL_") ) return 5;           // 損壞的黃金鐘
    else return 0;
}
int accept_object(object me, object ob)
{
    object item;
    if( is_busy() ) {
        do_chat((: command, "say 東西太多忙不過來阿！" :));
        return 0;
    }
    if( is_fighting() ) {
        do_chat((: command, "say 救命阿！殺人阿！" :));
        return 0;
    }
    me->start_busy(1);
    this_object()->start_busy(1);
    switch( give_check(ob) ) {
        case 1:
            if( me->query_temp("quest/seller") == 2) {
                if( ob->query_amount() > 1 ) {
                    do_chat((: command, "say 一個一個給吧，一次太多我不方便鑑定。" :));
                    return 0;
                }
                i = 100+random(400);
                message_vision("$N接過古董花瓶仔細鑑定。\n", this_object(), me);
                if( i >= 400) {
                    message_vision("$N高興地說﹕"HIG"這個裂紋瓶保存的真好阿！不過不懂的人還以為花瓶裂了呢！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else if( i >= 300) {
                    message_vision("$N難過地說﹕"HIG"可惜了這個花瓶阿！還好裂痕不是很嚴重。\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else if( i >= 200) {
                    message_vision("$N悲痛地說﹕"HIG"傷的真是太嚴重了！只能當次等貨賣！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else {
                    message_vision("$N哀傷地說﹕"HIG"大概不能賣了吧！看在你辛苦拿來的份上∼\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                }
                do_chat( ({ ( : destruct , ob : ), }) );
                break;
            }
            message_vision("$N說道﹕"HIG"想拿偷到的古董賣我阿！\n"NOR, this_object(), me);
            message_vision("$N說道﹕"HIG"想害我可沒這麼容易！\n"NOR, this_object(), me);
            return 0;
            break;
        case 2:
            if( me->query_temp("quest/seller") == 2) {
                if( ob->query_amount() > 1 ) {
                    do_chat((: command, "say 一個一個給吧，一次太多我不方便鑑定。" :));
                    return 0;
                }
                i = 150+random(550);
                message_vision("$N接過精緻娃娃仔細觀察。\n", this_object(), me);
                if( i >= 600) {
                    message_vision("$N笑道﹕"HIG"這個娃娃肯定能賣個好價錢！完全沒有受到傷害呢！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else if( i >= 400) {
                    message_vision("$N說道﹕"HIG"嗯∼有一點點破損，不過補一補大概就看不出來了。\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else if( i >= 250) {
                    message_vision("$N悲痛地說﹕"HIG"傷的真是太嚴重了！只能當次等貨賣！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else {
                    message_vision("$N哀傷地說﹕"HIG"大概不能賣了吧！看在你辛苦拿來的份上∼\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                }
                do_chat( ({ ( : destruct , ob : ), }) );
                break;
            }
            message_vision("$N說道﹕"HIG"想拿偷到的古董賣我阿！\n"NOR, this_object(), me);
            message_vision("$N說道﹕"HIG"想害我可沒這麼容易！\n"NOR, this_object(), me);
            return 0;
            break;
        case 3:
            if( me->query_temp("quest/seller") == 2) {
                if( ob->query_amount() > 1 ) {
                    do_chat((: command, "say 一個一個給吧，一次太多我不方便鑑定。" :));
                    return 0;
                }
                i = 200+random(700);
                message_vision("$N接過未知陶壺仔細鑑定。\n", this_object(), me);
                if( i >= 800) {
                    message_vision("$N高興地大喊﹕"HIG"這可是古代的真蹟阿！沒想到居然有這麼好的東西。\n"NOR, this_object(), me);
                    message_vision("$N爽快地說﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else if( i >= 600) {
                    message_vision("$N愉悅地說﹕"HIG"這陶壺雖然不知出自誰手，但也十分精美呢。\n"NOR, this_object(), me);
                    message_vision("$N笑著說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else if( i >= 400) {
                    message_vision("$N說道﹕"HIG"這大概是仿製品吧！不知道能騙過多少有錢人。\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else {
                    message_vision("$N生氣地說﹕"HIG"這種亂捏一通的陶壺也能叫古董！？\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"給$n"HIY+i+HIG"兩傭金換份工作吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                }
                do_chat( ({ ( : destruct , ob : ), }) );
                break;
            }
            message_vision("$N說道﹕"HIG"想拿偷到的古董賣我阿！\n"NOR, this_object(), me);
            message_vision("$N說道﹕"HIG"想害我可沒這麼容易！\n"NOR, this_object(), me);
            return 0;
            break;
        case 4:
            if( me->query_temp("quest/seller") == 2) {
                if( ob->query_amount() > 1 ) {
                    do_chat((: command, "say 一個一個給吧，一次太多我不方便鑑定。" :));
                    return 0;
                }
                i = 400+random(800);
                message_vision("$N接過木造藏後直接將木造藏剖開查看內部物品。\n", this_object(), me);
                if( i >= 1000) {
                    message_vision("$N驚訝地說﹕"HIG"這些珍珠瑪瑙可都是大顆的真品呢！稍微裝飾一下肯定能賣個好價！\n"NOR, this_object(), me);
                    message_vision("$N快樂地說﹕"HIG"這"HIY+i+HIG"兩傭金給$n還稍嫌不足呢！再多幫我拿幾個上來吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else if( i >= 900) {
                    message_vision("$N笑道﹕"HIG"裡面有些寶石還未經琢磨，但完工後也是一筆大收獲阿！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"這"HIY+i+HIG"兩傭金給$n剛剛好呢！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else if( i >= 700) {
                    message_vision("$N說道﹕"HIG"可惜只能稱的上中級品！賣給一般人家大概不錯。\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else if( i >= 500) {
                    message_vision("$N哀聲嘆氣﹕"HIG"這些寶石似乎太小了一點，可能連做個戒指都不夠吧。\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"就給$n"HIY+i+HIG"兩傭金吧！\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                } else {
                    message_vision("$N聳聳肩說﹕"HIG"搞不好外面的殼還比裡面值錢吧！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"給$n"HIY+i+HIG"兩傭金意思意思吧。\n"NOR, this_object(), me);
                    tell_object(me, "(傭金已經自動存在銀行裡。)\n");
                    me->add("bank", i);
                }
                do_chat( ({ ( : destruct , ob : ), }) );
                break;
            }
            message_vision("$N說道﹕"HIG"想拿偷到的古董賣我阿！\n"NOR, this_object(), me);
            message_vision("$N說道﹕"HIG"想害我可沒這麼容易！\n"NOR, this_object(), me);
            return 0;
            break;
        case 5:
            if( ob->query_amount() > 1 ) {
                do_chat((: command, "say 一個一個給吧，一次太多我不方便鑑定。" :));
                return 0;
            }
            message_vision("$N接過損壞的"HIY"黃金鐘"NOR"後邪邪的一笑。\n", this_object(), me);
            message_vision("$N邪惡地說﹕"HIG"玩壞了商店不收了吧！我這裡可是以"HIY"200"HIG"兩銀子收喔！\n"NOR, this_object(), me);
            message_vision("$N邪惡笑道﹕"HIG"謝謝光臨阿∼歡迎多多玩壞拿來當呦∼\n"NOR, this_object(), me);
            tell_object(me, "(傭金已經自動存在銀行裡。)\n");
            me->add("bank", 200);
            do_chat( ({ ( : destruct , ob : ), }) );
            break;
        default:
            do_chat((: command, "say 我只要古董啦！" :));
            return 0;
            break;
    }
    return 1;
}
