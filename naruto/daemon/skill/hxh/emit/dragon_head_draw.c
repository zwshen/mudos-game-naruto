#include <ansi.h>
#define SKILL_NAME "dragon-head draw"
#define SKILL_NAME_C "龍頭戲畫"
#define SKILL_CLASS "emit"

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

// 檢查是否能使用技能
int isCast(object me, string act, object target, int sk)
{
    if( !objectp(me) ) return 0;

    if( me->is_busy() ) {
        tell_object(me, "你現在沒有空使用" + SKILL_NAME_C + "。\n");
        return 0;
    }
    if( act != "summon" ) {
        tell_object(me, "目前龍頭戲畫有 summon, advance, none 三種功\能。\n");
        return 0;
    }

    if( me->query_condition("dragon_draw_cd") ) {
        tell_object(me, "因為念龍被破壞使你精神重創，暫時還無法召喚念龍。\n");
        return 0;
    }

    if( me->query_skill("emit", 1) < 80 ) {
        tell_object(me, "你的能力不足以使用這個技能。\n");
        return 0;
    }

    if( sk < 40 ) {
        tell_object(me, "你的" + SKILL_NAME_C + "等級不夠，無法使用這個技能。\n");
        return 0;
    }

    if( me->query_stat("mp") < 50 ) {
        tell_object(me, "你需要至少 50 點的念力，才能使用" + SKILL_NAME_C + "。\n");
        return 0;
    }

    if( !me->is_fighting(target) ) {
        tell_object(me, "你必須在戰鬥中才能釋放念龍。\n");
        return 0;
    }

    if( objectp(me->query_temp("SUMMON_DRAGON")) ) {
        tell_object(me, "你已經釋放出念龍了。\n");
        return 0;
    }
    return 1;
}

void advance_dragon(object me, int a, int b, int c, int d)
{
    int sk, lv;

    if( me->query_skill(SKILL_NAME, 1) < 100 ) {
        tell_object(me, "你的能力還無法自定屬性。\n");
        return;
    }
    sk = me->query_skill("emit", 1);
    lv = (me->query_skill(SKILL_NAME, 1)/10)*3;

    if( lv < me->query_level() + 5 ) {
        lv = (lv*150/100)*4 - (lv*40/60)*4;
        if( a + b + c + d > lv ) {
            tell_object(me, "念龍等級不足，最多只能投 "+chinese_number(lv)+" 點。\n");
            return;
        }
    } else {
        lv = (me->query_level()*150/100)*4 - (me->query_level()*40/60)*4;
        if( a + b + c + d > lv ) {
            tell_object(me, "使用者等級不足，最多只能投 "+chinese_number(lv)+" 點。\n");
            return;
        }
    }

    if( a + b + c + d > sk ) {
        tell_object(me, "你目前最多只能給念龍投"+chinese_number(sk)+"點。\n");
        return;
    }

    if( lv == (me->query_skill(SKILL_NAME, 1)/10)*3 ) lv = sk;
    printf("你的念龍目前投點設定為：\n力量: %d, 體格: %d, 敏捷: %d, 智慧: %d\n最高點數 "HIR"%d"NOR" 點、剩餘點數 "HIG"%d"NOR" 點、限制投點上限 "HIY"%d"NOR" 點\n"NOR, a, b, c, d, sk, lv - (a + b + c + d), lv );
    me->set("adv_dragon/str", a);
    me->set("adv_dragon/con", b);
    me->set("adv_dragon/dex", c);
    me->set("adv_dragon/int", d);
    return;
}

void advance_delete(object me, int sk)
{
    if( sk < 100 ) {
        tell_object(me, "你的能力還無法自定屬性。\n");
        return;
    }

    write("你決定取消念龍屬性投點的設定\n");
    me->delete("adv_dragon");
    return;
}

// 裝備爪判斷
void WieldClaw(object me, object shadow)
{
    int sk;
    object wp;

    wp = new(__DIR__"obj/claw.c");
    sk = (me->query_skill(SKILL_NAME) + me->query_skill("emit")/2)/2;

    wp->setup_weapon(sk, sk+10, 100, 1);
    wp->move(shadow);
    wp->wield("twohanded");
}

