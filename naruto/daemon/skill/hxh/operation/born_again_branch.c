#include <ansi.h>
#define SKILL_NAME "born-again branch"
#define SKILL_NAME_C "樹枝重生"
#define SKILL_CLASS "operation"

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

// 復原枯枝
void do_born(object me, int sk, int two)
{
    object branch, tree;
    int i, j = 0;

    branch = present("_WITHERED_", me);

    if( !objectp(branch) ) {
        write("你身上根本沒有枯枝。\n");
        return;
    }

    if( me->query_skill("operation") < 50 || me->query_skill("blood-cell revive") < 15 ) {
        write("你的能力不足以使用這一招。\n");
        return;
    }

    if( !two ) two = 1;
    if( two > sk/20 ) {
        write("已你目前"+SKILL_NAME_C+"的程度，一次只能再生 "YEL+sk/20+NOR" 根枯枝。\n");
        return;
    }

    if( branch->query_amount() < two ) {
        write("你身上的枯枝根本不夠再生。\n");
        return;
    }

    if( me->query_stat("mp") < two*5 ) {
        write("你的魔力不足以再生你指定數量的枯枝。\n");
        return;
    }

    if( me->is_fighting() ) {
        write("戰鬥中無法分心再生枯枝。\n");
        return;
    }
    message_vision(YEL"\n$N將"NOR+branch->query("name")+YEL"擺在手心上，緩緩操縱內部經脈構成...\n"NOR, me);
    tell_object(me, "\n");

    for(i=0;i<two;i++) {
        if( random(me->query_skill("blood-cell revive")) < random(50) ) {
            tell_object(me,HIR"但是你過於急躁，使枯枝得到過多的念力而破碎！\n"NOR);
            branch->add_amount(-1);
            if( !branch->query_amount() ) destruct(branch);
        } else {
            tell_object(this_player(),HIY"樹枝漸漸獲得生命，顏色逐漸變的鮮艷，活了過來。\n"NOR);
            j++;
            branch->add_amount(-1);
            if( !branch->query_amount() ) destruct(branch);
        }
    }
    tell_object(me, "\n");
    message_vision(HIG"$N收回念力，似乎製作結束了\n\n"NOR, me);
    if( j >= 1 ) {
        tree = new(_DIR_AREA_"thorn_pine/npc/item/branch.c");
        if( !present("_BRANCH_", me) ) tree->set_amount(j);
        else tree->add_amount(j-1);
        if( !tree->move(me) ) {
            if( environment(me)->is_area() ) move_side(tree, me);
            else tree->move(environment(me));
            tell_object(me,HIY"(你身上太重，樹枝因此掉在地上。)\n"NOR);
        }
    }
    me->damage_stat("mp", two*5, me);
    me->start_busy(2);
    return;
}

// 種植小樹
void do_crop(object me, int sk)
{
    object branch, tree;

    tree = new(__DIR__"obj/tree_obj.c");
    branch = present("_BRANCH_", me);

    if( me->query_skill("operation") < 60 ) {
        write("你的能力不足以使用這一招。\n");
        return;
    }
    if( me->query_stat("mp") < sk/10 ) {
        write("你的狀態無法使用"+SKILL_NAME_C+"。\n");
        return;
    }
    if( objectp(me->query_temp("TREE_ONE")) ) {
        write("你已經在種植樹了。\n");
        return;
    }
    if( objectp(me->query_temp("TREE_TWO")) ) {
        write("你已經在操縱一位樹人了。\n");
        return;
    }
    if( me->is_fighting() ) {
        write("戰鬥中還植樹！敵人可沒那麼好心等你！\n");
        return;
    }
    // 偵測身上有沒有樹枝
    if( !objectp(branch) ) {
        write("你身上沒有樹枝要拿什麼去種。\n");
        return;
    }

    message_vision("\n$N將"+branch->query("name")+"丟在地上，並操縱"+branch->query("name")+"緩緩長入地面。\n\n"NOR, me);
    if( !objectp(tree) ) {
        write("因為不明原因你種植失敗了...\n");
        destruct(tree);
        return;
    }
    if( environment(me)->is_area() ) {
        if( !area_move(environment(me), tree, me->query("area_info/x_axis"), me->query("area_info/y_axis")) ) {
            write("你所種植的樹忽然快速枯\萎了...\n");
            destruct(tree);
            return;
        }
    } else {
        if( !tree->move(environment(me)) ) {
            write("你所種植的樹忽然快速枯\萎了...\n");
            destruct(tree);
            return;
        }
    }
    // 個數減少
    branch->add_amount(-1);
    if( !branch->query_amount() ) destruct(branch);

    me->set_temp("TREE_ONE", tree);
    tree->set_owner(me);                      // 設定owner

    // 增加技能經驗
    me->damage_stat("mp", sk/10, me);
    me->improve_skill(SKILL_NAME, 1);
    me->start_busy(3);
    return;
}

