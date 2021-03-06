#include <npc.h>
#include <ansi.h>

#define CATEGORY    "prize"             // 獎賞型任務
#define ID1         3                   // 測試1
#define ID2         4                   // 測試2

inherit F_VENDOR;

void to_do_say()
{
    do_chat( ({ 
        (: command, "say 我做的東西有口碑阿！" :),
        (: command, "say 只是最近材料難求，想工作也不行∼" :),
        (: command, "say 森林裡的狐熊和沼魚都有我想要的好材料" :),
    }) );
}
void create()
{
    set_name("金鐵鑰" , ({ "gin tkey", "tkey" }) );
    set("long", "原是鑰匙店老闆，偶然發現天然材料，就改做防具去了。\n");
    set_level(40);
    set("gender", "male");
    set("title", "防具店長" );
    set("age", 60);
    // 一般時動作
    set("chat_chance", 5);
    set("chat_msg", ({
        (: to_do_say :),
    }) );
    set_goods(1, "eq", 1, 10, -1);
    set_goods(2, "eq", 2, 10, -1);
    set_goods(3, "eq", 3, 10, -1);
    set_goods(4, "eq", 4, 10, -1);
    set_goods(5, "eq", 5, 10, -1);
    set_goods(6, "eq", 6, 10, -1);
    set_goods(7, "eq", 7, 10, -1);
    set_goods(8, "eq", 8, 10, -1);
    set_goods(9, "eq", 9, 10, -1);
    set_goods(10, "eq", 10, 10, -1);
    set_goods(11, "eq", 11, 10, -1);
    set_goods(12, "eq", 12, 10, -1);
    set_goods(13, "eq", 13, 10, -1);
    set_goods(14, "eq", 14, 10, -1);
    set_goods(15, "eq", 15, 10, -1);
    set_goods(16, "eq", 16, 10, -1);
    set_goods(17, "eq", 17, 10, -1);
    set_goods(18, "eq", 18, 10, -1);
    set_goods(19, "eq", 19, 10, -1);
    set_goods(20, "eq", 20, 10, -1);
    set_goods(21, "eq", 21, 10, -1);
    set_goods(22, "eq", 22, 10, -1);
    set_goods(23, "eq", 23, 10, -1);
    set_goods(24, "eq", 24, 10, -1);
    set_goods(25, "eq", 25, 10, -1);
    setup();
}
void relay_say(object ob, string arg)
{
    if( arg == "材料" || arg == "好材料" )  {
        do_chat( ({ 
            (: command, "say 手套需要四個狐掌、二十條狐毛、十二片魚鱗，八張狐皮。" :),
            (: command, "say 鱗甲需要八片精鱗、四十片魚鱗。" :),
            (: command, "peer" :),
            (: command, "say 你說為什麼材料都要兩倍？" :),
            (: command, "say 在說廢話嗎∼不然我賺什麼阿∼" :),
            (: command, "say 想要就快去∼等你喔！" :),
        }) );
        return;
    }
    if( arg == "工作" ) {
        if( ob->query_quest(CATEGORY, ID1) ) {
            do_chat( ({ 
                (: command, "say 目前要我做的是鱗甲，別記錯了！。" :),
            }) );
        } else
        if( ob->query_quest(CATEGORY, ID2) ) {
            do_chat( ({ 
                (: command, "say 目前要我做的是手套，別記錯了！。" :),
            }) );
        } else {
            do_chat( ({ 
                (: command, "say 沒材料就沒工作∼" :),
                (: command, "say 沒工作就沒錢賺∼" :),
                (: command, "say 沒錢賺就關門睡馬路！" :),
                (: command, "say 阿∼！想到就可怕。" :),
                (: command, "fear" :),
            }) );
        }
        return;
    }
    if( arg == "口碑" ) {
        do_chat( ({ 
            (: command, "say 我做的鱗甲和手套可是有口碑的。" :),
        }) );
        return;
    }
    if( arg == "鱗甲" ) {
        if( ob->query_quest(CATEGORY, ID1) ) {
           do_chat( ({ 
               (: command, "say 什麼！忘記要什麼材料！" :),
               (: command, "say 鱗甲需要八片精鱗、四十片魚鱗。" :),
               (: command, "say 別再忘了！" :),
           }) );
        } else
        if( ob->query_quest(CATEGORY, ID2) ) {
           do_chat( ({ 
               (: command, "say 要改做鱗甲？" :),
               (: command, "say 好啦好啦∼材料拿來都一樣！" :),
               (: command, "say 不過剛才有給過材料的話！全都不算數喔！" :),
           }) );
           ob->delete_quest(CATEGORY, ID2);
           ob->add_quest(CATEGORY, ID1, 1);
        } else {
           do_chat( ({ 
               (: command, "say 做鱗甲嗎！材料交上來吧！" :),
               (: command, "say 只要有材料，馬上給你物品！" :),
           }));
           ob->add_quest(CATEGORY, ID1, 1);
        }
        return;
    }
    if( arg == "手套" ) {
        if( ob->query_quest(CATEGORY, ID2) ) {
            do_chat( ({ 
                (: command, "say 什麼！忘記要什麼材料！" :),
                (: command, "say 手套需要四個狐掌、二十條狐毛、十二片魚鱗，八張狐皮。" :),
                (: command, "say 別再忘了！" :),
           }) );
        } else
        if( ob->query_quest(CATEGORY, ID1) ) {
           do_chat( ({ 
               (: command, "say 要改做手套？" :),
               (: command, "say 好啦好啦∼材料拿來都一樣！" :),
               (: command, "say 不過剛才有給過材料的話！全都不算數喔！" :),
           }) );
           ob->delete_quest(CATEGORY, ID1);
           ob->add_quest(CATEGORY, ID2, 1);
        } else {
            do_chat( ({ 
                (: command, "say 做手套嗎！材料交上來吧！" :),
                (: command, "say 只要有材料，馬上給你物品！" :),
            }));
            ob->add_quest(CATEGORY, ID2, 1);
        }
        return;
    }
}
int give_check(object ob)
{
    if( ob->id("_FOX_HAIR_") ) return 1;              // 狐毛
    else if( ob->id("_FOX_LEATHER_") ) return 2;      // 狐皮
    else if( ob->id("_FISH_SCALE_") ) return 3;       // 魚鱗
    else if( ob->id("_GIN_LINE_") ) return 4;         // 精鱗
    else if( ob->id("_FOX_PAW_") ) return 5;          // 狐掌
    else return 0;
}

