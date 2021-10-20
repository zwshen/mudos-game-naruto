// clockd.c
// �o�Ӻ��F��U�ò��w�Ҧ�����ɶ����ʧ@
// Luky@DS 1999
//
//      #define LT_SEC          0
//      #define LT_MIN          1
//      #define LT_HOUR         2
//      #define LT_MDAY         3
//      #define LT_MON          4
//      #define LT_YEAR         5
//      #define LT_WDAY         6
//      #define LT_YDAY         7
//      #define LT_GMTOFF       8
//      #define LT_ZONE         9
//      
//      int     LT_SEC          ��� (0..59)
//      int     LT_MIN          ���� (0..59)
//      int     LT_HOUR         �p�� (0..23)
//      int     LT_MDAY         ��� (1..31)
//      int     LT_MON          ��� (0..11)
//      int     LT_YEAR         �~�� (�����j�� 1900)
//      int     LT_WDAY         �P���X (0..6)
//      int     LT_YDAY         �@�~�����ĴX�� (0..365)
//      int     LT_GMTOFF       ��L�ªv�ɶ��ۮt����� (UTC)
//      string  LT_ZONE         ���a�ɰϪ��W��
// #pragma save_binary
#include <localtime.h>
#include <ansi.h>
#include <login.h>
#include <obj.h>

inherit F_DBASE;

nosave int current_month;
nosave int current_day;
nosave int current_week;
nosave int current_hour;
nosave int current_min;

nosave int current_game_month;
nosave int current_game_day;
nosave int current_game_week;
nosave int current_game_hour;
nosave int current_game_min;

mixed *local,*game_time;


void init_time();

void create()
{
        seteuid(getuid());
        init_time();
}

int query_current_week()
{
        return current_week;
}

int query_current_min()
{
        return current_min;
}

int query_current_month()
{
        return current_month;
}

int query_current_day()
{
        return current_day;
}

int query_current_hour()
{
        return current_hour;
}

//�C�p�ɪ����I����
void every_hour()
{
        string week,str;
        switch(local[LT_WDAY])
        {       
                        case 0: week="��"; break;
                        case 1: week="�@"; break;
                        case 2: week="�G"; break;
                        case 3: week="�T"; break;
                        case 4: week="�|"; break;
                        case 5: week="��"; break;
                        case 6: week="��"; break;
                        default: week="??"; break;
        }
        str = sprintf(HIC+"�i�w�ɺ��F�j���I���ɡR�褸%d�~ %d�� %d�� �P��%s "+HIW+"%d:"+HIW+"00"+HIC+"�C\n"+NOR,
                                local[LT_YEAR],local[LT_MON]+1,local[LT_MDAY],week,local[LT_HOUR] );
/*
        switch(local[LT_HOUR])
        {
                case 1:
                        str+=HIG+"�i�Ǩ����j�R���o��ߤF�٤���ı�ڡH\n"+NOR;
                        break;
                case 2:
                        str+=HIG+"�i�ǱC�C�j�R���Ѥ��ΤW�ҶܡH\n"+NOR;
                        break;
                case 3:
                        str+=HIG+"�i�Ǧ��Y�j�R�A�A���h�δN���κΤF�C\n"+NOR;
                        break;
                case 4:
                        str+=HIG+"�i�ǩn�n�j�R�A�O��_���٬O�ڥ��S��ı�ڡH\n"+NOR;
                        break;
                case 5:
                        str+=HIG+"�i�ǦѯR�j�R�֤F�ܡH�h�ܪM�@�ئA�V�O�a�C\n"+NOR;
                        break;
                default:
                        break;
        
        }
        */
        message("system",str,users());
        //�w�ɧ�s����
//      RECORD_D->resort_record();
        // ��s�s�D�Y��
        NEWS_D->init();

}

//�C�p�ɪ�30������
void per_min_30()
{

}

// �C 15 ��������       by Shengsan
void per_15_min()
{
        // �έp�Τ��R�W���H��
//      RECORD_D->usage_statistics();
}

// �C 5 ��������       by tmr
void per_5_min()
{
       NEWS_D->broadcast();
// �Ȯɤ����s�D�F by tmr 2009/02/06
}
// �C 1 ��������        by Shengsan
void per_1_min()
{
        //RECORD_D->www_usrlist();
}

void clock_23h59m()     // �C�� 23 �I 59 ������
{
}

void clock_0() // �b�]12�I05������, �׶}���I�B�z�H�K�L������
{
}

void clock_1() { }
void clock_2() { }
void clock_3() { }
void clock_4() { }
void clock_5() { }
void clock_6() { }
void clock_7() { }
void clock_8() { }
void clock_9() { }
void clock_10() { }
void clock_11() { }
void clock_12() { }
void clock_13() { }
void clock_14() { }
void clock_15() { }
void clock_16() { }
void clock_17() { }
void clock_18() { }
void clock_19() { }
void clock_20() { }
void clock_21() { }
void clock_22() { }
void clock_23() { }

