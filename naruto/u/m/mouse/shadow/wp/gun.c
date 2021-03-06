#include <weapon.h>
#include <ansi.h>

inherit F_WEAPON;
int i;
int j;
int k;
int l;
int m;
int do_rifle(object obj);
int do_fire(object obj);
int do_attack(object obj);
int do_gin(object obj);
int do_die(object obj);

string *atk_msg = ({
        "左肩", "右肩", "左臂", "右臂", "左腿", "右腿", "左胸", "右胸",
        "左耳", "右耳", "左手", "右手", "左腳", "右腳", "肚子", "背部",
});

string report_status(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$n" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$n" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$n" + HIR + ratio + "%" + HIK"]\n"NOR;
}

string *combat_wp = ({
    "$N高舉$w送上槍機「"HIY+BLINK"機統速射"NOR"」子彈搭搭搭地瘋狂射向$n",
    "$N將$w槍口裝上榴彈裝置，對準$n所在位置發射榴彈攻擊",
    "$N把槍背在身後，拿出手榴彈一咬，快速丟向$n",
    "$N打開$w的空氣收納器「"HIW"空氣砲"NOR"」碰地一聲射向$n",
    "$N拿出鋼釘發射器裝在$w上，只聽見叮叮數聲，無數鋼釘已朝$n飛去",
    "$N將$w高舉過頂，帶上墨鏡朝空射擊，只見空中一陣閃光，數枚追尾彈射向$n",
});

string getCombatAction(object me, object weapon)
{
    if( weapon->is_weapon() ) return combat_wp[random(sizeof(combat_wp))];
    else return RACE_D(me->query_race())->query_action();
}

