/* go.c write by -Acme-
*/

#pragma optimize
// #pragma save_binary

#include <type.h>

inherit F_CLEAN_UP;

mapping default_dirs = ([
    "north":        "�_",
    "south":        "�n",
    "east":         "�F",
    "west":         "��",
    "northeast":    "�F�_",
    "northwest":    "��_",
    "southeast":    "�F�n",
    "southwest":    "��n",
    "up":           "�W",
    "down":         "�U",
    "out":          "�~",
]);

void create()
{
    /* �]�� go ���O�i��|���J��L����A�ҥH�ݭn�� euid */
    seteuid(getuid());
}

int do_area_move(object me, object env, string dir)
{
    int x, y;
    string *area_exits, dir_name, min, mout;
    object new_env, *obs;
    mapping info;

    if( me->over_encumbranced() ) {
        write("�A���t���L���A�ʼu���o�C\n");
        return 1;
    }

    if( !(info = me->query("area_info")) ) return 0;

    x = info["x_axis"];
    y = info["y_axis"];

    area_exits = env->query_exits(x, y);

    if( dir == "escape" ) {
        if( !sizeof(area_exits) ) {
            write("�A�w�g�L���i�k�F�I\n");
            return 1;
        } else dir = area_exits[random(sizeof(area_exits))];
    }

    if( member_array(dir, area_exits) == -1 ) {
        write("�o�Ӥ�V�S���X���C\n");
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
                tell_object(me, "�A�Q" + obj->name() + "�צ�F�I\n");
                me->start_busy(1);
                return 1;
            }
        }
    }

    // �ˬdarea�O�_�X�k������
    if( function_exists("valid_leave", env) && !env->valid_leave(me, dir) ) return 1;

    new_env = environment(me);

    if( undefinedp(dir_name = default_dirs[dir]) ) dir_name = dir;
    
    if( me->is_fighting() ) {
        mout = "��" + dir_name + "����Ӱk�F�C\n";
        min = "�^�^�����a�]�F�L�ӡM�Ҽ˦��ǯT�V�C\n";
    } else {
        mout = "��" + dir_name + "���}�C\n";
        min = "���F�L�ӡC\n";
    }

    // ������}�T��
    tell_area(env, x, y, me->name() + mout, ({me}));

    if( new_env->is_area() ) {
        // ��ܶi�J�T��
        tell_area(new_env, info["x_axis"], info["y_axis"], me->name() + min, ({me}) );

        // ��i�J���y�а�init()�ʧ@
        obs = new_env->query_inventory(info["x_axis"], info["y_axis"]);
        if( sizeof(obs) > 1 ) obs->init();
    } else tell_room(new_env, me->name() + min, me);

    // �����ʩʪ��]�w�k�s(�psneak)
    me->set_temp("pending", 0);

    // �O�_���H�����H
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
            write("�A�w�g�L���i�k�F�I\n");
            return 1;
        }
    }

    if( !(dest = env->query("exits/" + dir)) ) {
        write("�o�Ӥ�V�S���X���C\n");
        return 1;
    }
    
    switch( typeof(dest) ) {
        case OBJECT:
            if( !objectp(new_env = dest) ) {
                write("�o�@�Ӥ�V���X�f�����D�A�гq���Ův�B�z�C\n");
                return 1;
            }
            break;
        case STRING:
            if( !objectp(new_env = load_object(dest)) ) {
                write("�o�@�Ӥ�V���X�f�����D�A�гq���Ův�B�z�C\n");
                return 1;
            }
            break;
        case MAPPING:
            if( undefinedp(dest["filename"]) || undefinedp(dest["x_axis"]) || undefinedp(dest["y_axis"]) ) {
                write("�o�@�Ӥ�V���X�f�����D�A�гq���Ův�B�z�C\n");
                return 1;
            }
            if( !objectp(new_env = load_object(dest["filename"])) ) {
                write("�o�@�Ӥ�V���X�f�����D�A�гq���Ův�B�z�C\n");
                return 1;
            }
            break;
        case INT:
        case FLOAT:
        case ARRAY:
        default: write("�o�@�Ӥ�V���X�f�����D�A�гq���Ův�B�z�C\n"); return 1; break;
    }
    
    if( function_exists("valid_leave", env) && !env->valid_leave(me, dir) )
        return 0;

    if( undefinedp(dir_name = default_dirs[dir]) ) dir_name = dir;

    if( me->is_fighting() ) {
        int move, chance;
        object *enemy, obj;

        mout = "��" + dir_name + "����Ӱk�F�C\n";
        min = "�^�^�����a�]�F�L�ӡM�Ҽ˦��ǯT�V�C\n";

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
                tell_object(me, "�A�Q" + obj->name() + "�צ�F�I\n");
                me->start_busy(1);
                return 1;
            }
        }
    } else {
        mout = "��" + dir_name + "���}�C\n";
        min = "���F�L�ӡC\n";
    }

    message( "vision", me->name() + mout, env, me );
    if( new_env->is_area() ) {
    if( area_move(new_env, me, dest["x_axis"], dest["y_axis"]) ) {
            object *obs;
            obs = new_env->query_inventory(dest["x_axis"], dest["y_axis"]);
            tell_area(new_env, dest["x_axis"], dest["y_axis"], me->name() + min, ({me}) );
            // ��i�J���y�а�init()�ʧ@
            if( sizeof(obs) ) obs->init();
    }
    } else if( me->move(new_env) ) message( "vision", me->name() + min, new_env, me );

    // �����ʩʪ��]�w�k�s(�psneak)
    me->set_temp("pending", 0);
    all_inventory(env)->follow_me(me, dir);

    return 1;
}

int main(object me, string arg)
{
    object env;

    if( !arg ) return notify_fail("�A�n�����Ӥ�V���H\n");

    if( me->is_busy() ) {
        write("�A�{�b���b���A�@�ɤ����L�k���ʡC\n");
        return 1;
    }

    if( me->over_encumbranced() ) {
        write("�A���t���L�ʡA�ʼu���o�C\n");
        return 1;
    }

    if( !(env=environment(me)) ) {
        write("�A�{�b���̤]�h���F�C\n");
        return 1;
    }

    if( env->is_area() ) return do_area_move(me, env, arg);
    else return do_room_move(me, env, arg);
}
