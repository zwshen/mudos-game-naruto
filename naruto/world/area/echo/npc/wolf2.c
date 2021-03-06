#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("山狼", ({ "hill wolf", "wolf" }) );
    set_race("beast");
    set_level(15);
    set("age", 11+random(21));
    set("long", "一隻看起來很兇狠的山狼，時常對天狂哮。\n");
    set("limbs", ({ "狼頭", "身體", "腹部", "狼腿", "尾巴" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("chat_chance_combat", 5);
    set("chat_msg_combat", ({
        CYN"山狼向天狂哮著「ㄠ∼ㄨ∼ㄠ∼ㄨ∼」\n"NOR,
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":79, "amount":1, "p1":15, "p2":100 ]),    // 狼牙
        ([ "type":"food", "id":32, "amount":1, "p1":80, "p2":100 ]),   // 狼心
        ([ "type":"food", "id":33, "amount":1, "p1":80, "p2":100 ]),   // 狼肺
        ([ "type":"eq", "id":57, "amount":1, "p1":20, "p2":100 ]),     // 狼腳
        ([ "type":"eq", "id":58, "amount":1, "p1":18, "p2":100 ]),     // 狼皮
        ([ "type":"eq", "id":59, "amount":1, "p1":20, "p2":100 ]),     // 狼腳
        ([ "type":"eq", "id":60, "amount":1, "p1":20, "p2":100 ]),     // 狼頭
        ([ "type":"eq", "id":61, "amount":1, "p1":25, "p2":100 ]),     // 狼尾
        ([ "type":"wp", "id":13, "amount":1, "p1":10, "p2":100 ]),     // 狼爪
    }) );
    setup();
}
void init()
{
    int i;
    object *inv;
    inv = all_inventory(environment(this_object()));

    /* 若 this_player() 看不見這個人物，則不引發戰鬥。 */
    if( !this_object()->visible(this_player()) ) return;

    /* 增加area判斷 add by -Acme- */
    if( environment()->is_area() && !area_environment(this_object(), this_player())) return;

    for(i=0;i<sizeof(inv);i++) {
        if( inv[i] == this_object() ) continue;
        if( !this_object()->visible(inv[i]) ) continue;
        if( environment()->is_area() && !area_environment(this_object(), inv[i])) continue;
        if( this_object()->is_fighting(inv[i]) ) continue;
        if( living(inv[i]) ) {
            if( inv[i]->is_corpse() ) continue;

            // 若雙方正互相仇視中，開始戰鬥。
            if( inv[i]->is_killing(query("id")) ) {
                COMBAT_D->auto_fight(inv[i], this_object(), "hatred");
                continue;
            }
            if( is_killing(inv[i]->query("id")) ) {
                COMBAT_D->auto_fight(this_object(), inv[i], "hatred");
                continue;
            }
            // 看到老張女兒便開打
            if( inv[i]->id("_HELP_GIRL_") && !inv[i]->is_fighting(this_object()) ) {
                message_vision(HIR"$N狂哮一聲，開始攻擊$n了！\n\n"NOR, this_object(), inv[i]);

                this_object()->kill_ob(inv[i]);
                continue;
            }
            // 非玩家不用主動攻擊
            if( !userp(inv[i]) ) continue;

            switch( query("attitude") ) {
                case "aggressive":
                /* 主動攻擊的生物 */
                COMBAT_D->auto_fight(this_object(), inv[i], "aggressive");
                break;
            }
        }
    }
}
