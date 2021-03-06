#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;
inherit F_VENDOR;

void create()
{
    set_name("瓦傑", ({ "wa jie", "jie", "wa" }));
    set_race("human");
    set_level(50);
    set("age", 25);
    set("title", HIR"ＣＰ７"NOR);
    set_class("guard_sea");  // 海軍校衛
    set("long", "海軍成員，不但是個廚師而且自稱是武術高手。目前的工作是被派來\n"
                "司法島擔任販賣藥品的任務，不過瓦傑還是不忘記自己廚師的身份，\n"
                "不停的用鼻子噴出義大利麵打算賣給海兵吃。\n");

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
    set_goods(19, "food", 64, -1, -1);
    set_goods(20, "food", 10, -1, -1);
    set_goods(21, "food", 11, 50, -1);

    setup();
}
