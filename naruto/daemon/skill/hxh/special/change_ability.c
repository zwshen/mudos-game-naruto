#include <ansi.h>
#define SKILL_NAME "change ability"
#define SKILL_NAME_C "魂體轉換"
#define SKILL_CLASS "special"

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

void do_perform_up(object me, string msg, string two)
{
    write("你感覺成功\的將魄轉換為"+msg+NOR"了！\n");
    me->set("ghost_change/"+two, 1);
    me->damage_stat("mp", 50, me);
    me->start_busy(3);
    me->improve_skill(SKILL_NAME, 1);
    return;
}

void do_perform_down(object me, string msg, string two)
{
    mapping cnd = ([]);
    int sk;

    sk = me->query_skill(SKILL_NAME, 1);

    write(HIK"你感覺腦中一陣暈眩，似乎是魄發生轉換失敗！\n"NOR);
    me->delete_condition("ghost_change1");
    me->delete_condition("ghost_change2");
    me->delete_condition("ghost_change3");
    me->delete_condition("ghost_change4");
    me->delete("ghost_change");
    cnd["name"] = HIK"(魂轉中)"NOR;
    cnd["duration"] = sk*18;
    cnd["str"] = sk/2;
    cnd["dex"] = sk/2;
    cnd["con"] = sk/2;
    cnd["int"] = sk/2;
    me->damage_stat("mp", 100, me);
    me->set_condition("ghost_change_down", cnd);
    me->start_busy(3);
    return;
}

void do_perform(object me, string two)
{
    mapping cnd = ([]);
    string msg;
    int sk, i;

    sk = me->query_skill(SKILL_NAME, 1);

    if( me->is_fighting() ) {
        write("戰鬥中轉移魂魄？你希望靈魂出竅嗎？\n");
        return;
    }
    if( me->query_skill("special", 1) < 50 || sk < 50 ) {
        write("你還無法使用這樣技能。\n");
        return;
    }
    if( me->query_stat("mp") < 100 ) {
        write("你身體狀況不佳，不能使用" + SKILL_NAME_C + "。\n");
        return;
    }
    if( me->query_condition("ghost_change_down") != 0 ) {
        write("你目前魂魄一片混亂，稍微休息一段時間再用吧。\n");
        return;
    }
    if( two == "str" && me->query("ghost_change/str") ) {
        write("你已經有魂魄在提升力量了。\n");
        return;
    }
    if( two == "dex" && me->query("ghost_change/dex") ) {
        write("你已經有魂魄在提升敏捷了。\n");
        return;
    }
    if( two == "con" && me->query("ghost_change/con") ) {
        write("你已經有魂魄在提升體質了。\n");
        return;
    }
    if( two == "int" && me->query("ghost_change/int") ) {
        write("你已經有魂魄在提升智慧了。\n");
        return;
    }
    switch( two ) {
        case "str": msg = ""HIR"力量";
                    cnd["name"] = HIR"力量提升"NOR;
                    cnd["duration"] = sk/2;
                    cnd["str"] = sk/10;
                    cnd["ability"] = "str";
                    break;
        case "dex": msg = ""HIG"敏捷";
                    cnd["name"] = HIG"敏捷提升"NOR;
                    cnd["duration"] = sk/2;
                    cnd["str"] = sk/10;
                    cnd["ability"] = "dex";
                    break;
        case "con": msg = ""HIY"體質";
                    cnd["name"] = HIY"體質提升"NOR;
                    cnd["duration"] = sk/2;
                    cnd["str"] = sk/10;
                    cnd["ability"] = "con";
                    break;
        case "int": msg = ""HIC"智慧";
                    cnd["name"] = HIC"智慧提升"NOR;
                    cnd["duration"] = sk/2;
                    cnd["str"] = sk/10;
                    cnd["ability"] = "int";
                    break;
        default: write("可以指定的項目為 str, dex, con, int。\n");
                 return;
                 break;
    }

    // 魂體轉換第一次一定成功，二三次機率由技能等級影響，第四次則固定 200 級 +15
    // 轉換成功最高能加 20 點屬性，轉換失敗會全扣 40 點
    // 失敗時等於冷卻時間，必須要 1 個小時以上，沒失敗就不用冷卻

    i = 100;

    message_vision(HIW"\n$N"HIW"靜坐冥思，將體內的七魄藉由念力任意轉換...\n"NOR, me);
    if( !me->query_condition("ghost_change1") ) {
        me->set_condition("ghost_change1", cnd);
        do_perform_up(me, msg, two);
        return;
    } else if( !me->query_condition("ghost_change2") ) {
        if( sk > 100 ) i += sk - 100;
        if( random(i) >= 50 ) {
            me->set_condition("ghost_change2", cnd);
            do_perform_up(me, msg, two);
            return;
        }
        do_perform_down(me, msg, two);
        return;
    } else if( !me->query_condition("ghost_change3") ) {
        if( sk >= 150 ) i += sk - 150;
        if( random(i) > 75 ) {
            me->set_condition("ghost_change3", cnd);
            do_perform_up(me, msg, two);
            return;
        }
        do_perform_down(me, msg, two);
        return;
    } else if( !me->query_condition("ghost_change4") ) {
        if( sk >= 200 ) i += 15;
        if( random(i) > 95 ) {
            me->set_condition("ghost_change4", cnd);
            do_perform_up(me, msg, two);
            return;
        }
        do_perform_down(me, msg, two);
        return;
    } else {
        write("你已經花了一半以上的魄提升能力，再用可能會走火入魔。\n");
        return;
    }
    message_vision("似乎發生了一些異常..請洽巫師處理。\n"NOR, me);
    return;
}

int perform_action(object me, string act, object target)
{
    string one, two;
    if( !objectp(me) ) return 0;

    if( me->is_busy() )
        return notify_fail("你現在沒有空使用" + SKILL_NAME_C + "。\n");

    if( !act || sscanf(act, "%s %s", one, two) != 2 )
        return notify_fail("指令格式﹕perform change ability.change <屬性>\n");

    if( one != "change" ) return notify_fail("目前" + SKILL_NAME_C + "只有 change 功\能。\n");

    do_perform(me, two);
    return 1;
}
