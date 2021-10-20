/* �����F
   write by -Acme-
*/

// #pragma save_binary
#define GOODS_MAXIMUM 1000
#define GOODS_DEADLINE 7
#define AUC_MAXIMUM 20
#define NAME "�ͧJ�ʩ��|"

#include <ansi.h>
#include <localtime.h>

inherit F_CLEAN_UP;
inherit F_SAVE;

mapping goods;
mapping profit;

void create()
{
    seteuid(getuid());
//    if( !restore() && !mapp(goods) ) {
    if( !restore() ) {
        goods = ([]);
        profit = ([]);
    }
}

string query_save_file()
{
    return DATA_DIR + "aucd";
}

void do_clean()
{
    int index;

    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) break;
        if( time() > goods[index]["time"] + GOODS_DEADLINE*86400*2 )
            map_delete(goods, index);
    }
    save();
}

int do_auc_check(string id)
{
    int index, count=0;

    if( !stringp(id) ) return 0;

    if( !mapp(goods) ) {
        goods = ([]);
        profit = ([]);
        return 1;
    }

    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) continue;
        if( goods[index]["aucer"] == id ) count ++;
    }
        
    if( count >= AUC_MAXIMUM ) return 0;
    else return 1;
}

int do_stock(object aucer, object item, int value)
{
    int index, amount, changed;
    string file;

    if( !objectp(aucer) || !objectp(item) ) return 0;

    if( !userp(aucer) ) return 0;

    if( value <= 0 || value > 99999999 ) return 0;

    // ���O�}�񪺪���H
    if( base_name(item)[0..6] != "/world/" ) return 0;

    // �ӫ~�C��w��
    if( sizeof(goods) >= GOODS_MAXIMUM ) {
        // �յ۲M���L���B�S�H��^�����~
        do_clean();
        return 0;
    }

    if( !do_auc_check(aucer->query_id()) ) return 0;

    amount = item->query_amount();
    if( !amount ) amount = 1;

    file = base_name(item);

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
    goods[index]["value"] = value;

    if( item->query("wear_as") ) goods[index]["class"] = BBLU"����"NOR;
    else if( item->query("wield_as") ) goods[index]["class"] = BRED"�Z��"NOR;
    else if( function_exists("stuff_ob", item) ) goods[index]["class"] = BGRN"���~"NOR;
    else goods[index]["class"] = BYEL"�䥦"NOR;

    if( item->query("base_unit") ) goods[index]["unit"] = item->query("base_unit");
    else if( item->query("unit") ) goods[index]["unit"] = item->query("unit");
    else goods[index]["unit"] = "��";

    goods[index]["time"] = time();
    goods[index]["aucer"] = aucer->query_id();

    // �g�L�ק�L�����~�A�x�s���㪺���~���
    if( item->query("changed") ) {
        mapping dbase = item->query_entire_dbase();
        if( mapp(dbase) )
            goods[index]["dbase"] = dbase;
    }

    destruct(item);
    save();

    return 1;
}

string do_identify_msg(object obj)
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

        msg += sprintf("\n�j�Ʀ��ơG%d/10\n", obj->query("changed"));
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
        msg += sprintf("�j�Ʀ��ơG%d/3\n", obj->query("changed"));
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

string do_identify(int index)
{
    object item;
    string msg;

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

    msg = "���̡G" + goods[index]["aucer"] + "\n��檫�G" +  do_identify_msg(item);
    destruct(item);

    return msg;
}

string get_time(int t)
{
    mixed *local;
        string msg = "";

        if( time() > t ) msg += HIR;
    local = localtime(t);

    msg += sprintf("%d/%s/%s",
                   local[LT_YEAR],
                   local[LT_MON]+1 < 10 ? "0" + (local[LT_MON]+1) : (local[LT_MON]+1) + "",
                   local[LT_MDAY] < 10 ? "0" + local[LT_MDAY] : local[LT_MDAY] + "" );
        msg += NOR;
    return msg;
}


string do_search_goods(string key)
{
    int index;
    string msg;
    
    if( !sizeof(goods) ) return "�ثe�S������ӫ~�C\n";

    msg  = "�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    msg += sprintf("�x%-80s�x\n", NAME + "�ثe���ӫ~�C��" );
    msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�t\n";
    msg += "�x�s��  ���O  �ƶq  ���/�Ȩ�      �����  �W��                                   �x\n";
    msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) continue;
        if( strsrch(goods[index]["name"], key) == -1 && strsrch(goods[index]["id"], key) == -1 ) continue;
        msg += sprintf("�x%4d  %s%6d %10d  %s  %-s\n", 
                   index,
                   goods[index]["class"],
                   goods[index]["amount"],
                   goods[index]["value"],
                   get_time(goods[index]["time"] + GOODS_DEADLINE*86400),
                   goods[index]["name"] + "(" + goods[index]["id"] + ")" );
    }
    msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    msg += "�x��J help auc �A�Ѧp��ϥΩ����O�C  ����W�D�Gaucc                            �x\n";
    msg += "���w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��";
    return msg;
}

