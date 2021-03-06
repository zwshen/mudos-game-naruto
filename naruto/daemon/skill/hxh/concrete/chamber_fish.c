/* chamber fish 密室念魚 
   具現系 rank 2 sk
   -tmr 20060604
   update by Acme 2007.03.16
   增加附加能力 by mouse 2007/7/25
*/

#include <ansi.h>
#define SKILL_NAME "chamber fish"
#define SKILL_NAME_C "密室念魚"
#define SKILL_CLASS "concrete"

inherit SKILL;

void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon(SKILL_NAME);
}

string query_class() { return SKILL_CLASS; }

void skill_advanced(object me, string skill)
{
    int lv = me->query_skill(skill, 1);
    switch( lv ) {
        case 189: me->set_skill_require(skill, 1500000); break; // 關卡3 : 189升190
        case 149: me->set_skill_require(skill, 1000000); break; // 關卡2 : 149升150
        case  99: me->set_skill_require(skill, 500000);  break; // 關卡1 :  99升100
        default:  me->set_skill_require(skill, lv*lv*5); break;
    }
}

// 防禦技巧影響
int wittiness(object me, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/40;
}

// 命中能力影響
int exact(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/10;
}

// 創造分身函式
void construct_shadow(object me)
{
    int lv, sk;
    object shadow, armor;

    sk = me->query_skill("concrete", 1);

    if( sk < 50 ) {
        write("你的能力不足以使用這個技能。\n");
        return;
    }

    if( me->query_skill(SKILL_NAME, 1) < 10 ) {
        write("你的密室念魚等級不夠，無法使用這個技能。\n");
        return;
    }

    // 擁有者消秏一些查克拉
    if( me->query_stat("mp") < 100 ) {
        write("你需要至少100點的念力，才能召換密室念魚。\n");
        return;
    }

    if( objectp(me->query_temp("CHAMBER_FISH")) ) {
        write("你已經擁有一條密室念魚了。\n");
        return;
    }

    shadow = new(__DIR__"obj/fish_obj.c");
    if( !objectp(shadow) ) {
        write("你似乎無法具現成功...\n");
        destruct(shadow);
        return;
    }

    message_vision("$N身上的念力漸漸地在四週凝聚成塊，一條密室念魚來到這個世界了！！\n", me);
    me->damage_stat("mp", 100, me);
    me->start_busy(3);

    if( environment(me)->is_area() ) {
        if( !area_move(environment(me), shadow, me->query("area_info/x_axis"), me->query("area_info/y_axis")) ) {
            write("你的密室念魚出來後，又消失不見了...\n");
            destruct(shadow);
            return;
        }
    } else {
        if( !shadow->move(environment(me)) ) {
            write("你的密室念魚出來後，又消失不見了...\n");
            destruct(shadow);
            return;
        }
    }

    shadow->set_name(me->query("name") + "的密室念魚", ({ me->query_id() + "'s chamber fish",  "fish" }));

    // 技能影響念魚的強度
    // 每5級一個等級，最滿是60級
    lv = (me->query_skill(SKILL_NAME)/10)*3;

    // 依等級提升能力
    // 以下跟忍犬一樣
    shadow->set_level(lv);
    shadow->set_attr("str", lv*150/100);
    shadow->set_attr("con", lv*150/100);
    shadow->set_attr("dex", lv*150/100);
    shadow->set_attr("int", lv*150/100);
    shadow->set_stat_maximum("ap", lv*50);
    shadow->set_stat_maximum("hp", lv*50);
    shadow->set_stat_maximum("mp", lv*50);
    shadow->set_stat_current("ap", lv*50);
    shadow->set_stat_current("hp", lv*50);
    shadow->set_stat_current("mp", lv*50);
    shadow->set_skill("combat", lv*3);
    shadow->set_skill("parry", lv*3);
    shadow->set_skill("dodge", lv*3);
    shadow->set_skill("heavy hit", lv*3);
    shadow->set_skill("savage hit", lv*3);
    shadow->set_skill("continual hit", lv*3);

    // 念魚 armor
    if( sk > 100 ) {
        armor = new(__DIR__"obj/armor.c");

        armor->set("apply_armor/armor", ([
                   "armor": sk/2,
                   "hp": sk*5,
               ]));

        armor->move(shadow);
        armor->wear();
    }
    shadow->do_heal();

    shadow->set_leader(me);     //跟隨leader
    shadow->set_owner(me);      //設定owner

    me->set_temp("CHAMBER_FISH", shadow);

    // 增加技能經驗
    me->improve_skill(SKILL_NAME, 1);

    shadow->guard_ob(me);       //保護leader
    return;
}

