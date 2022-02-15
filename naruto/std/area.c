/* area.c write by -Acme-
   �o�̭t�d�ϰ쪫�󪺸��J�B�M���B���]���u�@�C
*/

// #pragma save_binary

#include <area.h>
#include <dbase.h>

inherit F_DBASE;
inherit F_CLEAN_UP;
inherit F_SAVE;

inherit AREA_MAP;
inherit AREA_BUILDING;

// �ϰ���J������
// Location Of Loaded Objects
// �Ҧ��ϰ���J�����󪺮y�Хt���@�Ӷ��X�A�H��K�ֳt�d��
string *LOLO = ({});

////////////////////////////////////////////////////////////
// �@��]�w�B�ˬd�B�d��
////////////////////////////////////////////////////////////
// �Ǧ^�����J���󪺮y�ж�
string *query_LOLO() { return LOLO; }
// �[�J�@�Ӯy�Ф����bLOLO����
void add_LOLO(string location) { if( member_array(location, LOLO) == -1 ) LOLO += ({ location }); }
// �R���@�Ӯy�Ф����bLOLO����
void del_LOLO(string location) { if( member_array(location, LOLO) != -1 ) LOLO -= ({ location }); }

// �x�s�ϰ��ƪ����|��m
string query_save_file() { return file_name(this_object()); }

// ���ﱵ�����󲾤J�ϰ쪫��
int receive_object(object ob, int from_inventory) { return 1; }

// �ϰ��ˬd
int is_area() { return 1; }

// �]�w�Y�y�Эn���J��������
int set_loads(int x, int y, string filename, int amount)
{
if( !check_scope(x, y) ) return 0;
if( amount <= 0 ) return 0;
if( undefinedp(area[y][x]["loads"]) )
area[y][x]["loads"] = ([]);
area[y][x]["loads"][filename] = amount;

// �[�J�ֳt�j�M��
add_LOLO((string)y+","+(string)x);
return 1;
}

// �N�Y�y�Эn���J�������ɲ���
int del_loads(int x, int y)
{
if( !check_scope(x, y) ) return 0;
if( undefinedp(area[y][x]["loads"]) ) return 1;
map_delete(area[y][x], "loads");

// �����ֳt�j�M��
del_LOLO((string)y+","+(string)x);
return 1;
}

// �N�Y�y�Ъ��w���J���󲾰�
int del_loaded(int x, int y)
{
if( !check_scope(x, y) ) return 0;
if( undefinedp(area[y][x]["loaded"]) ) return 1;
map_delete(area[y][x], "loaded");
return 1;
}

////////////////////////////////////////////////////////////
// �ϰ�̪�������J�B�M��
////////////////////////////////////////////////////////////
object make_inventory(string file, int x, int y)
{
string *exits;
    object ob;

    file = file_path(file);
    ob = new(file);

    // Support for uniqueness
    if( ob->violate_unique() ) ob = ob->create_replica();
    if( !ob ) return 0;

    ob->set("area_info/x_axis", x);
    ob->set("area_info/y_axis", y);
    ob->set("area_info/x_axis_old", x);
    ob->set("area_info/y_axis_old", y);

    // �N���󲾨�ϰ�̡A���ˬd�O�_��guard�Y��V
if( move_in(x, y, ob) ) {
if( (exits=ob->query("guard_exit")) ) {
int i = sizeof(exits);
while(i--) this_object()->set_area_guard(x, y, exits[i], ob);
}
    ob->move(this_object());
}
else destruct(ob);

    return ob;
}

void reset_callout(int temp)
{
    int i, j, x, y, amount, t=0;
    mapping ob;
string file;

if( !sizeof(LOLO) || temp >= sizeof(LOLO) ) return;

for(i=temp;i<sizeof(LOLO);i++) {
        if( sscanf(LOLO[i], "%d,%d", y, x) != 2 ) continue;
        if( !check_scope(x, y) ) continue;
        if( undefinedp(area[y][x]["loads"]) ) continue;
        if( !mapp(ob = area[y][x]["loaded"]) ) ob = ([]);
        foreach( file, amount in area[y][x]["loads"] ) {
            for(j=amount;j>0;j--) {
                if( objectp(ob[file + " " + j]) ) continue;
                ob[file + " " + j] = make_inventory(file, x, y);
            }
            area[y][x]["loaded"] = ob;
        }
        t++;
        if( t >= 3 ) {
            call_out("reset_callout", 1, i+1);
            return;
        }
    }
return;
}

