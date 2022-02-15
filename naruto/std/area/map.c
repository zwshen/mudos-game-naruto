/* map.c write by -Acme-
   �o�̭t�d�a�Ϫ���ܡB���󪺲��ʥH�Τ@�ǳ]�w�����C
*/

// #pragma save_binary

#include <area.h>
#include <ansi.h>
#include <dbase.h>

inherit AREA_PROMPT_ICON;

// �ϰ�y�и��(�y�Ъ���B�ϼ�...)
mixed *area;

// Location Of Objects
// �Ҧ��s�b���󪺮y�Хt���@�Ӷ��X�A�H��K�ֳt�d��
string *LOO = ({});

// ����Τ@��]�w��k������ (�ϰ�Φ����X�f�A�n�ίS�O���覡�]�w)
string *set_data_resist = ({ "objects", "loaded", "loads", "area_exit" });

// ����Τ@��R����k������ (�i��O�ϰ�޲z�Ϊ����ةΨ䥦�S�O������)
string *delete_data_resist = ({ "objects", "loaded", "loads" });

varargs int do_look(object me, string arg);

////////////////////////////////////////////////////////////
// �@��]�w�B�ˬd�B�d��
////////////////////////////////////////////////////////////
// �Ǧ^������s�b���y�ж�
string *query_LOO() { return LOO; }
// �[�J�@�Ӯy�Ф����bLOO����
void add_LOO(string location) { if( member_array(location, LOO) == -1 ) LOO += ({ location }); }
// �R���@�Ӯy�Ф����bLOO����
void del_LOO(string location) { if( member_array(location, LOO) != -1 ) LOO -= ({ location }); }

// �ϥ�__DIR__���۹���|
string file_path(string dir) { 
    dir = replace_string(dir, "__DIR__", query("file_path") );
    dir = replace_string(dir, "_DIR_AREA_", _DIR_AREA_);
    dir = replace_string(dir, "_DIR_NPC_", _DIR_NPC_);
    dir = replace_string(dir, "_DIR_WP_", _DIR_WP_);
    dir = replace_string(dir, "_DIR_EQ_", _DIR_EQ_);
    dir = replace_string(dir, "_DIR_ITEM_", _DIR_ITEM_);
    dir = replace_string(dir, "_DIR_WORLD_", _DIR_WORLD_);
    return dir;
}

// �y�нd���ˬd
int check_scope(int x, int y)
{
    if( y < 0 || x < 0 || y >= sizeof(area) || x >= sizeof(area[y]) ) return 0;
    return 1;
}

// �d�߬Y�y�Ъ���T
mapping *query_info(int x, int y)
{
    if( !check_scope(x, y) ) return 0;
    return area[y][x];
}

// �d�߬Y�y�и��J������
mapping query_loaded(int x, int y)
{
    if( !check_scope(x, y) ) return ([]);
    return area[y][x]["loaded"];
}

// �d�߰ϰ줤�Y�y�Ъ�����
//mapping *query_inventory(int x, int y)
object *query_inventory(int x, int y)
{
    if( !check_scope(x, y) ) return ({});
    if( undefinedp(area[y][x]["objects"]) ) return ({});
    return area[y][x]["objects"];
}

// �]�w�ϰ쫬�X�f
int set_area_exit(int x, int y, string filename, int exit_x, int exit_y)
{
    if( !check_scope(x, y) ) return 0;
    area[y][x]["area_exit"] = ([]);
    area[y][x]["area_exit"]["filename"] = filename;
    area[y][x]["area_exit"]["x_axis"] = exit_x;
    area[y][x]["area_exit"]["y_axis"] = exit_y;
    return 1;
}

// �]�w�ϰ�Ӹ`�y�z
int set_area_detail(int x, int y, string title, string detail)
{
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["detail"]) ) area[y][x]["detail"] = ([]);
    area[y][x]["detail"][title] = detail;
    return 1;
}

// �R���ϰ�Ӹ`�y�z
int del_area_detail(int x, int y, string title)
{
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["detail"]) ) return 1;

    map_delete(area[y][x]["detail"], title);

    if( sizeof(area[y][x]["detail"]) < 1 )
        map_delete(area[y][x], "detail");
    return 1;
}

