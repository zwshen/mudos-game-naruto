#include <ansi.h>
#include <npc.h>
#include "bandit.h"

inherit F_SEABANDIT;

void create()
{
    set_name("人猿", ({ "pongo" }) );
    set_race("human");
    set_level(45);
    set("title",HIY"猿山連合"NOR);
    set("nickname",HIC"打撈王"NOR);
    set("gender", "male");
    set("class","thief_sea");
    set("camp", "robber");
    set("age", 35);
    set("long", "長的一臉猿猴樣，沒事就擺出猴樣吱吱叫。他身上穿著一件吊帶褲，\n"
                "上面畫著一隻猴子還有「打撈王」的字樣。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        (: command, "say 今天還沒有收獲阿！嗚吱吱！" :),
    }));
    set("set_drop", ({
        ([ "type":"obj", "id":28, "amount":2+random(4), "p1":30, "p2":100 ]),  // 黃金
        ([ "type":"eq", "id":101, "amount":1, "p1":1, "p2":100 ]),             // 吊帶褲
        ([ "type":"eq", "id":102, "amount":1, "p1":1, "p2":400 ]),             // 猿猴護腿
        ([ "type":"eq", "id":35, "amount":1, "p1":50, "p2":100 ]),             // 防風鏡
        ([ "type":"eq", "id":13, "amount":1, "p1":20, "p2":100 ]),             // 寫輪眼鏡
    }) );
    setup();
    add_temp("apply/attack", 100);
    add_temp("apply/armor", 300);
}
