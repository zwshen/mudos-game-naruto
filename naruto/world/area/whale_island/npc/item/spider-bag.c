// bag.c

inherit ITEM;

void create()
{
          set_name("蜘蛛胃袋", ({ "spider stomach bag", "bag" }));
        set_weight(700);
        set_max_encumbrance(60000);
        if( !clonep() ) {
                set("unit", "隻");
                set("value", 5000);
                set("long", "一隻滿大的蜘蛛胃袋，你想要裝東西進去也行。\n");
        }
        setup();
}

int accept_object() { return 1; }


