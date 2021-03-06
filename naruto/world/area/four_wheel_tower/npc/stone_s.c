#include <npc.h>
#include <ansi.h>

void do_startDamage()
{
    int i, j, size;
    object room, area;
    object *inv;
    string file, msg, *pattern;

    file = base_name(environment(this_object())) + ".c";
    pattern = AREA_PATTERN_D->getPatterns();
    room = load_object(file);

    inv = all_inventory(room);
    size = sizeof(inv);

    if( !query("change_map") ) return;

    // 準確的判斷 pattern 為哪個編號
    for(j=0;j<sizeof(pattern);j++) {
        if( pattern[j] == "/world/area_pattern/mist900_s_02.c" ) break;
    }
    for(i=0; i<size; i++) {
        if( !userp(inv[i]) ) continue;

        // 如果在不會改變的位置定點掛，偶爾移動一下躲，會避過問答區
        // 所以把點設為同一位置，不管在哪個不改變點都一樣 +1
        if( (inv[i]->query("area_info/x_axis") >= 14 && inv[i]->query("area_info/x_axis") <= 16) 
            && (inv[i]->query("area_info/y_axis") >= 14 && inv[i]->query("area_info/y_axis") <= 18) ) {

            msg = environment(this_object())->query("name")+"x15y15";
        } else {
            msg = environment(this_object())->query("name")+"x"+inv[i]->query("area_info/x_axis")+"y"+inv[i]->query("area_info/y_axis");
        }

        AREA_PATTERN_D->setPattern(this_object(), j);

        // 判斷玩家是否定點掛機...
        // 當石頭換地形時會給玩家一個 temp 偵測位置
        // 三次都在同一個位置就傳回 recall
        if( inv[i]->query_temp("tower_recall/"+msg) ) {
            inv[i]->add_temp("tower_recall/"+msg, 1);
            if( inv[i]->query_temp("tower_recall/"+msg) >= 3 ) {
                if( inv[i]->is_busy() ) {
                    inv[i]->interrupt(inv[i], "*unconcious");
                    inv[i]->clear_condition();
                }
                if( !inv[i]->move("/world/area/wizard/guildhall.c") ) {
                    inv[i]->start_busy(1);
                } else {
                    message_vision(HIW"一陣白光過去，$N「唉喲∼」一聲，突然從天空中掉了下了，跌了個狗吃屎。\n"NOR, inv[i]);
                    inv[i]->delete_temp("tower_recall");
                    inv[i]->set_stat_current("ap", 1);
                    inv[i]->set_stat_current("hp", 1);
                    inv[i]->set_stat_current("mp", 1);
                }
            }
        } else {
            inv[i]->delete_temp("tower_recall");
            inv[i]->set_temp("tower_recall/"+msg, 1);
        }
        message_vision("$N"HIY"一陣搖晃後放出大量黃光！四周景色逐漸變化...\n"NOR, this_object());
        return;
    }
    delete("change_map");
    return;
}

void create()
{
    set_name(HIW"鎮沙石"NOR, ({ "stone", "sand" }) );
    set("channel_id", HIW"鎮沙石"NOR);
    set_level(1);
    set_race("human");
    set("age", 1);
    set("long", "白色的巨大石頭，好像對這片環境的沙化完全不受影響，不動如山。\n"
                "偶爾還會發出黃色的閃光，但是石頭表面卻仍然保持白色。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        (: do_startDamage :),
    }));
    setup();
}

// 判斷玩家是否出現
void init()
{
    if( query("change_map") ) return;

    if( userp(this_player()) ) set("change_map", 1);
    else return;
}

// 不能fight
int accept_fight(object me, string arg)
{
    return 0;
}

// 不能 kill
int accept_kill(object me, string arg)
{
    remove_all_killer();
    me->remove_killer(this_object());
    return 1;
}
