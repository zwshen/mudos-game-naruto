#include <ansi.h>
inherit ROOM;

string do_list()
{
    int index, size;
    string msg;

    msg  = "�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    msg += "�x�ϥλ����G    �@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�x\n";
    msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�t\n";
    msg += "�x1.��J�Z��(putwp) - �u���ּƪZ���~���J  �@�@�@�@�x\n";
    msg += "�x2.��i����(materials) - �������q�B�K�q�M���q      �x\n";
    msg += "�x3.�}�lű�y(found) - ���������ƥ]�M���e��m�����~  �x\n";
    msg += "�x4.����Z��(getwp) - �s�{�e�|�s���Ƥ@�P���X        �x\n";
    msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�t\n";
    msg += "�xps.���H�bű�y�ɤ��୫�ƨϥ�           �@�@�@�@�@�@�x\n";
    msg += "�xps.�[�u���Ʒf�t�P�Z���ˮ`��O����     �@�@�@�@�@�@�x\n";
    msg += "�xps.�C�إi�[�u�Z�������ۤv���f�t�Ҧ�   �@�@�@�@�@�@�x\n";
    msg += "�xps.�s�y�����άO���Q�s�y�O�o�N�Z�����X��K�L�H�ϥ� �x\n";
    msg += "�xps.�U�ا��Ƴ����̰��W���A�����s��Ѥ��O�|�תŶ��U �x\n";
    msg += "�xps.�Ʊ�j�a�ϥδr��                   �@�@�@�@�@�@�x\n";
    msg += "���w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";

    return msg;
}

object found;

