// gold.c

inherit MONEY;

void create()
{
	set_name("黃金", ({"gold", "ingot", "gold_money"}));
	if( !clonep() ) {
		set("money_id", "gold");
		set("long", "黃澄澄的金子﹐人見人愛的金子﹐啊∼∼金子﹗\n");
                set("unit", "兩");
		set("material", "gold");
		set("base_value", 1000);
		set("base_weight", 10);
	}
	set_amount(1);
	setup();
}