// 灌溉成樹人
void do_arise(object me, int sk)
{
    int lv, hair;
    object water, ob;

    ob = present("_TREE_", environment(me));

    if( me->query_skill("blood-cell revive") < 40 || sk < 30 ) {
        write("你的能力不足以使用這一招。\n");
        return;
    }
    if( me->query_stat("mp") < sk/5 ) {
        write("你的狀態無法使用"+SKILL_NAME_C+"。\n");
        return;
    }
    if( objectp(me->query_temp("TREE_TWO")) ) {
        write("你已經在操縱一位樹人了。\n");
        return;
    }
    if( me->is_fighting() ) {
        write("戰鬥中是無法分心去灌溉的。\n");
        return;
    }
    if( !ob ) {
        write("這裡又沒有樹能讓你灌溉。\n");
        return;
    }

    // 技能影響樹人的強度
    // 與馴獸術同步，改為最滿是60級
    lv = (me->query_skill(SKILL_NAME)/10)*3;

    // 依等級提升能力
    // 樹本身不會攻擊，只有自爆的威力，所以屬性略高
    ob->set("no_fight", 0);
    ob->set_level(lv);
    ob->set_attr("str", lv*2);
    ob->set_attr("con", lv*2);
    ob->set_attr("dex", lv*2);
    ob->set_attr("int", lv*2);
    ob->set_stat_maximum("ap", lv*50);
    ob->set_stat_maximum("mp", lv*50);
    ob->set_stat_current("ap", lv*50);
    ob->set_stat_current("mp", lv*50);
    ob->set_skill("parry", lv*3);
    ob->set_skill("dodge", lv*3);

    // 減少一些些攻防技巧
    ob->add_temp("apply/intimidate", -50);
    ob->add_temp("apply/wittiness", -50);

    // 樹人是不會攻擊的
    ob->set("no_combat", 1);

    // 偵測是用哪種樹液
    if( objectp(water = present("_HIY_WATER_", me)) ) {
        message_vision("$N拿起"+water->query("name")+"灑向地面後運用念力灌溉"+ob->query("name")+"...\n\n"NOR, me);
        ob->set_name(HIY"黃金樹人"NOR, ({ me->query_id() + "'s golden veggie", "veggie", "_VEGGIE_"+me->query_id() }));
        ob->set("long", "一棵壯碩的大樹，上面長滿了金光閃閃的黃金樹葉。\n");
        ob->set_stat_maximum("hp", lv*100);
        ob->set_stat_current("hp", lv*100);
    } else if( objectp(water = present("_HIR_WATER_", me)) ) {
        message_vision("$N拿起"+water->query("name")+"灑向地面後運用念力灌溉"+ob->query("name")+"...\n\n"NOR, me);
        ob->set_name(HIR"血紅樹人"NOR, ({ me->query_id() + "'s blood veggie", "veggie", "_VEGGIE_"+me->query_id() }));
        ob->set("long", "一棵壯碩的大樹，葉片在陽光照射下好像紅色鮮血。\n");
        ob->set_stat_maximum("hp", lv*90);
        ob->set_stat_current("hp", lv*90);
    } else if( objectp(water = present("_HIM_WATER_", me)) ) {
        message_vision("$N拿起"+water->query("name")+"灑向地面後運用念力灌溉"+ob->query("name")+"...\n\n"NOR, me);
        ob->set_name(HIM"櫻花樹人"NOR, ({ me->query_id() + "'s sakura veggie", "veggie", "_VEGGIE_"+me->query_id() }));
        ob->set("long", "一棵壯碩的大樹，就像櫻花樹般不斷地飄落粉紅色的花瓣。\n");
        ob->set_stat_maximum("hp", lv*70);
        ob->set_stat_current("hp", lv*70);
    } else if( objectp(water = present("_HIG_WATER_", me)) ) {
        message_vision("$N拿起"+water->query("name")+"灑向地面後運用念力灌溉"+ob->query("name")+"...\n\n"NOR, me);
        ob->set_name(HIG"常綠樹人"NOR, ({ me->query_id() + "'s green veggie", "veggie", "_VEGGIE_"+me->query_id() }));
        ob->set("long", "一棵壯碩的大樹，翠綠的顏色證明了它的生機。\n");
        ob->set_stat_maximum("hp", lv*50);
        ob->set_stat_current("hp", lv*50);
    } else {
        write("你身上沒有樹液不能灌溉小樹。\n");
        return;
    }
    water->add_amount(-1);
    if( !water->query_amount() ) destruct(water);

    if( me->query_skill("hair order") > 19 ) {
        hair = me->query_skill("hair order") - (random(20) + 1);
        ob->set_skill("hair order", hair);
    }

    // 樹給他多一點防禦能力
    // 不能攻擊所以將攻擊力補足防禦
    // 不過為了不影響自爆的威力，所以攻擊力不拿掉
    ob->add_temp("apply/armor", ob->query_ability("attack"));

    ob->set_leader(me);                     // 跟隨leader
    ob->set_owner(me);                      // 設定owner
    ob->set("change",1);                    // 更換

    me->start_busy(5);
    me->improve_skill(SKILL_NAME, 1);
    me->set_temp("TREE_TWO", ob);
    me->damage_stat("mp", sk/5, me);

    ob->guard_ob(me);                       // 保護leader
    return;
}

