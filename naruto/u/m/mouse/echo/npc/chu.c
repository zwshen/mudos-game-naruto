#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

void create()
{
    set_name("堂秋", ({ "tom chu", "chu" }));
    set_race("human");
    set("gender", "female");
    set_level(40);
    set("age", 25);
    set("nickname","村中獵人");
    set("long", "手上拿著火槍的獵人，正在整理身旁的裝備。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        (: command, "say 只要我還活著，一定要為村子的人報仇！" :),
        (: command, "say 不該小看那些蛇人的！" :),
    }) );
    setup();
}
void relay_say(object ob, string arg)
{
    if( arg == "蛇人" || arg == "位置" )  {
        do_chat(({
            (: command, "say 我研究了牠們一段日子。" :),
            (: command, "say 發現牠們就在回音洞穴的另一邊。" :),
            (: command, "say 不過數量不是很多...可能跟原族人分散了。" :),
            (: command, "say 也不知道是什麼原因。" :),
            (: command, "say 讓牠們認為奉上活祭品給蛇神，便能找回原本的族人。" :),
        }));
        return;
    }
    if( arg == "活祭品" )  {
        do_chat(({
            (: command, "think" :),
            (: command, "say 這要問老張比較清楚。" :),
            (: command, "say 當時我出去打獵不在村中。" :),
        }));
        return;
    }
    if( arg == "活著" )  {
        do_chat(({
            (: command, "say 這些蛇人真是太可惡了！" :),
            (: command, "say 此仇不報，對不起村人！" :),
        }));
        return;
    }
    if( arg == "報仇" )  {
        if( this_player()->query_temp("quest/helpvill") == 1) {
        do_chat(({
            (: command, "say 不想幫忙就說「不幫」" :),
            (: command, "say 畢竟你不是村人，不會了解這種感覺的。" :),
        }));
        return;
        } else
        if( this_player()->query_temp("quest/helpvill") == 2) {
            do_chat(({
                (: command, "say 不想幫忙啦？" :),
                (: command, "say 那就「停止」繼續幫忙吧。" :),
            }));
            return;
        }
        this_player()->add_temp("quest/helpvill", 1);
        do_chat(({
            (: command, "hmm" :),
            (: command, "say 先把事情的經過告訴你好了。" :),
            (: command, "say 其實就是一群蛇人突然來到村中。" :),
            (: command, "say 還要我們交給牠們一位女性當成活祭品！" :),
            (: command, "say 當然村長拒絕了牠們的要求。" :),
            (: command, "say 到了晚上...那些蛇人居然引了一群山狼來屠村！" :),
            (: command, "say 連唯一的退路回音山洞也被牠們引了一群地鼠在裡面。" :),
            (: command, "say 無法逃離的村人們就成了牠們的獵物。" :),
            (: command, "say 除了老張和我，全都被殺死了。" :),
            (: command, "say 所以我決定要找這些屠村的蛇人報仇！" :),
            (: command, "say 當然山狼和土鼠也是！" :),
            (: command, "say 你能夠「幫助」我嗎？" :),
        }));
        return;
    }
    if( arg == "幫助" ) {
        if( this_player()->query_temp("quest/helpvill") == 2) {
            do_chat(({
                (: command, "say 你已經在幫我了！" :),
            }));
            return;
        } else
        if( this_player()->query_temp("quest/helpvill") == 1) {
            this_player()->add_temp("quest/helpvill", 1);
            do_chat(({
                (: command, "jump" :),
                (: command, "say 太感謝你了！" :),
                (: command, "say 只要給我蛇蛋、鼠頭、狼牙。" :),
                (: command, "say 我就給你用這些物品製成的藥當做獎勵。" :),
                (: command, "say 希望將牠們破壞的力量化為救贖之力。" :),
            }));
            return;
        } else {
            do_chat(({
                (: command, "?" :),
                (: command, "say 還不了解狀況就想幫忙？" :),
            }));
            return;
        }
    }
    if( arg == "停止" || arg == "不幫" )  {
        if( this_player()->query_temp("quest/helpvill") < 1) {
            do_chat(({
                (: command, "?" :),
                (: command, "say 你沒有幫助我吧。" :),
            }));
        } else {
        this_player()->delete_temp("quest/helpvill");
            do_chat(({
                (: command, "sigh" :),
                (: command, "say 好吧，我自己對付牠們。" :),
            }));
            return;
        }
    }
}
int give_check(object ob)
{
    if( ob->id("_WOLF_TOOTH_") ) return 1;   // 狼牙
    if( ob->id("_MOUSE_HEAD_") ) return 2;   // 鼠腦
    if( ob->id("_SNAKE_EGG_") ) return 3;    // 蛇蛋
    else return 0;
}
int accept_object(object me, object ob)
{
    int amount;
    object item;

    amount = ob->query_amount();

    if( is_busy() ) {
        do_chat((: command, "say 太忙了！等等！" :));
        return 0;
    }
    if( is_fighting() ) {
        do_chat((: command, "say 誰來救救我阿！" :));
        return 0;
    }
    me->start_busy(1);
    this_object()->start_busy(1);
    switch( give_check(ob) ) {
        case 1:
            if( me->query_temp("quest/helpvill") == 2) {
                if( amount < 1 ) {
                    do_chat((: command, "say 至少要給一顆以上的狼牙！" :));
                    return 0;
                }
                if( file_size(__DIR__"item/powder.c") < 0 ) return 0;
                if( catch(item = new(__DIR__"item/powder.c")) ) return 0;
                if( amount ) {
                    if( function_exists("set_amount", ob) ) {
                        item->set_amount(amount);
                    } else
                    if( function_exists("set_volume", ob) ) {
                        item->set_volume(amount);
                    }
                }
                if( item->move(me) ) {
                    message_vision("$N說道﹕"HIG"多謝$n的幫忙，這樣村人在天之靈也得到安慰！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"給你同樣數量的"+item->name()+"共"NOR"("HIY+amount+NOR")"HIG"包。\n"NOR, this_object(), me);
                } else
                if( item->move(environment(me)) ) {
                    message_vision("$N說道﹕"HIG"多謝$n的幫忙，這樣村人在天之靈也得到安慰！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"給你同樣數量的"+item->name()+"共"NOR"("HIY+amount+NOR")"HIG"包，太重幫你放地上。\n"NOR, this_object(), me);
                } else {
                    destruct(item);
                    return 0;
                }
                ob->set_amount(0);
                do_chat( ({ ( : destruct , ob : ), }) );
                break;
            }
            message_vision("$N說道﹕"HIG"你有幫助我嗎？\n"NOR, this_object(), me);
            break;
        case 2:
            if( me->query_temp("quest/helpvill") == 2) {
                if( amount < 1 ) {
                    do_chat((: command, "say 至少要給一顆以上的鼠腦！" :));
                    return 0;
                }
                if( file_size(__DIR__"item/fat.c") < 0 ) return 0;
                if( catch(item = new(__DIR__"item/fat.c")) ) return 0;
                if( amount ) {
                    if( function_exists("set_amount", ob) ) {
                        item->set_amount(amount);
                    } else
                    if( function_exists("set_volume", ob) ) {
                        item->set_volume(amount);
                    }
                }
                if( item->move(me) ) {
                    message_vision("$N說道﹕"HIG"多謝$n的幫忙，這樣村人在天之靈也得到安慰！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"給你同樣數量的"+item->name()+"共"NOR"("HIY+amount+NOR")"HIG"塊。\n"NOR, this_object(), me);
                } else
                if( item->move(environment(me)) ) {
                    message_vision("$N說道﹕"HIG"多謝$n的幫忙，這樣村人在天之靈也得到安慰！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"給你同樣數量的"+item->name()+"共"NOR"("HIY+amount+NOR")"HIG"塊，太重幫你放地上。\n"NOR, this_object(), me);
                } else {
                    destruct(item);
                    return 0;
                }
                ob->set_amount(0);
                do_chat( ({ ( : destruct , ob : ), }) );
                break;
            }
            message_vision("$N說道﹕"HIG"你有幫助我嗎？\n"NOR, this_object(), me);
            break;
        case 3:
            if( me->query_temp("quest/helpvill") == 2) {
                if( amount < 1 ) {
                    do_chat((: command, "say 至少要給一顆以上的蛇蛋！" :));
                    return 0;
                }
                if( file_size(__DIR__"item/jelly.c") < 0 ) return 0;
                if( catch(item = new(__DIR__"item/jelly.c")) ) return 0;
                if( amount ) {
                    if( function_exists("set_amount", ob) ) {
                        item->set_amount(amount);
                    } else
                    if( function_exists("set_volume", ob) ) {
                        item->set_volume(amount);
                    }
                }
                if( item->move(me) ) {
                    message_vision("$N說道﹕"HIG"多謝$n的幫忙，這樣村人在天之靈也得到安慰！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"給你同樣數量的"+item->name()+"共"NOR"("HIY+amount+NOR")"HIG"塊。\n"NOR, this_object(), me);
                } else
                if( item->move(environment(me)) ) {
                    message_vision("$N說道﹕"HIG"多謝$n的幫忙，這樣村人在天之靈也得到安慰！\n"NOR, this_object(), me);
                    message_vision("$N說道﹕"HIG"給你同樣數量的"+item->name()+"共"NOR"("HIY+amount+NOR")"HIG"塊，太重幫你放地上。\n"NOR, this_object(), me);
                } else {
                    destruct(item);
                    return 0;
                }
                ob->set_amount(0);
                do_chat( ({ ( : destruct , ob : ), }) );
                break;
            }
            message_vision("$N說道﹕"HIG"你有幫助我嗎？\n"NOR, this_object(), me);
            break;
        default:
            do_chat((: command, "say 這些東西不是我要的..." :));
            return 0;
            break;
    }
    return 1;
}
