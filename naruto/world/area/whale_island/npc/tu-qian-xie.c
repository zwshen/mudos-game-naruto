/* guild: hunter  獵人 */
// write by Tmr 2005/10/22
// update by Acme 更新成新任務型態

#include <npc.h>
#include <ansi.h>

/*
#define QCATE "level_e"
#define QID 4
*/

inherit F_VILLAGER;

void create()
{
    set_name("屠千蟹", ({ "tu qian-xie", "tu", "xie"}) );
    set_race("human");
    set_level(5);
    set("title","快炒達人");
    set("age", 40);
    set("long",@long
屠千蟹是這一代赫赫有名的海鮮快炒達人，尤其是他對於蟹肉的
調理，無論是菜色的千變萬化，還是口味的出陳鋪新，都能非常人之
所能，叫他一聲「達人」也不為過。他真實的本名已經被大家遺忘了
，然而屠千蟹更能表揚他現在的成就。
long
);

    // 一般時動作
    set("chat_chance", 3);
    set("chat_msg", ({
        (: command, "say 近年來真是越來越忙了，訂單接都接不完..." :),
        (: command, "sweat" :),
        (: command, "say 蟹肉用料越用越兇，不知道有沒有人能幫忙搜集呢..." :),
    }) );


    setup();

}

/*
// 當char用say指令時，此mob的回應
int relay_say(object me, string arg)
{
    if( !objectp(me) || !stringp(arg) ) return 0;

    if( arg == "幫忙"  ) {
            if( me->query_score("elevel") >= 1000 ) {
                tell_object(me, "屠千蟹似乎不需要您的幫忙了。\n");
                return 0;
             }
        if( me->query_quest(QCATE, QID) ) {
                this_object()->force_me("say 咦...我已經有請您幫忙了不是嗎？");
                return 1;
        }
        this_object()->force_me("say 喔喔！！非常感謝，那就麻煩您幫我收集１０個蟹肉來吧。");
        me->add_quest(QCATE, QID, 1);
        return 1;
    }   
    return 1;
}

int accept_object(object me, object item)
{
    int score;

    if( !objectp(me) || !objectp(item) ) return 0;
    if( me->query_quest(QCATE, QID) != 1 ) return 0;
    if( !item->id("__CRAB_MEAT__") ) return 0;  //　不是蟹肉

    if( item->query_amount() < 10 ) {
        this_object()->force_me("say ㄜ..數量好像還不夠耶，能麻煩你再去補齊一點嗎...");
         return 0;
        }


    this_object()->force_me("say 啊哈∼∼非常謝謝你的幫忙了，這是我的一點報酬，謝謝了。");
        this_object()->force_me("thank " + me->query_id());
    tell_object(me, "(共 "HIY+item->query_amount()*100+NOR" 銀子已經自動存在銀行裡。)\n");
    me->add("bank", item->query_amount()*100);
        // 加e級任務1點
    me->gain_score("elevel", item->query_amount()/10);
        // 移除暫存的資料
        me->delete_quest(QCATE, QID);

    // 使用 do_chat 來延遲呼叫 destruct 先讓 give 動作完成
    do_chat((: destruct, item :));

    return 1;
}
*/
