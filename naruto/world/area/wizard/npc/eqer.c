#include <npc.h>

inherit F_VENDOR;

void create()
{
    set_name("防大師", ({ "armor master", "master" }));
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

    set_goods(1, "eq", 1, 10, -1);
    set_goods(2, "eq", 2, 10, -1);
    set_goods(3, "eq", 3, 10, -1);
    set_goods(4, "eq", 4, 10, -1);
    set_goods(5, "eq", 5, 10, -1);
    set_goods(6, "eq", 6, 10, -1);
    set_goods(7, "eq", 7, 10, -1);
    set_goods(8, "eq", 8, 10, -1);
    set_goods(9, "eq", 9, 10, -1);
    set_goods(10, "eq", 10, 10, -1);
    set_goods(11, "eq", 11, 10, -1);
    set_goods(12, "eq", 12, 10, -1);
    set_goods(13, "eq", 13, 10, -1);
    set_goods(14, "eq", 14, 10, -1);
    set_goods(15, "eq", 15, 10, -1);
    set_goods(16, "eq", 16, 10, -1);
    set_goods(17, "eq", 17, 10, -1);
    set_goods(18, "eq", 18, 10, -1);
    set_goods(19, "eq", 19, 10, -1);
    set_goods(20, "eq", 20, 10, -1);
    set_goods(21, "eq", 21, 10, -1);
    set_goods(22, "eq", 22, 10, -1);
    set_goods(23, "eq", 23, 10, -1);
    set_goods(24, "eq", 24, 10, -1);
    set_goods(25, "eq", 25, 10, -1);

    setup();
}