// 建立念龍
void construct_shadow(object me, int sk)
{
    int lv, ntar, i;
    object shadow, wp;
    object* targets;

    targets = me->query_enemy();
    ntar = sizeof(targets);

    shadow = new(__DIR__"obj/dragon_obj.c");
    if( !objectp(shadow) ) {
        write("你似乎無法具現成功...\n");
        destruct(shadow);
        return;
    }
    message_vision("$N雙拳集中念力施展"HIY"「發」"NOR"只見從$N身上衝出的念力漸漸"HIW"幻化成龍形"NOR"...\n", me);

    if( environment(me)->is_area() ) {
        if( !area_move(environment(me), shadow, me->query("area_info/x_axis"), me->query("area_info/y_axis")) ) {
            write("但是你忽然間念力不夠集中，念龍又消失了。\n");
            destruct(shadow);
            return;
        }
    } else {
        if( !shadow->move(environment(me)) ) {
            write("但是你忽然間念力不夠集中，念龍又消失了。\n");
            destruct(shadow);
            return;
        }
    }
    // 技能影響龍的強度
    // 最高 60 級
    lv = (me->query_skill(SKILL_NAME)/10)*3;

    // 依等級提升能力
    // 以下跟忍犬一樣、龍的等級會受主人影響
    // 最高不會超過主人等級 + 5
    if( lv <= me->query_level() + 5 ) shadow->set_level(lv);
    else shadow->set_level(me->query_level() + 5);

    // 屬性可以自行投點，只有基本的屬性是固定的
    // 防止有人點數已經投過又死回 99 級還能用屬性配置的
    if( me->query("adv_dragon") && sk > 99 ) {
        shadow->set_attr("str", lv*40/60 + me->query("adv_dragon/str"));
        shadow->set_attr("con", lv*40/60 + me->query("adv_dragon/con"));
        shadow->set_attr("dex", lv*40/60 + me->query("adv_dragon/dex"));
        shadow->set_attr("int", lv*40/60 + me->query("adv_dragon/int"));
    } else {
        shadow->set_attr("str", lv*150/100);
        shadow->set_attr("con", lv*150/100);
        shadow->set_attr("dex", lv*150/100);
        shadow->set_attr("int", lv*150/100);
    }

    // 龍只能在戰鬥中使用，ap 稍微增加一些
    shadow->set_stat_maximum("ap", lv*60);
    shadow->set_stat_maximum("hp", lv*50);
    shadow->set_stat_maximum("mp", lv*50);
    shadow->set_stat_current("ap", lv*60);
    shadow->set_stat_current("hp", lv*50);
    shadow->set_stat_current("mp", lv*50);
    shadow->set_skill("combat", lv*3);
    shadow->set_skill("parry", lv*3);
    shadow->set_skill("dodge", lv*3);
    shadow->set_skill("heavy hit", lv*3);
    shadow->set_skill("savage hit", lv*3);
    shadow->set_skill("continual hit", lv*3);
    shadow->set_skill("strength", sk);
    shadow->set_skill("powerup", sk);

    // 名稱分級，部分能力也分級
    switch( sk ) {
        case 0..99:
            shadow->set_name("鐵甲念龍", ({ me->query_id() + "'s dragon", "dragon", "_DRAGON_NPC_" }));
            break;
        case 100..149:
            shadow->set_name(HIK"銅甲念龍"NOR, ({ me->query_id() + "'s dragon", "dragon", "_DRAGON_NPC_" }));
            WieldClaw(me, shadow);
            break;
        case 150..199:
            shadow->set_name(HIW"銀甲念龍"NOR, ({ me->query_id() + "'s dragon", "dragon", "_DRAGON_NPC_" }));
            shadow->add_temp("apply/intimidate", sk/8);
            WieldClaw(me, shadow);
            break;
        case 200:
            shadow->set_name(HIY"金甲念龍"NOR, ({ me->query_id() + "'s dragon", "dragon", "_DRAGON_NPC_" }));
            shadow->add_temp("apply/intimidate", sk/4);
            WieldClaw(me, shadow);
            break;
    }
    shadow->do_heal();

    shadow->set_leader(me);     // 跟隨leader
    shadow->set_owner(me);      // 設定owner

    if( ntar > 0 ) {
        for(i=0;i<ntar;i++) {
            if( i == ntar ) break;          // 輪一圈
            shadow->kill_ob(targets[i]);    // 登場後攻擊敵人
            targets[i]->kill_ob(shadow);
        }
    }
    me->set_temp("SUMMON_DRAGON", shadow);
    shadow->guard_ob(me);                   // 保護leader
}

// 技能使用後 
void setEffect(object me, int sk)
{
    me->improve_skill(SKILL_NAME, 1);
    me->damage_stat("mp", sk/4, me);
    me->start_busy(2);
}

// 使用絕招
int perform_action(object me, string act, object target)
{
    int a, b, c, d, sk;

    sk = me->query_skill(SKILL_NAME, 1);

    if( act != "none" && act != "summon" ) {
        if( sscanf(act, "%s %d %d %d %d", act, a, b, c, d) == 5 ) {
            advance_dragon(me, a, b, c, d);
            return 1;
        } else if( act == "advance" ) {
            tell_object(me, "指令格式﹕perform dragon-head draw.advance <力量> <體格> <敏捷> <智慧>\n");
            return 1;
        }
    }

    if( act == "none" ) {
        advance_delete(me, sk);
        return 1;
    }

    // 檢查是否能使用技能
    if( !isCast(me, act, target, sk) ) return 1;

    // 召喚念龍
    construct_shadow(me, sk);

    // 使用後
    setEffect(me, sk);
    return 1;
}