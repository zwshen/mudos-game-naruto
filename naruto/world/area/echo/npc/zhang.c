#include <npc.h>
#include <ansi.h>

inherit F_VENDOR;

void create()
{
    set_name("老張", ({ "old zhang", "zhang" }) );
    set_race("human");
    set_level(50);
    set("long",@LONG
他是一位心情很差的老張，也是覺得生活很鬱卒的老張，賣麵賣了幾
十年，除了第一戰以牛肉麵打敗「一樂」拉麵店老板獲得『麵神戒』
後，接著十幾年每年都挑戰失敗。這次又遭逢巨變，使他從此成為一
位看起來非常頹廢的人，很難想像他曾經是麵店老闆。
LONG);
    set("title",HIY"賣牛肉麵的"NOR);
    set("age", 50);
    set("gender", "male");
    set("chat_chance", 5);
    set("chat_msg", ({
       (: command, "sigh" :),
       (: command, "say 誰能救救我的女兒阿！" :),
       (: command, "cry" :),
    }) );
    setup();
}
void relay_say(object ob, string arg)
{
    if( arg == "牛肉麵" ) {
        do_chat( ({
            (: command, "shake" :),
            (: command, "say 我女兒被蛇人抓了。" :),
            (: command, "say 現在沒心情煮什麼麵。" :),
        }) );
        return;
    }
    if( arg == "蛇人" || arg == "活祭品" ) {
        do_chat( ({
            (: command, "scream" :),
            (: command, "say 牠們抓了我女兒！" :),
            (: command, "say 誰能救救我阿！" :),
        }) );
        return;
    }
    if( arg == "女兒" ) {
        do_chat( ({
            (: command, "sigh" :),
            (: command, "say 我女兒被那些可惡的蛇人抓去了。" :),
            (: command, "say 當時村人都被殺光了，剩我和我女兒兩人。" :),
            (: command, "say 我女兒要求牠們放過我，她就跟牠們回去。" :),
            (: command, "slap zhang" :),
            (: command, "say 我怎麼那麼沒用呢！" :),
        }) );
        return;
    }
    if( arg == "救你" || arg == "救" ) {
        if( query_temp("that's_ok") >= 1) {
            tell_object(this_player(),HIY"老張正高興著打包行李，沒時間理你。\n"NOR);
            return;
        }
        if( this_player()->query_temp("quest/help_girl") == 1) {
            do_chat((: command, "say 時間緊迫！趕快去阿！" :));
            return;
        }
        this_player()->add_temp("quest/help_girl", 1);
        do_chat( ({
            (: command, "dance" :),
            (: command, "say 一切就拜託你了！" :),
            (: command, "say 快去快回喔！" :),
            (: command, "say 蛇人的位置就去隔壁問堂秋吧！" :),
        }) );
        return;
    }
    if( arg == "不救" ) {
        if( this_player()->query_temp("quest/help_girl") == 1) {
            this_player()->delete_temp("quest/help_girl");
            do_chat( ({
                (: command, "hammer " + this_player()->query("id") :),
                (: command, "say 浪費我的時間阿！" :),
            }) );
            return;
        }
        do_chat( ({
            (: command, "?" :),
            (: command, "say 不救什麼！別跟我開玩笑！" :),
        }) );
        return;
    }
}
void init()
{
    object item;
    int i;
    if( this_player()->id("_HELP_GIRL_") ) {
        i = random(100);
        set_temp("that's_ok", 1);
        message_vision(HIY"\n$N一見到$n便高興的帶著$n離開了，連謝謝都忘了說。\n"NOR, this_object(), this_player());
        if( i >= 50) {
            if( file_size("/world/drug/noodle2.c") < 0 ) return 0;
            if( catch(item = new("/world/drug/noodle2.c")) ) return 0;
            if( item->move(environment(this_object())) ) {
                message_vision(HIC"\n在地上留下一碗$N打包忘了帶走的"+item->name()+"。\n\n"NOR, this_object(), this_player());
            } else {
                destruct(item);
                return 0;
            }
        } else
        if( i >= 25 && i <= 49 ) {
            if( file_size(__DIR__"item/noodle.c") < 0 ) return 0;
            if( catch(item = new(__DIR__"item/noodle.c")) ) return 0;
            if( item->move(environment(this_object())) ) {
                message_vision(HIC"\n在地上留下一碗$N打包忘了帶走的"+item->name()+"。\n\n"NOR, this_object(), this_player());
            } else {
                destruct(item);
                return 0;
            }
        } else
        if( i >= 2 && i <= 24 ) {
            if( file_size("/world/area/muye/npc/item/noodle.c") < 0 ) return 0;
            if( catch(item = new("/world/area/muye/npc/item/noodle.c")) ) return 0;
            if( item->move(environment(this_object())) ) {
                message_vision(HIC"\n在地上留下一碗$N打包忘了帶走的"+item->name()+"。\n\n"NOR, this_object(), this_player());
            } else {
                destruct(item);
                return 0;
            }
        } else {
            if( file_size(__DIR__"eq/ring.c") < 0 ) return 0;
            if( catch(item = new(__DIR__"eq/ring.c")) ) return 0;
            if( item->move(environment(this_object())) ) {
                message_vision(HIW"\n在地上留下一枚閃閃發光的"NOR+item->name()+HIY"。\n\n"NOR, this_object(), this_player());
            } else {
                destruct(item);
                return 0;
            }
        }
        destruct(this_player());
        do_chat((: destruct, this_object() :));  // 延遲，讓物品能先掉在地上
    }
}
