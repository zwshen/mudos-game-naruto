#include <npc.h>
#include <ansi.h>

inherit F_VENDOR;

void create()
{
    set_name("豹可", ({ "bow kr", "kr" }));
    set_race("human");
    set_level(60);
    set("age", 25);
    set("gender", "male");
    set("nickname","雙手武器專賣");
    set("long", "排行老二，力大如牛，負責雙手武器的製做。\n");
    set("camp", "bow");
    set("chat_chance", 5);
    set("chat_msg", ({
        (: command, "sweat" :),
        CYN"豹可揮汗如雨的不停敲打武器。\n"NOR,
    }));

    // 設定商人所販賣的物品
    // set_goods(代碼, 種類, 編號, 數量, 單價)
    // 商人能販賣的東西只能由 query 指令裡查 eq, wp, food 能查出來的物品
    // 如 set_goods(1, "food", 1, 10, -1) 表示販賣 query 指令查出來的food編號為1的食品十個
    // 若數量設定 -1 表示無限量供應
    // 若單價設為 -1 表示價錢是使用該物件設定的value
    // 代碼是用於 buy 指令上，如 buy 1 則會向商人買下代碼為1的商品

    set_goods(1, "wp", 6, 20, -1);     // 雙刃斧
    set_goods(2, "wp", 1, 20, -1);     // 大斧
    set_goods(3, "wp", 4, 15, -1);     // 殺豬刀
    set_goods(4, "wp", 12, 15, -1);    // 砍馬大刀
    set_goods(5, "wp", 33, 10, -1);    // 大木棒
    set_goods(6, "wp", 31, 10, -1);    // 斧頭
    set_goods(7, "wp", 44, 10, -1);    // 迴旋斧
    set_goods(8, "wp", 43, 10, -1);    // 刺木棒
    set_goods(9, "wp", 42, 10, -1);    // 刺木槍
    set_goods(10, "wp", 39, 10, -1);   // 軟槍
    set_goods(11, "wp", 32, 5, -1);    // 巨斧
    set_goods(12, "wp", 37, 1, -1);    // 長柄砍斧

    setup();
}
