#include <npc.h>
#include <ansi.h>

void create()
{
    set_name("林阿罵", ({ "lin ama", "ama" }) );
    set_level(10);
    set_race("human");
    set("age", 21);
    set("no_fight", 1);
    set("title", "收門票的");
    set("long", "一臉老實樣的青年，似乎完全不懂什麼叫人世險惡。\n");
    set("guard_exit", ({ "north" })); // 守著出口
    setup();
}
int do_guard_exit(int x, int y, string exit)
{
    if( this_player()->query("guild") == "hunter" && this_player()->query_temp("gomagic") != 1 ) {
        message_vision(CYN"$n仔細的盤查了$N，連身上的每根毛都不放過。\n"NOR, this_player(), this_object());
        message_vision("$n說道："HIG"原來是"+this_player()->rank()+this_player()->query("name")+"阿！我們團長說獵人可以免費入場，請進！\n"NOR, this_player(), this_object());
        this_player()->set_temp("gomagic", 1);
    }
    if( this_player()->query_temp("gomagic") != 1) {
        message_vision(CYN"$n仔細的盤查了$N，連身上的每根毛都不放過。\n"NOR, this_player(), this_object());
        message_vision("$n伸手一拉機關整個大門關了起來。\n", this_player(), this_object());
        do_chat((: command, "say 管"+this_player()->query("name")+HIG"是什麼職業！想「進去」就得付費！"NOR:));
        return 1;
    }
    return 0;
}
private void goin(string arg, object me)
{
    if( arg != "" ) {
        if( arg[0] == 'y' || arg[0] == 'Y' ) {
            if( this_player()->query("bank") < 5000 ) {
                tell_object(me, "\n林阿罵瞪大眼睛說道："HIG"哇靠！沒錢還來什麼馬戲團！回家睡覺去吧！\n"NOR);
                return;
            }
            tell_object(me, HIY"\n(銀行匯了五千兩銀子到魔術馬戲團的專用戶頭中)\n"NOR);
            tell_object(me, "林阿罵點頭說道："HIG"謝謝惠顧！這位大爺請進！\n\n"NOR);
            this_player()->set_temp("gomagic", 1);
            this_player()->add("bank", -5000);
            return;
        } else if( arg[0] == 'N' || arg[0] == 'n' ) {
            tell_object(me, HIW"\n你心裡一想：哇靠！有沒有這麼貴！真是林阿罵！\n\n"NOR);
            return;
        }
    }
    tell_object(me, "林阿罵說道："HIG"入場門票是五千兩銀子！"HIW"要去嗎？(Y/n)"NOR);
    input_to("goin", me);
    return;
}
// 當char用say指令時，此mob的回應
int relay_say(object me, string arg)
{
    if( arg == "進去" ) {
        if( !userp(me) ) return 0;
        if( me->query("guild") == "hunter" ) {
            tell_object(me, "林阿罵說道："HIG"這位"+me->rank()+"可以直接入場喔！\n"NOR);
        } else {
            tell_object(me, "林阿罵說道："HIG"入場門票是五千兩銀子！"HIW"要去嗎？(Y/n)"NOR);
            input_to("goin", me);
            return notify_fail("");
        }
    }
    return 1;
}
