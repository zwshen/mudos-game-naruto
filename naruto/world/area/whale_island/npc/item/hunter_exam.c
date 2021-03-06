/* testpaper.c 下忍考試卷 write by -Acme- */

inherit ITEM;

mapping test = ([
    1: ([ "msg": "取得獵人執照有什麼好處？\n"
                 "           (1) 可以進入禁止進入的國家\n"
                 "           (2) 變賣執照可以七輩子吃穿不盡\n"
                 "           (3) 上網查詢公共設施\n"
                 "           (4)  以上皆是\n",
          "correct": 4,
          "answer": 0,
       ]),
    2: ([ "msg": "下面那個不是合法的獵人階級？\n"
                 "           (1) 二星獵人\n"
                 "           (2) 一猩獵人\n"
                 "           (3) 無照獵人\n"
                 "           (4) 有照獵人\n",
          "correct": 2,
          "answer": 0,
       ]),
    3: ([ "msg": "如要修習念能力，首先必須打開體內氣的通道，下述那項不是可能的打開方式？\n"
                   "           (1) 冥想的方式來打開精孔\n"
                 "           (2) 別人用念力強制打開您的精孔\n"
                 "           (3) 每天對著週遭的人碎碎念，是最快獲得念能力的方法\n"
                 "           (4) 天份過人，某一天早上醒來忽然就領悟了，一千萬人當中只會有一個\n",
          "correct": 3,
          "answer": 0,
       ]),
    4: ([ "msg": "什麼是念能力？\n"
                 "           (1) 形容一個人很會嘮叨\n"
                 "           (2) 使用特殊念技的能量源\n"
                 "           (3) 貨幣的單位\n"
                 "           (4) 是一種組織\n",
          "correct": 2,
          "answer": 0,
       ]),
    5: ([ "msg": "下述念能力的四大行，何者描述不對？\n"
                 "           (1) 纏：把從體內精孔流出的生命能量(氣)，留在身體四周\n"
                 "           (2) 絕：關閉體內的精孔 ，使身體保持沒有氣散發出來的狀態\n"
                 "           (3) 練：擴張體內精孔 ，發散出比平常更大量的氣 \n"
                 "           (4) 發：將剛吃飽飯後的屁發出以攻擊敵人\n",
          "correct": 4,
          "answer": 0,
       ]),
    6: ([ "msg": "下述念能力的應用技，何者描述不對？\n"
                 "           (1) 周： 將氣包圍手中所握物件，藉此對該物件進行強化，是纏的應用技。\n"
                 "           (2) 圓：以身體為中心，使用『練』將『纏』的範圍擴大\n"
                 "           (3) 堅：用比平常更多的氣罩住身體來增強攻防力\n"
                 "           (4) 凝：以練將提高的氣，只能集中於身體下半部份\n",
          "correct": 4,
          "answer": 0,
       ]),
    7: ([ "msg": "下面有關修習念能力的描述何者不正確？\n"
                 "           (1) 每個人依他的本性，適合不同種纇的念能力\n"
                 "           (2) 念能力和每個人的個性有關。若和自己的特性不合，想學別的念能力是一件很辛苦的事\n"
                 "           (3) 具現化系和操作系的念能力者後來有機會轉變為特質系\n"
                   "           (4) 每個獵人都朝全部修齊六個念系能力的目標前進\n",
          "correct": 4,
          "answer": 0,
       ]),
    8: ([ "msg": "下面描述使用水見式來檢查六大系的反應，何者不可能發生？\n"
                 "           (1) 強化系：水量改變\n"
                 "           (2) 特質系：水變成火紅色\n"
                 "           (3) 放出系：水的顏色改變\n"
                 "           (4) 操作系：樹葉移動\n"
                 "           (5) 具現化系：水中出現雜質\n"
                 "           (6) 變化系：水的味道改變\n",
          "correct": 2,
          "answer": 0,
       ]),
    9: ([ "msg": "下面有關念能力與個人的本性描述，何者不正確？\n"
                 "           (1) 強化系：頭腦簡單\n"
                 "           (2) 變化系：反覆無常、愛騙人\n"
                 "           (3) 放出系：喜歡切斷自已的手指頭，好模擬槍管\n"
                 "           (4) 操作系：愛講道理、我行我素\n",
          "correct": 3,
          "answer": 0,
       ]),
   10: ([ "msg": "有關幻影旅團的介紹，下面何者不正確？\n"
                 "           (1) 幻影旅團都是A級的通緝犯\n"
                 "           (2) 團員共有二百萬人\n"
                 "           (3) 身上都有12腳蜘蛛的刺青\n"
                 "           (4) 刺青上有該團員的號碼\n",
          "correct": 2,
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
    set_name("獵人資格模擬考", ({ "hunter inital test paper", "paper"}));
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

string is_test_paper() { return "hunter"; }