// 取得傷害
int getDamage(object me, object target, int sk, object ob)
{
    int damage, raiseDamage;
    object wp;

    if( sk < 80 ) raiseDamage = ob->query_stat_maximum("hp")/10;
    if( sk < 140 ) raiseDamage = ob->query_stat_maximum("hp")/9;
    if( sk < 200 ) raiseDamage = ob->query_stat_maximum("hp")/8;
    else raiseDamage = ob->query_stat_maximum("hp")/6;

    raiseDamage += sk + me->query_skill("operation");
    if( raiseDamage >= 2000 ) raiseDamage = 2000;

    me->add_temp("apply/attack", raiseDamage);

    if( wp = me->query_temp("weapon/twohanded") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/righthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else if( wp = me->query_temp("weapon/lefthand") ) damage = COMBAT_D->isDamage(me, target, wp);
    else damage = COMBAT_D->isDamage(me, target, 0);

    me->add_temp("apply/attack", -raiseDamage);

    return damage;
}

// 樹人自爆
int GameOver(object me, object target, int sk, string act)
{
    object ob;
    int damage;

    ob = present("_VEGGIE_"+me->query_id(), environment(me));

    if( !objectp(me) || !objectp(target) ) {
        tell_object(me, "你必須指定一個目標自爆。\n");
        return 0;
    }

    if( !ob ) {
        tell_object(me, "你根本就沒有樹人可以控制。\n");
        return 0;
    }

    if( !me->is_fighting(target) ) {
        tell_object(me, "沒有在戰鬥還炸什麼人。\n");
        return 0;
    }

    if( ob->query("WILL_DIE") == 1 ) {
        tell_object(me, "樹人已經快要死去了。\n");
        return 0;
    }

    message_vision("$N向後一躍運用念力操縱"+ob->query("name")+"的行動，只見"+ob->query("name")+"立刻轉頭衝向$n！\n\n"NOR, me, target);

    damage = getDamage(me, target, sk, ob);

    target->receive_damage(damage, me);
    message_vision( ob->query("name")+HIW"七手八腳的把"NOR"$n"HIW"纏住，身體的中心開始發出"HIR+BLINK"紅色光芒"NOR+HIW"！\n"NOR, me, target);
    message_vision( sprintf("「三」「二」「一」轟隆巨響將$n炸的四分五裂(%d) %s\n\n", damage, COMBAT_D->report_status(target)), me, target);

    // 扣除mp, 增加技能經驗
    me->improve_skill(SKILL_NAME, 1);
    me->delete_temp("TREE_ONE");
    me->delete_temp("TREE_TWO");
    ob->set("WILL_DIE", 1);
    ob->do_destruct();
    return 1;
}

int perform_action(object me, string act, object target)
{
    int sk, two;
    string one;

    sk = me->query_skill(SKILL_NAME, 1);

    if( !objectp(me) ) return 0;
    if( me->is_busy() ) return notify_fail("你現在沒有空使用"+SKILL_NAME_C+"。\n");

    if( !act || sscanf(act, "%s %d", one, two) != 2 ) {
        if( !act || sscanf(act, "%s", one) != 1 ) {
            tell_object(me, "目前"+SKILL_NAME_C+"有 born, crop, arise, over 四種功\能。\n");
            return 1;
        }
    }
    switch( one ) {
        case "born": do_born(me, sk, two); break;
        case "crop": do_crop(me, sk); break;
        case "arise": do_arise(me, sk); break;
        case "over": GameOver(me, target, sk, act); break;
        default: return notify_fail("目前"+SKILL_NAME_C+"有 born, crop, arise, over 四種功\能。\n"); break;
    }
    return 1;
}