// bag.c

inherit ITEM;

void create()
{
    set_name("鍋爐置物箱", ({ "box", "_WP_BOX_" }));
    set_weight(700);
    set_max_encumbrance(90000);
    if( !clonep() ) {
        set("unit", "隻");
        set("value", 3000);
        set("no_get", 1);
        set("no_sac", 1);
        set("no_box", 1);
        set("long", "看起來不是很大的置物箱，有條傳帶可以將物品送入鍋爐中。\n");
    }
    setup();
}

int accept_object() { return 1; }

