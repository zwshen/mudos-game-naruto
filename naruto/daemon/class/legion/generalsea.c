// money 瓁盢
// 2006/2/26 -mouse

void create()
{
        seteuid(getuid());
        DAEMON_D->register_class_daemon("general_sea");
}

string query_rank(object ob, string politeness)
{
        switch(politeness) {
                case "self": return "";
                case "rude self": return "";
                case "respectful": return "盢";
                case "rude": return "搁盢";
                default: return "瓁盢";
        }
}

// 瓁盢 71-80
int getMaxLV() { return 80; }
int getLvUpExp(object ob) { return ob->query_level()*ob->query_level()*80; }

void setup(object ob) {}

void initialize(object ob) {}

void advance_level(object ob)
{
        // 砞﹚厩策翴计肩翴计妮┦翴计м翴计;
        ob->add_point("score", 150);
        ob->add_point("attribute", 1);
        ob->add_point("skill", 3);
}