// ���o�ϰ�Ӹ`���
mapping query_area_detail(int x, int y)
{
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["detail"]) ) return ([]);
    return area[y][x]["detail"];
}

// ���o�Ydetail���y�z
string query_area_detail_arug(int x, int y, string title)
{
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["detail"]) ) return 0;
    if( undefinedp(area[y][x]["detail"][title]) ) return 0;
    return area[y][x]["detail"][title];
}

// �]�w�Y��V��guard
int set_area_guard(int x, int y, string exit, object ob)
{
    if( !check_scope(x, y) ) return 0;
    if( !objectp(ob) ) return 0;
    if( undefinedp(area[y][x]["guard"]) ) area[y][x]["guard"] = ([]);
    if( undefinedp(area[y][x]["guard"][exit]) ) area[y][x]["guard"][exit] = ({});
    area[y][x]["guard"][exit] += ({ ob });
    return 1;
}

// �d�߬Y��V�O�_�Qguard
int query_area_guard(int x, int y, string exit)
{
    int index;
    object guard;
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["guard"]) ) return 0;
    if( undefinedp(area[y][x]["guard"][exit]) ) return 0;
    if( !(index=sizeof(area[y][x]["guard"][exit])) ) return 0;
    while(index--) {
        if( objectp(guard=area[y][x]["guard"][exit][index]) )
        if( guard->query("area_info/x_axis") == x && guard->query("area_info/y_axis") == y ) 
        if( guard->do_guard_exit(x, y, exit) ) return 1;
    }
    return 0;
}

// �]�w�@����
int set_data(int x, int y, string type, mixed value)
{
    if( member_array(type, set_data_resist) != -1 ) return 0;
    if( !check_scope(x, y) ) return 0;
    area[y][x][type] = value;
    return 1;
}

// �R���@����
int delete_data(int x, int y, string type)
{
    if( member_array(type, delete_data_resist) != -1 ) return 0;
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x][type]) ) return 1;
    map_delete(area[y][x], type);
    return 1;
}

// ���o�@����
mixed query_data(int x, int y, string type)
{
    if( member_array(type, delete_data_resist) != -1 ) return 0;
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x][type]) ) return 0;
    return area[y][x][type];
}

////////////////////////////////////////////////////////////
// ����
////////////////////////////////////////////////////////////

// �ˬd�Y�y�ЬO�_����ê���A�O�_�i��z
int is_move(int x, int y)
{
    // �p�G�Ův�]�w������Ҧ�
    if( wizardp(this_player()) && this_player()->query("option/map_through") ) return 1;
    if( !check_scope(x, y) ) return 0;
    if( undefinedp(area[y][x]["block"]) ) return 1;
    if( !area[y][x]["block"] ) return 1;
    return 0;
}

// ���󲾤J�Y�y�гB�z
int move_in(int x, int y, object ob)
{
    // �W�X�ϰ�j�p�d��
    if( !check_scope(x, y) ) return 0;

    // �Ӯy�ШS������(objects)�A�h�N���󶰳]����
    if( undefinedp(area[y][x]["objects"]) ) area[y][x]["objects"] = ({});

    // �@��̦h�e��30�Ӫ���
/*
    if( sizeof(area[y][x]["objects"]) >= 30 ) {
        write("���Ӥ�V�Ӧh�F��F�C\n");
        return 0;
    }
*/
    // ����w�g�s�b����(objects)���A�N���ݭn�A�[�J����
    if( member_array( ob, area[y][x]["objects"] ) != -1 ) return 1;

    // ����[�J���󶰤�
    area[y][x]["objects"] += ({ ob });
    
    // ���ܧY�ɪ��ϥ�
    set_icon_weight(x, y, get_icon_weight(ob));

    // �W�[LOO�j�M��
    add_LOO((string)y + "," + (string)x);

    return 1;
}

