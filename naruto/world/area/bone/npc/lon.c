#include <npc.h>
#include <ansi.h>
#include "skill.h"

void create()
{
    set_name("竹取剛之郎", ({ "wheya gon lon", "lon" }) );
    set_level(60);
    set_class("superior");
    set_race("human");
    set("gender", "male");
    set("camp", "wheya");
    set("age", 85);
    set("title",HIR"竹取族長"NOR);
    set("long",@LONG
竹取族長，一個八十多歲的小老頭，但是他眼神銳利，四周的一切都
逃不過他的眼睛。當年竹取族人被追殺時的傷痕全都留在身上，全身
各處都有大大小小的傷痕，不過這些傷痕看似圓形從內往外的撕裂傷
，據說竹取族人擁有血繼限界，能將自己身上的骨頭拔出，雖然會對
自己造成傷害，所拔出的武器卻能夠隨心所慾的變化，比一般的武器
還要好用。也因為這樣，所以竹取一族又被稱為『惡魔一族』
LONG);
    set("chat_chance", 10);
    set("chat_msg", ({
        (: do_check :),
        (: command, "say 走了蛇人又來個怪物...":),
        (: command, "say 族人都派去對付蛇人了。":),
        (: command, "say 只要是大蛇丸大人託付的任務，一定要完成。":),
    }));
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":28, "amount":1+random(5), "p1":60, "p2":100 ]), // 黃金
        ([ "type":"obj", "id":78, "amount":1, "p1":100, "p2":100 ]),          // 輝夜之證
        ([ "type":"wp", "id":50, "amount":1, "p1":1, "p2":200 ]),             // 脊骨劍
        ([ "type":"eq", "id":85, "amount":1, "p1":1, "p2":150 ]),             // 咒印覆面
    }) );
    setup();
}

void relay_say(object ob, string arg)
{
    if( arg == "蛇人" )  {
        do_chat(({
            (: command, "say 這裡跟神廟、戰事林、絕望沼澤以前都是蛇人的地盤。" :),
            (: command, "say 我們來了之後截斷骸骨戰場，讓牠們兩地無法溝通。" :),
            (: command, "say 接著全力攻擊戰事林那裡的蛇族本村。" :),
            (: command, "say 就在我們和蛇人兩敗俱傷時...忽然跑出一堆怪物。" :),
            (: command, "say 那些怪物把我們和蛇人打跑，就佔據了那裡。" :),
        }));
        return;
    }
    if( arg == "怪物" )  {
        do_chat(({
            (: command, "say 牠們有著綠色的身體，還拿著一把菜刀" :),
            (: command, "say 我們通稱牠們叫「通倍利」。" :),
            (: command, "say 牠們現在就定居在戰事林。" :),
            (: command, "say 攻擊牠們要小心。" :),
            (: command, "say 牠們的王也會偽裝成普通的通倍利混在裡面。" :),
            (: command, "ah" :),
            (: command, "say 還有...戰事林中間有兩間破屋。" :),
            (: command, "say 通倍利們好像不太願意接近其中的一間。" :),
            (: command, "say 不要問為什麼，知道這個一定對你有幫助的。" :),
        }));
        return;
    }
    if( arg == "大蛇丸" )  {
        do_chat(({
            (: command, "say 他是我們竹取一族的恩人！" :),
        }));
        return;
    }
    if( arg == "族人" )  {
        do_chat(({
            (: command, "say 當然就是我們竹取一族！" :),
        }));
        return;
    }
}

void die()
{
    string msg;
    object ob, *obs, enemy, killer;
    int i;

    obs = all_inventory(this_object());
    enemy = this_object()->last_damage_giver();
    i = random(3) + 2;

    if( !enemy ) {
        ::die();
        return;
    }

    if( this_object()->query_temp("quest/psychical") == 1 ) {
        message_vision("因為$N死掉所以"HIW"脊骨劍"NOR"漸漸風化了...。\n"NOR, this_object());
        this_object()->delete_temp("quest/psychical");
        foreach( ob in obs ) destruct(ob);
    }

    // 寵物殺死算主人的
    if( !userp(enemy) && objectp(enemy->query_owner()) ) {
        killer = enemy->query_owner();
    } else {
        killer = enemy;
    }
    msg = "\n\n"RED"大蛇丸大人！沒想到我不但無法成為您的宿體\n\n連守護好骸骨戰場這片要地都做不到！我愧對您的恩情！";
    msg += HIR"\n\n【社會新聞】"+this_object()->query("name")+"("+this_object()->query("id")+")居然在地利之便的骸骨戰場敗給了"+enemy->query("name")+"("+enemy->query("id")+")！\n\n"NOR;

    killer->add("exchange", i);
    CHANNEL_D->say_channels(this_object(), "news", msg, 1);
    tell_object(killer, HIY"(因為你殺死竹取剛之郎獲得了 "+i+" 點兌換點數。)\n"NOR);
    ::die();
}