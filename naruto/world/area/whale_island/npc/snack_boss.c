// write by Tmr 2005/10/22

#include <npc.h>
#define QCATE "level_p"
#define QID 10

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("老板", ({ "snack boss", "boss" }) );
    set_race("human");
    set_level(5);
    set("age", 30);
    set("long",@long
一位經營燒賣小吃店的年輕店長，正在忙進忙出。
long
);

    // 一般時動作
    set("chat_chance", 3);
    set("chat_msg", ({
        (: command, "say 最近蟹黃燒賣越賣越好，材料也越用越兇了..." :),
        (: command, "say 不知道有沒有人願意幫忙搜尋蟹黃的材料呢..." :),
        (: command, "sweat" :),
    }) );

    set_goods(1, "food", 51, 100, 150); // 不知為何價錢只賣 30 自定價
    set_goods(2, "food", 62, 20, 600); // 不知為何價錢只賣 50 自定價
    set_goods(3, "food", 10, 50, -1);
    set_goods(4, "food", 11, 50, -1);

    setup();

}

// 當char用say指令時，此mob的回應
int relay_say(object me, string arg)
{
    if( !objectp(me) || !stringp(arg) ) return 0;

    if( arg == "幫忙" ) {
        if( me->query_quest(QCATE, QID) ) {
                this_object()->force_me("say 咦...我已經有請您幫忙了不是嗎？");
                return 1;
        }
        this_object()->force_me("say 喔喔！！非常感謝，那就麻煩您幫我收集５個蟹黃來吧。");
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
    if( !item->id("__CRAB_ROE__") ) return 0;  //　不是蟹黃

    if( item->query_amount() < 5 ) {
        this_object()->force_me("say 數量好像還不夠耶，能麻煩你再去補齊一點嗎...");
         return 0;
        }

    this_object()->force_me("say 啊哈∼∼非常謝謝你的幫忙，謝謝了！！");
        this_object()->force_me("thank " + me->query_id());
        tell_object(me, "(你的學習點數增加 " + 10*item->query_amount()/5 +" 點了。)\n");
        me->add_point("learn", 10*item->query_amount()/5 );
        // 移除暫存的資料
        me->delete_quest(QCATE, QID);

        // 使用 do_chat 來延遲呼叫 destruct 先讓 give 動作完成
        do_chat((: destruct, item :));
        return 1;
}

