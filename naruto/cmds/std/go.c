/* go.c write by -Acme-
*/

#pragma optimize
// #pragma save_binary

#include <type.h>

inherit F_CLEAN_UP;

mapping default_dirs = ([
    "north":        "北",
    "south":        "南",
    "east":         "東",
    "west":         "西",
    "northeast":    "東北",
    "northwest":    "西北",
    "southeast":    "東南",
    "southwest":    "西南",
    "up":           "上",
    "down":         "下",
    "out":          "外",
]);

void create()
{
    /* 因為 go 指令可能會載入其他物件，所以需要有 euid */
    seteuid(getuid());
}

int do_area_move(object me, object env, string dir)
{
    int x, y;
    string *area_exits, dir_name, min, mout;
    object new_env, *obs;
    mapping info;

    if( me->over_encumbranced() ) {
        write("你的負荷過重，動彈不得。\n");
        return 1;
    }

    if( !(info = me->query("area_info")) ) return 0;

    x = info["x_axis"];
    y = info["y_axis"];

    area_exits = env->query_exits(x, y);

    if( dir == "escape" ) {
        if( !sizeof(area_exits) ) {
            write("你已經無路可逃了！\n");
            return 1;
        } else dir = area_exits[random(sizeof(area_exits))];
    }

    if( member_array(dir, area_exits) == -1 ) {
        write("這個方向沒有出路。\n");
        return 1;
    }
        
    if( undefinedp(dir_name = default_dirs[dir]) ) dir_name = dir;

    if( me->is_fighting() ) {
        int move, chance;
        object *enemy, obj;
        enemy = me->query_enemy() - ({ 0 });

        move = me->query_ability("move");
        
        foreach(obj in enemy) {
            if( userp(obj) || !living(obj) ) continue;
            if( !area_environment(obj, me) ) continue;
            if( !me->visible(obj) ) continue;
            chance = 50 - ( (obj->query_level()-me->query_level())*2 );
            if( chance < 10 ) chance = 10;
            else if( chance > 90 ) chance = 90;
            if( chance < random(100) ) {
                tell_object(me, "你被" + obj->name() + "擋住了！\n");
                me->start_busy(1);
                return 1;
            }
        }
    }

    // 檢查area是否合法的移動
    if( function_exists("valid_leave", env) && !env->valid_leave(me, dir) ) return 1;

    new_env = environment(me);

    if( undefinedp(dir_name = default_dirs[dir]) ) dir_name = dir;
    
    if( me->is_fighting() ) {
        mout = "往" + dir_name + "落荒而逃了。\n";
        min = "跌跌撞撞地跑了過來﹐模樣有些狼狽。\n";
    } else {
        mout = "往" + dir_name + "離開。\n";
        min = "走了過來。\n";
    }

    // 顯示離開訊息
    tell_area(env, x, y, me->name() + mout, ({me}));

    if( new_env->is_area() ) {
        // 顯示進入訊息
        tell_area(new_env, info["x_axis"], info["y_axis"], me->name() + min, ({me}) );

        // 對進入的座標做init()動作
        obs = new_env->query_inventory(info["x_axis"], info["y_axis"]);
        if( sizeof(obs) > 1 ) obs->init();
    } else tell_room(new_env, me->name() + min, me);

    // 讓移動性的設定歸零(如sneak)
    me->set_temp("pending", 0);

    // 是否有人物跟隨
    obs = env->query_inventory(x, y);
    obs->follow_me(me, dir);
    
    return 1;
}

int do_room_move(object me, object env, string dir)
{
    string min, mout, dir_name;
    object new_env;
    mixed dest;

    if( dir == "escape" ) {
        mapping exits = env->query("exits");
        string *dirs;
        if( mapp(exits) ) {
            dirs = keys(exits);
            dir = dirs[random(sizeof(dirs))];
        } else {
            write("你已經無路可逃了！\n");
            return 1;
        }
    }

    if( !(dest = env->query("exits/" + dir)) ) {
        write("這個方向沒有出路。\n");
        return 1;
    }
    
    switch( typeof(dest) ) {
        case OBJECT:
            if( !objectp(new_env = dest) ) {
                write("這一個方向的出口有問題，請通知巫師處理。\n");
                return 1;
            }
            break;
        case STRING:
            if( !objectp(new_env = load_object(dest)) ) {
                write("這一個方向的出口有問題，請通知巫師處理。\n");
                return 1;
            }
            break;
        case MAPPING:
            if( undefinedp(dest["filename"]) || undefinedp(dest["x_axis"]) || undefinedp(dest["y_axis"]) ) {
                write("這一個方向的出口有問題，請通知巫師處理。\n");
                return 1;
            }
            if( !objectp(new_env = load_object(dest["filename"])) ) {
                write("這一個方向的出口有問題，請通知巫師處理。\n");
                return 1;
            }
            break;
        case INT:
        case FLOAT:
        case ARRAY:
        default: write("這一個方向的出口有問題，請通知巫師處理。\n"); return 1; break;
    }
    
    if( function_exists("valid_leave", env) && !env->valid_leave(me, dir) )
        return 0;

    if( undefinedp(dir_name = default_dirs[dir]) ) dir_name = dir;

    if( me->is_fighting() ) {
        int move, chance;
        object *enemy, obj;

        mout = "往" + dir_name + "落荒而逃了。\n";
        min = "跌跌撞撞地跑了過來﹐模樣有些狼狽。\n";

        enemy = me->query_enemy() - ({ 0 });
        move = me->query_ability("move");
        
        foreach(obj in enemy) {
            if( userp(obj) || !living(obj) ) continue;
            if( environment(obj) != environment(me) ) continue;
            if( !me->visible(obj) ) continue;
            chance = 50 + (move-obj->query_ability("move"))/2;
            if( chance < 10 ) chance = 10;
            else if( chance > 90 ) chance = 90;
            if( random(60) > chance ) {
                tell_object(me, "你被" + obj->name() + "擋住了！\n");
                me->start_busy(1);
                return 1;
            }
        }
    } else {
        mout = "往" + dir_name + "離開。\n";
        min = "走了過來。\n";
    }

    message( "vision", me->name() + mout, env, me );
    if( new_env->is_area() ) {
    if( area_move(new_env, me, dest["x_axis"], dest["y_axis"]) ) {
            object *obs;
            obs = new_env->query_inventory(dest["x_axis"], dest["y_axis"]);
            tell_area(new_env, dest["x_axis"], dest["y_axis"], me->name() + min, ({me}) );
            // 對進入的座標做init()動作
            if( sizeof(obs) ) obs->init();
    }
    } else if( me->move(new_env) ) message( "vision", me->name() + min, new_env, me );

    // 讓移動性的設定歸零(如sneak)
    me->set_temp("pending", 0);
    all_inventory(env)->follow_me(me, dir);

    return 1;
}

int main(object me, string arg)
{
    object env;

    if( !arg ) return notify_fail("你要往哪個方向走？\n");

    if( me->is_busy() ) {
        write("你現在正在忙，一時之間無法移動。\n");
        return 1;
    }

    if( me->over_encumbranced() ) {
        write("你的負荷過動，動彈不得。\n");
        return 1;
    }

    if( !(env=environment(me)) ) {
        write("你現在哪裡也去不了。\n");
        return 1;
    }

    if( env->is_area() ) return do_area_move(me, env, arg);
    else return do_room_move(me, env, arg);
}
