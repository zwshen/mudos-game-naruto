#include <ansi.h>
inherit ROOM;

string do_list()
{
    int index, size;
    string msg;

    msg  = "╭─────────────────────────╮\n";
    msg += "│使用說明：    　　　　　　　　　　　　　　　　　　│\n";
    msg += "├─────────────────────────┤\n";
    msg += "│1.放入武器(putwp) - 只有少數武器才能放入  　　　　│\n";
    msg += "│2.放進材料(materials) - 分為煤礦、鐵礦和銅礦      │\n";
    msg += "│3.開始鑄造(found) - 必須有材料包和先前放置之物品  │\n";
    msg += "│4.領取武器(getwp) - 製程前會連材料一同取出        │\n";
    msg += "├─────────────────────────┤\n";
    msg += "│ps.有人在鑄造時不能重複使用           　　　　　　│\n";
    msg += "│ps.加工材料搭配與武器傷害能力有關     　　　　　　│\n";
    msg += "│ps.每種可加工武器都有自己的搭配模式   　　　　　　│\n";
    msg += "│ps.製造完成或是不想製造記得將武器取出方便他人使用 │\n";
    msg += "│ps.各種材料都有最高上限，機器存放槽不是四度空間袋 │\n";
    msg += "│ps.希望大家使用愉快                   　　　　　　│\n";
    msg += "╰─────────────────────────╯\n";

    return msg;
}

object found;

void create()
{
        set("short", HIR"加工合成屋"NOR);
        set("long", @LONG
充滿著廢油味和生鏽鐵味，四周牆壁都被燒的火紅，要是稍微不
注意在屋子裡待太久，小心中暑喔！牆壁上掛著一張白鋼製的看板，
經過了常久的燒灼依然白亮如新，可見這製造的手法肯定與眾不同。
上面寫了一些使用的規則(paper)。
LONG);
    set("exits", ([
        "east" : "/u/b/byron/workroom.c",
    ]));
    set("detail", ([
        "paper": (: do_list :),
    ]));
    set("objects", ([
        __DIR__"item/box.c" : 1,
    ]));
    setup();
}
void init()
{
    add_action("do_putwp", "putwp");
    add_action("do_materials", "materials");
    add_action("do_found", "found");
    add_action("do_getwp", "getwp");
    add_action("do_no", "drop");
    add_action("do_no", "put");
    add_action("do_no", "get");
}
int do_putwp()
{
    object box;
    if( box = present("_WP_BOX_", environment(this_player())) ) {
        if( objectp(found = present("_FOUNDER_WP_", this_player())) ) {
            if( found->query("founder") >= 1 ) return notify_fail("這把武器已經鑄造過了。\n");
            if( found->query("equipped") ) return notify_fail("你不能將裝備中的武器放進置物箱。\n");
            if( found->query("keep_this") ) return notify_fail("必須解除保護狀態才能放置武器。\n");
            if( !query("founder") ) set("founder", this_player()->query("id"));
            else return notify_fail("裡面已經有一把武器等著鑄造了。\n");

            message_vision("$N將身上的$n放進鍋爐中準備加熱鑄造。\n"NOR, this_player(), found);
            found->move(box);
            return 1;
        } return notify_fail("你身上沒有適合的武器能放進置物箱鑄造。\n");
    } return notify_fail("這裡似乎沒有置物箱可以給你放武器。\n");
}

