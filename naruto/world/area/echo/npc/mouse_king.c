#include <npc.h>
#include <ansi.h>

void create()
{
    set_name(HIK"地鼠王"NOR, ({ "the king of mouse", "mouse", "king" }) );
    set_race("beast");
    set_level(21);
    set("title", "壞地鼠");
    set("long", "一隻肥胖到臃腫的超胖地鼠，與其他地鼠相異甚大。\n");
    set("limbs", ({ "鼠頭", "身體", "腹部", "鼠腿", "尾巴" }) );
    set("verbs", ({ "bite" }) );
    set("attitude", "aggressive");         // 主動攻擊
    set("chat_chance", 5);
    set("chat_msg", ({
        (: random_move :),
    }));
    set("set_drop", ({
        ([ "type":"food", "id":35, "amount":1, "p1":80, "p2":100 ]),   // 鼠目
        ([ "type":"food", "id":36, "amount":1, "p1":80, "p2":100 ]),   // 鼠腳
        ([ "type":"food", "id":37, "amount":1, "p1":80, "p2":100 ]),   // 鼠尾
        ([ "type":"food", "id":56, "amount":1, "p1":30, "p2":100 ]),   // 鼠腦
        ([ "type":"eq", "id":53, "amount":1, "p1":80, "p2":100 ]),     // 鼠頭
        ([ "type":"eq", "id":54, "amount":1, "p1":3, "p2":100 ]),      // 大暴牙
    }) );
    setup();
    add_temp("apply/attack", 20);
    set_skill("combat", 110);
    set_skill("dodge", 110);
    set_skill("parry", 110);
    set_skill("savage hit", 110);
    set_skill("heavy hit", 110);
    set_skill("continual hit", 110);
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
                message_vision(HIR"$N忽然吱吱叫了起來！開始攻擊$n了！\n\n"NOR, this_object(), inv[i]);

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
