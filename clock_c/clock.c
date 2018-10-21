#include "clock.h"
uint clock_date,clock_sec_h,clock_sec_l,clock_min_h,clock_min_l,clock_hour_h,clock_hour_l,clock_day_h,clock_day_l,clock_mon_h,clock_mon_l,clock_year_h1,clock_year_h2,clock_year_l1,clock_year_l2;
uint clock_sec=0,clock_min=30,clock_hour=12,clock_day=19,clock_mon=10,clock_year=2018;


//12M晶振，每50ms引起一次中断
void time_init()			   
{
	TMOD = 0x01;                              //选择定时器0工作方式1
	TH0 = 0x4C;                               //定时控制，每50ms中断一次
	TL0 = 0x00;
	EA = 1;                                   //开总中断
	ET0 = 0x01;                               //开启t0中断允许位
//	TR0 = 1;
}


//定时器服务子函数，实现时分秒转化
void time0()interrupt 1
{
	uint x;
	TH0 = 0x4C;								  //定时器重装
	TL0 = 0x00;
	clock_date++;
	if(clock_date == 20)				
		{ clock_date = 0;clock_sec++;		  //计时达到一秒
	if(clock_sec == 60)
		{clock_sec = 0;clock_min++;}
	if(clock_min == 60)
		{clock_min = 0;clock_hour++;}
	if(clock_hour == 24)
		{clock_hour = 0;clock_day++;}
	switch(clock_mon)
    {
        case 1:if(clock_day==32){clock_day=1;clock_mon++;}break;
		case 3:if(clock_day==32){clock_day=1;clock_mon++;}break;
   		case 5:if(clock_day==32){clock_day=1;clock_mon++;}break;
    	case 7:if(clock_day==32){clock_day=1;clock_mon++;}break;
    	case 8:if(clock_day==32){clock_day=1;clock_mon++;}break;
    	case 10:if(clock_day==32){clock_day=1;clock_mon++;}break;
    	case 12:if(clock_day==32){clock_day=1;clock_mon++;}break;
    	case 4:if(clock_day==31){clock_day=1;clock_mon++;}break;
    	case 6:if(clock_day==31){clock_day=1;clock_mon++;}break;
    	case 9:if(clock_day==31){clock_day=1;clock_mon++;}break;
    	case 11:if(clock_day==31){clock_day=1;clock_mon++;}break;
    	case 2:x=20*100+clock_year;
        		if((x%4==0 && x%100!=0) || x%400==0)
           		{
          			if(clock_day==30) {clock_day=1;clock_mon++;break;}
      			}
        		else if(clock_day==29) {clock_day=1;clock_mon++;break;}
	}
	if(clock_mon == 13)
		{ clock_mon = 1;clock_year++;}
	}
	clock_sec_h = clock_sec/10;clock_sec_l = clock_sec%10;
	clock_min_h = clock_min/10;clock_min_l = clock_min%10;
	clock_hour_h = clock_hour/10;clock_hour_l = clock_hour%10;
	clock_day_h = clock_day/10;clock_day_l = clock_day%10;
	clock_mon_h = clock_mon/10;clock_mon_l = clock_mon%10;
	clock_year_h1 = clock_year/1000; x = clock_year%1000;
	clock_year_h2 = x/100;	x = x % 100;
	clock_year_l1 = x/10;clock_year_l2 = x%10;
}

void time_date(uchar *time1,uchar *day1,uchar *time2,uchar *day2,uchar *time_day)			 //时间和日历格式化函数
{
	*time1 = '0'+clock_hour_h;									                             //时间格式化，时、分
	*(time1+1) = '0'+clock_hour_l;
	*(time1+2) = ':';
	*(time1+3) = '0'+clock_min_h;
	*(time1+4) = '0'+clock_min_l;

    *day1 = '0'+clock_year_h1;																 //日期格式化，标准显示日期
	*(day1+1) = '0'+clock_year_h2;
	*(day1+2) = '0'+clock_year_l1;
	*(day1+3) = '0'+clock_year_l2;
	*(day1+4) = '/';
	*(day1+5) = '0'+clock_mon_h;
	*(day1+6) = '0'+clock_mon_l;
	*(day1+7) = '/';
	*(day1+8) = '0'+clock_day_h;
	*(day1+9) = '0'+clock_day_l;
	

	*time2 = (*time1)*10+(*(time1+1))-16;													 //时间分解，时、分、秒两位一分解
	*(time2+1) = (*(time1+3))*10+(*(time1+4))-16;
	*(time2+2) = (48+clock_sec_h)*10+(48+clock_sec_l)-16;

	*day2 = (*day1)*1000+(*(day1+1))*100+(*(day1+2))*10+(*(day1+3));						 //日期分解，年、月、日
	*(day2+1) = (*(day1+5))*10+(*(day1+6));
	*(day2+1) = (*(day1+8))*10+(*(day1+9));
	
	*time_day = clock_hour_h;																 //时分秒年月日分解
	*(time_day+1) = clock_hour_l;
	*(time_day+2) = clock_min_h;
	*(time_day+3) = clock_min_l;
	*(time_day+4) = clock_sec_h;
	*(time_day+5) = clock_sec_l;
	*(time_day+6) = clock_year_h1;
	*(time_day+7) = clock_year_h2;
	*(time_day+8) = clock_year_l1;
	*(time_day+9) = clock_year_l2;
	*(time_day+10) = clock_mon_h;
	*(time_day+11) = clock_mon_l;
	*(time_day+12) = clock_day_h;
	*(time_day+13) = clock_day_l;
}

void clock_hour_addone()
{
	clock_hour++;
	if(clock_hour == 24)
		clock_hour = 0;
}

void clock_min_addone()
{
	clock_min++;
	if(clock_min == 60)
		clock_min = 0;
}

void clock_sec_addone()
{
	clock_sec++;
	if(clock_sec == 60)
		clock_sec = 0;
}

void clock_year_addone()
{
	clock_year++;
}

void clock_mon_addone()
{
	clock_mon++;
	if(clock_mon == 13)
		clock_mon = 1;
}

void clock_day_addone()
{
	uint x;
	switch(clock_mon)
    {
        case 1:clock_day++;if(clock_day==32){clock_day=1;}break;
		case 3:clock_day++;if(clock_day==32){clock_day=1;}break;
   		case 5:clock_day++;if(clock_day==32){clock_day=1;}break;
    	case 7:clock_day++;if(clock_day==32){clock_day=1;}break;
    	case 8:clock_day++;if(clock_day==32){clock_day=1;}break;
    	case 10:clock_day++;if(clock_day==32){clock_day=1;}break;
    	case 12:clock_day++;if(clock_day==32){clock_day=1;}break;
    	case 4:clock_day++;if(clock_day==31){clock_day=1;}break;
    	case 6:clock_day++;if(clock_day==31){clock_day=1;}break;
    	case 9:clock_day++;if(clock_day==31){clock_day=1;}break;
    	case 11:clock_day++;if(clock_day==31){clock_day=1;}break;
    	case 2:x=20*100+clock_year;
        		if((x%4==0 && x%100!=0) || x%400==0)
           		{
          			clock_day++;if(clock_day==30) {clock_day=1;break;}
      			}
        		else 
				{clock_day++;if(clock_day==29) clock_day=1;break;}
	}	
}		




						  