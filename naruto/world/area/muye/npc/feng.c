#include <npc.h>
#include <ansi.h>

object do_random(string category)
{
    int rnd, *key;
    key = keys(ITEM_D->do_query_all(category));
    rnd = key[random(sizeof(key))];
    return ITEM_D->get_item(category, rnd);
}

void do_fight()
{
    int damage, raiseDamage, i;
    object enemy, wp;

    enemy = this_object()->query_opponent();

    if( !enemy ) return;
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    this_object()->damage_stat("mp", 15, this_object());
    message_vision(HIK"\n$N結印施展「"HIB"影分身之術"HIK"」隨即出現三位影分身快速抽起$N背後武器施展"YEL"「三日月之舞」\n"NOR, this_object(), enemy);

    for(i=0;i<3;i++) {
        if( !COMBAT_D->isHit(this_object(), enemy) ) {
            message_vision("$N發現無法順利攻擊$n，便將影分身收回了。\n", this_object(), enemy);
            this_object()->start_busy(1);
        } else {
            wp = do_random("wp");
            raiseDamage = 600;

            add_temp("apply/attack", raiseDamage); 
            damage = COMBAT_D->isDamage(this_object(), enemy, wp);
            add_temp("apply/attack", -raiseDamage);

            if( damage < 200 ) damage = 250 + random(150);

            enemy->receive_damage(damage, this_object());
            message_vision( sprintf(HIB"[影]"NOR"$N迅速散開，手持"+wp->query("name")+"擊中了$n的破綻(%d) %s\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
            destruct(wp);
        }
    }
    message_vision("\n", this_object());
    return;
}

void to_do_say()
{
    do_chat( ({ 
        (: command, "say 這裡是古老的高塔「四輪之塔」" :),
        (: command, "say 因為靠近木葉村，所以由木葉忍者看管。" :),
        (: command, "say 裡面怪物成群，沒有實力不要隨便靠近。" :),
    }) );
}

void create()
{
    set_name("月光疾風", ({ "ji feng", "feng" }));
    set_race("human");
    set_level(60);
    set("camp", "muye");
    set("title", HIK"特別上忍"NOR);
    set_class("superior");   // 上忍
    set("long", "經常咳嗽像個病人似的，為人公平公正，能作出適當的判斷，在任何\n"
                "情況下都能保持鎮定，以敏捷的身手保護過不少應考生的性命，他也\n"
                "是木葉村的精銳忍者。\n");

    set("age", 23);
    set("gender", "male");
    set("chat_chance", 1);
    set("chat_msg", ({
        (: to_do_say :),
    }) );
    set("chat_chance_combat", 25);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    setup();
    set_skill("ninja", 200);
    set_skill("substitute", 200);
    map_skill("dodge", "substitute");
    carry_object(_DIR_AREA_"ship/npc/wp/snow_blade.c")->wield();
}

void relay_say(object ob, string arg)
{
    if( arg == "四輪之塔" )  {
        do_chat( ({ 
            (: command, "hmm" :),
            (: command, "say 四輪之塔共有四座，分別建立在各處。" :),
            (: command, "say 不過每一座都距離村子不遠。" :),
            (: command, "say 研判可能有什麼用途吧..." :),
            (: command, "say 但是關於塔的一切目前無人知曉。" :),
        }) );
    }
}
