#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;

void create()
{
    set_name("奧伊莫", ({ "oe mo", "oe", "mo" }) );
    set_race("human");
    set_level(55);
    set("age", 135);
    set("title", HIY"巨人族"NOR);
    set("long", "你的身高還不到他的小腿，他在你的面前就像一座高牆，聽說偉大的\n"
                "航道上有島嶼是巨人所生存的島，看來此人應該就是來自這座島吧！\n"
                "只聽巨人用無奈地說：「只要守住司法島五十年，我就能知道頭目的\n"
                "下落啦！別妄想攻擊這裡喔！」\n");

    set("set_drop", ({
        ([ "type":"wp", "id":43, "amount":1, "p1":50, "p2":100 ]),    // 刺木棒
        ([ "type":"wp", "id":32, "amount":1, "p1":1, "p2":100 ]),     // 巨斧
        ([ "type":"wp", "id":59, "amount":1, "p1":1, "p2":2000 ]),    // 巨人族之大槌
        ([ "type":"eq", "id":2, "amount":1, "p1":80, "p2":100 ]),     // 鐵胸甲
        ([ "type":"eq", "id":49, "amount":1, "p1":10, "p2":100 ]),    // 綠色緊身衣
        ([ "type":"eq", "id":36, "amount":1, "p1":5, "p2":100 ]),     // 阿蓋
    }) );
    setup();
    carry_object(_DIR_AREA_"thorn_pine/npc/wp/thorn_staff.c")->wield("twohanded");
    add_temp("apply/attack", 400);
}
void init()
{
    if( this_object() == this_player() ) return;

    // 若 this_player() 看不見這個人物，則不引發戰鬥。
    if( ! this_object()->visible(this_player()) ) return;

    // 區域設定
    if( environment()->is_area() && !area_environment(this_object(), this_player()) ) return;

    // 若雙方正互相仇視中，開始戰鬥。
    if( this_player()->is_killing(query("id")) ) {
        COMBAT_D->auto_fight(this_player(), this_object(), "hatred");
        return;
    }
    if( is_killing(this_player()->query("id")) )
    {
        COMBAT_D->auto_fight(this_object(), this_player(), "hatred");
        return;
    }
    // 遇到海賊職業的就主動攻擊
    if( this_player()->query_class() == "little_sea" 
        || this_player()->query_class() == "thief_sea" 
        || this_player()->query_class() == "big_sea" 
        || this_player()->query_class() == "reward_sea" 
        || this_player()->query_class() == "money_sea"
        || this_player()->query_class() == "king_sea" ) {

        message_vision(HIR"$N一見到$n立刻上前攻擊：「為了尋找頭目！一定要守住司法島！」\n\n"NOR, this_object(), this_player());
        this_object()->kill_ob(this_player());
        this_player()->kill_ob(this_object());
        do_chat((: command, "kill " + this_player()->query("id") :));
    }
}
void die()
{
    object enemy, killer;
    string msg;

    enemy = this_object()->last_damage_giver();

    if( !enemy ) {
        destruct(this_object());  // 找不到對手，直接消失
        return;
    }
    // 寵物殺死算主人的
    if( !userp(enemy) && objectp(enemy->query_owner()) ) {
        killer = enemy->query_owner();
    } else {
        killer = enemy;
    }
    msg = "\n\n"+this_object()->query("name")+"痛苦著說道："HIG"老大∼∼我救不了你們了∼嗚嗚∼\n\t　　　　跟海軍講好鎮守此地一百年就能放你們出來∼∼"NOR"\n\n"HIY"居然在 "+CHINESE_D->chinese_date(time())+" 被"+enemy->query("name")+"打敗了∼嗚嗚∼\n\n"NOR;
    msg += HIR"【社會新聞】艾爾帊布戰士"+this_object()->query("name")+"("+this_object()->query("id")+")被"+enemy->rank()+enemy->query("name")+"("+enemy->query("id")+")擊敗於司法島！\n\n"NOR;

    killer->add("exchange", 2);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死"+this_object()->query("name")+"獲得了 2 點兌換點數。)\n"NOR);
    ::die();
    return;
}