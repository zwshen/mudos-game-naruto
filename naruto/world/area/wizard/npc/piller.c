#include <npc.h>

inherit F_VENDOR;

void create()
{
    set_name("藥大師", ({ "pill master", "master" }));
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

    set_goods(1, "food", 1, -1, -1);
    set_goods(2, "food", 2, -1, -1);
    set_goods(3, "food", 3, -1, -1);
    set_goods(4, "food", 4, -1, -1);
    set_goods(5, "food", 5, -1, -1);
    set_goods(6, "food", 6, -1, -1);
    set_goods(7, "food", 7, -1, -1);
    set_goods(8, "food", 8, -1, -1);
    set_goods(9, "food", 9, -1, -1);
    set_goods(10, "food", 12, -1, -1);
    set_goods(11, "food", 13, -1, -1);
    set_goods(12, "food", 14, -1, -1);
    set_goods(13, "food", 15, -1, -1);
    set_goods(14, "food", 16, -1, -1);
    set_goods(15, "food", 17, -1, -1);
    set_goods(16, "food", 18, -1, -1);
    set_goods(17, "food", 19, -1, -1);
    set_goods(18, "food", 20, -1, -1);

    setup();
}