int accept_object(object me, object ob)
{
    object item;

    if( is_busy() ) {
        tell_object(me,"對方正在忙碌中，請等一下。\n");
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
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            if( me->query_quest(CATEGORY, ID1) == 1) {
                me->add_temp("quest/" + CATEGORY+ID1 + "/" + give_check(ob), ob->query_amount() );
                if( me->query_temp("quest/"+CATEGORY+ID1+"/3") >= 40 &&
                    me->query_temp("quest/"+CATEGORY+ID1+"/4") >= 8 ) {
                    me->delete_temp("quest/"+CATEGORY+ID1);
                    me->delete_quest(CATEGORY, ID1);
                    if( file_size(__DIR__"eq/scalearmor.c") < 0 ) return 0;
                    if( catch(item = new(__DIR__"eq/scalearmor.c")) ) return 0;
                    if( item->move(me) ) {
                        message_vision("$N接過材料走進工作室，不一會便走出拿著" + item->name() + "給$n。\n", this_object(), me);
                    } else {
                        if( item->move(environment(me)) ) {
                            message_vision("$N接過材料走進工作室，不一會便走出拿著" + item->name() + "給$n，但是掉在地上了。\n", this_object(), me);
                        } else {
                            destruct(item);
                            return 0;
                        }
                    }
                } 
            } else
            if( me->query_quest(CATEGORY, ID2) == 1) {
                me->add_temp("quest/" + CATEGORY+ID2 + "/" + give_check(ob), ob->query_amount() );
                if( me->query_temp("quest/"+CATEGORY+ID2+"/1") >= 20 &&
                    me->query_temp("quest/"+CATEGORY+ID2+"/2") >= 8 &&
                    me->query_temp("quest/"+CATEGORY+ID2+"/3") >= 12 &&
                    me->query_temp("quest/"+CATEGORY+ID2+"/5") >= 4 ) {

                    me->delete_temp("quest/"+CATEGORY+ID2);
                    me->delete_quest(CATEGORY, ID2);
                    if( file_size(__DIR__"eq/foxscale.c") < 0 ) return 0;
                    if( catch(item = new(__DIR__"eq/foxscale.c")) ) return 0;
                    if( item->move(me) ) {
                        message_vision("$N接過材料走進工作室，不一會便走出拿著" + item->name() + "給$n。\n", this_object(), me);
                    } else {
                        if( item->move(environment(me)) ) {
                            message_vision("$N接過材料走進工作室，不一會便走出拿著" + item->name() + "給$n，但是掉在地上了。\n", this_object(), me);
                        } else {
                            destruct(item);
                            return 0;
                        }
                    }
                }
            } else {
                message_vision("$N疑惑地問道﹕"HIG"$n沒說要做什麼防具吧！\n"NOR, this_object(), me);
                return 0;
            }
            ob->set_amount(0);
            do_chat( ({ ( : destruct , ob : ), }) );
            break;
        default:
            do_chat((: command, "say 這材質太差了！" :));
            return 0;
            break;
    }
    return 1;
}
