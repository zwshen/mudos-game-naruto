#include <weapon.h>
#include <ansi.h>

inherit F_WEAPON;

int i = 0;
int do_attack(object obj);

string *combat_wp = ({
    "$N一面快速奔跑裝填子彈，隨後一個轉身一槍射向$n",
    "$N舉起$w施展「托擊法」打向$n$l",
    "$N發現來不及裝填子彈，隨手就舉起$w砸向$n$l",
});

string *atk_msg = ({
        "左肩", "右肩", "左臂", "右臂", "左腿", "右腿", "左胸", "右胸",
        "左耳", "右耳", "左手", "右手", "左腳", "右腳", "肚子", "背部",
});

string getCombatAction(object me, object weapon)
{
    if( weapon->is_weapon() ) return combat_wp[random(sizeof(combat_wp))];
    else return RACE_D(me->query_race())->query_action();
}

void create()
{
    set_name("海軍制式鐵砲", ({ "iron gun", "gun" }));
    set_weight(1000);
    setup_weapon(8, 8, 100, 1);
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("value", 808);
        set("have_mag", 1);
        set("long", "海軍士兵都會配帶的制式武器，能夠發射出鐵制的砲彈。\n"
                    "使用"HIY"[check gun]"NOR"可以查看剩餘彈數\n"
                    "使用"HIY"[change gun]"NOR"可以更換彈夾(需要有彈夾才能更換)\n"
                    "使用"HIY"[gun attack on (目標)]"NOR"射擊敵人。\n");
    }
    set("wield_msg", "$N將$n上膛後拿在手上。\n");
    setup();
}

void init()
{
    add_action("do_firegun", "gun");
    add_action("do_change", "change");
    add_action("do_check", "check");
}

int do_change(string arg)
{
    object clip;

    if( this_player()->is_busy() )
        return notify_fail("你正在忙碌，沒空換彈。\n");

    // 檢查有沒有帶彈夾
    if( !objectp(clip = present("_CLIP_", this_player())) )
        return notify_fail("你的身上沒有彈夾，無法換彈。\n");

    if( arg == "gun" ) {
        message_vision(CYN"$N開始更換彈夾。\n"NOR, this_player());
        if( i >= 10) {
            i = 0;
            write("彈夾更換完畢。\n");
            destruct(clip);
        } else {
            write("彈數十分充足，不用更換。\n");
        }
        if( this_player()->is_fighting() ) {
            write("你在戰鬥中更換彈夾，一時間無法行動！");
            this_player()->start_busy(3);
        } else {
            this_player()->start_busy(1);
        }
        return 1;
    }
    return 0;
}

int do_check(string arg)
{
    int a = 20 - i;

    if( arg == "gun" ) {
        message_vision(CYN"$N仔細檢查著剩餘彈數。\n"NOR, this_player());
        write("子彈剩餘("HIY+a+NOR")發。\n");
        return 1;
    }
}

int do_firegun(string arg)
{
    string func,target;
    object ob;

    if( this_player()->is_busy() )
        return notify_fail("你正在忙碌中，沒空用槍。\n");

    if( !this_object()->query("equipped") )
        return notify_fail("你沒拿槍怎麼用。\n");

    if( !this_player()->is_fighting() )
        return notify_fail("你沒在戰鬥，不能用槍。\n");

    if( !arg || sscanf(arg, "%s on %s", func, target)!=2 )
        return notify_fail("使用指令為 gun attack on <目標>\n");

    if( !objectp(ob = present(target, environment(this_player()))) )
        return notify_fail("你找不到目標。\n");

    if( !ob || !ob->is_character() || ob->is_corpse() || ob == this_player() )
        return notify_fail("這個目標根本不需要用槍射擊。\n"NOR);

    if( func == "attack" ) {
        do_attack(ob);
    }
    return 1;
}

int do_attack(object ob)
{
    string msg;
    object me;
    int damage, exact, evade;

    me = this_player();
    exact = me->query_level();
    evade = ob->query_level();
    msg = atk_msg[random(sizeof(atk_msg))];

    if( i > 20 ) {
        message_vision("鐵砲發出喀喀聲響，應該是子彈用光了。\n", me);
        return 1;
    }
    me->add_temp("apply/attack", 100);
    damage = COMBAT_D->isDamage(me, ob, this_object());
    me->add_temp("apply/attack", -100);

    if( damage < 20 ) damage = random(20);

    message_vision("\n$N半蹲著拿起"HIW"鐵砲"NOR"瞄準$n，「碰」地一聲射出子彈。\n", me, ob);
    if( !COMBAT_D->SkillHit(me, ob, exact, evade) ) {
        message_vision("但是子彈射偏了，沒打中$n。\n\n", me, ob);
    } else {
        ob->damage_stat("hp", damage, me);
        message_vision( sprintf("$n被鐵彈擊中了"+msg+"，好像受到了一些傷害(%d) %s\n\n", damage, COMBAT_D->report_status(ob) ), me, ob);
    }
    i++;
    me->start_busy(2);
    return 1;
}
