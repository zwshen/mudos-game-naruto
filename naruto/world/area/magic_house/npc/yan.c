#include <npc.h>
#include <ansi.h>

inherit F_SOLDIER;
inherit F_TRAINER;    // °V½m¾É®v

void do_fight()
{
    object enemy, sword, item;

    // ¨S¦³¼Ä¤H
    enemy = this_object()->query_opponent();

    if( !enemy ) return;

    // ¼Ä¤H¦b¤£¦P¦ì¸m
    if( environment(this_object())->is_area() ) {
        if( !area_environment(this_object(), enemy) ) return;
    } else {
        if( environment(enemy) != environment(this_object()) ) return;
    }
    if( !objectp(sword = present("_CREATION_SWORD_", this_object())) ) {
        item = new("/daemon/skill/hxh/concrete/obj/sword_obj.c");
        item->move(this_object());
    }
    if( this_object()->query_condition("firewall") == 0 ) {
        command("perform fire wall.fire");
    } else {
        command("perform frost closed ball.ball on " + enemy->query_id() );
    }
    return;
}

void create()
{
    set_name("¨¥®p†ýŠà", ({ "yan feng", "feng", "yan" }) );
    set_race("human");
    set_level(70);
    set_class("hxh_star2");  // ¤G¬PÂy¤H
    set("age", 46);
    set("camp", "hunter");
    set("nickname", HIM"Å]³N®v"NOR);
    set("long", "µ½ªø¥H©À¤OÂà¤Æ¬°¯à¶qªº¯à¤O¡A¦]¬°°Ñ¥[¤@¶µ¦W¬°¸tªM¾Ôª§ªº¹CÀ¸\n"
                "¦Ó¨ì³B·j¶°¨ä¥L°Ñ¥[ªÌ±¡³ø¡AÁÙ³Ð¿ì¡uÅ]³N°¨À¸¹Î¡v±N¦Û¤vªº©À¯à\n"
                "¤O°°¸Ë¦¨Å]³N¨ì³Bªíºt¡A¨ä¤¤¤£¤Ö¹Î­û³£¤£ª¾¹D¥L¯u¥¿ªº¥Øªº¡C\n"
                "¥i¥H§Q¥Îtrain «ü¥O¨Ó¾Ç²ß§Þ¯à¡C\n"
                "¨Ï¥Î list «ü¥O¬d¸ß¥i¾Ç²ßªº§Þ¯à¦Cªí¡C\n");

    set("chat_chance_combat", 50);
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
    set_train_with_camp("combat", 1, 1, 160, "hunter", -2);              // ®æ°«§Þ¥©
    set_train_with_camp("dodge", 1, 1, 140, "hunter", -2);               // °{¸ú§Þ¥©
    set_train_with_camp("parry", 1, 1, 160, "hunter", -2);               // ¾×®æ§Þ¥©
    set_train_with_camp("heavy hit", 1, 5, 160, "hunter", -2);           // ­«À»¤§³N
    set_train_with_camp("savage hit", 1, 5, 140, "hunter", -2);          // ¼ÉÀ»¤§³N
    set_train_with_camp("continual hit", 1, 5, 180, "hunter", -2);       // ³sÀ»¤§³N
    set_train_with_camp("variation", 1, 10, 200, "hunter", -2);          // ÅÜ¤Æ¨tµ{«×
    set_train_with_camp("fire variation", 0, 15, 160, "hunter", -1);     // ¤õ©À¤OÅÜ¤Æ
    set_train_with_camp("ice variation", 0, 15, 160, "hunter", -1);      // ¦B©À¤OÅÜ¤Æ
    set_train_with_camp("electric variation", 0, 15, 160, "hunter", -1); // ¹q©À¤OÅÜ¤Æ
    set_train_with_camp("frost closed ball", 0, 21, 140, "hunter", 0);   // ¦B«Ê²y
    set_train_with_camp("chain lighting", 0, 21, 140, "hunter", 0);      // ³sÂê°{¹q
    set_train_with_camp("fire wall", 1, 21, 140, "hunter", 0);           // ¤õÀð

    setup();
    set_skill("combat", 160);
    set_skill("dodge", 140);
    set_skill("parry", 160);
    set_skill("heavy hit", 160);
    set_skill("savage hit", 140);
    set_skill("continual hit", 180);
    set_skill("variation", 200);
    set_skill("ice variation", 200);
    set_skill("frost closed ball", 200);
    set_skill("fire wall", 200);
}
int accept_fight(object me, string arg)
{
    return 0;
}
