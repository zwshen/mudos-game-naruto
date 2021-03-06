#include <ansi.h>

inherit COMBINED_ITEM;

object owner;

// 設定主人
int set_owner(object ob)
{
    if( !objectp(ob) ) return 0;
    owner = ob;
}

// 查詢主人
object query_owner()
{
    if( !objectp(owner) ) return 0;
    return owner;
}

void create()
{
    set_name(GRN"寄"NOR+HIG"生"NOR"丸"NOR, ({ "bad pill", "pill", "_BAD_PILL" }));
    set("unit", "沱");
    set("base_value", -1);
    set("base_weight", 10);
    set("no_sac", 1);
    set("no_drop", 1);
    set("no_sell", 1);
    set("no_box", 1);
    set("no_give", 1);
    set("long", "寄生能力特強的蕨類植物，特別喜歡寄生在即時治療的藥品上。\n");
    setup();
    call_out("poison_pill", 10, this_object());
}

void poison_pill(object ob)
{
    mapping cnd = ([]);
    object pill, me;
    int i, damage;

    me = query_owner();

    if( !me ) {
        me = environment(this_object());
        set_owner(me);
    }
    if( !objectp(ob) || !me ) return;

    i = random(20) + 1;
    switch( random(6) ) {
        case 0: if( pill = present("heal hp pill", me) ) {
                    if( pill->query_amount() >= i ) damage = i*5;
                    else damage = pill->query_amount()*5;

                    me->receive_damage(damage, me);
                    message_vision( sprintf(HIR"寄生藤刺在 "HIY+i+HIR" 顆$n上，使之爆裂炸傷了$N"NOR"(%d) %s\n", damage, COMBAT_D->report_status(me) ), me, pill);
                } else {
                    set_temp("pill", 1);
                }
                break;
        case 1: if( pill = present("heal mp pill", me) ) {
                    message_vision(HIM"寄生藤刺在 "HIY+i+HIM" 顆$n上，使之產生異變成為了寄生丸。\n"NOR, me, pill);
                    set_temp("bad_add", 1);
                } else {
                    set_temp("pill", 1);
                }
                break;
        case 2: if( pill = present("heal ap pill", me) ) {
                    message_vision(HIC"寄生藤刺在 "HIY+i+HIC" 顆$n上，使之迅速萎縮乾癟失去效用。\n"NOR, me, pill);
                } else {
                    set_temp("pill", 1);
                }
                break;
        case 3: if( pill = present("big heal hp pill", me) ) {
                    if( pill->query_amount() >= i ) damage = i*10;
                    else damage = pill->query_amount()*10;

                    me->receive_damage(damage, me);
                    message_vision( sprintf(HIR"寄生藤刺在 "HIY+i+HIR" 顆$n上，使之爆裂炸傷了$N"NOR"(%d) %s\n", damage, COMBAT_D->report_status(me) ), me, pill);
                } else {
                    set_temp("pill", 1);
                }
                break;
        case 4: if( pill = present("big heal mp pill", me) ) {
                    message_vision(HIM"寄生藤刺在 "HIY+i+HIM" 顆$n上，使之產生異變成為了寄生丸。\n"NOR, me, pill);
                    set_temp("bad_add", 2);
                } else {
                    set_temp("pill", 1);
                }
                break;
        case 5: if( pill = present("big heal ap pill", me) ) {
                    message_vision(HIC"寄生藤刺在 "HIY+i+HIC" 顆$n上，使之迅速萎縮乾癟失去效用。\n"NOR, me, pill);
                } else {
                    set_temp("pill", 1);
                }
                break;
    }
    if( !me->query_condition("vp") && query_temp("pill") ) {
        message_vision("$N噴出一陣惡臭的毒氣，使$n立刻中毒了。\n"NOR, this_object(), me);

        cnd["name"] = HIG"中毒"NOR;
        cnd["duration"] = this_object()->query_amount();

        me->set_condition("vp", cnd);
    } else {
        if( query_temp("bad_add") ) {
            if( pill->query_amount() > i ) this_object()->add_amount(i*query_temp("bad_add"));
            else this_object()->add_amount(pill->query_amount()*query_temp("bad_add"));
            delete_temp("bad_add");
        }
        if( pill->query_amount() > i ) pill->add_amount(-i);
        else {
            tell_object(me,"但是你身上沒有足夠的藥品，所以所持藥品全部銷毀了。\n"NOR);
            destruct(pill);
        }
    }
    delete_temp("pill");
    call_out("poison_pill", 20, ob);
    return;
}
