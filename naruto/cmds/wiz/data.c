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
     if( !ob1 ) return notify_fail ("本地無此生物: "+id+"\n");
     if (!ob=present(arg, ob1)) return notify_fail ("該生物身上無此物件: "+arg+"\n");
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
     if(!ob) return notify_fail("Data: 無法找到此物件: "+arg+"。\n");
   }

   list = (mapping)ob->query_entire_dbase();
   tlist = (mapping)ob->query_entire_temp_dbase();
   if( (!list || !mapp(list)) && (!tlist || !mapp(tlist)))
            return notify_fail("Data: 此物件並沒有任何的資料。\n");

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
     return notify_fail("Data: 此物件並沒有儲存任何資料。\n");

   if (!spec || spec == "-d") {
     text = "Object : " + base_name(ob) + ".c\n";

     for(loop=0; loop<sizeof(klist); loop++)  {

       if(strlen(klist[loop]) > 7)  text += klist[loop] + "\t: ";
       else text += klist[loop] + "\t\t: ";

        text +=sprintf("%O \n",list[ klist[loop] ]);
     }
     text += "\n總共有 " + sizeof(klist) + " 個儲存的資料。\n\n";
   }
   else text = "";

   if (!spec || spec == "-t") {

     text += "TEMP DATA :\n\n";

     for(loop=0; loop<sizeof(tlist2); loop++)  {
       if(strlen(tlist2[loop]) > 7)  text += tlist2[loop] + "\t: ";
       else text += tlist2[loop] + "\t\t: ";
         text +=sprintf("%O \n",tlist[ tlist2[loop] ]);
     }

     text += "\n總共有 " + sizeof(tlist2) + " 個暫存的資料。\n\n";
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
指令格式: data [-t|-d] [玩家|物件|here] [in 玩家或生物]
指令範例: data                  <-- 看自己的所有 data base
          data -t               <-- 看自己的暫存資料
          data -d               <-- 看自己的永久資料
          data -t here          <-- 看所在房間的暫時資料
          data wade             <-- 看 wade 這個玩家(或物件)的所有資料
          data board            <-- 看版子的資料
          data cloth in wade    <-- 看 wade 身上的 cloth 的資料
指令說明:
        此命令讓你可以觀看所指定物件的資料，且將會以 more 的方式
輸出，如果沒有指定數，則自動以使用者為參數。其中的 -t 選項可以顯
示暫時變數, -d 選項可以只顯示永久變數, 所要看的對象可以是玩家或
任何物件.
LONG);

  return 1;
}

