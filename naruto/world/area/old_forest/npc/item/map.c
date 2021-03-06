inherit ITEM;

void create()
{
    set_name("古老森林地圖", ({ "old forest map", "map" }));
    set_weight(100);
    if( !clonep() ) {
        set("unit", "張");
        set("value", 10);
        set("long","一張古老的地圖，可以用(look 古老地圖)觀看。");
    }
    setup();
}
void init()
{
    add_action("do_look", "look");
}
int do_look(string arg)
{
    if( !arg ) return 0;
    if( arg == "古老地圖" ) {
        string line;
        line  = "　\n";
        line += "一張不知從何而來的地圖，上頭畫了一些奇奇怪怪的符號...\n";
        line += "　\n";
        line += "梢\n";
        line += "│\n";
        line += "◎─□─□─入─□─□\n";
        line += "    │      │      │\n";
        line += "□─□─□─□─□─□─◎\n";
        line += "│        ／            │\n";
        line += "□─◎─□─□─□─□─□─□\n";
        line += "            │          │    \n";
        line += "    □─□─□  木  □─□─◎─梢\n";
        line += "        │          │           \n";
        line += "        □─□─◎─□─□─□\n";
        line += "            │              │\n";
        line += "            □─□─□─□─□\n";
        line += "　\n";
        line += "　\n";
        write(line);
        return 1;
    }
}
