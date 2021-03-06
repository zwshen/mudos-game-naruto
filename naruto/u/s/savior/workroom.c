#include <ansi.h>
#include <room.h>

inherit INN;

void create()
{
    set("short", "羊圈");
    set("long", "冷冽的寒風從臉上呼嘯而過，讓人不禁抖起陣陣寒顫，寒風中還夾帶著
濃郁的羊屎味讓人久久不能言語。這片廣大的草原四周地型平緩，草原上圈
起了一道圍籬，一條小溪穿過圍籬轉而流向東方。這個附著著美麗紋路的木
質圍籬圈養了一群溫馴的羔子，在羊圈的中心有一顆大樹，樹下放著一台電
子琴，有興趣的可以去試試。 \n");
    set("exits", ([
        "wizard" : "/world/area/wizard/guildhall.c", 
    ]));
    setup();
    load_object("/daemon/board/savior");
}
