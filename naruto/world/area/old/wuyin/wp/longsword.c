#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name("�Ӫ��C", ({ "long sword","sword"}));
    set_weight(200);
    setup_weapon(1, 10, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", "sword");
        set("unit", "��");
        set("value", 500);
        set("long", "����²�K���C�A������a�A�����ˤO�������C");
    }
    setup();
}
