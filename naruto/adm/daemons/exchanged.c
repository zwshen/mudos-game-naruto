/* �I�ưӫ�
   copy aucd >///< by mouse
   2009/2/17
*/
// #pragma save_binary
#define GOODS_MAXIMUM 500       // �̦h 500 �اI���ӫ~
#define NAME HIY"���i�a"HIG"�s�q"NOR"���"

#include <ansi.h>
#include <localtime.h>

inherit F_CLEAN_UP;
inherit F_SAVE;

mapping goods;
mapping profit;

void create()
{
    seteuid(getuid());
    if( !restore() ) {
        goods = ([]);
        profit = ([]);
    }
}

string query_save_file()
{
    return DATA_DIR + "exchanged";
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
    }
}

int do_stock(object aucer, object item, int value, int amulet)
{
    int index, changed;
    string file;

    if( !objectp(aucer) || !objectp(item) ) return 0;
    if( !userp(aucer) ) return 0;
    if( value <= 0 || value > 99999999 ) return 0;

    // ���O�}�񪺪���H
    if( base_name(item)[0..6] != "/world/" ) return 0;

    // �ӫ~�C��w��
    if( sizeof(goods) >= GOODS_MAXIMUM ) {
        // ���F�N����A�W�[
        tell_object(aucer, "�ӫ~�w���A���N�@�ǹL�ɪ��I���~�U�[�a�C\n");
        return 0;
    }
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
    goods[index]["amount"] = amulet;
    goods[index]["name"] = item->query("name");
    goods[index]["id"] = item->query("id");
    goods[index]["value"] = value;

    if( item->query("wear_as") ) goods[index]["class"] = BBLU"����"NOR;
    else if( item->query("wield_as") ) goods[index]["class"] = BRED"�Z��"NOR;
    else if( function_exists("stuff_ob", item) ) goods[index]["class"] = BGRN"���~"NOR;
    else if( item->query("effect") ) goods[index]["class"] = BMAG"�j��"NOR;
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
    // �u�O�n�����~�W�[�A���ΧR��(����)
    // destruct(item);
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
    // �I�ưӫ~����ܩ��H�W�r
    msg = "\n��檫�G" +  do_identify_msg(item);
    destruct(item);

    return msg;
}

string get_time(int t)
{
    mixed *local;
    string msg = "";

    if( time() > t ) msg += HIR;
    local = localtime(t);

    msg += sprintf("%d/%s/%s", local[LT_YEAR], local[LT_MON]+1 < 10 ? "0" + (local[LT_MON]+1) : (local[LT_MON]+1) + "", local[LT_MDAY] < 10 ? "0" + local[LT_MDAY] : local[LT_MDAY] + "" );
    msg += NOR;
    return msg;
}

string do_search_goods(string key)
{
    int index;
    string msg;
    
    if( !sizeof(goods) ) return "�ثe�S������ӫ~�C\n";

    msg  = "���ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ�\n";
    msg += sprintf("\t\t    %s\n", NAME + "�ثe���ӫ~�C��" );
    msg += "�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    msg += "�x�s��  ���O   �ƶq   �I�ƻݨD  �W��                                  �x\n";
    msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    for(index=1;index<=GOODS_MAXIMUM;index++) {
        if( undefinedp(goods[index]) ) continue;
        if( strsrch(goods[index]["name"], key) == -1 && strsrch(goods[index]["id"], key) == -1 ) continue;
        msg += sprintf("�x%4d  %s %6d %10d  %-s\n", 
                   index,
                   goods[index]["class"],
                   goods[index]["amount"],
                   goods[index]["value"],
                   goods[index]["name"] + "(" + goods[index]["id"] + ")" );
    }
    msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
    msg += "�x��J help exc �A�Ѧp��ϥΧI�����O�C  ����W�D�Gaucc                �x\n";
    msg += "���w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��";
    return msg;
}