string do_list(string arg)
{
    int index;
    string msg;
    
    if( !sizeof(goods) ) return "�ثe�S������ӫ~�C\n";

    if( arg ) {
        msg  = "�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        msg += sprintf("�x%-80s�x\n", NAME + "�ثe���ӫ~�C��" );
        msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�t\n";
        msg += "�x�s��  ���O  �ƶq  ���/�Ȩ�      �����  �W��                                   �x\n";
        msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        for(index=1;index<=GOODS_MAXIMUM;index++) {
            if( undefinedp(goods[index]) ) continue;
                if( goods[index]["aucer"] != arg ) continue;
            msg += sprintf("�x%4d  %s%6d %10d  %s  %-s\n", 
                       index,
                       goods[index]["class"],
                       goods[index]["amount"],
                       goods[index]["value"],
                       get_time(goods[index]["time"] + GOODS_DEADLINE*86400),
                       goods[index]["name"] + "(" + goods[index]["id"] + ")" );
        }
        msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        msg += "�x��J help auc �A�Ѧp��ϥΩ����O�C  ����W�D�Gaucc                            �x\n";
        msg += "���w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��";
    } else {
        msg  = "�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        msg += sprintf("�x%-68s�x\n", NAME + "�ثe���ӫ~�C��" );
        msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�t\n";
        msg += "�x�s��  ���O  �ƶq  ���/�Ȩ�  �W��                                   �x\n";
        msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        for(index=1;index<=GOODS_MAXIMUM;index++) {
            if( undefinedp(goods[index]) ) continue;
//            if( time() - goods[index]["time"] > GOODS_DEADLINE*86400 ) continue;
            msg += sprintf("�x%4d  %s%6d %10d  %-s\n", 
                       index,
                       goods[index]["class"],
                       goods[index]["amount"],
                       goods[index]["value"],
                       goods[index]["name"] + "(" + goods[index]["id"] + ")" );
        }

        msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        msg += "�x��J help auc �A�Ѧp��ϥΩ����O�C  ����W�D�Gaucc                �x\n";
        msg += "���w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��";
    }
    
    return msg;
}

int to_sell(object who, int number, int amount)
{
    int value;
    object item;

    if( !objectp(who) ) return 0;

    // �ƶq�ˬd
    if( !amount ) amount = 1;

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
        tell_object(who, NAME+"�o�{�o�Ӱӫ~�����D���H�Y�U�[�F�A�A�L�k�ʶR�C\n");
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
        tell_object(who, NAME+"�o�{�A���G�����ʳo�˰ӫ~�A�K����A�F�C\n");
        // �R�����~
        destruct(item);
        return 1;
    }

    message_vision("$N��F" + chinese_number(value) + "��Ȥl�V" + NAME + "�R�U" +
                   chinese_number(amount) + goods[number]["unit"] + goods[number]["name"] + "�C\n", who);

    CHANNEL_D->do_channel( this_player(), "aucc",
        "��F" + chinese_number(value) + "��Ȥl�V" + NAME + "�R�U" +
        chinese_number(amount) + goods[number]["unit"] + goods[number]["name"] +
        "(" +  CHINESE_D->chinese_date(time()) + ")�C" );


    // �R�a�q�Ȧ榩��
    who->add("bank", -value);

    // �ӫ~�ƶq����
    goods[number]["amount"] -= amount;

    // ��a�W�[��
    if( undefinedp(profit[goods[number]["aucer"]]) )
        profit[goods[number]["aucer"]] = value;
    else profit[goods[number]["aucer"]] += value;

    // �槹�F�A�q�C���R��
    if( goods[number]["amount"] <= 0 ) map_delete(goods, number);
    save();

    return 1;
}

// ��a���^��
int get_money(object aucer)
{
        if( !objectp(aucer) || !userp(aucer) ) return 0;
        if( undefinedp(profit[aucer->query_id()]) ) return 0;
        tell_object(aucer, "�A�q" + NAME + "���^�F" + profit[aucer->query_id()] + "�Ȩ�A�æs�J�Ȧ�C\n");
        aucer->add("bank", profit[aucer->query_id()]);
        map_delete(profit, aucer->query_id());
    save();
        return 1;
}

// ��a���^�ӫ~
int get_goods(object who, int number)
{
        object item;

    // �S���o�Ӱӫ~�s��
    if( undefinedp(goods[number]) ) {
        tell_object(who, "�S���o�Ӱӫ~�s���C\n");
        return 0;
    }

    if( goods[number]["aucer"] != who->query_id() && !wizardp(who) ) {
        tell_object(who, "�o��ӫ~���O�A�b��檺�C\n");
        return 0;
    }

    // �L�k�إ߸Ӱӫ~
    if( !objectp(item = new(goods[number]["file"])) ) {
        tell_object(who, NAME + "�o�{�o�Ӱӫ~�����D���H�Y�U�[�F�A�A�L�k���^�C\n");
        // �γ\�ɮפw�g���s�b�A�q�C���R��
        map_delete(goods, number);
        return 0;
    }

    item->set_amount(goods[number]["amount"]);
    
    if( !undefinedp(goods[number]["dbase"]) ) {
        string *key;
        int j;
        key = keys(goods[number]["dbase"]);
        j = sizeof(key);
        while(j--) item->set(key[j], goods[number]["dbase"][key[j]]);
        item->delete("equipped");
    }

    if( !item->move(who) ) {
        tell_object(who, NAME+"�o�{�A���G�����ʳo�˰ӫ~�A�K���٧A�F�C\n");
        // �R�����~
        destruct(item);
        return 0;
    }

        tell_object(who, "�A�q" + NAME + "���^�F" + item->query("name") + "�C\n");

    //�q�C���R��
    map_delete(goods, number);

    save();
    return 1;
}

/*

// �bremove()�ɤ~�i��save()�ʧ@
int remove()
{
    save();
    return 1;
}
*/
