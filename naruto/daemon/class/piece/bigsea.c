// big �j����
// 2006/2/26 -mouse

void create()
{
	seteuid(getuid());
	DAEMON_D->register_class_daemon("big_sea");
}

string query_rank(object ob, string politeness)
{
	switch(politeness) {
		case "self": return "�b�U";
		case "rude self": return "�b�U";
		case "respectful": return "����";
		case "rude": return "�c��";
		default: return "�j����";
	}
}

// �j���� 41-60��
int getMaxLV() { return 60; }
int getLvUpExp(object ob) { return ob->query_level()*ob->query_level()*60; }

void setup(object ob) {}

void initialize(object ob) {}

void advance_level(object ob)
{
	// �]�w�ǲ��I�ơB����I�ơB�ݩ��I�ơB�ޯ��I��;
	ob->add_point("score", 150);
	ob->add_point("attribute", 4);
	ob->add_point("skill", 2);
}