// ���󲾥X�Y�y�гB�z
int move_out(int x, int y, object ob)
{
    // �W�X�ϰ�j�p�d��
    if( !check_scope(x, y) ) return 0;

    // �Ӯy�ШS������(objects)
    if( undefinedp(area[y][x]["objects"]) ) return 1;

    // ���ܧY�ɪ��ϥ�
    set_icon_weight(x, y, -get_icon_weight(ob));

    // ���󤣦s�b�󪫥�(objects)���A�N���ݭn�A���X����
    if( member_array( ob, area[y][x]["objects"] ) == -1 ) return 1;

    // ���󲾥X����
    area[y][x]["objects"] -= ({ ob });
     
    // �y�Ч����S����ɡA�R������
    if( sizeof(area[y][x]["objects"]) < 1 ) {
        map_delete(area[y][x], "objects");
        // �R��LOO�j�M��
        del_LOO((string)y + "," + (string)x);
    }

    return 1;
}

// �i�沾��
// ����O�_�X�k���b�ϰ줤����
int valid_leave(object ob, string dir)
{
    int x, y, x_past, y_past;
    x_past = ob->query("area_info/x_axis");
    y_past = ob->query("area_info/y_axis");
    
    // �y���ഫ
    switch( dir ) {
        case     "north":  y = y_past-1; x = x_past;   break;
        case      "east":  y = y_past;   x = x_past+1; break;
        case     "south":  y = y_past+1; x = x_past;   break;
        case      "west":  y = y_past;   x = x_past-1; break;
        case "northeast":  y = y_past-1; x = x_past+1; break;
        case "southeast":  y = y_past+1; x = x_past+1; break;
        case "southwest":  y = y_past+1; x = x_past-1; break;
        case "northwest":  y = y_past-1; x = x_past-1; break;
        default: return 0; break;
    }
    
    // �L�k���ʦܸӮy��(����ê��)
    if( !check_scope(x, y) || !is_move(x, y) ) {
        write("�o�Ӥ�V�S���X��");
        return 0;
    }

    // �L�k���Y��V���ʦ]���Q�Y�Hguard
    if( query_area_guard(x_past, y_past, dir) ) return 0;

    //////////////////////////////
    // �����O���ж�
    //////////////////////////////
    if( !undefinedp(area[y][x]["room_exit"]) ) {
        object room;
        if( !objectp(room = load_object(file_path(area[y][x]["room_exit"]))) ) {
            write("�o�Ӥ�V���X�f�����D�A�гq���޲z�̨ӳB�z�C\n");
            return 0;
        }
        if( room->is_area() ) {
            write("�o�Ӥ�V���X�f�����D�A�гq���޲z�̨ӳB�z�C\n");
            return 0;
        } else {
        // �p�G���\����ж�, move �|�۰ʦb���e��area�̰�move_out�ʧ@
            if( ob->move(room) ) return 1;
            else {
                write("�o�Ӥ�V���X�f�����D�A�гq���޲z�̨ӳB�z�C\n");
                return 0;
            }
        }
        return 0;
    }

    //////////////////////////////
    // �����O���ϰ�
    //////////////////////////////
    if( !undefinedp(area[y][x]["area_exit"]) ) {
        object room;
        if( !objectp(room = load_object(file_path(area[y][x]["area_exit"]["filename"]))) ) {
            write("�o�Ӥ�V���X�f�����D�A�гq���޲z�̨ӳB�z�C\n");
            return 0;
        }
        if( !room->is_area() ) {
            write("�o�Ӥ�V���X�f�����D�A�гq���޲z�̨ӳB�z�C\n");
            return 0;
        }

        if( !area_move(room, ob, area[y][x]["area_exit"]["x_axis"], area[y][x]["area_exit"]["y_axis"]) ) {
            write("�o�Ӥ�V���X�f�����D�A�гq���޲z�̨ӳB�z�C\n");
        return 0;
        }
        return 1;
    }

    //////////////////////////////
    // ���ibuild
    //////////////////////////////
    /*
    if( !undefinedp(area[y][x]["_BUILDING_FILE_"]) ) {
        object room;
        if( !objectp(room = load_object( this_object()->getBuildFolderPath() + area[y][x]["_BUILDING_FILE_"] )) ) {
            write("�o�Ӥ�V���X�f�����D�A�гq���޲z�̨ӳB�z�C\n");
            return 0;
        }
        if( room->is_area() ) {
            if( !area_move(room, ob, room->query("entryX"), room->query("entryY")) )
                write("�o�Ӥ�V���X�f�����D�A�гq���޲z�̨ӳB�z�C\n");
            return 0;
        } else {
            // �p�G���\����ж�, move �|�۰ʦb���e��area�̰�move_out�ʧ@
            if( ob->move(room) ) return 1;
            else {
                write("�o�Ӥ�V���X�f�����D�A�гq���޲z�̨ӳB�z�C\n");
                return 0;
            }
        }
        return 0;
    }
    */
    //////////////////////////////
    // �b�ϰ줤���� 
    //////////////////////////////
    // ���󲾥X�®y��
    if( move_out(x_past, y_past, ob) ) {
        // ���󲾤J�s�y��
        if( move_in(x, y, ob) ) {
            ob->set("area_info/x_axis", x);
            ob->set("area_info/y_axis", y);
            ob->set("area_info/x_axis_old", x);
            ob->set("area_info/y_axis_old", y);
        } else { 
            // ���󲾤J���ѡA�h�^��y��
            move_in(x_past, y_past, ob);
            return 0;
        }
        if( userp(ob) ) do_look(ob, 0);
    } else return 0;

    return 1;
}

