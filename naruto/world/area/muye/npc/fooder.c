#include <ansi.h>
#include <npc.h>

inherit F_VENDOR;

void create()
{
    set_name("拉麵店老闆", ({ "noodles boss", "boss" }));
    set_race("human");
    set_level(50);
    set("age", random(50)+18);
    set("camp", "muye");
    set("long", "他是「一樂拉麵」的老闆，看起來和藹可親。\n");

    // 設定商人所販賣的物品
    // set_goods(代碼, 種類, 編號, 數量, 單價)
    // 商人能販賣的東西只能由 query 指令裡查 eq, wp, food 能查出來的物品
    // 如 set_goods(1, "food", 1, 10, -1) 表示販賣 query 指令查出來的food編號為1的食品十個
    // 若數量設定 -1 表示無限量供應
    // 若單價設為 -1 表示價錢是使用該物件設定的value
    // 代碼是用於 buy 指令上，如 buy 1 則會向商人買下代碼為1的商品

    set_goods(1, "food", 10, 50, -1);
    set_goods(2, "food", 11, 50, -1);

    setup();
}

// 當char用say指令時，此mob的回應
int relay_say(object me, string arg)
{
    if( !objectp(me) || !stringp(arg) ) return 0;
    if( arg == "項鍊" ) {
        command("say 你是說牆上的那個項鍊啊，那是在古老森林裡的祭師送給我的。");
    }
    return 1;
}
