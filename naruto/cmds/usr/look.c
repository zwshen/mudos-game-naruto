/* look.c write by -Acme-
*/

// #pragma save_binary
#include <ansi.h>

inherit "/adm/daemons/itemd.c";

mapping named_apply = ([
    "head_eq": HIK"["NOR"�Y��"HIK"]"NOR,
    "face_eq": HIK"["NOR"�y��"HIK"]"NOR,
    "neck_eq": HIK"["NOR"�V��"HIK"]"NOR,
    "wrist_eq": HIK"["NOR"���"HIK"]"NOR,
    "hand_eq": HIK"["NOR"�ⳡ"HIK"]"NOR,
    "finger_eq": HIK"["NOR"���"HIK"]"NOR,
    "cloth": HIK"["NOR"��A"HIK"]"NOR,
    "armor": HIK"["NOR"�Z��"HIK"]"NOR,
    "waist_eq": HIK"["NOR"�y��"HIK"]"NOR,
    "pants": HIK"["NOR"�Ǥl"HIK"]"NOR,
    "leg_eq": HIK"["NOR"�L��"HIK"]"NOR,
    "feet_eq": HIK"["NOR"����"HIK"]"NOR,
    "lefthand": HIK"["NOR"����"HIK"]"NOR,
    "righthand": HIK"["NOR"�k��"HIK"]"NOR,
    "twohanded": HIK"["NOR"����"HIK"]"NOR,
]);

string status_msg(string who, int ratio)
{
    switch( ratio ) {
		case    100: return HIG + who + "�ݰ_�ӨèS�����ˡC\n" NOR; break;
		case 96..99: return HIG + who + "���G���F�I���ˡA���L���q�~��ݤ��j�X�ӡC\n" NOR; break;
		case 91..95: return HIG + who + "�ݰ_�ӥi����F�I���ˡC\n" NOR; break;
		case 81..90: return HIG + who + "���F�X�B�ˡA���L���G�ä�ê�ơC\n" NOR; break;
		case 61..80: return HIY + who + "���ˤ����A�ݰ_�Ӫ��p�ä��Ӧn�C\n" NOR; break;
		case 41..60: return HIY + who + "�𮧲ʭ��A�ʧ@�}�l���áA�ݨөҨ����˵۹ꤣ���C\n" NOR; break;
		case 31..40: return HIY + who + "�w�g�˲��ֲ֡A���b�j�O�伵�ۤ��ˤU�h�C\n" NOR; break;
		case 21..30: return HIR + who + "���F�۷����ˡA�u�ȷ|���ͩR�M�I�C\n" NOR; break;
		case 11..20: return HIR + who + "�˭����U�w�g���H�伵�A���ݴN�n�˦b�a�W�C\n" NOR; break;
		case  5..10: return HIR + who + "���˹L���A�w�g�a�a�@���A�R�b���i�F�C\n" NOR; break;
		default:     return HIR + who + "���˹L���A�w�g���p��������A�H�ɳ��i���_��C\n" NOR; break;
    }    
}

string inventory_look(object obj, int flag)
{
    string str, type, sub_type;

    str = obj->short();
    if( type = obj->query("equipped") ) {
        if( sscanf(type, "%s/%s", type, sub_type) == 2 ) {
            str = sprintf("  %s %s",
            	          !undefinedp(named_apply[sub_type]) ? named_apply[sub_type] : sub_type,
            	          str );
        } else str = HIY "  ��"NOR + str;
    } else if( !flag ) str = "    " + str;
    else return 0;

    return str;
}

int look_living(object me, object obj)
{
    int age;
    string msg, race, pro;
    mixed *inv, drop;

    race = obj->query_race();
    pro = (obj==me) ? gender_self(obj->query("gender")) : gender_pronoun(obj->query("gender"));
    age = obj->query("age");

    if( me != obj ) message("vision", me->name() + "���n�ۧA�ݡM�����D���Ǥ���D�N�C\n", obj);

    msg = sprintf("%s�ݰ_��%s���C\n", pro, age > 10 ? "��" + chinese_number(age/10*10) + "�h" : "�����" );
    msg += obj->long();
    if( obj->query_stat_maximum("hp") )
        msg += status_msg(pro, obj->query_stat_current("hp")*100/obj->query_stat_maximum("hp"));

    inv = all_inventory(obj);
    if( sizeof(inv) ) {
        inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse() ? 0 : 1 );
        inv -= ({ 0 });
        if( sizeof(inv) )
            msg += sprintf( obj->is_corpse() ? "%s���򪫦��R\n%s\n" : "%s���W�a�ۡR\n%s\n", pro, implode(inv, "\n") );
    }

    // �˵�������
    if( !userp(obj) && arrayp(drop = obj->query("set_drop")) ) {
    	int power = 0;
        mapping dd, record;
        
        if( wizardp(me) ) power = 2;
        else {
            if( mapp(me->query_condition("know1")) ) power = 1;
            if( mapp(me->query_condition("know2")) ) power = 2;
        }
        
        if( power > 0 ) {
            msg += "\n�������G\n";
            foreach( dd in drop ) {
                if( !mapp(dd) ) continue;
                record = 0;
                switch( dd["type"] ) {
                    case "eq":   record = ITEM_D->do_query("eq", dd["id"]); break;
                    case "wp":   record = ITEM_D->do_query("wp", dd["id"]); break;
                    case "food": record = ITEM_D->do_query("food", dd["id"]); break;
                    case "obj":  record = ITEM_D->do_query("obj", dd["id"]); break;
                    default: record = 0;
                }
                if( !mapp(record) ) continue;
                msg += "  " + record["name"];
                if( power > 1 ) msg += " [���v�G" + dd["p1"] + "/" + dd["p2"] + "]\n";
                else msg += "\n";
            }
        }
    }

    message("vision", msg, me);

    return 1;
}

int look_item(object me, object obj)
{
    mixed *inv;

    me->start_more(obj->long());
    inv = all_inventory(obj);
    if( sizeof(inv) ) {
        if( sizeof(inv) < 30 ) {
            inv = map_array(inv, "inventory_look", this_object() );
            message("vision", sprintf("�̭����R\n  %s\n", implode(inv, "\n  ") ), me);
        }
        else tell_object(me, YEL"�̭����C���K����۳\�h�F��..\n"NOR);
    }
    return 1;
}

int main(object me, string arg)
{
    object obj;

    if( !environment(me) )
        return notify_fail("�A�{�b����]�ݤ���I\n");

    if( me->query_temp("block_msg/vision") )
        return notify_fail("�A�{�b����]�ݤ���I\n");

    if( !arg ) return environment(me)->do_look(me, arg);
    
    if( (obj = present(arg, environment(me))) || (obj = present(arg, me)) ) {
        if( obj->is_character() ) return look_living(me, obj);
            else return look_item(me, obj);
    } else return environment(me)->do_look(me, arg);
    
    return 1;
}

int help (object me)
{
    write(@HELP
���O�榡: look [<���~>|<�ͪ�>]
 
�o�ӫ��O���A�d�ݧA�Ҧb�����ҡB�Y�󪫫~�B�ͪ��C
 
HELP);
    return 1;
}
