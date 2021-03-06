/* alter_ego.c 忍術：分身術 
   增加影分身術部份 by mouse 2007/8/12
   修改經驗獲得部份 by mouse 2008/4/26
*/

#include <ansi.h>
#define SKILL_NAME "alter ego"
#define SKILL_NAME_C "分身術"
#define SKILL_CLASS "ninja"
#define SHADOW_NUM 5

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

// 攻擊技巧影響
int intimidate(object me, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)*3/40;
}

// 迴避能力影響
int evade(object me, object target, int ability, int type)
{
    return ability + me->query_skill(SKILL_NAME)/20;
}

// 創造分身函式
void construct_shadow(object me)
{
    int i, count, sk, sha;
    object shadow;
    mapping map;

    sk = me->query_skill(SKILL_NAME, 1);
    sha = me->query_skill("shadow", 1);

    if( sk < 40 || me->query_skill("ninja") < 20 ) {
        write("你的能力不足，不能使用"+SKILL_NAME_C+"。\n");
        return;
    }

    if( me->query_stat("mp") < 20 ) {
        write("你目前沒有足夠的查克拉來使用" + SKILL_NAME_C + "。\n");
        return;
    }
    map = me->query_temp("shadow");
    count = sizeof(map);

    // 尋找可用編號 count
    if( count ) {
        count = 0;
        for(i=0;i<SHADOW_NUM;i++)
            if( objectp(map["shadow"+i]) ) count++;
    }

    if( count >= SHADOW_NUM || count >= sk/40 ) {
        write("你的分身數量已經夠多了，無法再創造多餘的分身。\n");
        return;
    }
    
    shadow = new(__DIR__"obj/shadow.c");
    if( !objectp(shadow) ) {
        write("你似乎無法創造分身...\n");
        destruct(shadow);
        return;
    }
    shadow->set("number", "shadow/shadow"+count);

    if( sha > 39 && sk > 99 && count < sha/60 ) {

        // 影分身的查克拉限制在這裡判斷
        if( me->query_stat("mp") < 50 ) {
            write("你沒有足夠的查克拉使用影分身術。\n");
            return;
        }
        message_vision("$N雙手飛快地結印，將查克拉分散到四周，施展了"HIB"影分身"HIW"之術"NOR"！！\n", me);
        me->damage_stat("mp", 50, me);
        me->start_busy(3);
    } else {
        message_vision("$N雙手快速的結印，施展了"HIW+ SKILL_NAME_C +NOR"！！\n", me);
        me->damage_stat("mp", 20, me);
        me->start_busy(3);
    }
    if( environment(me)->is_area() ) {
        if( !area_move(environment(me), shadow, me->query("area_info/x_axis"), me->query("area_info/y_axis")) ) {
            write("你的分身出來後，又消失不見了...\n");
            destruct(shadow);
            return;
        }
    } else {
        if( !shadow->move(environment(me)) ) {
            write("你的分身出來後，又消失不見了...\n");
            destruct(shadow);
            return;
        }
    }
    // 設定名稱, ID
    if( sha > 39 && sk > 99 && count < sha/60 ) shadow->set_name(HIB"[影]"NOR+me->query("name"), ({ me->query_id() + "'s shadow",  "shadow" }));
    else shadow->set_name(HIW"[分]"NOR+me->query("name"), ({ me->query_id() + "'s alter ego",  "ego" }));
    shadow->set("nickname", me->query("nickname"));
    shadow->set("title", me->query("title"));

    // 相同等級
    shadow->set("level", me->query_level());

    // 相同屬性
    shadow->set_attr("str", me->query_attr("str"));
    shadow->set_attr("con", me->query_attr("con"));
    shadow->set_attr("int", me->query_attr("int"));
    shadow->set_attr("dex", me->query_attr("dex"));

    // 相同狀態
    shadow->set_stat_current("ap", me->query_stat_maximum("ap"));
    shadow->set_stat_maximum("ap", me->query_stat_maximum("ap"));
    shadow->set_stat_current("hp", me->query_stat_maximum("hp"));
    shadow->set_stat_maximum("hp", me->query_stat_maximum("hp"));
    shadow->set_stat_current("mp", me->query_stat_maximum("mp"));
    shadow->set_stat_maximum("mp", me->query_stat_maximum("mp"));

    // 分兩段判斷，中間可以共用就不用多寫了
    if( sha > 39 && sk > 99 && count < sha/60 ) {
        // 判斷玩家設定的影分身是什麼類型的
        switch( me->query_temp("SHADOW_TEMP") ) {
            // 平均型
            case 0: shadow->set("no_evade", 1);

                    shadow->set("apply/attack", me->query_ability("attack")/2);
                    shadow->set("apply/armor", me->query_ability("defend")/2);

                    shadow->set_skill("parry", me->query_skill("parry"));
                    shadow->set_skill("combat", me->query_skill("combat"));
                    break;
            // 防禦型
            case 1: shadow->set("no_combat", 1);

                    shadow->set("apply/armor", me->query_ability("defend")/2);
                    shadow->set("apply/evade", me->query_ability("evade")/2);

                    shadow->set_skill("parry", me->query_skill("parry"));
                    shadow->set_skill("dodge", me->query_skill("dodge"));
                    break;
            // 攻擊型
            case 2: shadow->set("no_defend", 1);
                    shadow->set("no_evade", 1);

                    // 攻擊型的給予戰鬥動作，戰鬥指令寫在分身裡
                    shadow->set("chat_chance_combat", 10);
                    shadow->set("apply/attack", me->query_ability("attack"));
                    shadow->set("apply/exact", me->query_ability("exact"));

                    // sk 也要設定
                    shadow->set_skill("combat", me->query_skill("combat"));
                    shadow->set_skill("continual hit", me->query_skill("continual hit"));
                    shadow->set_skill("savage hit", me->query_skill("savage hit"));
                    shadow->set_skill("heavy hit", me->query_skill("heavy hit"));
                    if( me->query_skill("thousand year kill") > 49 ) {
                        shadow->set_skill("thousand year kill", me->query_skill("thousand year kill"));
                        shadow->set_skill("force", me->query_skill("force"));
                    }
                    break;
        }
        shadow->set_skill("heavy hit", me->query_skill("heavy hit"));
        if( sha >= 200 ) {
            shadow->set_skill("substitute", me->query_skill("substitute")/2);
            shadow->map_skill("dodge", "substitute");
        }
        // 使用影分身增加影分身的經驗
        me->improve_skill("shadow", 1);
    } else {
        // 戰鬥設定
        shadow->set("no_combat", 1);      // 不能攻擊
        shadow->set("no_defend", 1);      // 不能防禦
        shadow->set("no_evade", 1);       // 不能迴避
        me->improve_skill(SKILL_NAME, 1); // 增加技能經驗
    }
    shadow->set("skill", SKILL_NAME);  // shadow是由alter ego技能叫出
    me->set_temp("shadow/shadow"+count, shadow);

    shadow->guard_ob(me);       //保護leader
    shadow->set_leader(me);     //跟隨leader
    shadow->set_owner(me);      //設定owner
    return;
}

// 刪除分身函式
void destruct_shadow(object me)
{
    object shadow, *obs;
    
    if( !me->query_temp("shadow") ) {
        write("你目前沒有任何的分身存在。\n");
        return;
    }
    
    if( sizeof(obs = values(me->query_temp("shadow"))) <= 0 ) {
        write("你目前沒有任何的分身存在。\n");
        return;
    }
    foreach(shadow in obs) {
        if( objectp(shadow) ) shadow->do_destruct();
        me->delete_temp("shadow");
    }
    write("你的所有分身都消失了。\n");

    return;
}

// 使用絕招
int perform_action(object me, string act, object target)
{
    if( !objectp(me) ) return 0;
    if( me->is_busy() ) return notify_fail("你現在沒有空使用分身術。\n");

    switch( act ) {
        case "shadow": construct_shadow(me); break;
        case "destruct": destruct_shadow(me);  break;
        default: return notify_fail("目前分身有 shadow, destruct 兩種功\能。\n"); break;
    }
    return 1;
}