void create()
{
    set_name(HIK"多功\能"HIR"步槍"NOR, ({ "diversify rifle", "rifle", "gun" }));
    set_weight(5000);
    setup_weapon(1, 1, 1, 1);
    
    if( !clonep() ) {
        set("wield_as", ({ "twohanded" }) );
        set("unit", "把");
        set("value", 101);
        set("have_mag", 1);
        set("long", @LONG
來自外星的神秘武器，一把槍包含了多種槍的功能，威力強大。
目前能使用的武器種類有：
�翦������踛��������踛������踛�����������������������������
│槍  種│殺 傷 力│總彈數│使  用  方  法              │
�澺������蕅��������蕅������蕅�����������������������������
│來福槍│20-200  │50(1) │firegun rifle on mob        │
│火箭炮│500     │5(1)  │firegun fire on mob         │
│機關槍│10-60*5 │200(5)│firegun attack on mob       │
│精神波│10-100  │10(1) │firegun gin on mob          │
│死光波│?       │500(?)│firegun die on mob          │
│      │        │      │                            │
│      │        │      │                            │
│      │        │      │                            │
�澺������蕅��������蕅������蕅�����������������������������
│查  詢│0       │∞    │check gun                   │
�澺������蕅��������蕅������蕅�����������������������������
│換  彈│0       │∞    │change gun                  │
�檛������薋��������薋������薋�����������������������������
LONG);
    }
    set("wield_msg", "四周傳出"RED"紅色「一級警戒」"NOR"警鳴聲，$N馬上拿出$n裝上彈夾隨時準備攻擊！\n");
    set("unwield_msg", "當燈號回到"HIG"綠色「安全警戒」"NOR"時，$N早已將$n藏回身上。\n");
    setup();
}
void init()
{
    add_action("do_firegun", "firegun");
    add_action("do_change", "change");
    add_action("do_check", "check");
}
int do_change(string arg)
{
    if( this_player()->is_busy()) {
        write(CYN"你正在忙碌，沒空換彈。"NOR"\n");
        return 1;
    }
    if( this_player()->is_fighting() ) {
        write(CYN"戰鬥中沒空換彈啦。"NOR"\n");
        return 1;
    }
    if( arg == "gun" ) {
        message_vision("$N拿起"HIK"多功\能"HIR"步槍"NOR"開始更換彈夾。\n"NOR, this_player());
        if( i >= 40) {
            this_player()->start_busy(1);
            i = 0;
            write("機器音﹕"HIG"來福槍彈倉更換完畢。"NOR"\n");
            return 1;
        }
        if( j >= 4) {
            this_player()->start_busy(1);
            j = 0;
            write("機器音﹕"HIG"火箭炮飛彈補充完畢。"NOR"\n");
            return 1;
        }
        if( k >= 80) {
            this_player()->start_busy(1);
            k = 0;
            write("機器音﹕"HIG"機槍彈夾補充完畢。"NOR"\n");
            return 1;
        }
        if( l >= 5) {
            this_player()->start_busy(1);
            l = 0;
            write("機器音﹕"HIG"精神能源補充完畢。"NOR"\n");
            return 1;
        }
        if( m >= 400) {
            this_player()->start_busy(1);
            m = 0;
            write("機器音﹕"HIG"死光波動補充完畢。"NOR"\n");
            return 1;
        }
        write("機器音﹕"HIG"彈數十分充足，不用更換。"NOR"\n");
        return 1;
    }
}
int do_check(string arg)
{
    int a;

    if( arg == "gun" ) {
        message_vision(CYN"$N仔細檢查著剩餘彈數。\n"NOR, this_player());
        a = 50;
        a = a - i;
        write("機器音﹕"HIG"來福槍子彈剩餘("HIY+a+HIG")發。"NOR"\n");
        a = 5;
        a = a - j;
        write("機器音﹕"HIG"火箭炮飛彈剩餘("HIR+a+HIG")發。"NOR"\n");
        a = 200;
        a = a - k;
        write("機器音﹕"HIG"機槍彈夾剩餘("HIB+a+HIG")發。"NOR"\n");
        a = 10;
        a = a - l;
        write("機器音﹕"HIG"精神光線能源剩餘("NOR+GRN+a+HIG")。"NOR"\n");
        a = 500;
        a = a - m;
        write("機器音﹕"HIG"死光波動剩餘("HIK+a+HIG")。"NOR"\n");
        return 1;
    }
}
int do_firegun(string arg)
{
    string func,target;
    object ob;

    if( this_player()->is_busy()) {
        write(CYN"你正在忙碌中，沒空用槍。"NOR"\n");
        return 1;
    }
    if( !this_object()->query("equipped")) {
        write("機器音﹕"HIG"你沒拿槍怎麼用。"NOR"\n");
        return 1;
    }
    if( !this_player()->is_fighting() ) {
        write("機器音﹕"HIG"你沒在戰鬥，不能用槍。"NOR"\n");
        return 1;
    }
    if ( !arg || sscanf(arg, "%s on %s", func, target)!=2 )
           return notify_fail("機器音﹕"HIG"你想射誰阿？"NOR"\n");

    if ( !objectp(ob = present(target, environment(this_player()))) )
            return notify_fail("機器音﹕"HIG"你想射誰阿？"NOR"\n");

    if ( !ob ||
         !ob->is_character() ||
         ob->is_corpse() ||
         ob==this_player() )
         return notify_fail("機器音﹕"HIG"你想射誰阿？\n"NOR);

    if( func == "rifle") {  do_rifle(ob); }
    if( func == "fire") {  do_fire(ob); }
    if( func == "attack") {  do_attack(ob); }
    if( func == "gin") {  do_gin(ob); }
    if( func == "die") {  do_die(ob); }
    return 1;
}
int do_rifle(object ob)
{
    string msg;
    object me;
    int damage;

    me = this_player();
    msg = atk_msg[random(sizeof(atk_msg))];

    message_vision("$N說道﹕"HIG"來福槍模式。\n"NOR, me, ob);
    if( i < 50) {
        message_vision("$N手中武器慢慢變化成"HIY"來福槍"NOR"的樣子，對準$n一槍轟去！\n", me, ob);
        i = i+1;
        damage = random(181) + 20;
        if( random(me->query_ability("evade")) - random(ob->query_ability("evade"))) {
            ob->damage_stat("hp", damage, ob);
            message_vision("        $n被子彈打中"+msg+"！痛的哇哇大叫。("+damage+")"+report_status(ob)+"", me, ob);
            me->start_busy(1);
            return 1;
        }
        message_vision("        $n早就跑的遠遠的，浪費一發子彈(0)"+report_status(ob)+"", me, ob);
        me->start_busy(2);
        return 1;
    }
    message_vision("機器音﹕"HIG"報告，子彈已經用完。\n"NOR, me, ob);
    me->start_busy(1);
    return 1;
}
int do_fire(object ob)
{
    object me;
    int damage;

    me = this_player();

    message_vision("$N半蹲著說道﹕"HIG"火箭炮模式。\n"NOR, me, ob);
    if( j < 5) {
        message_vision("$N手中武器改裝成"HIR"火箭炮"NOR"的樣子，「轟！」地一聲發射！\n", me, ob);
        j = j+1;
        damage = 500;
        if( random(ob->query_ability("defend")) < random(501)) {
            ob->damage_stat("hp", damage, ob);
            message_vision("        「轟隆」火雲竄起，焦黑如炭的$n就躺在火雲正下方。("+damage+")"+report_status(ob)+"", me, ob);
            me->start_busy(2);
            ob->start_busy(1);
            return 1;
        }
        message_vision("        「轟隆」火雲竄起，$n除了身上有點焦黑並無大礙。(0)"+report_status(ob)+"", me, ob);
        me->start_busy(4);
        return 1;
    }
    message_vision("機器音﹕"HIG"報告，飛彈已經用完。\n"NOR, me, ob);
    me->start_busy(2);
    return 1;
}
int do_attack(object ob)
{
    string msg;
    object me;
    int damage;

    me = this_player();

    message_vision("$N說道﹕"HIG"機關槍模式。\n"NOR, me);
    if( k > 200) {
        k = 200;
    }
    if( k < 200) {
        message_vision("$N手中武器改裝成"HIB"機關槍"NOR"「答.答.答..！」連續射擊！\n", me);
        if((80 - random(ob->query_ability("wittiness"))) < 0) {
            k = k + 5;
            message_vision("但是$n似乎沒有受傷。(0)"+report_status(ob)+"", me, ob);
            me->start_busy(1);
            if( random(5) < 2) {
                message_vision(CYN"$N見狀立刻停止射擊！\n"NOR, me, ob);
                return 1;
            }
        } else {
            damage = 10 + random(51);
            msg = atk_msg[random(sizeof(atk_msg))];
            ob->damage_stat("hp", damage, ob);
            k = k + 5;
            message_vision("$n被強勁的子彈貫穿"+msg+"！("+damage+")"+report_status(ob)+"", me, ob);
        }
        if((80 - random(ob->query_ability("wittiness"))) < 0) {
            k = k + 5;
            message_vision("但是$n似乎沒有受傷。(0)"+report_status(ob)+"", me, ob);
            me->start_busy(1);
            if( random(5) < 2) {
                message_vision(CYN"$N見狀立刻停止射擊！\n"NOR, me, ob);
                return 1;
            }
        } else {
            damage = 10 + random(51);
            msg = atk_msg[random(sizeof(atk_msg))];
            ob->damage_stat("hp", damage, ob);
            k = k + 5;
            message_vision("$n被強勁的子彈貫穿"+msg+"！("+damage+")"+report_status(ob)+"", me, ob);
        }
        if((80 - random(ob->query_ability("wittiness"))) < 0) {
            k = k + 5;
            message_vision("但是$n似乎沒有受傷。(0)"+report_status(ob)+"", me, ob);
            me->start_busy(1);
            if( random(5) < 2) {
                message_vision(CYN"$N見狀立刻停止射擊！\n"NOR, me, ob);
                return 1;
            }
        } else {
            damage = 10 + random(51);
            msg = atk_msg[random(sizeof(atk_msg))];
            ob->damage_stat("hp", damage, ob);
            k = k + 5;
            message_vision("$n被強勁的子彈貫穿"+msg+"！("+damage+")"+report_status(ob)+"", me, ob);
        }
        if((80 - random(ob->query_ability("wittiness"))) < 0) {
            k = k + 5;
            message_vision("但是$n似乎沒有受傷。(0)"+report_status(ob)+"", me, ob);
            me->start_busy(1);
            if( random(5) < 2) {
                message_vision(CYN"$N見狀立刻停止射擊！\n"NOR, me, ob);
                return 1;
            }
        } else {
            damage = 10 + random(51);
            msg = atk_msg[random(sizeof(atk_msg))];
            ob->damage_stat("hp", damage, ob);
            k = k + 5;
            message_vision("$n被強勁的子彈貫穿"+msg+"！("+damage+")"+report_status(ob)+"", me, ob);
        }
        if((80 - random(ob->query_ability("wittiness"))) < 0) {
            k = k + 5;
            message_vision("但是$n似乎沒有受傷。(0)"+report_status(ob)+"", me, ob);
            me->start_busy(1);
            if( random(5) < 2) {
                message_vision(CYN"$N見狀立刻停止射擊！\n"NOR, me, ob);
                return 1;
            }
        } else {
            damage = 10 + random(51);
            msg = atk_msg[random(sizeof(atk_msg))];
            ob->damage_stat("hp", damage, ob);
            k = k + 5;
            message_vision("$n被強勁的子彈貫穿"+msg+"！("+damage+")"+report_status(ob)+"", me, ob);
        }
        message_vision(CYN"$N停止了連續機槍射擊！\n"NOR, me, ob);
        return 1;
    }
    message_vision("機器音﹕"HIG"報告，機槍彈夾已經用完。\n", me);
    return 1;
}
int do_gin(object ob)
{
    object me;
    int damage;

    me = this_player();

    message_vision("$N說道﹕"HIG"精神光線。\n"NOR, me, ob);
    if( l < 10) {
        message_vision("$N武器換成雷達發射器的樣子，發射出"GRN"綠色的光束"NOR"！\n", me, ob);
        l = l+1;
        damage = 10+random(91);
        if( random(ob->query_ability("evade")) < random(301)) {
            ob->damage_stat("ap", damage, ob);
            message_vision("        「逼滋」一聲綠光射中$n頭部，$n只覺得腦中一片混亂。("+damage+")"+report_status(ob)+"", me, ob);
            ob->start_busy(2);
            return 1;
        }
        message_vision("        「啪」地一聲，綠光打在地上爆出綠色濃漿。(0)"+report_status(ob)+"", me, ob);
        me->start_busy(1);
        return 1;
    }
    message_vision("機器音﹕"HIG"報告，能源已經用盡。\n"NOR, me, ob);
    me->start_busy(2);
    return 1;
}
int do_die(object ob)
{
    string msg;
    int b;
    object me;
    int damage;

    me = this_player();
    b = ob->query_stat("hp");
    msg = atk_msg[random(sizeof(atk_msg))];

    message_vision("$N說道﹕"HIG"死光。\n"NOR, me, ob);
    if( m < 500) {
        message_vision("$N武器成為避雷針的樣子，發射出"HIK"黑色死光波"NOR"！\n", me, ob);
        if( b > 500) {
            b = 500;
        }
        m = m+b;
        if( m > 500) {
            b = m - 500;
            m = 500;
        }
        damage = b+1;
        if( random(50) > 20) {
            ob->damage_stat("hp", damage, ob);
            message_vision("        黑光擊中$n"+msg+"，$n感覺全身體力快速流失！("+damage+")"+report_status(ob)+"", me, ob);
            ob->start_busy(2);
            return 1;
        }
        message_vision("        結果黑光不受控制，完全射偏了。(0)"+report_status(ob)+"", me, ob);
        me->start_busy(1);
        return 1;
    }
    message_vision("機器音﹕"HIG"報告，能源已經用盡。\n"NOR, me, ob);
    me->start_busy(2);
    return 1;
}
