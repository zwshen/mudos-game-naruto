#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name("�K�b", ({ "blade" }));
    set_weight(20000);
    setup_weapon(1, 10, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", "blade");
        set("unit", "��");
        set("value", 500);
        set("long", "�H���K�ҥ��y���M�A���O�ܺ�o�A�O�q���� �C");
    }
    setup();
}
