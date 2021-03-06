#include <npc.h>

inherit F_VENDOR;

void create()
{
    set_name("術大師", ({ "skill master", "master" }));
    set_race("human");
    set_level(50);
    set("age", random(50)+18);

    set("long", "無奸不成商，十足的奸商樣的老奸商人。\n");

    // 設定商人所販賣的物品
    // set_goods(代碼, 種類, 編號, 數量, 單價)
    // 商人能販賣的東西只能由 query 指令裡查 eq, wp, food 能查出來的物品
    // 如 set_goods(1, "food", 1, 10, -1) 表示販賣 query 指令查出來的food編號為1的食品十個
    // 若數量設定 -1 表示無限量供應
    // 若單價設為 -1 表示價錢是使用該物件設定的value
    // 代碼是用於 buy 指令上，如 buy 1 則會向商人買下代碼為1的商品

    set_goods(1, "obj", 1, 10, 50000);
    set_goods(2, "obj", 4, 10, 50000);
    set_goods(3, "obj", 6, 10, 50000);
    set_goods(4, "obj", 8, 10, 50000);
    set_goods(5, "obj", 2, 10, 200000);
    set_goods(6, "obj", 3, 10, 200000);
    set_goods(7, "obj", 5, 10, 200000);
    set_goods(8, "obj", 7, 10, 200000);
    set_goods(9, "obj", 14, 10, 50000);
    set_goods(10, "obj", 15, 10, 50000);
    set_goods(11, "obj", 18, 10, 50000);
    set_goods(12, "obj", 19, 10, 50000);
    set_goods(13, "obj", 20, 10, 200000);
    set_goods(14, "obj", 21, 10, 200000);
    set_goods(15, "obj", 16, 10, 200000);
    set_goods(16, "obj", 17, 10, 200000);
    set_goods(17, "obj", 83, 10, 1000000);
    set_goods(18, "obj", 84, 10, 1000000);
    set_goods(19, "obj", 85, 10, 1000000);
    set_goods(20, "obj", 86, 10, 1000000);
    set_goods(21, "obj", 10, 10, 200000);
    set_goods(22, "obj", 11, 10, 50000);
    set_goods(23, "obj", 12, 10, 100000);
    set_goods(24, "obj", 75, 10, 100000);
    set_goods(25, "obj", 91, 10, 430000);
    set_goods(26, "obj", 93, 10, 75000);
//    set_goods(17, "obj", 10, 50, -1);
//    set_goods(18, "obj", 11, 50, -1);
//    set_goods(19, "obj", 12, 50, -1);
//    set_goods(20, "obj", 75, 10, -1);



    setup();
}
