#include <npc.h>

inherit F_VENDOR;

void create()
{
    set_name("豹哥", ({ "bow gr", "gr" }));
    set_race("human");
    set_level(60);
    set("age", 28);
    set("gender", "male");
    set("nickname","單手武器專賣");
    set("long", "排行老大，雙手靈巧，善於製作單手武器。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        (: command, "say 歡迎光臨！" :),
        (: command, "say 請隨便看看阿！" :),
    }));

    // 設定商人所販賣的物品
    // set_goods(代碼, 種類, 編號, 數量, 單價)
    // 商人能販賣的東西只能由 query 指令裡查 eq, wp, food 能查出來的物品
    // 如 set_goods(1, "food", 1, 10, -1) 表示販賣 query 指令查出來的food編號為1的食品十個
    // 若數量設定 -1 表示無限量供應
    // 若單價設為 -1 表示價錢是使用該物件設定的value
    // 代碼是用於 buy 指令上，如 buy 1 則會向商人買下代碼為1的商品

    set_goods(1, "wp", 10, 20, -1);    // 藤條
    set_goods(2, "wp", 3, 20, -1);     // 單刀
    set_goods(3, "wp", 2, 15, -1);     // 大刀
    set_goods(4, "wp", 7, 15, -1);     // 長劍
    set_goods(5, "wp", 8, 15, -1);     // 雙截棍
    set_goods(6, "wp", 45, 10, -1);    // 木劍
    set_goods(7, "wp", 41, 10, -1);    // 刺木刀
    set_goods(8, "wp", 35, 10, -1);    // 鐵勾
    set_goods(9, "wp", 34, 10, -1);    // 鐵刀
    set_goods(10, "wp", 38, 10, -1);   // 長勾鐵爪
    set_goods(11, "wp", 36, 10, -1);   // 刻紋劍
    set_goods(12, "wp", 30, 5, -1);    // 突擊戰刀
    set_goods(13, "wp", 40, 1, -1);    // 螺旋劍
    setup();
}