////////////////////////////////////////////////////////////
// �˵��ϰ�����
////////////////////////////////////////////////////////////

// �d�߬Y���Ъ��X�f
string *query_exits(int x, int y, int option)
{
    string *exits=({});

    if( !option ) {
        // ���_�i�঳��
        if( y-1 >= 0 ) {
            if( x-1 >= 0 && is_move(x-1, y-1) ) exits += ({ "northwest" });
            if( x >= 0 && is_move(x, y-1) ) exits += ({ "north" });
            if( x+1 < sizeof(area[0]) && is_move(x+1, y-1) ) exits += ({ "northeast" });
        }

        // ���n�i�঳��
        if( y+1 < sizeof(area) ) {
            if( x-1 >= 0 && is_move(x-1, y+1) ) exits += ({ "southwest" });
            if( x >= 0 && is_move(x, y+1) ) exits += ({ "south" });
            if( x+1 < sizeof(area[0]) && is_move(x+1, y+1) ) exits += ({ "southeast" });
        }

        // ���F�i�঳��
        if( x+1 < sizeof(area[0]) && is_move(x+1, y) ) exits += ({ "east" });
    
        // ����i�঳��
        if( x-1 >= 0 && is_move(x-1, y) ) exits += ({ "west" });
    } else {
        // ���_�i�঳��
        if( y-1 >= 0 ) {
            if( x-1 >= 0 && is_move(x-1, y-1) ) exits += ({ "��_("HIK"nw"NOR")" });
            if( x >= 0 && is_move(x, y-1) ) exits += ({ "�_("HIK"n"NOR")" });
            if( x+1 < sizeof(area[0]) && is_move(x+1, y-1) ) exits += ({ "�F�_("HIK"ne"NOR")" });
        }

        // ���n�i�঳��
        if( y+1 < sizeof(area) ) {
            if( x-1 >= 0 && is_move(x-1, y+1) ) exits += ({ "��n("HIK"sw"NOR")" });
            if( x >= 0 && is_move(x, y+1) ) exits += ({ "�n("HIK"s"NOR")" });
            if( x+1 < sizeof(area[0]) && is_move(x+1, y+1) ) exits += ({ "�F�n("HIK"se"NOR")" });
        }

        // ���F�i�঳��
        if( x+1 < sizeof(area[0]) && is_move(x+1, y) ) exits += ({ "�F("HIK"e"NOR")" });
    
        // ����i�঳��
        if( x-1 >= 0 && is_move(x-1, y) ) exits += ({ "��("HIK"w"NOR")" });
    }
    return exits;
}

