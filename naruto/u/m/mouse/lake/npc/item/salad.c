#include <ansi.h>

inherit F_FOOD;

void create()
{
    set_name(HIR"龍蝦沙拉"NOR, ({ "salad" }));
    if( !clonep() ) {
        set("base_unit", "盤");
        set("unit", "盤");
        set("base_value", 100);
        set("base_weight", 500);
        set("food_stuff", 20);
        set("long", "新鮮的龍蝦搭配馬鈴薯沙拉，價格昂貴深受有錢人喜愛。\n");
    }
    setup();
}
