#include <npc.h>

inherit F_VENDOR;

void create()
{
    set_name("泡湯老闆", ({ "pool boss", "boss" }));
    set_race("human");
    set_level(50);
    set("age", random(50)+18);
    set("camp", "muye");
    set("long", "他是泡溫泉的老闆，看起來和藹可親。\n");

    // 設定商人所販賣的物品
    // set_goods(代碼, 種類, 編號, 數量, 單價)
    // 商人能販賣的東西只能由 query 指令裡查 eq, wp, food 能查出來的物品
    // 如 set_goods(1, "food", 1, 10, -1) 表示販賣 query 指令查出來的food編號為1的食品十個
    // 若數量設定 -1 表示無限量供應
    // 若單價設為 -1 表示價錢是使用該物件設定的value
    // 代碼是用於 buy 指令上，如 buy 1 則會向商人買下代碼為1的商品

    setup();
}
