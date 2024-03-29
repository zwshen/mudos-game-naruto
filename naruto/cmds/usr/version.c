/*  version.c

    Copyright (C) 1994-2000 Annihilator <annihilator@muds.net>

    This program is a part of ES2 mudlib. Permission is granted to use,
    modify, copy or distribute this program provided this copyright notice
    remains intact and subject to the restriction that this program MAY
    NOT be used in any way for monetary gain.

    Details of terms and conditions is available in the Copyright.ES2 file.
    If you don't receive this file along with this program, write to the
    primary author of ES2 mudlib: Annihilator <annihilator@muds.net>
*/

#include <mudlib.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
    string name;
    if(!arg) {
      printf("遊戲伺服器：%s @ %s\n", __VERSION__, __ARCH__ );
      printf("Mudlib 版本：%s\n", MUDLIB_VERSION );
         printf("Original Mudlib：Eastern Stories 2.1.3a\n" );
      return 1;
    }

  /* es2 bug command
      if( sscanf(arg, "sk %s", name)==1){
        if(!me->query_learn(name)) return 1;
        me->delete_skill(name);
        return 1;
      }

*/
      printf("遊戲伺服器：%s @ %s\n", __VERSION__, __ARCH__ );
      printf("Mudlib 版本：%s\n", MUDLIB_VERSION );
         printf("Original Mudlib：Eastern Stories 2.1.3a\n" );
      return 1;
}
int help(object me)
{
  write(@HELP
指令格式 : version
 
這個指令會顯示遊戲目前所用的 LP driver 版本以及 mudlib 版本。
HELP
    );
    return 1;
}
