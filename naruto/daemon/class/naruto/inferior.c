// Fighter class daemon.
void create()
{
	seteuid(getuid());
	DAEMON_D->register_class_daemon("inferior");
}

string query_rank(object ob, string politeness)
{
	switch(politeness) {
		case "self": return "在下";
		case "rude self": return "在下";
		case "respectful": return "忍者";
		case "rude": return "惡賊";
		default: return "下忍";
	}
}

void setup(object ob) {}

// 下忍 1-20級
int getMaxLV() { return 20; }
int getLvUpExp(object ob) { return ob->query_level()*ob->query_level()*20; }
	
void initialize(object ob)
{
/* 升級不看這個了
    int lv;
	seteuid(geteuid(ob));

    lv = ob->query_level();

    // 下忍只能升到lv20
    if( lv < 20 ) {
		// 超過十級必需要有完成E級任務
    	if( lv > 10 ) ob->set_target_score("elevel", lv-10);
        ob->set_target_score("combat exp", lv*lv*100);
    } else ob->delete("target_score");
*/
}

void advance_level(object ob)
{
/* 升級不看這個了
    int lv;
	lv = ob->query_level();
	if( !lv ) return;
	
	// 設定下次升級所需經驗
	if( lv < 20 ) {
		// 超過十級必需要有完成E級任務
    	if( lv > 10 ) ob->set_target_score("elevel", lv-10);
	    ob->set_target_score("combat exp", lv*lv*100);
	} else ob->delete("target_score");
*/	
	// 設定學習點數、潛能點數、屬性點數、技能點數;
//	ob->add_point("learn", 100);
	ob->add_point("score", 50);
	ob->add_point("attribute", 2);
	ob->add_point("skill", 2);
}