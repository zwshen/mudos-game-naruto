#include <ansi.h>
#include <weapon.h>

inherit F_WEAPON;

void create()
{
    set_name(YEL"雅典娜的岔怒"NOR, ({ "athena's wrath","wrath" }));
    set_weight(20000);
    setup_weapon(1, 99, 100, 1);
    
    if( !clonep() ) {
        set("wield_as", "twohanded blade");
        set("unit", "把");
        set("value", 9999);
        set("long", "一把長型的鐮刀，是戰爭女神雅典娜所賜給依林的武器，看來必
須要兩手才拿得動。");
    }

    set("apply_weapon/twohanded blade", 
        ([ "str" : 20,            // 屬性：力量
           "con" : 20,            // 屬性：體格
           "int" : 20,            // 屬性：智慧
           "dex" : 20,            // 屬性：敏捷
           "attack" : 9999,         // 攻擊力量
           "defend" : 9999,         // 防禦力量
           "exact" : 99,          // 命中率
           "evade" : 99,          // 迴避率
           "intimidate" : 99,     // 攻擊能力
           "wittiness" : 99,      // 防禦能力
           "move" : 99,           // 移動力
           "carriage" : 9999,    // 負重能力
    ]) );
    setup();
}
