/* hockshop.c
   write by -Acme-
*/

// #pragma save_binary

#define GOODS_MAXIMUM 100

#include <dbase.h>
#include <ansi.h>

inherit F_SAVE;
inherit ROOM;

mapping goods;

mapping query_goods() { return goods; }

int to_stock(object item)
{
    int index, amount, changed;
    string file;

    // goods ���O�@�Ӫ���
    if( !objectp(item) ) return 0;

    if( base_name(item)[0..6] != "/world/" ) return 0;

    // �ӫ~�C��w��
    if( sizeof(goods) >= GOODS_MAXIMUM ) {
        for(index=1;index<=GOODS_MAXIMUM;index++) {
            if( undefinedp(goods[index]) ) continue;
            map_delete(goods, index);
        }
    }

    amount = item->query_amount();
    if( !amount ) amount = 1;

    file = base_name(item);

    changed = item->query("changed");

    // �Y�f�~�O�S���g�L�u���ܡv�]�N�O�f�~���]�w�P��l�ɮ׳]�w�ۦP�A�h
    // �ˬd�O�_�P�ӫ~�C�����Y�ӫ~�ۦP�A�p�G�ۦP�A�Y�W�[�ƶq�K�i�C
    if( !changed ) {
        for(index=1;index<=GOODS_MAXIMUM;index++) {
            if( undefinedp(goods[index]) ) continue;

            // ���ۦP���ɮצW�١A�W�[��ƶq
            if( goods[index]["file"] == file ) {
                goods[index]["amount"] += amount;
                destruct(item);
                return 1;
            }
        }
    }

    // �M��i�Ϊ��ӫ~�s��
    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) break;
    }

    // �s���W�L���E�ӫ~�ƶq�W��
    if( index > GOODS_MAXIMUM ) return 0;

    // �]�w�x�s�Ӱӫ~�����
    goods[index] = ([]);
    goods[index]["file"] = file;
    goods[index]["amount"] = amount;
    goods[index]["name"] = item->query("name");
    goods[index]["id"] = item->query("id");

    if( item->query("base_value") ) goods[index]["value"] = item->query("base_value");
    else goods[index]["value"] = item->query("value");

    if( item->query("wear_as") ) goods[index]["class"] = BBLU"����"NOR;
    else if( item->query("wield_as") ) goods[index]["class"] = BRED"�Z��"NOR;
    else if( function_exists("stuff_ob", item) ) goods[index]["class"] = BGRN"���~"NOR;
    else goods[index]["class"] = BYEL"�䥦"NOR;

    if( item->query("base_unit") ) goods[index]["unit"] = item->query("base_unit");
    else if( item->query("unit") ) goods[index]["unit"] = item->query("unit");
    else goods[index]["unit"] = "��";


    // �g�L�ק�L�����~�A�x�s���㪺���~���
    if( changed ) {
        mapping dbase = item->query_entire_dbase();
        if( mapp(dbase) )
            goods[index]["dbase"] = dbase;
    }

    destruct(item);

    return 1;
}

int to_sell(object who, int number, int amount)
{
    int value;
    object item;

    if( !objectp(who) ) return 0;

    if( sizeof(all_inventory(who)) >= 40 ) {
        tell_object(who, "���a�o�{�A���G�����ʳo�˰ӫ~�A�K����A�F�C\n");
        return 1;
    }

    if( who->query_encumbrance() >= who->query_ability("carriage") ) {
        tell_object(who, "���a�o�{�A���G�����ʳo�˰ӫ~�A�K����A�F�C\n");
        return 1;
    }

    if( amount <= 0 ) {
        tell_object(who, "�A�Q�n�R�X�Ӱӫ~�H\n");
        return 1;
    }
    if( amount > 999 ) {
        tell_object(who, "�@���̦h�u���ʶR999�Ӱӫ~...\n");
        return 1;
    }

    // �S���o�Ӱӫ~�s��
    if( undefinedp(goods[number]) ) {
        tell_object(who, "�S���o�Ӱӫ~�s���C\n");
        return 1;
    }

    // �ƶq�ˬd
    if( !amount ) amount = 1;
    if( goods[number]["amount"] < amount ) {
        tell_object(who, "�o�Ӱӫ~�ƶq�S���o��h�C\n");
        return 1;
    }
    
    value = goods[number]["value"] * amount;
    // �Ȧ������
    if( who->query("bank") < value ) {
        tell_object(who, "�A�Ȧ�̪��������A�L�k�ʶR���ӫ~�C\n");
        return 1;
    }
    
    // �L�k�إ߸Ӱӫ~
    if( !objectp(item = new(goods[number]["file"])) ) {
        tell_object(who, "���a�o�{�o�Ӱӫ~�����D���H�Y�U�[�F�A�A�L�k�ʶR�C\n");
        // �γ\�ɮפw�g���s�b�A�q�C���R��
        map_delete(goods, number);
        return 1;
    }
    
    if( !function_exists("set_amount", item) && amount > 1) {
        tell_object(who, "�o�ӪF��@���u��R�@�ӡC\n");
        destruct(item);
        return 1;
    }

    item->set_amount(amount);
    
    if( !undefinedp(goods[number]["dbase"]) ) {
        string *key;
        int j;
        key = keys(goods[number]["dbase"]);
        j = sizeof(key);
        while(j--) item->set(key[j], goods[number]["dbase"][key[j]]);
        item->delete("equipped");
    }

    if( !item->move(who) ) {
        tell_object(who, "���a�o�{�A���G�����ʳo�˰ӫ~�A�K����A�F�C\n");
        // �R�����~
        destruct(item);
        return 1;
    }

    message_vision("$N��F" + chinese_number(value) + "��Ȥl�V" + this_object()->query("short") + "�R�U" +
                   chinese_number(amount) + goods[number]["unit"] + goods[number]["name"] + "�C\n", who);

    // �q�Ȧ榩��
    who->add("bank", -value);

    // �ӫ~�ƶq����
    goods[number]["amount"] -= amount;

    // �槹�F�A�q�C���R��
    if( goods[number]["amount"] <= 0 ) map_delete(goods, number);

    return 1;
}