// �a�����
varargs string show_area(int x, int y, int type)
{
    int i, j, x_start, y_start, x_size, y_size;
    string msg;

    // �M�w��ܦa�Ϫ�Y�b�_�I, X�b�_�I
    y_size = sizeof(area);
    x_size = sizeof(area[0]);

    if( y <= 5 || y_size <= 11 ) y_start = 0;
    else if( y >= y_size-6 ) y_start = y_size-11;
    else y_start = y-5;

    if( x <= 9 || x_size <= 19 ) x_start = 0;
    else if( x >= x_size-9 ) x_start = x_size-19;
    else x_start = x-9;

    // �إߧY�ɦa��
    msg = sprintf(BBLU"��"LINE" %-21s %s (%2d,%2d) "NOR+BBLU"��\n"NOR,
            query("name") + (area[y][x]["short"] ? " - " + area[y][x]["short"] : ""),
            (area[y][x]["no_fight"] ? "�D�԰�" : "�԰���"), x, y, );
    
    for(i=y_start;i<y_size && i<y_start+11;i++) {
        msg += BBLU"�y"NOR;
        for(j=x_start;j<x_size && j<x_start+19;j++) {
            if( y == i && x == j ) msg += HIY"��"NOR;
            else if( undefinedp(area[i][j]["icon"]) && 
                    (!undefinedp(area[i][j]["room_exit"]) || !undefinedp(area[i][j]["area_exit"])) )
                        msg += HIW"�C"NOR;
            else {
                int check=1;
                if( check && (type & 2) == 2 ) {
                    // �y�Ц��]���Y���ܧ�ϥ�
                    if( !area[i][j]["nonprompt_icon"] && check_icon(j, i) ) {
                        msg += get_icon(j, i);
                        check = 0;
                    }
                }
                if( check ) {
                    if( (type & 8 ) == 8 ) {
                        if( area[i][j]["_BUILDING_"] ) {
                            if( !area[i][j]["_BUILDING_FILE_"] )
                                msg += "�C";
                            else msg += area[i][j]["icon"];
                            check = 0;
                        }
                    }
                    if( check && (type & 4 ) == 4 ) {
                        if( area[i][j]["block"] ) {
                            msg += "��";
                            check = 0;
                        } else {
                            msg += "  ";
                            check = 0;
                        }
                    }
                }

                // �ϧΥ��w
                if( check ) msg += area[i][j]["icon"] ? area[i][j]["icon"] : "  ";
            }
        }
        msg += BBLU"�j"NOR;
        msg += "\n";
    }
    msg += BBLU"���ááááááááááááááááááâ�\n"NOR;
    
    if( (type & 1) == 1 ) return msg;
    else return SAVEC+HOME+msg+RESTC;
}

varargs string show_objects(int x, int y, int type)
{
    string str = "";
    object ob;
    
    if( undefinedp(area[y][x]["objects"]) ) return "";

    if( sizeof(area[y][x]["objects"]) >= 30 ) return "�o�̪��F��Ӧh�A�@�ɬݤ��M��...\n";

    foreach(ob in area[y][x]["objects"]) {
        if( ob == this_player() ) continue;
    if( !objectp(ob) || environment(ob) != this_object() ||
            ob->query("area_info/y_axis") != y || ob->query("area_info/x_axis") != x ) {
                area[y][x]["objects"] -= ({ ob });
                continue;
        }
        if( !userp(ob) && QUEST_D->hasQuest(this_player(), ob) )
            str += sprintf("%s%s\n", BLINK+HIY"�I"NOR, ob->short());
        else
        str += sprintf("  %s\n", ob->short() );
    }
    
/*  debug ��
    whos = all_inventory(this_object());
    str += sprintf("\n====== Environment_Objects (%d) ======\n", sizeof(whos)) ;
    for(i=0;i<sizeof(whos);i++) {
        str += sprintf("  %s(%s) -> (%d,%d)\n",
            whos[i]->query("name"),
            whos[i]->query("id"),
            whos[i]->query("area_info/x_axis"),
            whos[i]->query("area_info/y_axis") );
    }
*/
    return str;
}

