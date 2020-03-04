#include <ansi.h>

// »¡©ú¦¹ÀÉ¬O¥ô°È¡A³o­Ó¨ç¦¡¤£»Ý­nÅÜ°Ê
int isQuest() { return 1; }

/* ¦¹¥ô°È¬O§_¯à­«½Æ¸Ñ  return 0  ¤£¯à­«½Æ
                       return 1  ¥i­«½Æ
   «ØÄ³³Ì¦n³]©w¤£¯à­«½Æ¡C
 */
int isNewly() { return 1; }

// ¥ô°È¦WºÙ
string getName() {
    return "¦MÀIªh¿A¦a";
}

// ¥ô°È´y­z
string getDetail() {
    string msg;

    msg  = "ªQ•µ¤j»²¦]¬°¯à©M¾ð»¡¸Ü¦Ó»P¾ð²£¥Í¤F²`«pªº¤Í±¡¡AÅ¥»¡¦b¾Ô¨ÆªLªº\n";
    msg += "ªþªñ¦³¤@¤ù¦W¬°¡uµ´±æªh¿A¡v¦a¤è¡A¸Ì­±¦³ºØ¦W¥sªh¿A¬r³½ªº¥Íª«·|\n";
    msg += "±N¾ð¤ì»G»k¡Aµ´±æªh¿A­ì¥»¤j¥bªº¦a¬q¦ü¥G³£¬O´ËªL¡A¦ý¬O¥Ø«e¤w¸g\n";
    msg += "«K¦¨¦p¦¹¤F¡A¦]¦¹ªQ•µ¤j»²­n¨D§A¥h²M°£¤@¨Ç¬r³½¡C\n";

    return msg;
}

// ¥ô°Èµ¥¯Å
int getLevel() {
    return 20;
}

/* ±µ¨ü¥ô°Èªº«e¸m±ø¥ó¡A¥i¯à¬O
        1. µ¥¯Å»Ý¨D
        2. Â¾·~»Ý¨D
        3. ºØ±Ú»Ý¨D
        4. ¤w§¹¦¨¬Y¨Ç¥ô°È»Ý¨D
    µ¥µ¥¡AÀ³¥i¥H¦Û¥Ñµo´§¤~¬O¡C
    ¦^¶Ç«D¹s­Èªí¥Ü²Å¦X±ø¥ó¡C
 */
int preCondition(object player) {
    if( player->query("guild") != "hunter" ) return 0;
    if( player->query_class() == "hxh_initial" ) return 0;
    if( player->query_skill("born-again branch", 1) ) return 0;
    if( player->query("level") < 20 ) return 0;
    return 1;
}

// ±µ¨ü¥ô°ÈªºNPC  (¥HÀÉ¦W¨ÓÃÑ§O)
string getAssigner() {
    return "/world/area/magic_house/npc/daisuke.c";   // ªQ•µ¤j»²
}

// ±µ¨ü¥ô°È®Éªº°T®§
string *getAssignMessage() {
    // $N¬°NPC, $n¬°player
    string *msg = ({
        "$N»¡¹D¡G"HIG"$nª¾¹D¾Ô¨ÆªLªºªL¦a¬°¤°»ò·U¨Ó·U¤p¤F¶Ü¡I\n"NOR,
        "$N»¡¹D¡G"HIG"¦]¬°¤W¤èµ´±æªh¿A¸Ì¦³ºØ¬r³½·|»G»k¾ð¤ì¡I\n"NOR,
        "$N»¡¹D¡G"HIG"¦pªG¦³¤H¯à¥h®Æ²z¨e­Ì§Ú´N§â¾ð¤ì­«¥Í¤§³N±Ð¥L¡I\n"NOR,
    });
    return msg;
}

// ¥ô°È¶·­n±þ¦º¬Y¨Ç©Çª«¡A­Y¤£»Ý­n«h return 0
mapping getKill() {
    mapping kill = ([
        "/world/area/bone/npc/fish.c": 10,     // ªh¿A¬r³½
    ]);
    return kill;
}

// ¥ô°È¶·­n¨ú±o¬Y¨Çª««~¡A­Y¤£»Ý­n«h return 0
// ª`·N¡G³o¨Çª««~¥²»Ý¬O½Æ¦X«¬ª«¥ó¤~¦æ
mapping getItem() {
    return ([]);
}

// §¹¦¨¥ô°Èªº±ø¥ó°£¤F¨t²Î´£¨Ñªº
// 1. ·j¶°ª««~
// 2. ±þ¤F¨¬°÷¼Æ¶qªº©Çª«¤§¥~
// ¦³»Ý­nªº¸Ü¡AÁÙ¥i¥H¦Û­q§¹¦¨¥ô°È±ø¥ó
// return 1, ¬°º¡¨¬±ø¥ó, return 0;¬°¥¢±Ñ
int postCondition(object player, object npc)
{
    return 1;
}

// §¹¦¨¥ô°ÈªºNPC  (¥HÀÉ¦W¨ÓÃÑ§O)
string getRewarder() {
    return "/world/area/magic_house/npc/daisuke.c";   // ªQ•µ¤j»²
}

// §¹¦¨¥ô°È®Éªº°T®§
string *getRewardMessage() {
    // $N¬°NPC, $n¬°player
    string *msg = ({
        "$N»¡¹D¡G"HIG"¨S·Q¨ì$n¯uªº¥h±þ¤Fªü¡I\n"NOR,
        "$N»¡¹D¡G"HIG"ÁöµM¨e­ÌÁc´Þªº«Ü§Ö¡A¤£¹L§Ú¬Û«H·|¦³À°§Uªº¡C\n"NOR,
        "$N»¡¹D¡G"HIG"·íªì¬ù©wªº§Þ¯à³o´N¨Ó±Ð$n§a¡C\n"NOR,
    });
    return msg;
}

string getReward()
{
    string msg = "¾Ç²ß§Þ¯à¡u"HIY"¾ðªK­«¥Í"NOR"¡v\n";
    return msg;
}

/*  ¥ô°È¼úÀy
    ¼úÀyÀ³¸Ó¯à¦Û¥Ñµo´§¡A¦p¡G
        1. Àò±o¸gÅç
        2. Àò±oª««~
        3. Àò±oµu¼ÈBuff
        4. ²ß±o¬Y§Þ¯à
        5. §ó§ïª±®aª¬ºA, ex: ÂàÂ¾
 */
void reward(object player, object npc)
{
    player->set_skill("born-again branch", 2);
    tell_object(player, HIY"(§AÅ¥¤FªQ•µ¤j»²ªº«ü¾É¡A¦ü¥G¦³¨Ç¤ß±o¤F)\n"NOR);
}
