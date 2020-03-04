// thief 瓁
// 2006/2/26 -mouse

void create()
{
	seteuid(getuid());
	DAEMON_D->register_class_daemon("soldier_sea");
}

string query_rank(object ob, string politeness)
{
	switch(politeness) {
		case "self": return "";
		case "rude self": return "";
		case "respectful": return "";
		case "rude": return "搁";
		default: return "瓁";
	}
}

// 瓁 21-40
int getMaxLV() { return 40; }
int getLvUpExp(object ob) { return ob->query_level()*ob->query_level()*40; }
void setup(object ob) {}

void initialize(object ob) {}

void advance_level(object ob)
{
	// 砞﹚厩策翴计肩翴计妮┦翴计м翴计;
	ob->add_point("score", 100);
	ob->add_point("attribute", 3);
	ob->add_point("skill", 2);
}