varargs int do_look(object me, string arg)
{
    int i=0, op=0;
    string str="", *exits;
    mapping info, option;

    if( !userp(me) ) return 0;

    info = me->query("area_info");
    option = me->query("option");

    if( !info ) return 0;
    if( !option ) option = ([]);
    if( !check_scope(info["x_axis"], info["y_axis"]) ) return 0;

    if( arg ) {
    if( (str = query_area_detail_arug(info["x_axis"], info["y_axis"], arg)) )
            message("vision", str + "\n", me);
        else return notify_fail("�A�n�ݤ���H\n");
        return 1;
    }

    // �O�_�����ᵲ�Y�ɦa��
    if( option["map_unfreeze"] ) op = op | 1;

    // ��ܧY�ɹϧ��ܴ�
    if( !option["map_obj_icon_hidden"] ) op = op | 2;

    // �N�쥻���a�Ϲϧ��ܴ����G�� ����ê�� �P �S��ê��
    if( option["map_block"] ) op = op | 4;

    // �a�ϹϧΥu��ܫؿv���Ϋئa
    if( option["map_build"] ) op = op | 8;

    // ��ܦa��
    if( !option["map_hidden"] ) {
        str = show_area(info["x_axis"], info["y_axis"], op);
    }
    
    // �X�f����
    if( !option["map_exits_hidden"] ) {
        exits = query_exits(info["x_axis"], info["y_axis"], 1);
        if( (i = sizeof(exits)) ) {
            str += "�o�̪��X�f�� ";
        while( i-- ) str += exits[i] + ( i ? "�B" : "�C\n" );
        } else str += "�o�̨S������X�f�C\n";
    }
    // ��ܪ���
    if( !option["map_obj_hidden"] ) str += show_objects(info["x_axis"], info["y_axis"], 0);
    message("vision", str, me);

    return 1;
}

varargs int map_ansi_save()
{
    int i, j, x, y;
    string file, msg="", msg2="";

    y = sizeof(area);
    x = sizeof(area[0]);

    file = base_name(this_object());

    for(i=0;i<y;i++) {
        for(j=0;j<x;j++) {
        if( j <= 49 ) {
            if( undefinedp(area[i][j]["icon"]) ) msg += "  ";
            else msg += area[i][j]["icon"];
        } else {
            if( undefinedp(area[i][j]["icon"]) ) msg2 += "  ";
            else msg2 += area[i][j]["icon"];
        }
        }
        msg += "\n";
        if( x > 49 ) msg2 += "\n";
    }
    
    if( x <= 49 ) {
        if( !write_file(file + ".ansi" , msg, 1) ) write("�x�sANSI�ɥ��ѡC\n");
        else write("�x�sANSI�ɦ��\\(" + file + ".ansi)�C\n");
    } else {
        write("�]����area�e�׶W�L���̭Ӧr�j�p�A�G�������k�G�ӹ����x�s�C\n");
        if( !write_file(file + "_left.ansi" , msg, 1) ) write("�x�s���b��ANSI�ɥ��ѡC\n");
        else write("�x�s���b��ANSI�ɦ��\\(" + file + "_left.ansi)�C\n");
        if( !write_file(file + "_right.ansi" , msg2, 1) ) write("�x�s�k�b��ANSI�ɥ��ѡC\n");
        else write("�x�s�k�b��ANSI�ɦ��\\(" + file + "_right.ansi)�C\n");
    }
    
    return 1;
}

varargs int map_html_save()
{
    int i, j, x, y;
    string file, msg="", tmp;

    y = sizeof(area);
    x = sizeof(area[0]);

    file = base_name(this_object());

    msg += "<html>\n";
    msg += "<head>\n";
    msg += "<title>" + this_object()->query("name") + "</title>\n";
    msg += "</head>\n";
    msg += "<body bgcolor=000000><font size=2 face=�ө���>\n";
    for(i=0;i<y;i++) {
        for(j=0;j<x;j++) {
            if( undefinedp(area[i][j]["icon"]) ) msg += "�@";
           else {
           tmp = replace_string(area[i][j]["icon"], "  ", "�@");
               msg += color_to_html(tmp);
               msg += "</span>";
           }
        }
        msg += "\n<br>";
    }
    msg += "</font></body>\n</html>";

    if( !write_file(file + ".html" , msg, 1) )
        write("�x�sHTML�ɥ��ѡC\n");

    write("�x�sHTML�ɦ��\\�C\n");

    return 1;
}
