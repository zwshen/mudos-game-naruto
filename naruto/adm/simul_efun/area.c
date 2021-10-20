/* area.c write by -Acme-
*/

#pragma optimize
// #pragma save_binary

// ����G�Ӫ���O�_�B�b�ۦP���ϰ�y�Ф�
int area_environment(object ob1, object ob2)
{
    if( environment(ob1) != environment(ob2) ) return 0;
    else {
        mapping info1, info2;
        if( !(info1 = ob1->query("area_info")) ) return 0;
        if( !(info2 = ob2->query("area_info")) ) return 0;
        if( info1["x_axis"] != info2["x_axis"] || info1["y_axis"] != info2["y_axis"] ) return 0;
    }
    return 1;
}

// �Nwho����Pme�P�@�檺��m
int move_side(object who, object me)
{
int env_area = 0, x, y;
object area;
mapping who_info;

    if( !objectp(who) || !objectp(me) )  return 0;
    if( !environment(me) ) return 0;
    if( !environment(me)->is_area() ) return 0;
    
    if( environment(who) && environment(who)->is_area() ) {
    who_info = who->query("area_info");
        env_area = 1;
    }
    
    // �w�g�b�P�@�Ӧ�m�F
    if( environment(me) == environment(who) &&
    me->query("area_info/x_axis") == who->query("area_info/x_axis") &&
    me->query("area_info/y_axis") == who->query("area_info/y_axis") ) return 1;
    
    area = environment(me);
    x = me->query("area_info/x_axis");
    y = me->query("area_info/y_axis");
    
    // �p�Gwho����area������
    if( !area->move_in(x, y, who) ) {
        return 0;
    }
    
    who->set("area_info/x_axis", x);
    who->set("area_info/y_axis", y);
    
    // ���\���Jarea, move() �|�۰ʱq��area�̲��X
    if( who->move(area) ) {
        who->set("area_info/x_axis_old", x);
        who->set("area_info/y_axis_old", y);
        return 1;

    } else {
        // �N���e����s��area�A�����X
        area->move_out(x, y, who);
        if( env_area ) {
            // �]�^���e�� x, y 
            who->set("area_info/x_axis", who_info["x_axis_old"]);
            who->set("area_info/y_axis", who_info["y_axis_old"]);
            if( !environment(who)->move_in(who_info["x_axis_old"], who_info["y_axis_old"]) ) {
                tell_object(who, "�]���Y�ح�]�A�A������b�ϰ첾�ʮɲ��ͤF���~...\n");
                destruct(who);
                return 0;
            }
        }
    }
    
}

int area_move(object area, object who, int x, int y)
{
    mapping info;
    int env_area = 0;

    if( !objectp(who) || !objectp(area) ) return 0;

    if( environment(who) && environment(who)->is_area() ) {
        info = who->query("area_info");
        env_area = 1;
    }

    // �w�g�b�P�@�Ӧ�m�F
    if( area == environment(who) &&
    x == who->query("area_info/x_axis") &&
    y == who->query("area_info/y_axis") ) return 1;

    // �p�Gwho move_in��s��area������
    if( !area->move_in(x, y, who) ) return 0;

    who->set("area_info/x_axis", x);
    who->set("area_info/y_axis", y);
    // ���\���Jarea, move() �|�۰ʱqarea�̲��X
    if( who->move(area) ) {
        who->set("area_info/x_axis_old", x);
        who->set("area_info/y_axis_old", y);
        return 1;
    }
    // ���Jarea���ѡA�p�G�쥻�O�barea���Ҥ��A�����A���J�@��
    else {
        // �N���e����s��area�A�����X
        area->move_out(x, y, who);
        if( env_area ) {
            // �]�^���e�� x, y 
            who->set("area_info/x_axis", info["x_axis_old"]);
            who->set("area_info/y_axis", info["y_axis_old"]);
            if( !environment(who)->move_in(info["x_axis_old"], info["y_axis_old"]) ) {
                tell_object(who, "�]���Y�ح�]�A�A������b�ϰ첾�ʮɲ��ͤF���~...\n");
                destruct(who);
                return 0;
            }
        }
    }
    return 0;
}

// �мgmudos present�禡
object present(mixed arg, object ob)
{
    if( ob->is_area() ) {
        int p=0, index;
        object *obs, t;
        mapping area_info;

        area_info = this_player()->query("area_info");
    
        if( sscanf(arg, "%s %d", arg, index) != 2 ) index = 1;

        obs = ob->query_inventory(area_info["x_axis"], area_info["y_axis"]);

        foreach(t in obs) {
            if( !objectp(t) ) continue;
            if( t->id(arg) ) {
                p += 1;
                if( p == index ) return t;
            }
        }
        return 0;
    } else return efun::present(arg, ob);
}
