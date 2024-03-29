// write by -Acme-
/* pet.c 寵物：忍犬 */
// #pragma save_binary

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;
inherit F_SAVE;
//inherit F_AUTOLOAD;

inherit "/feature/user/autoload.c";

object owner;

//int food_maximum = 999; // 食物量上限
//int food = 0;           // 目前食物量
//int exp = 0;            // 經驗值

int query_food_maximum() { return 999; }
int query_food() { return query("food"); }
int query_exp() { return query("exp"); }
void add_food(int value) { add("food", value); }
void add_exp(int value) { add("exp", value); }

// 食物量增減
int food_gain(int fo)
{
    if( query_food() + fo > query_food_maximum() ) return 0;
    add_food(fo);
    return 1;
}

// level up
void level_up()
{
    // 依等級提升能力
    this_object()->set_attr("str", this_object()->query_level()*150/100);
    this_object()->set_attr("con", this_object()->query_level()*150/100);
    this_object()->set_attr("dex", this_object()->query_level()*150/100);
    this_object()->set_attr("int", this_object()->query_level()*150/100);
    this_object()->set_stat_maximum("ap", this_object()->query_level()*50);
    this_object()->set_stat_maximum("hp", this_object()->query_level()*50);
    this_object()->set_stat_maximum("mp", this_object()->query_level()*50);
    this_object()->set_stat_current("ap", this_object()->query_level()*50);
    this_object()->set_stat_current("hp", this_object()->query_level()*50);
    this_object()->set_stat_current("mp", this_object()->query_level()*50);
    this_object()->set_skill("combat", this_object()->query_level()*3);
    this_object()->set_skill("parry", this_object()->query_level()*3);
    this_object()->set_skill("dodge", this_object()->query_level()*3);
    this_object()->set_skill("heavy hit", this_object()->query_level()*3);
    this_object()->set_skill("savage hit", this_object()->query_level()*3);
    this_object()->set_skill("continual hit", this_object()->query_level()*3);
}

// 經驗值獲得
void exp_gain(int ex)
{
/*
    if( query_exp() >= 100000) {
        return;
    }
*/
    add_exp(ex);

    if( !objectp(owner) ) return;
    if( this_object()->query_level() >= owner->query_level() ) return;

    // 升級檢查
    if( this_object()->query_level() * this_object()->query_level() * 10 <= query_exp() ) {
        add_exp(-query_exp());
        this_object()->set_level(this_object()->query_level()+1);
        level_up();
        this_object()->save();
        tell_object(owner, HIY"你的忍犬 " + this_object()->query("name") + " 的等級提升至 " + this_object()->query_level() + " 級。\n"NOR);
    }

    return;
}

// 設定主人
int set_owner(object obj)
{
    if( !objectp(obj) ) return 0;
    owner = obj;
}

// 查詢主人
object query_owner()
{
    if( !objectp(owner) ) return 0;
    return owner;
}

// 刪除忍犬
void do_destruct()
{
    // 發現寵物召喚過多次會發生保護錯誤
    // 因為離開時沒有刪除寵物保護
    // 所以累積了過多的 guard 資訊  by mouse 2009/2/16
    this_object()->guard_ob(0);
    
    // 已經要消失的寵物就不用一直喊要消失了
//   if( query("WILL_DELETE") ) return;
    message_vision("$N一溜煙的就跑得無影無蹤了...\n", this_object());
    set("WILL_DELETE", 1);
    save_autoload();
    save();

    // 延遲讓一些動作先跑過
    do_chat( ({ (: destruct, this_object() :) }) );
    return;
}

// 寵物等級下降
void level_down()
{


    // 已經要消失的寵物就不用一直喊要消失了
    if( query("WILL_DELETE") ) return;

    // 當寵物等級降低時才會離開，不然寵物是不會死掉的
    tell_object(owner, HIR"因為你沒有妥善照顧自己的寵物，使得牠的等級降低了。\n"NOR);

    // 原本就是經驗不夠扣才掉級，所以exp應當歸0
    add_exp(-query_exp());

    // 有可能是因食物不足死亡，必免狂死所以死掉後食物會自動增加一點
    add_food(20);

    // 當等級小於或等於一級時就不會再降級了
    if( this_object()->query_level() > 1 ) {
        this_object()->set_level(this_object()->query_level() - 1);
        level_up();
    }

    do_destruct();
    return;
}

