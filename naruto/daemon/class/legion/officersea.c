// big 瓁﹛
// 2006/2/26 -mouse

void create()
{
	seteuid(getuid());
	DAEMON_D->register_class_daemon("officer_sea");
}

string query_rank(object ob, string politeness)
{
	switch(politeness) {
		case "self": return "";
		case "rude self": return "";
		case "respectful": return "﹛";
		case "rude": return "搁﹛";
		default: return "瓁﹛";
	}
}

// 瓁﹛ 41-60
int getMaxLV() { return 60; }
int getLvUpExp(object ob) { return ob->query_level()*ob->query_level()*60; }

void setup(object ob) {}

void initialize(object ob) {}

void advance_level(object ob)
{
	// 砞﹚厩策翴计肩翴计妮┦翴计м翴计;
	ob->add_point("score", 150);
	ob->add_point("attribute", 4);
	ob->add_point("skill", 2);
}