void create()
{
        set("short", HIR"�[�u�X����"NOR);
        set("long", @LONG
�R���ۼo�o���M�����K���A�|�P������Q�N�������A�n�O�y�L��
�`�N�b�Τl�̫ݤӤ[�A�p�ߤ�����I����W���ۤ@�i�տ��s���ݪO�A
�g�L�F�`�[���N�`�̵M�իG�p�s�A�i���o�s�y����k�֩w�P�����P�C
�W���g�F�@�ǨϥΪ��W�h(paper)�C
LONG);
    set("exits", ([
        "east" : __DIR__"foundhouse.c",
    ]));
    set("detail", ([
        "paper": (: do_list :),
    ]));
    set("objects", ([
        "/world/area/old_forest/item/box.c" : 1,
    ]));
    setup();
}
void init()
{
    add_action("do_putwp", "putwp");
    add_action("do_materials", "materials");
    add_action("do_found", "found");
    add_action("do_getwp", "getwp");
    add_action("do_no", "drop");
    add_action("do_no", "put");
    add_action("do_no", "get");
}
int do_putwp()
{
    object box;
    if( box = present("_WP_BOX_", environment(this_player())) ) {
        if( objectp(found = present("_FOUNDER_WP_", this_player())) ) {
            if( found->query("founder") >= 1 ) return notify_fail("�o��Z���w�gű�y�L�F�C\n");
            if( found->query("equipped") ) return notify_fail("�A����N�˳Ƥ����Z����i�m���c�C\n");
            if( found->query("keep_this") ) return notify_fail("�����Ѱ��O�@���A�~���m�Z���C\n");
            if( !query("founder") ) set("founder", this_player()->query("id"));
            else return notify_fail("�̭��w�g���@��Z������ű�y�F�C\n");

            message_vision("$N�N���W��$n��i���l���ǳƥ[��ű�y�C\n"NOR, this_player(), found);
            found->move(box);
            return 1;
        } return notify_fail("�A���W�S���A�X���Z�����i�m���cű�y�C\n");
    } return notify_fail("�o�̦��G�S���m���c�i�H���A��Z���C\n");
}

int do_getwp()
{
    object box, item;
    int a, b, c, i;
    if( box = present("_WP_BOX_", environment(this_player())) ) {
        if( objectp(found = present("_FOUNDER_WP_", box)) ) {
            if( !wizardp(this_player()) ) {
                if( query("founder") != this_player()->query("id") ) return notify_fail("�m���c�̪��F��S���O�A���A�Q��������C\n");
            }
            if( query("run_found") >= 1 ) {
                if( this_player()->query_condition("founder") != 0 ) return notify_fail("�Z���٦b�s�y���A�еy���C\n");

                if( found->query("coal_need") ) a = query("coal_in")/found->query("coal_need");
                else a = 0;
                if( found->query("iron_need") ) b = query("iron_in")/found->query("iron_need");
                else b = 0;
                if( found->query("copper_need") ) c = query("copper_in")/found->query("copper_need");
                else c = 0;

                i = 0;
                if( a != 0 ) i += a;
                if( b != 0 ) i += b;
                if( c != 0 ) i += c;
                i = i/3;
                if( i >= 3 ) i = i - random(4);

                switch( i ) {
                    case 19:
                    case 1: i=1;found->setup_weapon(5+random(10), 15+random(10), 100, 1); break;

                    case 18:
                    case 2: i=2;found->setup_weapon(10+random(10), 20+random(10), 100, 1); break;

                    case 17:
                    case 3: i=3;found->setup_weapon(15+random(15), 30+random(20), 100, 1); break;

                    case 16:
                    case 4: i=4;found->setup_weapon(20+random(15), 35+random(25), 100, 1); break;

                    case 15:
                    case 5: i=5;found->setup_weapon(30+random(20), 50+random(30), 100, 1); break;

                    case 14:
                    case 6: i=6;found->setup_weapon(30+random(30), 60+random(40), 100, 1); break;

                    case 13:
                    case 7: i=7;found->setup_weapon(50+random(30), 80+random(40), 100, 1); break;

                    case 12:
                    case 8: i=8;found->setup_weapon(70+random(30), 100+random(50), 100, 1); break;

                    case 11:
                    case 9: i=9;found->setup_weapon(100+random(30), 120+random(50), 100, 1); break;

                    case 10: i=10;found->setup_weapon(120+random(30), 150+random(50), 100, 1); break;

                    case 0: 
                    default: i=0;found->setup_weapon(1+random(5), 5+random(10), 100, 1); break;
                }
                found->set("name", HIY"(+"+i+")"NOR" "+found->query("name")+"");
                message_vision(HIR"$N���U�F�Ұʪ����s�A�N��ű���Z���e�J���l���i��[�u�ĦX�C\n"NOR, this_player());
                message_vision(CYN"�����n�q�l���ǥX�A���G�Z���N�֧����F�C\n"NOR, this_player());
                message_vision("\n$N��۴��ݪ��߱����}����A���X�F�ۤv��߻s�@���Z��$n�C\n"NOR, this_player(), found);
                found->set("founder",1);
                if( found->move(this_player()) ) {
                    item = new("/world/area/old_forest/item/residue.c");
                    item->add_amount(i*15+random(80));
                    if( item->move(this_player()) ) {
                        tell_object(this_player(), "(���}�e�бN�o�󪫤]�a���C)\n"NOR);
                    } else {
                        tell_object(this_player(), "(�]�����W�ӭ��F�A�o�󪫼Q�F���a�C)\n"NOR);
                        destruct(item);
                    }
                    item = new("/world/area/old_forest/item/scrap.c");
                    item->add_amount(i);
                    if( item->move(this_player()) ) {
                        tell_object(this_player(), "(���}�e�бN�o�o�]�a���P���C)\n"NOR);
                    } else {
                        tell_object(this_player(), "(�]�����W�ӭ��F�A�o�o���½�b�a�W�C)\n"NOR);
                        destruct(item);
                    }
                } else {
                    tell_object(this_player(), HIY"�A���W�ӭ��F�A�����ʳo�˪Z���C\n"NOR);
                    return 1;
                }
                delete("founder");
                delete("run_found");
                delete("coal_in");
                delete("iron_in");
                delete("copper_in");
                return 1;
            }
            message_vision("$N�٬O�M�w��ű�y�F�A�N�Z�����ƥ������F�X�ӡC\n"NOR, this_player(), found);
            found->move(this_player());

            if( query("coal_in") >= 1 ) {
                if( file_size("/world/area/old_forest/item/coal.c") < 0 ) return 0;
                if( catch(item = new("/world/area/old_forest/item/coal.c")) ) return 0;
                item->add_amount(query("coal_in")-1);
                item->move(this_player());
                delete("coal_in");
            }
            if( query("iron_in") >= 1 ) {
                if( file_size("/world/area/old_forest/item/iron.c") < 0 ) return 0;
                if( catch(item = new("/world/area/old_forest/item/iron.c")) ) return 0;
                item->add_amount(query("iron_in")-1);
                item->move(this_player());
                delete("iron_in");
            }
            if( query("copper_in") >= 1 ) {
                if( file_size("/world/area/old_forest/item/copper.c") < 0 ) return 0;
                if( catch(item = new("/world/area/old_forest/item/copper.c")) ) return 0;
                item->add_amount(query("copper_in")-1);
                item->move(this_player());
                delete("copper_in");
            }
            delete("founder");
            delete("run_found");
            return 1;
        } return notify_fail("�m���c�̪ŪŦp�]�C\n");
    } return notify_fail("�o�̦��G�S���m���c�i�H���A���Z���C\n");
}

int do_found()
{
    mapping cnd = ([]);
    object bag;
    int i;

    if( !query("founder") ) return notify_fail("�n��J�Z���~��i��ű�y�C\n");
    if( query("founder") != this_player()->query("id") ) return notify_fail("���G�w�g���O�H�bű�y�F�C\n");
    if( query("run_found") >= 1 ) return notify_fail("�Z�����bű�y���C\n");

    i = query("coal_in") + query("iron_in") + query("copper_in");
    if( objectp(bag = present("_WP_BAG_", this_player())) ) {
        message_vision("$N�N���ƥ]��i���l�����W�p������A�p���l�l�a�}�l�[��ű�y�C\n"NOR, this_player());
        destruct(bag);

        cnd["name"] = HIR+BLINK"ű�y��"NOR;
        cnd["duration"] = i;

        this_player()->set_condition("founder", cnd);
        set("run_found", 1);

        return 1;
    } return notify_fail("�����֦����ƥ]�~��i��Z���s�@�C\n");
}

int do_no()
{
    tell_object(this_player(), "�o�̤���å�þߪF��I\n"NOR);
    return 1;
}

int do_materials(string arg)
{
    object coal, iron, copper, me;
    int a, b, c;

    me = this_player();

    if( !arg || sscanf(arg, "%d %d %d", a, b, c) != 3 ) return notify_fail("�{�b���l�������q "HIY+query("coal_in")+NOR" ���B�K�q "HIY+query("iron_in")+NOR" ���B���q "HIY+query("copper_in")+NOR" ���C�C\n"HIR"���O�榡�Gmaterials <�Ѷq> <�K�q> <�ɶq>\n"NOR);
    if( query("founder") != me->query("id") ) return notify_fail("�{�b�bű�y���H���G���O�A�A����é�F��i�h�C\n"NOR);
    if( query("run_found") >= 1 ) return notify_fail("�Z�����bű�y���A�����{�ɥ[�J���ơC\n");

    if( a > 0 ) {
        if( objectp(coal = present("_COAL_", me)) ) {
            if( a > 1000 ) a = 1000;
            if( coal->query_amount() >= a ) {
                message_vision("$N���X�F"+chinese_number(a)+"�����q��i���l���C\n"NOR, me);
                coal->add_amount(-a);

                if( !query("coal_in") ) set("coal_in", a);
                else add("coal_in", a);

                if( !coal->query_amount() ) destruct(coal);
            } else {
                tell_object(me, "�A���W�����q���Ƥ����I\n"NOR);
            }
        } else {
            tell_object(me, "�A���W�ڥ��S�����q�I\n"NOR);
        }
    } else {
        tell_object(me, "�A�M�w������q�F�C\n"NOR);
    }
    if( b > 0 ) {
        if( objectp(iron = present("_IRON_", me)) ) {
            if( b > 1000 ) b = 1000;
            if( iron->query_amount() >= b ) {
                message_vision("$N���X�F"+chinese_number(b)+"���K�q��i���l���C\n"NOR, me);
                iron->add_amount(-b);

                if( !query("iron_in") ) set("iron_in", b);
                else add("iron_in", b);

                if( !iron->query_amount() ) destruct(iron);
            } else {
                tell_object(me, "�A���W���K�q���Ƥ����I\n"NOR);
            }
        } else {
            tell_object(me, "�A���W�ڥ��S���K�q�I\n"NOR);
        }
    } else {
        tell_object(me, "�A�M�w�����K�q�F�C\n"NOR);
    }
    if( c > 0 ) {
        if( objectp(copper = present("_COPPER_", me)) ) {
            if( c > 500 ) c = 500;
            if( copper->query_amount() >= c ) {
                message_vision("$N���X�F"+chinese_number(c)+"�����q��i���l���C\n"NOR, me);
                copper->add_amount(-c);

                if( !query("copper_in") ) set("copper_in", c);
                else add("copper_in", c);

                if( !copper->query_amount() ) destruct(copper);
            } else {
                tell_object(me, "�A���W�����q���Ƥ����I\n"NOR);
            }
        } else {
            tell_object(me, "�A���W�ڥ��S�����q�I\n"NOR);
        }
    } else {
        tell_object(me, "�A�M�w������q�F�C\n"NOR);
    }
    return 1;
}
