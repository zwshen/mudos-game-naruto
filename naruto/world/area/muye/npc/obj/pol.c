#include <ansi.h>
inherit ITEM;

int i=5;

void create()
{
    set_name("拍立得"NOR, ({ "polaroid", "pol", "__POL__" }));
    set("unit", "台");
    set("value", 0);
    set("no_box", 1);
    set("long", "照像機的一種，能夠立即將拍攝的內容顯現出來，十分方便。\n"
                "使用方法為(use pol to <某人>)，還剩餘"HIY"("+i+")"NOR"張軟片。\n");
    setup();
}

void do_use(object me, string arg)
{
    object obj, pic;

    if( !objectp(obj = present(arg, environment(me)))) {
        write("沒有這個人...\n");
        return;
    }
    if( me->is_busy() ) {
        write("你正在忙，沒辦法拍照。\n");
        return;
    }
    if( me->is_fighting() ) {
        write("戰鬥還分心拍照？\n");
        return;
    }
    if( i <= 0 ) {
        write("這台相機已經沒有軟片了。\n");
        return;
    }
    message_vision("\n$N拿起拍立得對準$n說道："HIG"要拍啦！笑一個！\n\n"NOR, me, obj);

    pic = new(__DIR__"picture.c");

    if( !objectp(pic) ) {
        write("這台像機好像固障了...\n");
        destruct(pic);
        return;
    }
    message_vision(CYN"$n立即反應擺了個美美的 Pose，噹噹噹！照片出爐啦！\n\n\n"NOR, me, obj);

    pic->set("name", obj->query("name")+pic->query("name"));
    pic->set("id", obj->query("id")+" "+pic->query("id"));

    if( !obj->is_character() || obj->is_corpse() ) {
        pic->set("long", "哇勒！你拍到靈異相片拉！"+obj->query("name")+"居然會擺 Pose！？\n");
        pic->set("pic", 0);
    } else if( obj->query("gender") == "female" && obj->query("race") == "human" ) {
        pic->set("long", obj->query("name")+"在照片上看起來十分誘人，拍的非常成功！\n");
        pic->set("pic", 1);
    } else if( obj->query("gender") == "male" && obj->query("race") == "human" ) {
        pic->set("long", obj->query("name")+"在照片上看起來英氣不凡，拍的非常成功！\n");
        pic->set("pic", 2);
    } else {
        pic->set("long", obj->query("name")+"在照片上看起來雄壯威武，拍的非常成功！\n");
        pic->set("pic", 3);
    }
    if( !pic->move(me) ) {
        write("你的身上太重了，沒辦法攜帶新的相片。\n");
        destruct(pic);
        return;
    }
    i--;
    set("long", "照像機的一種，能夠立即將拍攝的內容顯現出來，十分方便。\n"
                "使用方法為(use pol to <某人>)，還剩餘"HIY"("+i+")"NOR"張軟片。\n");

    return;
}
