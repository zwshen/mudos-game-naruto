#include <ansi.h>
#include <npc.h>

void do_fight()
{
    object enemy;

    // 沒有敵人
    enemy = this_object()->query_opponent();

    if( !enemy ) return;

    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    message_vision(HIG"\n$N快速的捲起身子，眼神中帶著一種妖魔般的殺意，吐出一顆經過高速壓縮的風砲！\n\n\t\t"HIW"『"BGRN+BLINK"風龍絞殺"NOR+HIW"』"NOR"\n\n壓縮砲彷彿視四周為無物，所到之處斷源殘壁連根拔起！\n"NOR, this_object(), enemy);
    message_vision(HIR"\n$n根本無從閃躲，只能被風砲絞入，眼前一片混亂...\n\n"NOR, this_object(), enemy);
    this_object()->start_busy(2);
    this_object()->remove_all_killer();
    this_object()->do_heal();
    enemy->unconcious();
    return;
}

void create()
{
    set_name("龍空大王", ({ "lich dragon king", "king" }));
    set_level(80);
    set_race("human");
    set("age", 15001);
    set("limbs", ({ "龍頭", "龍爪", "龍尾", "風鱗", "指甲", "龍鬚", "龍鱗" }) );
    set("long", "身材巨大的妖怪，全身散發出一種類似龍族的氣息。傳說中如果妖魔\n"
                "修道有成，也是可以成為龍族的，這位妖怪也許就是已經成為妖龍的\n"
                "其中之一吧。只見牠盤旋在室內的石柱上，正在吸收著這充滿魔力籠\n"
                "罩的神獸森林之氣，為了回復以前所受的創傷。\n");
    set("nickname", HIG"風巢之主"NOR);
    set("title", HIW"妖龍"NOR);
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    setup();
}
