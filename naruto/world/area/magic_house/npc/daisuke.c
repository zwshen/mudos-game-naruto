#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;
inherit F_TRAINER;    // °V½m¾É®v

void do_fight()
{
    object enemy, ob;
    int damage, damage_attack;

    // ¨S¦³¼Ä¤H
    enemy = this_object()->query_opponent();

    if( !enemy ) return;

    // ¼Ä¤H¦b¤£¦P¦ì¸m
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( enemy->query_condition("hairstick", 1) == 0 ) {
        command("perform hair order.lunge on " + enemy->query_id() );
    } else if( ob = present("_VEGGIE_"+this_object()->query_id(), environment(this_object())) ) {
        if( !ob->is_fighting() ) {
            damage_attack = COMBAT_D->attack(this_object(), this_object(), 0, this_object()) - COMBAT_D->defend(enemy, enemy, 0);
            if( damage_attack < 0 ) damage_attack = 0;

            message_vision("$N¦V«á¤@ÅD¹B¥Î©À¤O¾ÞÁa"+ob->query("name")+"ªº¦æ°Ê¡A¥u¨£"+ob->query("name")+"¥ß¨èÂàÀY½Ä¦V$n¡I\n\n"NOR, this_object(), enemy);

            damage = ob->query_stat_maximum("hp")/2 + this_object()->query_skill("born-again branch") + random(100) + damage_attack;

            enemy->receive_damage(damage, this_object());
            message_vision( ob->query("name")+HIW"¤C¤â¤K¸}ªº§â"NOR"$n"HIW"Äñ¦í¡A¨­Åéªº¤¤¤ß¶}©lµo¥X"HIR+BLINK"¬õ¦â¥ú¨~"NOR+HIW"¡I\n"NOR, this_object(), enemy);
            message_vision( sprintf("¡u¤T¡v¡u¤G¡v¡u¤@¡vÅF¶©¥¨ÅT±N$n¬µªº¥|¤À¤­µõ(%d)%s\n\n", damage, COMBAT_D->report_status(enemy)), this_object(), enemy);

            this_object()->delete_temp("TREE_ONE");
            this_object()->delete_temp("TREE_TWO");
            destruct(ob);
        }
    }
    return;
}

void do_heal()
{
    object item;

    if( this_object()->query_condition("blood_cell_revive_cond") == 0 && this_object()->query_stat("hp") < this_object()->query_stat_maximum("hp")/2 ) {
        command("perform blood-cell revive.revive");
        return;
    } else {
        if( this_object()->query_temp("TREE_ONE") == 0 && this_object()->query_temp("TREE_TWO") == 0 ) {
            item = new(_DIR_AREA_"thorn_pine/npc/item/branch.c");
            item->move(this_object());
            command("perform born-again branch.crop");
        } else if( present("_TREE_", environment(this_object())) ) {
            item = new(_DIR_AREA_"thorn_pine/npc/item/water04.c");
            item->move(this_object());
            command("perform born-again branch.arise");
        }
    }
    return;
}

void create()
{
    set_name("ªQ•µ¤j»²", ({ "matsuzaka daisuke", "daisuke" }) );
    set_race("human");
    set_level(60);
    set_class("hxh_star");  // ¤@¬PÂy¤H
    set("age", 22);
    set("camp", "hunter");
    set("nickname", HIK"¥­¦¨©Çª«"NOR);
    set("long", "­ì¥»©~¦í¦b¥­¦¨¦a°Ïªº¤p§ø¤¤¡A¦]¬°¯à°÷©M¾ð¤ì»¡¸Ü¦Ó³Q¨ä¥L¤p«Ä\n"
                "·í¦¨©Çª«¬Ý«Ý¡Aª½¨ìÅ]³N°¨À¸¹Îµo²{¥LÅå¤Hªº¤~¯à«á¡A«K±N¥L±a¶i\n"
                "°¨À¸¹Î¡A¤]¤£¦A³Q¤H§Áµø¤F¡Cªíºt¶µ¥Ø¬°¾Þ°¸³N¡C¥i¥H§Q¥Îtrain \n"
                "«ü¥O¨Ó¾Ç²ß§Þ¯à¡C¨Ï¥Î list «ü¥O¬d¸ß¥i¾Ç²ßªº§Þ¯à¦Cªí¡C\n");

    set("chat_chance", 50);
    set("chat_msg", ({
        (: do_heal :),
    }) );

    set("chat_chance_combat", 100);
    set("chat_msg_combat", ({
        (: do_fight :),
    }) );

    // ¥u±Ð¾ÉÂy¤H
    set("guild", "hunter");

    // ³]©w¯à°V½mªº§Þ¯à
    //
    // set_train(§Þ¯à¦W, ¬O§_¥iª½±µ²ß±o, ¾Ç²ß¸Ó§Þ¯à©Ò»Ý­nªº¨¤¦âµ¥¯Å, ¦¹§Þ¯à¥i¾Ç²ß¨ìªº¤W­­µ¥¯Å)
    //
    // ·íª±®a¨S¦³¸Ó§Þ¯à®É¡A­Y"¬O§_¥iª½±µ²ß±o"³o­Ó³]©w­È¬°«D¹s­È®É¡Aª±®a¦V°V½mªÌ¾Ç²ß®É«h¥i°O¦í
    // ³o­Ó§Þ¯à¨ìlv1¡A¦Ó¦³lvªº§Þ¯à¤~¥i¥H§ëÂIÄ~ÄòÁë½m¡C¬G¥i¥Î©ó¯S®í§Þ¡A­n¸ÑÁ¼±o¨ìlv«á¤è¥i°V½m¡C
    //
    set_train_with_camp("combat", 1, 1, 140, "hunter", -2);             // ®æ°«§Þ¥©
    set_train_with_camp("dodge", 1, 1, 160, "hunter", -2);              // °{¸ú§Þ¥©
    set_train_with_camp("parry", 1, 1, 200, "hunter", 0);              // ¾×®æ§Þ¥©
    set_train_with_camp("heavy hit", 1, 5, 140, "hunter", -2);          // ­«À»¤§³N
    set_train_with_camp("savage hit", 1, 5, 160, "hunter", -2);         // ¼ÉÀ»¤§³N
    set_train_with_camp("continual hit", 1, 5, 160, "hunter", -2);      // ³sÀ»¤§³N
    set_train_with_camp("operation", 1, 10, 200, "hunter", -1);         // ¾Þ§@¨tµ{«×
    set_train_with_camp("blood-cell revive", 0, 15, 160, "hunter", -1); // ¦å²y¦A¥Í
    set_train_with_camp("hair order", 1, 21, 140, "hunter", 0);         // ¤ò¾v©À±±
    set_train_with_camp("born-again branch", 0, 20, 120, "hunter", 0);  // ¾ðªK­«¥Í

    setup();
    set_skill("combat", 140);
    set_skill("dodge", 160);
    set_skill("parry", 180);
    set_skill("heavy hit", 140);
    set_skill("savage hit", 160);
    set_skill("continual hit", 160);
    set_skill("operation", 200);
    set_skill("blood-cell revive", 200);
    set_skill("hair order", 200);
    set_skill("born-again branch", 200);
}
int accept_fight(object me, string arg)
{
    return 0;
}
