#include <npc.h>
#include <ansi.h>
#include "fire_sk.h"

void create()
{
    set_name("炙焰金剛", ({ "fire kingkong", "kingkong", "_KING_FOUR_" }) );
    set_level(60);
    set_race("human");
    set("gender", "male");
    set("title", BRED+HIR"燃"NOR);
    set("nickname", HIY"肆"NOR);
    set("limbs", ({ "猴頭", "火臂", "火尾", "胸口", "猴腳", "肩膀", "腰部", "火毛" }) );
    set("age", 5000);
    set("long", "金剛之王，全身噴出雄雄烈火，看起來氣勢非常驚人，不但四周的金\n"
                "剛們對牠投以崇敬的目光，連你看見他的模樣都有點心生畏懼。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        NOR"炙焰金剛"RED"身上的"HIR"火焰"NOR+RED"不斷地燃燒著...四周一片火紅。\n"NOR,
    }));
    set("chat_chance_combat", 35);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":151, "amount":random(20)+1, "p1":80, "p2":100 ]),  // 廢土
        ([ "type":"obj", "id":152, "amount":random(30)+1, "p1":80, "p2":100 ]),  // 塵埃
        ([ "type":"obj", "id":153, "amount":random(5)+1, "p1":80, "p2":100 ]),   // 爛果
        ([ "type":"obj", "id":156, "amount":random(10)+1, "p1":80, "p2":100 ]),  // 碎石
        ([ "type":"obj", "id":148, "amount":random(30)+1, "p1":30, "p2":100 ]),  // 炎灰
        ([ "type":"obj", "id":158, "amount":random(15)+1, "p1":10, "p2":100 ]),  // 燒土
    }) );
    setup();
    add_temp("apply/attack", 50);
}

void die()
{
    object enemy, killer, *targets;
    int i, ntar, x, y;
    string msg;

    enemy = this_object()->last_damage_giver();

    if( !enemy ) {
        ::die();
        return;
    }
    // 寵物殺死算主人的
    if( !userp(enemy) && objectp(enemy->query_owner()) ) {
        killer = enemy->query_owner();
    } else {
        killer = enemy;
    }
    i = query_level()*10;
    msg = "\n"HIW"【四方之塔】"HIR"紅蓮之塔四樓一聲巨響，"+enemy->query("name")+"突破了四樓守塔者"NOR"「"+this_object()->query("title")+"」"HIR+this_object()->query("name")+"！\n\n"NOR;

    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    if( killer->query_level() - 10 <= this_object()->query_level() ) {
        tell_object(killer, HIY"(因為你殺死"+this_object()->query("name")+"獲得了 3 點兌換點數。)\n"NOR);
        tell_object(killer, HIR"\n你殺死了"+this_object()->query("name")+"而額外獲得了 "HIY+i+HIR" 點學點。\n"NOR);
        killer->add("exchange", 3);
        killer->add_point("learn", i);
    }
    if( random(10) > 7 ) {
        targets = query_enemy();
        x = random(30);
        y = random(30);

        // 將玩家的所有動作取消然後丟到其他位置去
        // 先指定座標，好讓玩家的寵物也跟著飛過去
        for(ntar=0;ntar<sizeof(targets);ntar++) {
            if( killer->is_busy() ) targets[ntar]->interrupt(targets[ntar], "*unconcious");
            if( userp(targets[ntar]) ) tell_object(targets[ntar], YEL"\n"+this_object()->query("name")+"臨死前用盡最後的力量將你擊飛到火堆中！\n"NOR);
            if( targets[ntar]->is_busy() ) {
                if( userp(targets[ntar]) ) tell_object(killer, "但被你僥倖逃過一劫。\n\n"NOR);
            } else {
                if( !area_move(environment(targets[ntar]), targets[ntar], x, y) ) {
                    if( userp(targets[ntar]) ) tell_object(targets[ntar], "但被你僥倖逃過一劫。\n\n"NOR);
                }
            }
        }
    }
    ::die();
    return;
}
