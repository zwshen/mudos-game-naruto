#include <ansi.h>

void relay_say(object ob, string arg)
{
    if( arg == "需要" )  {
        this_object()->do_chat( ({ 
            (: command, "say 只要能給我兩百顆猴牙，就給你神木的祝福項鍊。" :),
        }) );
        return;
    }
}

int give_check(object ob)
{
    if( ob->id("_TREE_FRUIT_") ) return 1;            // 樹果
    if( ob->id("_MONKEY_TOOTH_") ) return 2;          // 猴牙
    else return 0;
}

int accept_object(object me, object ob)
{
    object item;
    if( this_object()->is_busy() ) {
        this_object()->do_chat((: command, "say 急什麼！祝福可是很花時間的！" :));
        return 0;
    }
    if( this_object()->is_fighting() ) {
        this_object()->do_chat((: command, "say 看我被打還不快幫忙！不想要項鍊啦！" :));
        return 0;
    }
    me->start_busy(1);
    this_object()->start_busy(1);
    switch( give_check(ob) ) {
        case 1:
            if( me->query_temp("quest/necklace") == 1) {
            if( ob->query_amount() < 100 ) {
                this_object()->do_chat((: command, "say 樹果給的數目不對喔，再去多採點吧。" :));
                return 0;
            }
            if( file_size(__DIR__"eq/necklace.c") < 0 ) return 0;
            if( catch(item = new(__DIR__"eq/necklace.c")) ) return 0;
            if( item->move(me) ) {
                message_vision("$N將"YEL"樹果"NOR"清點後從旁邊拿出一串" + item->name() + "給$n。\n", this_object(), me);
                message_vision("土著祭師溫和地說﹕"HIG"$n快離開吧，其他土著們可不歡迎外人。\n"NOR, this_object(), me);
            } else {
                if( item->move(environment(me)) ) {
                    message_vision("$N將"YEL"樹果"NOR"清點後從旁邊拿出一串" + item->name() + "給$n，但是掉在地上了。\n", this_object(), me);
                    message_vision("土著祭師憤怒地說﹕"HIG"$n居然亂丟神木的項鍊！拿了東西快滾！\n"NOR, this_object(), me);
                } else {
                    me->delete_temp("quest/necklace");
                    destruct(item);
                    return 0;
                }
            }
            me->delete_temp("quest/necklace");
            ob->set_amount(0);
            this_object()->do_chat( ({ ( : destruct , ob : ), }) );
            break;
            } else {
                message_vision("土著祭師說道﹕"HIG"前一種還沒找完呢，急什麼。\n"NOR, this_object(), me);
                return 0;
            }
        case 2:
            if( me->query_temp("quest/necklace")) {

                message_vision("土著祭師說道﹕"HIG"已經給過啦！快找第二種吧。\n"NOR, this_object(), me);
                return 0;
            } else {
            if( ob->query_amount() < 200 ) {
                this_object()->do_chat((: command, "say 猴牙給的數目不對喔，再去多拿點吧。" :));
                return 0;
                } else {
                me->add_temp("quest/necklace", 1);
                message_vision(CYN"土著祭師清點著"HIW"猴牙"NOR""CYN"的數量。\n"NOR, this_object(), me);
                message_vision("土著祭師說道﹕"HIG"差點忘了我還需要一百顆樹果，順便幫我吧。\n"NOR, this_object(), me);
                }
            break;
            }
        default:
            this_object()->do_chat((: command, "say 除了目前需要的物品其他我不要！" :));
            return 0;
            break;
    }
    return 1;
}
