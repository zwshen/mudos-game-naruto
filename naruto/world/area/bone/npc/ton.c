#include <npc.h>
#include <ansi.h>

int i;

void do_fight()
{
    int damage, number;
    object enemy;

    // 沒有敵人
    enemy = this_object()->query_opponent();

    if( query_temp("tonbeli_king") == 1 ) number = random(1000);
    else number = 500;

    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    switch( number ) {
        case 0..200:
            message_vision("\n$N"HIW"從懷裡拿出一堆大型垃圾不停地往"NOR"$n"HIW"的頭頂亂丟，天空被垃圾罩的一片漆黑。\n"NOR, this_object(), enemy);
            if( random(5) == 0) {
                message_vision("但是垃圾的黑影逐漸遠離了$n，愈飛愈遠不知道被丟到哪裡去了。\n\n"NOR, this_object(), enemy);
            } else {
                damage = enemy->query_ability("intimidate")*5 + random(100);
                if( damage > 1500 ) damage = 1500 + random(200);
                enemy->receive_damage(damage, this_object());
                message_vision( sprintf("大型垃圾黑影逐漸擴大，不斷從空中落下砸在$n頭上，使$n四處逃竄(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
            }
            break;
        case 201..700:
            if( i > 1 ) {
                message_vision("$N"HIG"慢慢往前走了一步！\n"NOR, this_object(), enemy);
                i = i-1;
                message_vision("$N"HIG"還距離"NOR"$n ("HIY+i+NOR") "HIG"步！\n"NOR, this_object(), enemy);
                return;
            }
            message_vision("\n$N"HIR"走到了"NOR"$n"HIR"身前，亮出了銳利的菜刀，臉上露出奇怪的微笑...\n"NOR, this_object(), enemy);
            if( random(10) >= 7) {
                message_vision("$N搔搔頭，拿起菜刀用力往空氣一戳...不知道在幹啥...\n\n"NOR, this_object(), enemy);
                i = random(7)+1;
                message_vision("$N"HIG"又往後跳離了"NOR"$n ("HIY+i+NOR") "HIG"步！\n"NOR, this_object(), enemy);
            } else {
                damage = enemy->query_stat_maximum("hp")/10 + random(50);
                enemy->receive_damage(damage, this_object());
                message_vision( sprintf("$N拿起菜刀往$n一戳，噗地一聲菜刀刺進$n胸口，不停的冒出大量鮮血(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
                i = random(10)+1;
                message_vision("$N"HIG"又往後跳離了"NOR"$n ("HIY+i+NOR") "HIG"步！\n"NOR, this_object(), enemy);
            }
            break;
        default:
            // 原本五次照別人一次..太gy了..-Acme
            // 改變一下寫法，應該會比較清楚
            if( random(50) > 1 ) enemy = this_object();
            message_vision("\n$N"HIG"搖晃著手上的燈籠，忽然手一揮將燈籠舉高，發出綠色光芒照亮$n。\n"NOR, this_object(), enemy);
            if( enemy->query_stat("hp") >= enemy->query_stat_maximum("hp") ) {
                message_vision("但似乎沒有任何事情發生，過度發光的燈籠立刻暗淡了下去。\n\n"NOR, this_object(), enemy);
            } else {
                if( userp(enemy) ) enemy->heal_stat("hp", 200);
                else enemy->heal_stat("hp", enemy->query_stat_maximum("hp")/10);
                message_vision( sprintf("綠色的光芒瞬間籠罩住$N全身，快速地治療了$N的傷勢(%d) %s\n\n", damage, COMBAT_D->report_status(enemy) ), this_object(), enemy);
                // 不能有破表的情況產生
                if( enemy->query_stat("hp") > enemy->query_stat_maximum("hp") ) enemy->set_stat_current("hp", enemy->query_stat_maximum("hp"));
            }
            break;
    }
    return;
}
void create()
{
    set_name("通倍利", ({ "tonbeli" }));
    set_race("human");
    set_level(30);
    set("nickname",HIG"菜刀怪"NOR);
    set("age", 10+random(21));
    set("long","綠色提著燈籠的小妖怪，手上拿著一把奇怪的菜刀。\n");
    if( random(2) == 1) {
        set("gender", "female");
    } else {
        set("gender", "male");
    }
    set("chat_chance", 15);
    set("chat_msg", ({
        (: random_move :),
        CYN"通倍利緩緩的走著...\n"NOR,
    }));
    set("chat_chance_combat", 30);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    set("set_drop", ({
        ([ "type":"food", "id":23, "amount":1, "p1":30, "p2":100 ]),   // 高路魚
        ([ "type":"food", "id":24, "amount":1, "p1":30, "p2":100 ]),   // 路杰魚
        ([ "type":"food", "id":27, "amount":1, "p1":30, "p2":100 ]),   // 漱魚
        ([ "type":"food", "id":26, "amount":1, "p1":30, "p2":100 ]),   // 刷魚
        ([ "type":"food", "id":25, "amount":1, "p1":30, "p2":100 ]),   // 膏魚
        ([ "type":"obj", "id":77, "amount":1, "p1":1, "p2":200 ]),     // 通倍利燈籠
        ([ "type":"wp", "id":46, "amount":1, "p1":1, "p2":450 ]),      // 菜刀
        ([ "type":"eq", "id":86, "amount":1, "p1":5, "p2":100 ]),      // 通大衣
            ([ "type":"obj", "id":89, "amount":1, "p1":1, "p2":500 ]), // 粽葉飛天掃帚
    }) );
    setup();
}
int accept_fight(object ob)
{
    do_chat((: command, "shake" :));
    return 0;
}
int accept_kill(object ob)
{
    if( query_temp("tonbeli_go") == 1 ) {
        message_vision("$N決定開始跟隨$n一起行動。\n", this_object(), this_player());
        this_object()->set_leader(this_player());
        return 0;
    }
    if( random(20) > 18) {
        set_name("通倍利王", ({ "tonbeli king", "king" }));
        set_level(40);
        set("nickname",HIY"菜刀王"NOR);
        set("age", 45);
        set("long","綠色提著燈籠的妖怪，手上拿著一把奇怪的菜刀，頭上戴著皇冠。\n");
        message_vision(HIG"「碰」的一陣煙霧竄起，"NOR"通倍利"HIG"居然變身成了"NOR"$N"HIG"！\n"NOR, this_object());
        set("chat_chance", 15);
        set("chat_msg", ({
            (: random_move :),
            CYN"通倍利王拿著燈龍照亮四周。\n"NOR,
        }));
        set("set_drop", ({
            ([ "type":"food", "id":28, "amount":1, "p1":20, "p2":100 ]),   // 鮑魚
            ([ "type":"food", "id":45, "amount":1, "p1":20, "p2":100 ]),   // 生蠔
            ([ "type":"obj", "id":77, "amount":1, "p1":5, "p2":100 ]),     // 通倍利燈籠
            ([ "type":"wp", "id":46, "amount":1, "p1":1, "p2":300 ]),      // 菜刀
            ([ "type":"eq", "id":86, "amount":1, "p1":20, "p2":100 ]),     // 通大衣
            ([ "type":"obj", "id":89, "amount":1, "p1":1, "p2":450 ]),     // 粽葉飛天掃帚
        }) );
        add_temp("apply/hp", 1100);
        add_temp("apply/ap", 1100);
        add_temp("apply/mp", 1100);
        add_temp("apply/attack", 250);
        add_temp("apply/armor", 300);
        add_temp("apply/intimidate", 150);
        add_temp("apply/wittiness", 100);
        add_temp("apply/exact", 50);
        add_temp("apply/evade", 50);
        add_temp("tonbeli_king", 1);
        do_heal();
    }
    add_temp("tonbeli_go", 1);
    message_vision("$N決定開始跟隨$n一起行動。\n", this_object(), this_player());
    this_object()->set_leader(this_player());
    i = random(10)+1;
    message_vision("$N"HIG"還距離"NOR"$n ("HIY+i+NOR") "HIG"步！\n"NOR, this_object(), this_player());
}