void init_time()
{
        // Get time of today.
        local = localtime(REAL_TIME_TICK);
        current_month = local[LT_MON]; //0~11
        current_day = local[LT_MDAY]; //1~31
        current_week = local[LT_WDAY]; //0~6 (0==�P����)
        current_hour = local[LT_HOUR]; //0~23
        current_min = local[LT_MIN]; //0~59


        // Get time of today.
        game_time = localtime(GAME_TIME_TICK);
        current_game_month= game_time[LT_MON]; //0~11
        current_game_day = game_time[LT_MDAY]; //1~31
        current_game_week = game_time[LT_WDAY]; //0~6
        current_game_hour = game_time[LT_HOUR]; //0~23
        current_game_min = game_time[LT_MIN];   //0~59
        
        call_out("update_time",60-game_time[LT_MIN]);
}

mixed query_game_time(int a)
{
        mixed *game_time;
        game_time = localtime(GAME_TIME_TICK);
        return game_time;
}

void update_time()
{
        int pre_week,pre_hour,pre_min,pre_game_month,pre_game_day,pre_game_week,pre_game_hour;
        string week;

        remove_call_out("update_time");
        pre_week=current_week;
        pre_hour=current_hour;
        pre_min=current_min;
        
        pre_game_month=current_game_month;
        pre_game_day=current_game_day;
        pre_game_week=current_game_week;
        pre_game_hour=current_game_hour;
        
        // Get REAL time of today.
        local = localtime(REAL_TIME_TICK);
        current_month = local[LT_MON]; //0~11
        current_week = local[LT_WDAY]; //0~6
        current_day = local[LT_MDAY]; //1~31
        current_hour = local[LT_HOUR]; //0~23
        current_min = local[LT_MIN];   //0~59

        // Get time of GAME.
        game_time = localtime(GAME_TIME_TICK);
        current_game_month= game_time[LT_MON]; //0~11
        current_game_day = game_time[LT_MDAY]; //1~31
        current_game_week = game_time[LT_WDAY]; //0~6
        current_game_hour = game_time[LT_HOUR];   //0~23
        
        if( current_hour == 23 && pre_min==58 && current_min==59)
                clock_23h59m();
                
        if(pre_game_hour!=current_game_hour)
        {
                switch(current_game_hour)
                {
                        case 4:
                                NATURE_D->update_day_phase(DAWN_PHASE);
                                break;
                        case 5:
                                NATURE_D->update_day_phase(SUNRISE_PHASE);
                                break;
                        case 7:
                                NATURE_D->update_day_phase(MORNING_PHASE);
                                break;
                        case 12:
                                NATURE_D->update_day_phase(NOON_PHASE);
                                break;
                        case 16:
                                NATURE_D->update_day_phase(AFTERNOON_PHASE);
                                break;
                        case 19:
                                NATURE_D->update_day_phase(EVENING_PHASE);
                                break;
                        case 21:
                                NATURE_D->update_day_phase(NIGHT_PHASE);
                                break;
                        case 0:
                                NATURE_D->update_day_phase(MIDNIGHT_PHASE);
                                // add by -alickyuen@ds-  for club bank �۰ʬ��Q��
//                              if( current_game_day == 1 ) 
//                                      BANK_D->interest_receive();
                                break;
                        default:
                                break;
                }
        }

        //����
        if(pre_min==59 && current_min==0)
        {
                every_hour();
        }
        else
        if(pre_min==29 && current_min==30) //�C��30����
        {
                per_min_30();
        }
        else
        if((pre_min==14 && current_min==15) ||
           (pre_min==29 && current_min==30) ||
           (pre_min==44 && current_min==45) ||
           (pre_min==59 && current_min==0)  )
        {
        //      per_15_min();           // �C 15 ���� by Shengsan
        }
        
         if( current_min % 5 ==0 && pre_min%5==4 )  {
              per_5_min();           // �C 5 ����
        }

        if(pre_min==4 && current_min==5)
        {
                switch(current_hour)
                {
                        case 0: clock_0();
                                break;
                        case 1: clock_1();
                                break;
                        case 2: clock_2();
                                break;
                        case 3: clock_3();
                                break;
                        case 4: clock_4();
                                break;
                        case 5: clock_5();
                                break;
                        case 6: clock_6();
                                break;
                        case 7: clock_7();
                                break;
                        case 8: clock_8();
                                break;
                        case 9: clock_9();
                                break;
                        case 10: clock_10();
                                break;
                        case 11: clock_11();
                                break;
                        case 12: clock_12();
                                break;
                        case 13: clock_13();
                                break;
                        case 14: clock_14();
                                break;
                        case 15: clock_15();
                                break;
                        case 16: clock_16();
                                break;
                        case 17: clock_17();
                                break;
                        case 18: clock_18();
                                break;
                        case 19: clock_19();
                                break;
                        case 20: clock_20();
                                break;
                        case 21: clock_21();
                                break;
                        case 22: clock_22();
                                break;
                        case 23: clock_23();
                                break;

                        default:
                                break;
                }
        } 
        
        //per_1_min();          // �C 1 ���� by Shengsan

        call_out("update_time",60-game_time[LT_MIN]);
        return;
}