// 判斷應該昏倒還是降級
void check_lv()
{
    int lv = this_object()->query_level();

    // 被連打不用一直叫
    if( query("no_say_again") ) return;

    set("no_say_again", 1);
    message_vision("$N慘叫「該∼∼該∼∼」後倒了下來...\n", this_object());
    if( userp(owner) && owner->query_skill("animal taming") < 180 ) {
        if( query_exp() >= lv*10 ) {
            add_exp(-lv*10);
            tell_object(owner, HIY"寵物的經驗值下降了。\n"NOR);
            do_destruct();
        } else {
            level_down();
        }
        return;
    }
    do_destruct();
    return;
}

void unconcious()
{
    die();
    return;
}

// 寵物判斷改變，如果沒有好好照顧寵物，等級可能會下降
void die()
{
    check_lv();
    return;
}

// 是否接受命令
int accept_order(object who, string cmd)
{
    if( owner != who ) return 0;
    // 馴獸術必需大於150級，才會受控制
    if( who->query_skill("animal taming", 1) <= 150 ) return 0;

    // 直接命令寵物打怪如果寵物暈掉會直接消失
    // 所以直接禁止玩家命令寵物打怪，主人在一旁納涼
    if( cmd == "kill" ) return 0;
    if( cmd == "fight" ) return 0;
    return 1;
}

// 給予物品判斷
int accept_object(object me, object ob)
{
    if( me != owner ) {
        tell_object(me, "只有主人才能給自己的寵物物品。\n");
        return 0;
    }
    
    if( is_busy() ) {
        tell_object(me, "寵物正常忙碌中，無法給予東西。\n");
        return 0;
    }
    
    if( is_fighting() ) {
        tell_object(me, "戰鬥中無法給予物品。\n");
        return 0;
    }
    
    if( ob->query("value") <= 0 ) {
        if( ob->query("base_value") <= 0 ) return 0;
    }

    return 1;
}

// 隨時檢查主人是否存在
void do_check_owner()
{
    // 主人消失，則忍犬也消失
    if( !objectp(owner) ) {
        do_destruct();
        return;
    }

    // 在不同位置也會消失
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), owner) ) {
            do_destruct();
            return;
        }
    } else {
        if( environment(this_object()) != environment(owner) ) {
            do_destruct();
            return;
        }
    }
    if( query("no_say_again") ) delete("no_say_again");
}

// 食物量檢查
void do_check_food()
{
    if( !objectp(this_object()) || !objectp(owner) ) return;
    if( query_food() <= 0 ) {
        // 原本餓一次只扣10，有些人根本不在意寵物是不是饑餓狀態 by mouse
        tell_object(owner, HIR"你的忍犬 "+this_object()->query("name")+" 似乎肚子餓得很...\n"NOR);
        this_object()->damage_stat("ap", this_object()->query_stat_maximum("ap")/20, this_object());    // 扣精神
        this_object()->receive_damage(this_object()->query_stat_maximum("hp")/20, this_object());       // 扣體力
        this_object()->damage_stat("mp", this_object()->query_stat_maximum("mp")/20, this_object());    // 扣查克拉
        return;
    }

    // 減少食物量
    add_food(-(random(3) + 1));
}

// 忍犬恢復狀態比較快
void do_heal_stat()
{
    if( !objectp(this_object()) ) return;
    this_object()->heal_stat("ap", this_object()->query_level());
    this_object()->heal_stat("hp", this_object()->query_level());
    this_object()->heal_stat("mp", this_object()->query_level());
}

void normal_action()
{
    do_check_owner();
    do_check_food();
    do_heal_stat();
    exp_gain(1);
}

void reset_action()
{
    // 平時動作：檢查owner還在不在
    set("chat_chance", 10);
    set("chat_msg", ({
        (: normal_action :),
    }));

    // 戰鬥時動作：檢查owner還在不在
    set("chat_chance_combat", 50);
    set("chat_msg_combat", ({
        (: normal_action :),
    }) );
}

void create()
{
    set_name("忍犬", ({ "dog", "_MY_PET_" }));
    set_race("beast");
    set("no_fight", 1);
    setup();
}

// 狗可以存檔
string query_save_file()
{
    if( owner && objectp(owner) )
        return DATA_DIR + "pet/ninja_dog/" + owner->query_id();

    else return DATA_DIR + "pet/ninja_dog/no_owner";
}
