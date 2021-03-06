#include <npc.h>

#define CATEGORY    "prize"             // 獎賞型任務
#define ID1         3// 蛇皮腰帶任務
#define ID2         4                   // 虛弱的捕蛇丸大人

inherit F_VILLAGER;

void to_do_say()
{
    do_chat( ({ 
        (: command, "say 蛇的各種部位都有其妙用之處，但最近的蛇是越來越兇了，唉∼" :),
        (: command, "say 就連捕蛇好手，人稱「來就捕」的捕蛇丸大人，也被大蛇王咬傷了..." :),
    }) );
}

void create()
{
    set_name("秦琴" , ({ "qin qin", "qin" }) );
    set("long", "手持了一支長柄鐵叉，腰間繫了個小竹簍，一副捕蛇人家的打扮。\n");

    set_level(35);

    set("gender", "female");
    set("title", "捕蛇人家" );
    set("age", 42);

    // 一般時動作
    set("chat_chance", 3);
    set("chat_msg", ({
        (: to_do_say :),
    }) );

    setup();

}

void relay_say(object ob, string arg)
{
    if( arg == "蛇皮" )  {
        do_chat( ({ 
            (: command, "say 你只要有三十條蛇皮，再付一百銀兩子，我可以幫你製作蛇皮腰帶。" :),
        }) );
        return;
    }

    if( arg == "蛇膽" ) {
        do_chat( ({ 
            (: command, "say 據說利用蛇膽製成的丹藥可以強身。" :),
        }) );
        return;
    }

    if( arg == "蛇蛋" ) {
        do_chat( ({ 
            (: command, "say 據說利用蛇蛋製成的丹藥可以促進血液循環。" :),
        }) );
        return;
    }

    if( arg == "捕蛇丸大人" || arg == "捕蛇丸" || arg == "來就捕" ) {
        do_chat( ({ 
            (: command, "say 自從捕蛇丸大人被蛇咬傷之後，身體就一直相當虛弱。" :),
            (: command, "say 應該要找些燉一些湯藥來讓捕蛇丸大人進進補。" :),
        }) );
        return;
    }

    if( arg == "進補" || arg == "藥" || arg == "湯藥" || arg == "燉藥" ) {
        if( ob->query_quest(CATEGORY, ID2) ) {
            do_chat( ({ 
                (: command, "say 你只要幫忙搜集五個熊掌、十顆鮑魚、二個蛇膽..." :),
                (: command, "say 還有三顆蛇蛋、一條豬腸跟六顆龜頭..." :),
                (: command, "say 搜集好拿來給我便行了..." :),
            }) );
        } else {
            do_chat( ({ 
                (: command, "say 你想幫忙我找一些藥材嗎？" :),
            }) );
        }
        return;
    }

    if( arg == "是" || arg == "好" || arg == "想" || arg == "幫忙" || arg == "要" ) {
        if( !ob->query_quest(CATEGORY, ID2) ) {
            do_chat( ({ 
                (: command, "say 你只要幫忙搜集五個熊掌、十顆鮑魚、二個蛇膽..." :),
                (: command, "say 還有三顆蛇蛋、一條豬腸跟六顆龜頭..." :),
                (: command, "say 搜集好拿來給我便行了..." :),
            }) );
            ob->add_quest(CATEGORY, ID2, 1);
        }
        return;
    }
}

int give_check(object ob)
{
    if( ob->id("_SNAKE_SKIN_") ) return 1;            // 蛇皮
    else if( ob->id("_SNAKE_GALL_") ) return 2;       // 蛇膽
    else if( ob->id("_SNAKE_EGG_") ) return 3;        // 蛇蛋
    else if( ob->id("_BEAR_PAW_") ) return 4;         // 熊掌
    else if( ob->id("_TURTLE_HEAD_") ) return 5;      // 龜頭
    else if( ob->id("_ABALONE_") ) return 6;          // 鮑魚
    else if( ob->id("_PIG_GUT_") ) return 7;          // 豬腸
    else return 0;
}

int accept_object(object me, object ob)
{
    object item;

    if( is_busy() ) {
        tell_object(me, "對方正在忙碌中，請等一下。\n");
        return 0;
    }

    if( is_fighting() ) {
        do_chat((: command, "say 別吵！沒看到我正在打架啊！" :));
        return 0;
    }

    me->start_busy(1);
    this_object()->start_busy(1);

    switch( give_check(ob) ) {
        case 1:
            if( ob->query_amount() < 30 ) {
                do_chat((: command, "say 才這一點蛇皮，不夠做一條腰帶吧。" :));

                return 0;
            }
            if( me->query("bank") < 100 ) {
                do_chat((: command, "say 你的銀行裡不足一百兩也想找我做蛇皮腰帶？" :));
                return 0;
            }

            if( file_size(__DIR__"eq/snake_belt.c") < 0 ) return 0;
            if( catch(item = new(__DIR__"eq/snake_belt.c")) ) return 0;

            if( item->move(me) ) {
                message_vision("$N從背後拿出" + item->name() + "給$n。\n", this_object(), me);
            } else {
                if( item->move(environment(me)) ) {
                    message_vision("$N從背後拿出" + item->name() + "給$n，但是掉在地上了。\n", this_object(), me);
                } else {
                    destruct(item);
                    return 0;
                }
            }

            me->add("bank", -100);
            ob->set_amount(0);
            do_chat( ({ ( : destruct , ob : ), }) );

            break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            if( !me->query_quest(CATEGORY, ID2) ) {
                do_chat((: command, "say 我又沒要你幫我的忙，這怎麼好意思收下..." :));
                return 0;
            }

            me->add_temp("quest/" + CATEGORY+ID2 + "/" + give_check(ob), ob->query_amount() );

            if( me->query_temp("quest/"+CATEGORY+ID2+"/2") >= 2 && me->query_temp("quest/"+CATEGORY+ID2+"/3") >= 3 &&
                me->query_temp("quest/"+CATEGORY+ID2+"/4") >= 5 && me->query_temp("quest/"+CATEGORY+ID2+"/5") >= 6 &&
                me->query_temp("quest/"+CATEGORY+ID2+"/6") >= 10 && me->query_temp("quest/"+CATEGORY+ID2+"/7") >= 1 ) {
                me->delete_temp("quest/"+CATEGORY+ID2);
                me->delete_quest(CATEGORY, ID2);
                if( file_size(__DIR__"eq/snake_legging.c") < 0 ) return 0;
                if( catch(item = new(__DIR__"eq/snake_legging.c")) ) return 0;
                if( item->move(me) ) {
                message_vision("$N從背後拿出" + item->name() + "給$n。\n", this_object(), me);
                } else {
                    if( item->move(environment(me)) ) {
                        message_vision("$N從背後拿出" + item->name() + "給$n，但是掉在地上了。\n", this_object(), me);
                    } else {
                        destruct(item);
                        return 0;
                    }
                 }
            }

            ob->set_amount(0);
            do_chat( ({ ( : destruct , ob : ), }) );

            break;

        default:
            do_chat((: command, "say 這是什麼玩意兒啊？我不要這種東西！" :));
            return 0;
            break;
    }

    return 1;
}
