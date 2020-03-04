// king 瓁い盢
// 2005/10/19 -tmr

void create()
{
	seteuid(getuid());
	DAEMON_D->register_class_daemon("admiral_sea");
}

string query_rank(object ob, string politeness)
{
	switch(politeness) {
		case "self": return "";
		case "rude self": return "";
		case "respectful": return "い盢";
		case "rude": return "搁盢";
		default: return "瓁い盢";
	}
}

// 瓁い盢 81-99
int getMaxLV() { return 99; }
int getLvUpExp(object ob) { return ob->query_level()*ob->query_level()*99; }

void setup(object ob) {}

void initialize(object ob) {}

void advance_level(object ob)
{
	// 砞﹚厩策翴计肩翴计妮┦翴计м翴计;
	ob->add_point("score", 100);
	ob->add_point("attribute", 2);
	ob->add_point("skill", 2);
}