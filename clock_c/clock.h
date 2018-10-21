#include "reg51.h"

#define  uchar unsigned char 
#define  uint unsigned int 



void time_init();													                     //定时器初始化函数
void time_date(uchar *time1,uchar *day1,uchar *time2,uchar *day2,uchar *time_day);		 //时间和日历格式化函数
void clock_hour_addone();
void clock_min_addone();
void clock_sec_addone()	 ;
void clock_year_addone()	;
void clock_mon_addone()   ;
void clock_day_addone()  ;
