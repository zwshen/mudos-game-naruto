/* testpaper.c 下忍考試卷 write by -Acme- */

inherit ITEM;

mapping test = ([
    1: ([ "msg": "在火影忍者世界中，最大的忍者村是？\n"
                 "           (1) 音隱村\n"
                 "           (2) 霧隱村\n"
                 "           (3) 木葉村\n"
                 "           (4) 砂隱村\n",
          "correct": 3,
          "answer": 0,
       ]),
    2: ([ "msg": "忍者村中通常會設立暗部組織，通常是用來？\n"
                 "           (1) 搞笑用\n"
                 "           (2) 從事間碟、暗殺、追殺叛忍\n"
                 "           (3) 忍術指導組織\n"
                 "           (4) 保護村民\n",
          "correct": 2,
          "answer": 0,
       ]),
    3: ([ "msg": "忍書「臨兵鬥者皆陣列在前」 的 \"在\" 該如何用雙手來使用咒印？\n"
                 "           (1) 五指柔柔分開 雙手拇指與食指圍成圓形\n"
                 "           (2) 食指 中指 拇指\n"
                 "           (3) 食指 拇指 小拇指\n"
                 "           (4) 右手 食指 左手 握住食指\n",
          "correct": 1,
          "answer": 0,
       ]),
    4: ([ "msg": "什麼是查克拉？\n"
                 "           (1) 是一種食物\n"
                 "           (2) 使用忍術、幻術的能量源\n"
                 "           (3) 錢幣的單位\n"
                 "           (4) 是一種組織\n",
          "correct": 2,
          "answer": 0,
       ]),
    5: ([ "msg": "使用法術前必須透過什麼動作來發動？\n"
                 "           (1) 做暖身操\n"
                 "           (2) 倒立\n"
                 "           (3) 挖鼻屎\n"
                 "           (4) 連續的手印\n",
          "correct": 4,
          "answer": 0,
       ]),
    6: ([ "msg": "木葉村第五代火影是？\n"
                 "           (1) 猿飛\n"
                 "           (2) 自來也\n"
                 "           (3) 綱手\n"
                 "           (4) 鳴人\n",
          "correct": 3,
          "answer": 0,
       ]),
    7: ([ "msg": "下列哪一位是木葉村的叛忍？\n"
                 "           (1) 獅子丸\n"
                 "           (2) 大蛇丸\n"
                 "           (3) 小蛇丸\n"
                 "           (4) 兵糧丸\n",
          "correct": 2,
          "answer": 0,
       ]),
    8: ([ "msg": "什麼是體術？\n"
                 "           (1) 利用體內的查克拉在自已或對手身上使用的法術\n"
                 "           (2) 是一種體操，戰鬥前使用的暖身操\n"
                 "           (3) 以幻覺製造催眠狀態\n"
                 "           (4) 利用自已的身體做出攻擊\n",
          "correct": 4,
          "answer": 0,
       ]),
    9: ([ "msg": "什麼是忍術？\n"
                 "           (1) 利用體內的查克拉在自已或對手身上使用的法術\n"
                 "           (2) 是一種體操，戰鬥前使用的暖身操\n"
                 "           (3) 以幻覺製造催眠狀態\n"
                 "           (4) 利用自已的身體做出攻擊\n",
          "correct": 1,
          "answer": 0,
       ]),
   10: ([ "msg": "什麼是幻術？\n"
                 "           (1) 利用體內的查克拉在自已或對手身上使用的法術\n"
                 "           (2) 是一種體操，戰鬥前使用的暖身操\n"
                 "           (3) 以幻覺製造催眠狀態\n"
                 "           (4) 利用自已的身體做出攻擊\n",
          "correct": 3,
          "answer": 0,
       ]),
]);

string do_look_long()
{
    int index, size;
    string msg;
    
    size = sizeof(test);

    msg  = this_object()->query("name") + ", 請使用 answer 指令作答。\n";
    msg += "────────────────────────────────────\n";

    for(index=1;index<=size;index++) {
        if( undefinedp(test[index]) ) continue;
        msg += sprintf("（%|3s）%2d. %s\n",
               test[index]["answer"] ? test[index]["answer"] + "" : "",
               index,
               test[index]["msg"] );
    }

    msg += "────────────────────────────────────";
    return msg;
}

int do_check()
{
    int index, score = 0 , size;
    size = sizeof(test);

    for(index=1;index<=size;index++) {
        if( undefinedp(test[index]) ) continue;
        if( test[index]["correct"] == test[index]["answer"] ) score += 10;   //答對一題得十分
    }

    return score;
}

void create()
{
    set_name("木葉村下忍考試卷", ({ "muye inferior ninja test paper", "paper"}));
    set_weight(500);
    if( !clonep() ) {
        set("unit", "張");
        set("value", 0);
        set("no_box", 1);
        set("long", (: do_look_long :) );
    }
    setup();
}

void init()
{
    add_action("do_answer", "answer");
}

int do_answer(string arg)
{
    int no, ans;

    // paper不是在user身上不會有answer動作
    if( !userp(environment(this_object())) ) return 0;

    if( !arg ) return notify_fail("指令格式： answer <題號> <答案>\n");

    if( sscanf(arg, "%d %d", no, ans) != 2 ) return notify_fail("指令格式： answer <題號> <答案>\n");

    if( undefinedp(test[no]) ) return notify_fail("沒有這一個題目。\n");
    
    tell_object(this_player(), "你在第 " + no + " 題的答案欄寫上 " + ans + " 這個答案。\n");

    test[no]["answer"] = ans;

    this_object()->set("long", do_look_long());

    return 1;
}

string is_test_paper() { return "muye"; }
