/* write by -Acme- */

#include <room.h>

inherit BANK;

void create()
{
    set("short", "木葉銀行");

    set("long", @long
一間偌大的銀行，四周戒備相當森嚴，當你一走進來，四週人的
眼神全集中在你身上，好似要將你生吞活剝一般。銀行門口掛著一副
對聯是這樣子寫的「貸貸來借錢、代代去還錢」，看來你最好別跟銀
行借錢，要不然十輩子也還不完。
相關指令：[存錢] deposit <數量> <貨幣種類>
          [領錢] withdraw <數量> <貨幣種類>
          [匯錢] outward <人物> <數量>
long);

    set("exits", ([
        "north" : ([ "filename": __DIR__"muye.c",
                      "x_axis": 25,
                      "y_axis": 38,
                 ]),
    ]));

    setup();
}
