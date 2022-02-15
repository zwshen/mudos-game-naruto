/* data.c
*/

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
   mapping list, tlist;
   mixed *klist, *tlist2;
   object ob, ob1;
   string text,*tmp, id, spec;
   int loop;

   seteuid(geteuid(me));

   if (arg) {
     sscanf (arg, "%s %s", spec, arg);
     if (arg == "-t" || arg == "-d") {
       spec = arg;
       arg = 0;
     }
     if (spec && spec != "-d" && spec != "-t") {
       arg = spec + " " + arg;
       spec = 0;
     }
   }
   if(!arg || arg == "")  ob=me;
   else if (sscanf (arg, "%s in %s", arg, id) == 2) {
     ob1 = present(id, environment(me));
     if( !ob1 ) ob1 = present(id, me);
     if( !ob1 ) return notify_fail ("���a�L���ͪ�: "+id+"\n");
     if (!ob=present(arg, ob1)) return notify_fail ("�ӥͪ����W�L������: "+arg+"\n");
   }
   else if (arg == "here") {
     ob = environment(me);
   }
   else {
     arg = lower_case(arg);
     ob = present(arg, environment(me));
     if (!ob) ob = find_player(arg);
     if (!ob) ob = find_living(arg);
     if (!ob) ob = present(arg, me);
     if(!ob) return notify_fail("Data: �L�k��즹����: "+arg+"�C\n");
   }

   list = (mapping)ob->query_entire_dbase();
   tlist = (mapping)ob->query_entire_temp_dbase();
   if( (!list || !mapp(list)) && (!tlist || !mapp(tlist)))
            return notify_fail("Data: ������èS�����󪺸�ơC\n");

   if (sizeof(list))
   {
        klist = keys(list);
        klist = sort_array(klist, "sort_keys", this_object());
   }

   if (sizeof(tlist))
   {
        tlist2 = keys(tlist);
        tlist2 = sort_array(tlist2, "sort_keys", this_object());
   }

   // if(!member_group(geteuid(this_player()), "admin"))
//      klist = filter_array(klist, "filter_props", this_object(), ob);

   if(!klist || !sizeof(klist))
     return notify_fail("Data: ������èS���x�s�����ơC\n");

   if (!spec || spec == "-d") {
     text = "Object : " + base_name(ob) + ".c\n";

     for(loop=0; loop<sizeof(klist); loop++)  {

       if(strlen(klist[loop]) > 7)  text += klist[loop] + "\t: ";
       else text += klist[loop] + "\t\t: ";

        text +=sprintf("%O \n",list[ klist[loop] ]);
     }
     text += "\n�`�@�� " + sizeof(klist) + " ���x�s����ơC\n\n";
   }
   else text = "";

   if (!spec || spec == "-t") {

     text += "TEMP DATA :\n\n";

     for(loop=0; loop<sizeof(tlist2); loop++)  {
       if(strlen(tlist2[loop]) > 7)  text += tlist2[loop] + "\t: ";
       else text += tlist2[loop] + "\t\t: ";
         text +=sprintf("%O \n",tlist[ tlist2[loop] ]);
     }

     text += "\n�`�@�� " + sizeof(tlist2) + " �ӼȦs����ơC\n\n";
   }

   me->start_more( text );
   // tmp = explode(text, "\n");
   // for(loop=0; loop<sizeof(tmp); loop++)   write(tmp[loop]+"\n");
   return 1;
}

//  This function is used to sort the key array.

protected int sort_keys(string one, string two) {
   return strcmp(one, two);  }

//  This function strips out the secured props from the data array.

protected int filter_props(string prop, object target) {

//   if(member_array((int)target->query_permission(prop),
//      ({ MASTER_ONLY, PRIVATE, OWNER_ONLY })) != -1)   return 0;

return 1; }

int help(object me)
{
  write( @LONG
���O�榡: data [-t|-d] [���a|����|here] [in ���a�Υͪ�]
���O�d��: data                  <-- �ݦۤv���Ҧ� data base
          data -t               <-- �ݦۤv���Ȧs���
          data -d               <-- �ݦۤv���ä[���
          data -t here          <-- �ݩҦb�ж����Ȯɸ��
          data wade             <-- �� wade �o�Ӫ��a(�Ϊ���)���Ҧ����
          data board            <-- �ݪ��l�����
          data cloth in wade    <-- �� wade ���W�� cloth �����
���O����:
        ���R�O���A�i�H�[�ݩҫ��w���󪺸�ơA�B�N�|�H more ���覡
��X�A�p�G�S�����w�ơA�h�۰ʥH�ϥΪ̬��ѼơC�䤤�� -t �ﶵ�i�H��
�ܼȮ��ܼ�, -d �ﶵ�i�H�u��ܥä[�ܼ�, �ҭn�ݪ���H�i�H�O���a��
���󪫥�.
LONG);

  return 1;
}