// 刪除分身函式
void destruct_shadow(object me)
{
    object shadow, *obs;
    
    if( !me->query_temp("CHAMBER_FISH") ) {
        write("你目前沒有任何的密室念魚。\n");
        return;
    }
    write("你具現出來的密室念魚回到牠原本的世界了。\n");
    me->query_temp("CHAMBER_FISH")->do_destruct();
    me->delete_temp("CHAMBER_FISH");
    return;
}

// 飼養念魚，讓牠長出毒牙
void feed_fish(object me)
{
    int lv, atk;
    object fish, wp;

    lv = me->query_skill(SKILL_NAME)/5;

    if( !objectp(fish=me->query_temp("CHAMBER_FISH")) ) {
        write("你目前沒有任何的密室念魚。\n");
        return;
    }
    if( me->query_stat("mp") < 100 ) {
        write("你至少需要100點的念力值，才能飼養密室念魚。\n");
        return;
    }

    if( me->query_skill(SKILL_NAME) < 100 ) {
        write("你的技能等級還不足夠。\n");
        return;
    }
    if( fish->query("feed") > 1000 ) {
        write("你的密室念魚已經不需要再飼養了。\n");
        return;
    }
    // 增加技能經驗
    me->improve_skill(SKILL_NAME, 1);

    message_vision(CYN"$N捲起褲管露出大腿，$n一口咬住$N的大腿，開始吸吮$N的念力...\n"NOR, me, fish);
    me->damage_stat("mp", 20 + random(10), me);
    me->start_busy(1);
    
    fish->add("feed", me->query_attr("con") + random(me->query_level()) );
    fish->add_temp("fish_armor", 1);

    if( fish->query("feed") < 1000 ) return;

    // 毒牙的攻擊力會受到體質影響
    atk = 140 - ( fish->query_temp("fish_armor") * 10 );
    if( atk < 40 ) atk = 40;
    wp = new(__DIR__"obj/tooth.c");

    wp->setup_weapon(atk, atk+20, 100, 1);
    wp->move(fish);
    wp->wield("righthand");
    message_vision(HIG"忽然$n劇烈地抖動，嘴裡竟然長出一排深綠色的尖牙...\n"NOR, me, fish);
    if( me->query_skill(SKILL_NAME) > 150 && random(me->query_skill(SKILL_NAME)) > me->query_skill(SKILL_NAME)*3/10 ) {
        wp = new(__DIR__"obj/tooth.c");
        wp->setup_weapon(atk, atk+20, 100, 1);
        wp->move(fish);
        wp->wield("lefthand");
        message_vision(HIG"誰知尖牙尚未長成，$n發出一陣低鳴，嘴裡又長出了另一排綠色尖牙...\n"NOR, me, fish);
    }
    fish->set("name", me->query("name") + "的"GRN"密室念魚"NOR);
}

// 查詢念魚
void show_state(object me)
{
    object fish, armor, tooth;
    string *msg, cnd, show = "";
    int i, cnd_data;
    
    if( !objectp(fish = me->query_temp("CHAMBER_FISH")) ) {
        write("你根本就沒有具現念魚。\n");
        return;
    }
    armor = present("scale armor", fish);
    tooth = present("fish tooth", fish);

    printf("[%s] 精神：%d/%d, 體力：%d/%d, 魔力：%d/%d\n"NOR,
        fish->query("name"),
        fish->query_stat_current("ap"),
        fish->query_stat_maximum("ap"),
        fish->query_stat_current("hp"),
        fish->query_stat_maximum("hp"),
        fish->query_stat_current("mp"),
        fish->query_stat_maximum("mp"), );

    write("＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝\n");

    if( armor ) {
        msg = armor->query("apply_armor/armor");
        foreach(cnd, cnd_data in msg) {
            show += cnd+":"+cnd_data+"  ";
        }
        printf("[%s]鎧甲強度：%s\n"NOR, armor->query("name"), show);
    }
    if( tooth ) printf("[%s]武器強度：%d - %d\n"NOR, tooth->query("name"), tooth->query("damage/righthand/lower"), tooth->query("damage/righthand/upper") );
    return;
}

// 使用絕招
int perform_action(object me, string act, object target)
{
    if( !objectp(me) ) return 0;
    if( me->is_busy() ) return notify_fail("你現在沒有空使用。\n");

    switch( act ) {
        case "feed": feed_fish(me); break;
        case "fish": construct_shadow(me); break;
        case "destruct": destruct_shadow(me);  break;
        case "state": show_state(me); break;
        default: return notify_fail("目前密室念魚有 fish, feed, destruct, state 四種功\能。\n"); break;
    }
    
    return 1;
}