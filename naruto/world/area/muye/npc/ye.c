#include <npc.h>
#include <ansi.h>

inherit F_FIGHTER;

void random_fly()
{
    object area;
    int i;
    string area_file = "/world/area/muye/muye.c";

    i = random(49);

    if( !objectp(area = load_object(area_file)) ) return 0;
    message_vision(CYN"$N好像發現了什麼，一溜煙地就不見了。\n"NOR, this_object());

    if( !area_move(area, this_object(), i, i) ) {
        message_vision(CYN"但是不到一秒$N又偷偷摸摸地出現在附近。\n"NOR, this_object());
        return;
    }
    message_vision(CYN"一陣狂風而過，$N忽然出現在旁邊。\n"NOR, this_object());
    return;
}
void create()
{
    set_name("自來也", ({ "zi lai ye", "ye" }));
    set_race("human");
    set_level(80);
    set("camp", "muye");
    set("long", "傳說中的三忍之一，因為相當好色所以鳴人叫稱他為好色仙人，你可\n"
                "以看到他手舞足蹈的似乎因為找到尋找他寫小說素材的好地方了。\n");

    set("title", "三忍");
    set("nickname", "好色仙人");
    set("age", 52);
    set("gender", "male");
    
    // 一般時動作
    set("chat_chance", 10);
    set("chat_msg", ({
        (: command, "say 素材素材！哈哈！到處逛找素材！" :),
        (: random_fly :),
    }) );
    setup();
}
void relay_say(object ob, string arg)
{
    object item, pol;

    if( arg == "素材" )  {
        do_chat(({
            (: command, "?" :),
            (: command, "say 尋找素材是很神聖的事情。" :),
            (: command, "say 這可是攸關親熱天堂「續集」的內容。" :),
            (: command, "say 為了我廣大的讀者，也只好拼了！" :),
            (: command, "snicker" :),
        }));
        return;
    }
    if( arg == "續集" )  {
        do_chat(({
            (: command, "stare " + this_player()->query("id") :),
            (: command, "say 急什麼，等正式出版再買就好了。" :),
            (: command, "say 雖然我現在素材量不太足夠..." :),
            (: command, "say 如果肯「幫忙」，我可能會考慮看看..." :),
        }));
        return;
    }
    if( arg == "幫忙" )  {
        if( objectp(pol = present("__POL__", this_player())) ) {
            message_vision("$N疑惑地說道："HIG"身上還有拍立得又要幫忙？照片快拿來拉！\n"NOR, this_object());
            return;
        }
        do_chat(({
            (: command, "hmm" :),
            (: command, "say 既然這樣！這台拍立得就借給" + this_player()->query("name") + "用，不過底片只剩五張。" :),
            (: command, "say 去拍三張美女的照片給我！" :),
        }));

        pol = new(__DIR__"obj/pol.c");

        if( pol->move(this_player()) ) tell_object(this_player(), HIY"(自來也給你一台" + pol->query("name") +"。)\n"NOR);
        else {
            if( environment(this_player())->is_area() ) move_side(pol, this_player());
            else pol->move(environment(this_player()));
            tell_object(this_player(), HIY"(自來也給你一台" + pol->query("name") + "，但是你身上太重，只好放在地上。)\n"NOR);
        }
        this_player()->set_temp("picquest", 3);
        return;
    }
}
int give_check(object ob)
{
    if( ob->id("__PIC__") ) return 1;   // 照片
    else return 0;
}
int accept_object(object me, object ob)
{
    object item, book;

    if( is_busy() ) {
        do_chat((: command, "say 急什麼！鑑定不用時間嗎！" :));
        return 0;
    }
    if( is_fighting() ) {
        do_chat((: command, "say 等我趕走他再專心鑑定！" :));
        return 0;
    }
    if( !me->query_temp("picquest") ) {
        message_vision("$N說道："HIG"$n沒事別來防礙我工作。\n"NOR, this_object(), me);
        return 0;
    }
    me->start_busy(3);
    this_object()->start_busy(5);
    switch( give_check(ob) ) {
        case 1:
            if( me->query_temp("picture/"+ob->query("id")) ) {
                message_vision("$N疑惑地說道："HIG"喂喂$n...這張照片剛才給過拉，想混水摸魚喔。\n"NOR, this_object(), me);
                return 0;
            }
            switch( ob->query("pic") ) {
                case 0: message_vision("$N奮怒地吼道："HIG""+me->query("name")+"我是要找親熱天堂的素材耶！給我靈異照片做啥！\n"NOR, this_object(), me);
                        return 0;
                        break;
                case 1: message_vision("$N色咪咪地說道："HIG"幹的不錯麻"+me->query("name")+"！很有天份喔！讓我來鑑定鑑定...\n"NOR, this_object(), me);
                        break;
                case 2: message_vision("$N說道："HIG"拍的是很帥氣啦...但是男性不要給我鑑定。\n"NOR, this_object(), me);
                        return 0;
                        break;
                case 3: do_chat(({
                            (: command, "say 嗯..我看看.." :),
                            (: command, "say 人獸大戰？好題材..." :),
                            (: command, "angry" :),
                            (: command, "say 搞什麼東西阿！給我女性照片就好！" :),
                        }));
                        return 0;
                        break;
            }
            if( me->query_temp("picquest") == 1 ) {
                message_vision("\n\n$N愉快地說道："HIG"$n幫了我這麼多忙，再不回饋一下說不過去。\n"NOR, this_object(), me);
                do_chat(({
                    (: command, "say 其實親熱天堂續集的素材我早就選好了。" :),
                    (: command, "snicker" :),
                    (: command, "say 這些資料就當做未來第三集用吧！" :),
                    (: command, "say 這本編輯讓我預覽的第二集就送你做紀念。" :),
                }));

                book = new(__DIR__"item/kiss_book2.c");

                if( book->move(me) ) tell_object(me, HIY"\n(自來也將"NOR+book->query("name")+NOR+HIY"交給了你。)\n\n"NOR);
                else {
                    if( environment(me)->is_area() ) move_side(book, me);
                    else book->move(environment(me));
                    tell_object(me, HIY"\n(自來也想將"NOR+book->query("name")+NOR+HIY"交給你，但是你身上太重，只好放在地上。)\n\n"NOR);
                }
                // 移除暫存的資料
                me->delete_temp("picquest");
                me->delete_temp("picture");
            } else {
                do_chat( ({
                   (: command, "nod" :),
                   (: command, "say 這張拍的不錯！繼續努力吧！" :),
                   ( : destruct , ob : ),
                }) );
                me->set_temp("picture/"+ob->query("id"), 1);
                me->add_temp("picquest", -1);
            }
            break;
        default:
            do_chat((: command, "say 不是照片給我幹麻！" :));
            return 0;
            break;
    }
    return 1;
}
int accept_fight(object me)
{
    tell_object(me, HIY"(自來也正在尋找素材完全無視你的存在。)\n\n"NOR);
    return 0;
}
int accept_kill(object me)
{
    remove_all_killer();
    me->remove_killer(this_object());
    tell_object(me, HIY"(自來也專注的尋找素材沒看到你，但你卻打不著他。)\n\n"NOR);
    return 1;
}