int do_getwp()
{
    object box, item;
    int a, b, c, i;
    if( box = present("_WP_BOX_", environment(this_player())) ) {
        if( objectp(found = present("_FOUNDER_WP_", box)) ) {
            if( !wizardp(this_player()) ) {
                if( query("founder") != this_player()->query("id") ) return notify_fail("置物箱裡的東西又不是你的，想做什麼阿。\n");
            }
            if( query("run_found") >= 1 ) {
                if( this_player()->query_condition("founder") != 0 ) return notify_fail("武器還在製造中，請稍等。\n");

                if( found->query("coal_need") ) a = query("coal_in")/found->query("coal_need");
                else a = 0;
                if( found->query("iron_need") ) b = query("iron_in")/found->query("iron_need");
                else b = 0;
                if( found->query("copper_need") ) c = query("copper_in")/found->query("copper_need");
                else c = 0;

                i = 0;
                if( a != 0 ) i += a;
                if( b != 0 ) i += b;
                if( c != 0 ) i += c;
                i = i/3;

                switch( i ) {
                    case 19:
                    case 1: i=1;found->setup_weapon(5+random(10), 15+random(10), 100, 1); break;

                    case 18:
                    case 2: i=2;found->setup_weapon(10+random(10), 20+random(10), 100, 1); break;

                    case 17:
                    case 3: i=3;found->setup_weapon(15+random(15), 30+random(20), 100, 1); break;

                    case 16:
                    case 4: i=4;found->setup_weapon(20+random(15), 35+random(25), 100, 1); break;

                    case 15:
                    case 5: i=5;found->setup_weapon(30+random(20), 50+random(30), 100, 1); break;

                    case 14:
                    case 6: i=6;found->setup_weapon(30+random(30), 60+random(40), 100, 1); break;

                    case 13:
                    case 7: i=7;found->setup_weapon(50+random(30), 80+random(40), 100, 1); break;

                    case 12:
                    case 8: i=8;found->setup_weapon(70+random(30), 100+random(50), 100, 1); break;

                    case 11:
                    case 9: i=9;found->setup_weapon(100+random(30), 120+random(50), 100, 1); break;

                    case 10: i=10;found->setup_weapon(120+random(30), 150+random(50), 100, 1); break;

                    case 0: 
                    default: i=0;found->setup_weapon(1+random(5), 5+random(10), 100, 1); break;
                }
                found->set("name", HIY"(+"+i+")"NOR" "+found->query("name")+"");
                message_vision(HIR"$N按下了啟動的按鈕，將待鑄的武器送入鍋爐中進行加工融合。\n"NOR, this_player());
                message_vision(CYN"滋滋聲從爐中傳出，似乎武器就快完成了。\n"NOR, this_player());
                message_vision("\n$N抱著期待的心情打開鍋門，取出了自己精心製作的武器$n。\n"NOR, this_player(), found);
                found->set("founder",1);
                if( found->move(this_player()) ) {
                    item = new(__DIR__"item/residue.c");
                    item->add_amount(i*15+random(80));
                    if( item->move(this_player()) ) {
                        tell_object(this_player(), "(離開前請將廢棄物也帶離。)\n"NOR);
                    } else {
                        tell_object(this_player(), "(因為身上太重了，廢棄物噴了滿地。)\n"NOR);
                        destruct(item);
                    }
                    item = new(__DIR__"item/scrap.c");
                    item->add_amount(i);
                    if( item->move(this_player()) ) {
                        tell_object(this_player(), "(離開前請將廢油也帶離銷毀。)\n"NOR);
                    } else {
                        tell_object(this_player(), "(因為身上太重了，廢油整桶打翻在地上。)\n"NOR);
                        destruct(item);
                    }
                } else {
                    tell_object(this_player(), HIY"你身上太重了，拿不動這樣武器。\n"NOR);
                    return 1;
                }
                delete("founder");
                delete("run_found");
                delete("coal_in");
                delete("iron_in");
                delete("copper_in");
                return 1;
            }
            message_vision("$N還是決定不鑄造了，將武器材料全都取了出來。\n"NOR, this_player(), found);
            found->move(this_player());

            if( query("coal_in") >= 1 ) {
                if( file_size(__DIR__"item/coal.c") < 0 ) return 0;
                if( catch(item = new(__DIR__"item/coal.c")) ) return 0;
                item->add_amount(query("coal_in")-1);
                item->move(this_player());
                delete("coal_in");
            }
            if( query("iron_in") >= 1 ) {
                if( file_size(__DIR__"item/iron.c") < 0 ) return 0;
                if( catch(item = new(__DIR__"item/iron.c")) ) return 0;
                item->add_amount(query("iron_in")-1);
                item->move(this_player());
                delete("iron_in");
            }
            if( query("copper_in") >= 1 ) {
                if( file_size(__DIR__"item/copper.c") < 0 ) return 0;
                if( catch(item = new(__DIR__"item/copper.c")) ) return 0;
                item->add_amount(query("copper_in")-1);
                item->move(this_player());
                delete("copper_in");
            }
            delete("founder");
            delete("run_found");
            return 1;
        } return notify_fail("置物箱裡空空如也。\n");
    } return notify_fail("這裡似乎沒有置物箱可以給你拿武器。\n");
}

