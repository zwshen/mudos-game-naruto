inherit ITEM;

mapping test = ([
    1: ([ "msg": "下列哪一項是身為一位海軍不該做的事？\n"
                 "           (1) 保護人民\n"
                 "           (2) 逮捕海賊\n"
                 "           (3) 維護世界\n"
                 "           (4) 掠奪財物\n",
          "correct": 4,
          "answer": 0,
       ]),
    2: ([ "msg": "通常辯別是否為海賊團是以什麼物品？\n"
                 "           (1) 骷髏\標誌的旗幟\n"
                 "           (2) 掛在胸前的徽章\n"
                 "           (3) 帶在頭上的帽子\n"
                 "           (4) 船的外觀\n",
          "correct": 1,
          "answer": 0,
       ]),
    3: ([ "msg": "海軍和「七武海」的關係是什麼？\n"
                 "           (1) 與海軍敵對的組織\n"
                 "           (2) 被海軍雇用的暗殺集團\n"
                 "           (3) 政府所認可的海賊\n"
                 "           (4) 海軍七個最強的將領\n",
          "correct": 3,
          "answer": 0,
       ]),
    4: ([ "msg": "惡魔果實是什麼？\n"
                 "           (1) 能獲得特殊能力的物品\n"
                 "           (2) 一種很常見的食物\n"
                 "           (3) 好吃的水果\n"
                 "           (4) 由大廚所做出來的美味佳餚\n",
          "correct": 1,
          "answer": 0,
       ]),
    5: ([ "msg": "惡魔果實能力者遇到什麼會全身無力？\n"
                 "           (1) 烤雞腿\n"
                 "           (2) 手槍\n"
                 "           (3) 海樓石\n"
                 "           (4) 假牙\n",
          "correct": 3,
          "answer": 0,
       ]),
    6: ([ "msg": "海軍的元帥叫什麼名字？\n"
                 "           (1) 漢朝\n"
                 "           (2) 戰國\n"
                 "           (3) 春秋\n"
                 "           (4) 傑克\n",
          "correct": 2,
          "answer": 0,
       ]),
    7: ([ "msg": "海軍是如何判斷海賊應該給予多少懸賞金？\n"
                 "           (1) 高興給多少就多少\n"
                 "           (2) 依照航海的年齡\n"
                 "           (3) 由海賊自己訂\n"
                 "           (4) 依照其對世界政府的威脅性\n",
          "correct": 4,
          "answer": 0,
       ]),
    8: ([ "msg": "關於橡膠果實的說明哪項是錯的？\n"
                 "           (1) 惡魔果實的一種\n"
                 "           (2) 吃了會變成橡膠人\n"
                 "           (3) 果實是用橡膠做的\n"
                 "           (4) 吃了會被大海遺棄\n",
          "correct": 3,
          "answer": 0,
       ]),
    9: ([ "msg": "海軍的屠魔令是什麼樣的指令？\n"
                 "           (1) 由上將以上才可以發動\n"
                 "           (2) 由十艘軍艦和五名中將一同發動攻擊\n"
                 "           (3) 不惜任何手段摧毀一座島嶼\n"
                 "           (4) 以上皆對\n",
          "correct": 4,
          "answer": 0,
       ]),
   10: ([ "msg": "以下何者不是海軍將領？\n"
                 "           (1) 斯摩格\n"
                 "           (2) 阿鶴\n"
                 "           (3) 巴奇\n"
                 "           (4) 雪帕特\n",
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
    set_name("海軍入門測試", ({ "navy entry-level test paper", "paper"}));
    set_weight(500);
    if( !clonep() ) {
        set("unit", "份");
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

string is_test_paper() { return "piece"; }
