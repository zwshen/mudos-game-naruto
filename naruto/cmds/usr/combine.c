#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string str1, str2, type, *kk;
    object book, eq;
    mapping effect;

    if( me->is_busy() ) return notify_fail("你現在沒有空。\n");
    if( !arg || arg=="" ) return notify_fail("指令格式：combine <卷軸> with <武器/防具>\n");

    if( sscanf(arg, "%s with %s", str1, str2) != 2 ) 
        return notify_fail("指令格式：combine <卷軸> with <武器/防具>\n");

    book = present(str1, me);
    if( !book ) return notify_fail("你身上沒有這種卷軸...\n");

    if( !mapp(effect = book->query("effect")) )
        return notify_fail("這個不是用來強化裝備的卷軸...\n");

    eq = present(str2, me);
    if( !eq ) return notify_fail("你身上沒有這種裝備...\n");

    if( eq->query("no_combine") >= 1 ) 
        return notify_fail("這樣物品不能進行強化。\n");

    if( eq->query("equipped") ) 
        return notify_fail("你必須先把這個裝備卸除才能進行強化。\n");

    switch( effect["type"] ) {
        case "EQ":
            if( !eq->is_armor() ) return notify_fail("防卷只能使用在防具上面。\n");
            if( eq->query("changed") >= 3 ) return notify_fail("這件防具已經無法使用任何卷軸了。\n");

            message_vision(HIW"$N將 $n "HIW"放在胯下夾著且嘴裡唸唸有辭，雙手胡亂比劃...\n"NOR, me, book);
            
            destruct(book);

            eq->add("changed", 1);

            // 先跑機率
            if( random(100) >= effect["success"] ) {
                message_vision("好像什麼事情也沒發生...\n", me);
                return 1;
            } else message_vision(HIY"瞬間 $N "HIY"散出七彩光芒，閃閃動人...\n"NOR, eq);

            eq->add("success", 1);
            eq->set("apply_armor", eq->query("apply_armor") );

            if( sscanf(eq->query("name"), "%s %s", str1, str2) == 2 ) {
                eq->set("name", HIY"(+" + eq->query("success") + ") "NOR + str2 );
            } else eq->set("name", HIY"(+" + eq->query("success") + ") "NOR + eq->query("name") );

            type = eq->query("wear_as");

            foreach( str1 in keys(effect) ) {
                if( str1 == "type" || str1 == "success" ) continue;
                eq->add("apply_armor/" + type + "/" + str1, effect[str1]);
            }

            break;
        case "WP":
            if( !eq->is_weapon() ) return notify_fail("武卷只能使用在武器上面。\n");
            if( eq->query("changed") >= 10 ) return notify_fail("這把武器已經無法使用任何卷軸了。\n");

            message_vision(HIW"$N將 $n "HIW"放在胯下夾著且嘴裡唸唸有辭，雙手胡亂比劃...\n"NOR, me, book);
            
            destruct(book);

            eq->add("changed", 1);

            // 先跑機率
            if( random(100) >= effect["success"] ) {
                message_vision("好像什麼事情也沒發生...\n", me);
                return 1;
            } else message_vision(HIY"瞬間 $N "HIY"散出七彩光芒，閃閃動人...\n"NOR, eq);

            eq->add("success", 1);

            if( sscanf(eq->query("name"), "%s %s", str1, str2) == 2 ) {
                eq->set("name", HIY"(+" + eq->query("success") + ") "NOR + str2 );
            } else eq->set("name", HIY"(+" + eq->query("success") + ") "NOR + eq->query("name") );

            eq->set("apply_weapon", eq->query("apply_weapon") );

            kk = eq->query("wield_as");
            foreach( str1 in kk ) {
                foreach( str2 in keys(effect) ) {
                    if( str2 == "type" || str2 == "success" ) continue;
                    eq->add("apply_weapon/" + str1 + "/" + str2, effect[str2]);
                }
            }

            break;
        default:
            return notify_fail("這個卷軸有問題，看來無法使用...\n");
            break;
    }

    if( objectp(eq=find_object(base_name(eq))) ) destruct(eq);
    return 1;
}

int help()
{
    write(@TEXT
指令格式：combine <卷軸> with <武器/防具>

這個指令可以利用卷軸來強化你的武器或防具。
TEXT);
    return 1;
}