void reset()
{
    int i, amount, x, y;
    mapping ob;
    string file, location;

    // �M��LOO�y�ж�
    LOO = ({});

    // ������J�������, ���j����I�s����mob�H�Kcost�L�h
    call_out("reset_callout", 1, 0);
    return;
}

int clean_up(int inherit_flag)
{
    int i, y, x;
    mapping items;
    string file;
    object ob;

    i = sizeof(LOLO);
    while(i--)
if( sscanf(LOLO[i], "%d,%d", y, x) == 2 ) {
        if( !mapp(items = query_loaded(x, y)) ) continue;
        foreach(file, ob in items)
    if( objectp(ob) && ob->is_character() && environment(ob) != this_object() )
return 1;
    }

    return ::clean_up(inherit_flag);
}

// �ϰ�����ɩI�s���禡
void remove()
{
    int i, y, x, cnt;
    mapping items;
    string file, *objects;
    object ob;

i = sizeof(LOLO);
while(i--)
if( sscanf(LOLO[i], "%d,%d", y, x) == 2 ) {
if( !mapp(items = query_loaded(x, y)) ) continue;
foreach(file, ob in items) {
if( objectp(ob) ) {
message("vision", ob->name() + "�Ʀ������ƪ��շϮ����F�C\n", environment(ob));
destruct(ob);
cnt++;
}
}
// �M�Ůy�Ъ��󶰡A�H�K����X��
map_delete(area[y][x], "objects");

        // �M�Ůy�Фw���J���󤧸�ơA�H�K����X�� 
        map_delete(area[y][x], "loaded");
    }

    if( cnt && this_player() ) write("ĵ�i�G" + cnt + " ��NPC�Ѧ��ϰ�гy�óQ�j��R���C\n");
}

int save()
{
int i, j, x_size, y_size;
    string *LOO_BAK;
    mapping ICON_BAK, LOADED_BAK, OBJECTS_BAK;
    mixed *AREA_BAK;
    
// �s�ɫe�N���ݭn�x�����ܼƲM�šA�H�K����o�͵L�k�w�������~
LOO_BAK = LOO;
ICON_BAK = icon;
AREA_BAK = area;

LOO = ({});
icon = ([]);

    LOADED_BAK = ([]);
    OBJECTS_BAK = ([]);

x_size = this_object()->query("x_axis_size");
y_size = this_object()->query("y_axis_size");

    // �C��y�Ф����Ȯ��ܼƤ]�n�M��, �üȦs�_��
for(i=0;i<y_size;i++) {
if( undefinedp(LOADED_BAK[i]) ) LOADED_BAK[i] = ([]);
if( undefinedp(OBJECTS_BAK[i]) ) OBJECTS_BAK[i] = ([]);
for(j=0;j<x_size;j++) {
LOADED_BAK[i][j] = area[i][j]["loaded"];
    OBJECTS_BAK[i][j] = area[i][j]["objects"];
            map_delete(area[i][j], "loaded");// loaded -> mapping
            map_delete(area[i][j], "objects");// objects -> array
        }
    }

if( ::save() ) {
// �x�s���K�٭�
LOO = LOO_BAK;
icon = ICON_BAK;
area = AREA_BAK;

for(i=0;i<y_size;i++) {
for(j=0;j<x_size;j++) {
area[i][j]["loaded"] = LOADED_BAK[i][j];
area[i][j]["objects"] = OBJECTS_BAK[i][j];
        }
    }
return 1;
}

return 0;
}

void setup()
{
int i;
    string file;

seteuid(getuid());

// �S���x�s��
if( !restore() ) {
    int j, y_size, x_size;

        // �N�ϰ����ܼ� area �@��l��
        y_size = this_object()->query("y_axis_size");
        x_size = this_object()->query("x_axis_size");
        if( !y_size || y_size<AREA_YAXIS_MIN || y_size>AREA_YAXIS_MAX ) y_size = DEFAULT_YAXIS_SIZE;
        if( !x_size || x_size<AREA_XAXIS_MIN || x_size>AREA_XAXIS_MAX ) x_size = DEFAULT_XAXIS_SIZE;

        // �n�D�O����
        area = allocate( y_size );
        for(i=0;i<sizeof(area);i++) {
            area[i] = allocate( x_size );
            for(j=0;j<sizeof(area[i]);j++) area[i][j]=([]);
        }
        
        // �M�Ŭ�������
        LOO = ({});
        LOLO = ({});
        
        // �x�s
        save();
}

    // update �۹���|
    file = base_name(this_object());
    i = strlen(file);
    while(i--) if( file[i..i] == "/" ) break;
    set("file_path", file[0..i] );
    
this_object()->reset();

}
