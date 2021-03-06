#include <npc.h>
#include <ansi.h>

inherit F_BANDIT;
int i;

string *def_msg = ({
        "$n身子微蹲，危險的避開了殺招！",
        "$n害怕的抱頭蹲下，運氣好避開了攻擊。",
});
string *atk_msg = ({
        "只見鐮刀劃過$n頭顱，一片鮮血飛濺而出。",
        "$n哀嚎了一聲，身上的傷口不停噴出大量的鮮血。",
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
void do_fight()
{
    int damage;
    object enemy;
    string msg;
    // 沒有敵人
    enemy = this_object()->query_opponent();
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
    i = random(3)+1;
    message_vision(HIW"$N右手一揮，冒出一陣濃煙。\n"NOR, this_object());
    if( i==1) {
        do_chat(({ 
            HIR"凱特手中突然冒出一把"HIK"黑色鐮刀"HIR"....\n"NOR,
            "一顆小丑的頭在鐮刀握把上大喊﹕"HIG"「我是二號！是二號！」\n"NOR,
            (: command, "say 真是糟糕...怎麼是二號呢..." :),
        }));
        this_object()->add_temp("quest/psychical", 1);
        call_out("deathsickle_1",10,this_object(),enemy);
    } else
    if( i ==2) {
        do_chat(({ 
            "凱特手中突然冒出一把"YEL"獵槍"NOR"....\n",
            "一顆小丑的頭在獵槍槍桿上大喊﹕"HIG"「我是七號！是七號！」\n"NOR,
            (: command, "say 這念技的缺點要確實使用後才會消失。" :),
        }));
        this_object()->add_temp("quest/psychical", 1);
        call_out("gunstar_1",10,this_object(),enemy);
    } else
    if( i ==3){
        do_chat(({ 
            "凱特手中突然冒出一根"HIC"小丑棒"NOR"....\n",
            "一顆小丑的頭在棒子尾端上大喊﹕"HIG"「我是三號！是三號！」\n"NOR,
            (: command, "say 只好用來拖住你的行動了！" :),
        }));
        this_object()->add_temp("quest/psychical", 1);
        call_out("clownstaff_1",10,this_object(),enemy);
    }
}
void deathsickle_1()
{
    int damage;
    object enemy;
    string msg;
    // 沒有敵人
    enemy = this_object()->query_opponent();
    this_object()->delete_temp("quest/psychical");
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy)) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    damage = this_object()->query_ability("attack")*3;
    damage -= random(100) + random(enemy->query_ability("move"));
    message_vision(HIR"$N水平舉起"HIK"黑色鐮刀"HIR"，四周一陣寂靜「"HIK"死神圓舞曲"HIR"」。\n"NOR, this_object());
    message_vision("$N手中黑色鐮刀劃出美麗的圓弧，直劈$n的人頭！\n"NOR, this_object(), enemy);
    if( random(enemy->query_ability("evade")) > 300 + random(500)) {
        msg = def_msg[random(sizeof(def_msg))];
        message_vision("        "+msg+"(0)"+report_status(enemy)+"", this_object(), enemy);
        this_object()->start_busy(4);
        return;
    } else {
        msg = atk_msg[random(sizeof(atk_msg))];
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        "+msg+"("+damage+")"+report_status(enemy)+"", this_object(), enemy);
        this_object()->start_busy(1);
    }
    return;
}
void gunstar_1()
{
    int damage;
    object enemy;
    string msg;
    // 沒有敵人
    enemy = this_object()->query_opponent();
    this_object()->delete_temp("quest/psychical");
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    damage = this_object()->query_ability("intimidate") + this_object()->query_ability("exact");
    damage -= random(enemy->query_ability("defend")) + random(enemy->query_ability("wittiness"));
    message_vision("$N拿起"YEL"獵槍"NOR"對準$n，快速的打出一發「"HIY"子彈"NOR"」。\n"NOR, this_object(), enemy);
    if( random(enemy->query_ability("defend")) > 200 + random(300)) {
        message_vision("        $n仗著強大的防禦硬是承受住攻擊！(0)"+report_status(enemy)+"", this_object(), enemy);
        this_object()->start_busy(2);
        return;
    } else {
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        $n被子彈貫穿身體，難過的抱緊身子。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
        enemy->start_busy(1);
    }
    return;
}
void clownstaff_1()
{
    int damage;
    object enemy;
    string msg;
    // 沒有敵人
    enemy = this_object()->query_opponent();
    this_object()->delete_temp("quest/psychical");
    if( !enemy ) return;
    // 敵人在不同位置
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if(enemy->is_busy()) {
        message_vision("$N說道﹕"HIG"原來已經不能動了，真是白廢功夫。\n"NOR, this_object(), enemy);
        this_object()->delete_temp("quest/psychical");
        return;
    }
    message_vision("$N拿起"HIC"小丑棒"NOR"高速旋轉著，棒內的沙子產聲陣陣念波困住$n！\n"NOR, this_object(), enemy);
    if( random(enemy->query_ability("evade")) > 200 + random(200)) {
        message_vision("        $n並沒有受到這聲音的影響！(0)"+report_status(enemy)+"", this_object(), enemy);
        this_object()->start_busy(1);
        return;
    } else {
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        $n只覺得腦中一片混亂，無法思考了。(0)"+report_status(enemy)+"", this_object(), enemy);
        enemy->start_busy(6);
    }
    return;
}
void create()
{
    set_name("凱特", ({ "kate" }));
    set_race("human");
    set_level(60);
    set("title","金的弟子");
    set("age",28);
    set("long", "帶著一頂鴨舌帽，看起來非常普通的男子，似乎在尋找著什麼東西。\n");
    set("chat_chance", 10);
    set("chat_msg", ({
        (: random_move :),
        (: command, "say 這就是鯨魚島吧，怎麼地圖好像不太對..." :),
        CYN"凱特自言自語的說﹕好像也不在這裡...\n"NOR,
    }));
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    setup();
}
