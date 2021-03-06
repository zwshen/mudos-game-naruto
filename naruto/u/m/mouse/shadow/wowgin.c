#include <npc.h>
#include <ansi.h>

inherit F_BANDIT;
int i;

string *def_msg = ({
        "$n擺出全力防禦姿態，辛苦的擋住了這擊！",
        "$n雙手發麻，費了好大一番功夫才擋住。",
});
string *atk_msg = ({
        "「啪啦！」數聲，$n的骨頭不知被打斷了多少！",
        "$n兩眼翻白的倒飛了出去，似乎早已失去知覺。",
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
    if(this_object()->is_busy()) {
        message_vision("$N啐了一口說道﹕"HIG"哼！力量還沒集中，先饒了$n。\n"NOR, this_object(), enemy);
        return;
    }
    i = random(7) + 1;
    if( i == 4) {
        message_vision("$N單拳灌飽念力，打出驚天動地"HIW"「"HIR"超•"HIY"破壞拳"HIW"」\n"NOR, this_object());
        damage = this_object()->query_ability("attack")*2;
        damage += random(200);
        msg = def_msg[random(sizeof(def_msg))];
        if( (random(enemy->query_ability("evade")) + random(enemy->query_ability("attack")))/2 > 300+random(300)) {
            message_vision("        "+msg+"(0)"+report_status(enemy)+"", this_object(), enemy);
            this_object()->start_busy(6);
            return;
        }
        msg = atk_msg[random(sizeof(atk_msg))];
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        "+msg+"("+damage+")"+report_status(enemy)+"", this_object(), enemy);
        this_object()->start_busy(2);
        return;
    } else 
    if( i > 4) {
        if(enemy->is_busy()) {
            message_vision("$N吼道﹕"HIG"沒用的東西！\n"NOR, this_object(), enemy);
            return;
        }
        message_vision("$N大吼一聲！四周震耳欲聾！\n"NOR, this_object());
        if( random(enemy->query_ability("wittiness")) > 100+random(50)) {
            message_vision("        $n似乎沒有受到這吼聲的影響。"+report_status(enemy)+"", this_object(), enemy);
            this_object()->start_busy(3);
            return;
        }        
        message_vision("        $n腦中一陣暈眩，身體完全動不了！(0)"+report_status(enemy)+"", this_object(), enemy);
        enemy->start_busy(random(5)+2);
        return;
    } else {
        message_vision("$N念力集中，打出"HIW"「"HIY"破壞拳"HIW"」\n"NOR, this_object());
        damage = random(this_object()->query_ability("attack"));
        damage += random(100);
        if( (random(enemy->query_ability("evade")) + random(enemy->query_ability("attack")))/2 > 200+random(200)) {
            message_vision("        $n仗著銅身鐵骨擋下了這招！(0)"+report_status(enemy)+"", this_object(), enemy);
            this_object()->start_busy(4);
            return;
        }
        enemy->damage_stat("hp", damage, enemy);
        message_vision("        「碰！」的一聲，$n口吐鮮血倒退了幾步。("+damage+")"+report_status(enemy)+"", this_object(), enemy);
        this_object()->start_busy(1);
        return;
    }
}
void create()
{
    set_name("窩金", ({ "wowgin" }));
    set_race("human");
    set_level(60);
    set("title",HIK"幻影旅團"NOR);
    set("age",28);
    set("long", "身材魁梧，一看就知道他充滿了最強的爆發力。\n");
    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );
    setup();
}
int give_check(object ob)
{
    if( ob->id("_TEAM_PAPER_") ) return 1;           // 旅團雇請單
    else return 0;
}
int accept_object(object me, object ob)
{
    object item;
    me->start_busy(1);
    this_object()->start_busy(1);
    switch( give_check(ob) ) {
        case 1:
            if( ob->query_amount() > 1 ) {
                do_chat((: command, "say 一張就夠了！啤酒多來幾罐才是真的。" :));
                return 0;
            }
            message_vision("$N說道﹕"HIG"哼！好吧∼看在你付錢的份上！\n"NOR, this_object());
            do_chat(({ 
               (: command, "follow " + this_player()->query("id") :),
               (: command, "guard " + this_player()->query("id") :),
            }));
            break;
        default:
            do_chat((: command, "say 少給我垃圾啦！" :));
            return 0;
            break;
    }
    return 1;
}
