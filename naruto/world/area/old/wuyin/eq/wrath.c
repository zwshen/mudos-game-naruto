#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(YEL"����R���ë�"NOR, ({ "athena's wrath","wrath" }));
    set_weight(20000);
    setup_weapon(1, 99, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "��");
        set("value", 9999);
        set("long", "�@��������I�M�A�O�Ԫ��k������R�ҽ絹�̪L���Z���A�ݨӥ�
���n���~���o�ʡC");
    }

    set("apply_weapon/twohanded blade", 
        ([ "str" : 20,            // �ݩʡG�O�q
           "con" : 20,            // �ݩʡG���
           "int" : 20,            // �ݩʡG���z
           "dex" : 20,            // �ݩʡG�ӱ�
           "attack" : 9999,         // �����O�q
           "defend" : 9999,         // ���m�O�q
           "exact" : 99,          // �R���v
           "evade" : 99,          // �j�ײv
           "intimidate" : 99,     // ������O
           "wittiness" : 99,      // ���m��O
           "move" : 99,           // ���ʤO
           "carriage" : 9999,    // �t����O
    ]) );
    setup();
}