string do_list(string arg)
{
    int index;
    string msg;
    
    if( !sizeof(goods) ) return "�ثe�S������ӫ~�C\n";

    if( arg ) {
        msg  = "���ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ�\n";
        msg += sprintf("\t\t    %s\n", NAME + "�ثe���ӫ~�C��" );
        msg += "�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        msg += "�x�s��  ���O   �ƶq   �I�ƻݨD  �W��                                  �x\n";
        msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        for(index=1;index<=GOODS_MAXIMUM;index++) {
            if( undefinedp(goods[index]) ) continue;
                if( goods[index]["aucer"] != arg ) continue;
            msg += sprintf("�x%4d  %s %6d %10d  %-s\n", 
                       index,
                       goods[index]["class"],
                       goods[index]["amount"],
                       goods[index]["value"],
                       goods[index]["name"] + "(" + goods[index]["id"] + ")" );
        }
        msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        msg += "�x��J help exc �A�Ѧp��ϥΧI�����O�C  ����W�D�Gaucc                �x\n";
        msg += "���w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��";
    } else {
        msg  = "���ݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡݡ�\n";
        msg += sprintf("\t\t    %s\n", NAME + "�ثe���ӫ~�C��" );
        msg += "�~�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        msg += "�x�s��  ���O   �ƶq   �I�ƻݨD  �W��                                  �x\n";
        msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        for(index=1;index<=GOODS_MAXIMUM;index++) {
            if( undefinedp(goods[index]) ) continue;
            msg += sprintf("�x%4d  %s %6d %10d  %-s\n", 
                       index,
                       goods[index]["class"],
                       goods[index]["amount"],
                       goods[index]["value"],
                       goods[index]["name"] + "(" + goods[index]["id"] + ")" );
        }
        msg += "�u�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��\n";
        msg += "�x��J help exc �A�Ѧp��ϥΧI�����O�C  ����W�D�Gaucc                �x\n";
        msg += "���w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w�w��";
    }
    return msg;
}

int to_sell(object who, int number, int amount)
{
    int value;
    object item, disco = new("/world/npc/disco.c");

    if( !objectp(who) ) return 0;

    // �ƶq�ˬd
    if( !amount ) amount = 1;

    if( amount <= 0 ) {
        tell_object(who, "�A�Q�n�I���X�Ӱӫ~�H\n");
        return 1;
    }
    if( amount > 50 ) {
        tell_object(who, "�@���̦h�u��I�� 50 �Ӱӫ~...\n");
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

    // �I���I�Ƥ���
    if( who->query("exchange") < value ) {
        tell_object(who, "�A���I���I�Ƥ����A�L�k�ʶR�����C\n");
        return 1;
    }
    // �L�k�إ߸Ӱӫ~
    if( !objectp(item = new(goods[number]["file"])) ) {
        tell_object(who, NAME+"�o�{�o�Ӱӫ~�����D���H�Y�U�[�F�A�A�L�k�I���C\n");

        // �γ\�ɮפw�g���s�b�A�q�C���R��
        map_delete(goods, number);
        return 1;
    }
    if( !function_exists("set_amount", item) && amount > 1) {
        tell_object(who, "�o�ذӫ~�C���u��I���@�ӡC\n");
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
        tell_object(who, NAME+"�o�{�A���W�ӭ��L�k�������~�A�K�����A�I���F�C\n");

        // �R�����~
        destruct(item);
        return 1;
    }
    message_vision("$N��F" + chinese_number(value) + "�I�I���I�ƦV" + NAME + "�I��" + chinese_number(amount) + goods[number]["unit"] + goods[number]["name"] + "�C\n", who);
    CHANNEL_D->do_channel(disco, "aucc", "�ӫ~" + chinese_number(amount) + goods[number]["unit"] + goods[number]["name"] + "�w�g�I�����F"HIY+this_player()->query("name")+NOR"�I�w��A�����{" + NAME + "�I(" + CHINESE_D->chinese_date(time()) + ")");

    // �R�a�����I���I��
    who->add("exchange", -value);

    // �ӫ~�ƶq����
    goods[number]["amount"] -= amount;

    // �槹�F�A�q�C���R��
    if( goods[number]["amount"] <= 0 ) map_delete(goods, number);
    save();
    destruct(disco);

    return 1;
}

// �R���I�����~��
int get_goods(object who, int number)
{
    object item;

    // �S���o�Ӱӫ~�s��
    if( undefinedp(goods[number]) ) {
        tell_object(who, "�S���o�Ӱӫ~�s���C\n");
        return 0;
    }
    if( !wizardp(who) ) {
        tell_object(who, "���O�Ův����N�I�����~�����C\n");
        return 0;
    }
    // ���ݭn�ٵ��Ův�A�����q�C���R��
    map_delete(goods, number);

    save();
    return 1;
}
