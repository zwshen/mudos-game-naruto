#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

int num=0;

string *name1 = ({ "志貴", "琥珀", "翡翠", "瑪瑙", "琉璃", "水晶", "瑾子",
                   "諾立", "桐田", "幽山", "征玲", "天地", "白茫", "黑骨",
                   "風飯", "片瑁", "玳瑁", "紅月", "白月", "黑月", "正月",
                   "琳", "理", "御", "礫", "骸", "骨", "破", "刃", "霧",
                   "燼", "燃", "無", "卯", "巳", "酉", "戌", "亥", "丑",
                   "半兵衛", "中之介", "子午郎", "上之介", "下之介" });

string report_status(object ob)
{
    int ratio;
    if( !ob->query_stat_maximum("hp") ) return "\n";
    ratio = (int)ob->query_stat("hp")*100/(int)ob->query_stat_maximum("hp");
    if( ratio > 80 ) return HIK"["HIG"$N" + HIG + ratio + "%" + HIK"]\n"NOR;
    else if( ratio > 30 ) return HIK"["HIY"$N" + HIY + ratio + "%" + HIK"]\n"NOR;
    else return HIK"["HIR"$N" + HIR + ratio + "%" + HIK"]\n"NOR;
}
void do_check()
{
    if( num > 0) {
        set("chat_chance", 10);
        this_object()->heal_stat("hp", num);
        message_vision("$N"HIW"從地上撿起骸骨補充剛才消耗骨頭的傷害。("HIR+num+HIW")"+report_status(this_object())+""NOR, this_object());
        num = 0;
        return;
    }
    message_vision(CYN"$N檢查著四周有沒有敵人....\n"NOR, this_object());
    return;
}
void do_whip(object enemy)
{
    int damage, i;
    object* targets;
    // 沒有敵人
    set("chat_chance", 100);
    enemy = this_object()->query_opponent();
    targets = this_object()->query_enemy();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    num = num + 30;
    message_vision("$N"NOR"從身上爆出幾根骨頭使出「"HIY"柳之舞"NOR"」骨頭像鞭子般打向四方！\n"NOR, this_object(), enemy);
    for(i=0;i<sizeof(targets);i++) {
        if( i > 4) break;   // 對五個人有用
        damage = random(101)+20;
        if( random(targets[i]->query_ability("evade")) > 150) {
            message_vision("        $N狼狽的躲過了攻擊！(0)"+report_status(targets[i])+"", targets[i], this_object());
            this_object()->start_busy(1);
        } else {
            targets[i]->damage_stat("hp", damage, targets[i]);
            message_vision("        $N被骨頭掃中，身上馬上多了一道傷痕。("+damage+")"+report_status(targets[i])+"", targets[i], this_object());
        }
    }
}
void do_flower()
{
    int damage;
    object enemy;
    // 沒有敵人
    set("chat_chance", 100);
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    num = num + 50;
    message_vision("$N"NOR"手骨瞬間爆出，變成有如刺槍般的「"HIR"鐵線花之舞"NOR"」！\n"NOR, this_object(), enemy);
    damage = random(this_object()->query_ability("attack")) - random(enemy->query_ability("defend"));
    if( damage <= 0 || random(enemy->query_ability("wittiness")) > 120) {
        message_vision("        $N費了一番功夫才將此招化解！(0)"+report_status(enemy)+"", enemy, this_object());
        this_object()->start_busy(2);
        return;
    }
    enemy->damage_stat("hp", damage, enemy);
    message_vision("        「噗」地一聲在$N身上戳出一道血洞，血流不止。("+damage+")"+report_status(enemy)+"", enemy, this_object());
    enemy->start_busy(1);
    return;
}
void do_finger()
{
    int damage;
    object enemy;
    // 沒有敵人
    set("chat_chance", 100);
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    num = num + 50;
    message_vision("$N"NOR"十指放平朝著$n射出「"HIW"指骨"NOR"」！\n"NOR, this_object(), enemy);
    damage = random(31)+20;
    if( random(enemy->query_ability("evade")) > 170) {
        message_vision("        $N快速的閃過了指骨！(0)"+report_status(enemy)+"", enemy, this_object());
        this_object()->start_busy(1);
    } else {
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        $N「噗」地一聲被指骨戳出了一道傷口。("+damage+")"+report_status(enemy)+"", enemy, this_object());
    }
    damage = random(31)+20;
    if( random(enemy->query_ability("evade")) > 170) {
        message_vision("        $N快速的閃過了指骨！(0)"+report_status(enemy)+"", enemy, this_object());
        this_object()->start_busy(1);
    } else {
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        $N「噗」地一聲被指骨戳出了一道傷口。("+damage+")"+report_status(enemy)+"", enemy, this_object());
    }
    damage = random(31)+20;
    if( random(enemy->query_ability("evade")) > 170) {
       message_vision("        $N快速的閃過了指骨！(0)"+report_status(enemy)+"", enemy, this_object());
        this_object()->start_busy(1);
        return;
    } else {
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        $N「噗」地一聲被指骨戳出了一道傷口。("+damage+")"+report_status(enemy)+"", enemy, this_object());
        return;
    }
}
void do_fight()
{
    int damage;
    object enemy;
    // 沒有敵人
    set("chat_chance", 100);
    enemy = this_object()->query_opponent();
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    num = num + 200;
    message_vision("$N"NOR"身子往地下一沉，使出捨命必殺"HIY"『"HIR+BLINK"早蕨之舞"NOR+HIY"』"NOR"全身骨頭戳向四面八方！\n"NOR,this_object(), enemy);
    damage = random(this_object()->query_ability("attack"))*2 + 100;
    damage -= random(enemy->query_ability("defend"));
    if( damage <= 0 || random(enemy->query_ability("evade")) > 230) {
        message_vision("        $N率先看穿了攻擊才避開此招！(0)"+report_status(enemy)+"", enemy, this_object());
        this_object()->start_busy(2);
        return;
    }
    enemy->damage_stat("hp", damage, enemy);
    message_vision("        「噗噗」連續幾聲，$N早已被戳成蜂窩，血流如注。("+damage+")"+report_status(enemy)+"", enemy, this_object());
    return;
}
void do_clone()
{
    object enemy, item;
    // 沒有敵人
    set("chat_chance", 100);
    enemy = this_object()->query_opponent();
    item = new(__DIR__"wp/spinal.c");
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( this_object()->query_temp("quest/psychical") == 1) {
    return;
    }
    this_object()->add_temp("quest/psychical", 1);
    num = num + 300;
    message_vision("$N"HIW"背部慢慢凸起一塊白色骨頭，伸手拔出後居然是他自己的脊椎骨！\n"NOR, this_object());
    item->move(this_object());
    do_chat((: command, "wield sword" :));
    return;
}
void create()
{
    set_name("輝夜"+name1[random(sizeof(name1))], ({ "wheya ninja", "ninja" }) );
    set_level(35);
    set_class("middle");
    set_race("human");
    if( random(2) == 1) {
        set("gender", "male");
    } else {
        set("gender", "female");
    }
    set("age", 15+random(41));
    set("title",HIR"血繼限界"NOR);
    set("vendetta_mark", "wheya");  // 世仇：輝夜一族
    set("long",@LONG
輝夜一族，在很久以前的一場戰爭後，突然出現的新族群，他們大多
是戰爭過後存活下來的人，也有一些是後代子孫。他們會被人發現的
最大原因，就是他們能夠將骨頭化為利刃，在必要的時刻還能將自己
身上的骨頭拔出做為武器，因太過血腥而被世人認為是惡魔一族，直
到後來被控制音忍的大蛇丸所收留，便定居在他們隨手能拿到武器的
『骸骨戰場』幫助大蛇丸抵制旁邊的蛇人一族。
LONG);
    set("chat_chance", 10);
    set("chat_msg", ({
        (: do_check :),
        (: random_move :),
    }));
    set("chat_chance_combat", 20);
    set("chat_msg_combat", ({
        (: do_fight :),
        (: do_clone :),
        (: do_flower :),
        (: do_finger :),
        (: do_whip :),
    }) );
    set("set_drop", ({
        ([ "type":"obj", "id":29, "amount":100+random(200), "p1":60, "p2":100 ]), // 銀子
        ([ "type":"food", "id":16, "amount":1, "p1":3, "p2":100 ]),    // 大精力丸
        ([ "type":"food", "id":18, "amount":1, "p1":5, "p2":100 ]),    // 大體力丸
        ([ "type":"food", "id":20, "amount":1, "p1":3, "p2":100 ]),    // 大查克丸
        ([ "type":"obj", "id":78, "amount":1, "p1":80, "p2":100 ]),    // 輝夜之證
        ([ "type":"wp", "id":50, "amount":1, "p1":1, "p2":700 ]),      // 脊骨劍
        ([ "type":"eq", "id":85, "amount":1, "p1":1, "p2":600 ]),      // 咒印覆面
    }) );
    setup();
    add_temp("apply", (["hp":1500 ]) );
    // 有調整過 ap, hp, mp 的要 do_heal(), 才能讓狀態補滿
    do_heal();
}
void die()
{
    object ob, *obs;
    obs = all_inventory(this_object());
    if( this_object()->query_temp("quest/psychical") == 1 ) {
        message_vision("因為$N死掉所以"HIW"脊骨劍"NOR"漸漸風化了...。\n"NOR, this_object());
        this_object()->delete_temp("quest/psychical");
        foreach( ob in obs ) destruct(ob);
    }
    ::die();
}