int do_found()
{
    mapping cnd = ([]);
    object bag;
    int i;

    if( !query("founder") ) return notify_fail("要放入武器才能進行鑄造。\n");
    if( query("founder") != this_player()->query("id") ) return notify_fail("似乎已經有別人在鑄造了。\n");
    if( query("run_found") >= 1 ) return notify_fail("武器正在鑄造中。\n");

    i = query("coal_in") + query("iron_in") + query("copper_in");
    if( objectp(bag = present("_WP_BAG_", this_player())) ) {
        message_vision("$N將材料包丟進鍋爐中關上厚重鍋門，小心翼翼地開始加熱鑄造。\n"NOR, this_player());
        destruct(bag);

        cnd["name"] = HIR+BLINK"鑄造中"NOR;
        cnd["duration"] = i;

        this_player()->set_condition("founder", cnd);
        set("run_found", 1);

        return 1;
    } return notify_fail("必須擁有材料包才能進行武器製作。\n");
}

int do_no()
{
    tell_object(this_player(), "這裡不能亂丟亂撿東西！\n"NOR);
    return 1;
}

int do_materials(string arg)
{
    object coal, iron, copper, me;
    int a, b, c;

    me = this_player();

    if( !arg || sscanf(arg, "%d %d %d", a, b, c) != 3 ) return notify_fail("現在鍋爐中有煤礦 "HIY+query("coal_in")+NOR" 顆、鐵礦 "HIY+query("iron_in")+NOR" 塊、銅礦 "HIY+query("copper_in")+NOR" 塊。。\n"HIR"指令格式：materials <煤量> <鐵量> <銅量>\n"NOR);
    if( query("founder") != me->query("id") ) return notify_fail("現在在鑄造的人似乎不是你，不能亂放東西進去。\n"NOR);
    if( query("run_found") >= 1 ) return notify_fail("武器正在鑄造中，不能臨時加入材料。\n");

    if( a > 0 ) {
        if( objectp(coal = present("_COAL_", me)) ) {
            if( a > 1000 ) a = 1000;
            if( coal->query_amount() >= a ) {
                message_vision("$N拿出了"+chinese_number(a)+"顆煤礦放進鍋爐中。\n"NOR, me);
                coal->add_amount(-a);

                if( !query("coal_in") ) set("coal_in", a);
                else add("coal_in", a);

                if( !coal->query_amount() ) destruct(coal);
            } else {
                tell_object(me, "你身上的煤礦材料不夠！\n"NOR);
            }
        } else {
            tell_object(me, "你身上根本沒有煤礦！\n"NOR);
        }
    } else {
        tell_object(me, "你決定不放煤礦了。\n"NOR);
    }
    if( b > 0 ) {
        if( objectp(iron = present("_IRON_", me)) ) {
            if( b > 1000 ) b = 1000;
            if( iron->query_amount() >= b ) {
                message_vision("$N拿出了"+chinese_number(b)+"塊鐵礦放進鍋爐中。\n"NOR, me);
                iron->add_amount(-b);

                if( !query("iron_in") ) set("iron_in", b);
                else add("iron_in", b);

                if( !iron->query_amount() ) destruct(iron);
            } else {
                tell_object(me, "你身上的鐵礦材料不夠！\n"NOR);
            }
        } else {
            tell_object(me, "你身上根本沒有鐵礦！\n"NOR);
        }
    } else {
        tell_object(me, "你決定不放鐵礦了。\n"NOR);
    }
    if( c > 0 ) {
        if( objectp(copper = present("_COPPER_", me)) ) {
            if( c > 500 ) c = 500;
            if( copper->query_amount() >= c ) {
                message_vision("$N拿出了"+chinese_number(c)+"塊銅礦放進鍋爐中。\n"NOR, me);
                copper->add_amount(-c);

                if( !query("copper_in") ) set("copper_in", c);
                else add("copper_in", c);

                if( !copper->query_amount() ) destruct(copper);
            } else {
                tell_object(me, "你身上的銅礦材料不夠！\n"NOR);
            }
        } else {
            tell_object(me, "你身上根本沒有銅礦！\n"NOR);
        }
    } else {
        tell_object(me, "你決定不放銅礦了。\n"NOR);
    }
    return 1;
}