string do_identify(object obj)
{
string msg = "";

if( !objectp(obj) ) return msg;

    msg += obj->query("name") + "(" + obj->query("id") + ")\n\n";
    msg += obj->query("long") + "\n";

    if( obj->is_weapon() ) {
        string s;
        mapping dp, apply;
        mixed sk = obj->query("wield_as");
        
        msg += "�i�ϥΤ覡�G\n";

        if( stringp(sk) ) sk = ({ sk });
        foreach(s in sk) {
            msg += sprintf("\n�� %s (%s)\n", to_chinese(s), s);
            dp = obj->query("damage/" + s);
            msg += sprintf("   �ˮ`�O�G %d - %d (�ˮ`�O�ץ� %d%%�A�Z������ %d)\n", 
                dp["lower"], dp["upper"], dp["bonus"], dp["level"] );

            apply = obj->query("apply_weapon/" + s);
            if( mapp(apply) ) {
                string prop;
                mixed value;
            
                msg += "\n   �Z���S�ʡG\n";
                foreach(prop, value in apply) {
                    prop = to_chinese(prop);
                    msg += sprintf("     %-30s %O\n", prop, value);
                }
            }
        }
    } else if( obj->is_armor() ) {
    string sub_type = obj->query("wear_as");
    mapping apply = obj->query("apply_armor/" + sub_type);
        msg += sprintf("�@�㳡��G%s\n", to_chinese(sub_type) );
        if( mapp(apply) ) {
            string prop;
            mixed value;
            
            msg += "�@��S�ʡG\n";
            foreach(prop, value in apply) {
                msg += sprintf("  %-30s %O\n", to_chinese(prop), value);
            }
        }
    }

return msg;
}


string do_list(string arg)
{
    int index;
    string msg;
    
    if( !sizeof(goods) ) return "�ثe�S������ӫ~�C\n";

if( stringp(arg) ) {
object item;
index = atoi(arg);
    if( undefinedp(goods[index]) ) return "�S���o�Ӱӫ~�s���C\n";

    // �L�k�إ߸Ӱӫ~
    if( !objectp(item = new(goods[index]["file"])) ) {
        // �γ\�ɮפw�g���s�b�A�q�C���R��
        map_delete(goods, index);
        return "�o�Ӱӫ~���G���@�I���D�A�Q���a���F�^�h�C\n";
    }
    
    // �S�O���~�[��O
    if( !undefinedp(goods[index]["dbase"]) ) {
        string *key;
        int j;
        key = keys(goods[index]["dbase"]);
        j = sizeof(key);
        while(j--) item->set(key[j], goods[index]["dbase"][key[j]]);
       item->delete("equipped");
    }

    msg = do_identify(item);
    destruct(item);
    return msg;
}

    msg  = "�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    msg += sprintf("�x%-68s�x\n", this_object()->query("short") + "�ثe���ӫ~�C��" );
    msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�t\n";
    msg += "�x�s��  ���O    �ƶq  ���/�Ȩ�  �W��                                 �x\n";
    msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) continue;
        msg += sprintf("�x%4d  %s %7d %10d  %-s\n", 
                       index,
                       goods[index]["class"],
                       goods[index]["amount"],
                       goods[index]["value"],
                       goods[index]["name"] + "(" + goods[index]["id"] + ")" );
    }
    msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    msg += "�x��J help trade �A�Ѧp��ϥΥ�����O�C                              �x\n";
    msg += "���w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��";
    
    return msg;
}

// �x�s���E��ƪ����|��m
string query_save_file() { return file_name(this_object()); }

// �o�O���E
int is_hockshop() { return 1; }

// �breset()�ɤ~�i��save()�ʧ@
//void reset() { save(); }

// �bremove()�ɤ~�i��save()�ʧ@
int remove()
{
    save();
    return 1;
}

void setup()
{
    if( !restore() ) goods = ([]);
}
