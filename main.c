//////////////////////////////////////////////////////////////////////////////////	 
//              SSD1306_OLED_128*64说明(选用SPI接口): 
//              ----------------------------------------------------------------
//              GND    电源地
//              VCC  接5V或3.3v电源
//              D0   P1^0（SCL）
//              D1   P1^1（SDA）
//              RES  接P12
//              DC   接P13
//              CS   接P14               
//              ----------------------------------------------------------------
//******************************************************************************/
#include "reg51.h"
#include "header_file/oled.h"
//#include "header_file/bmp.h"			  //51测试，节省空间					  
#include "clock_c/clock.h"
#include "delay_c/delay.h"

//按键定义
sbit key1 = P1^5;
sbit key2 = P1^6;
sbit key3 = P1^7;
sbit int0 = P3^2;

uchar time_one[6];				//时间按位分解,每个数字占一位
uchar day_one[11];				//日期按位分解,每个数字占一位
uchar time_two[4];				//时间储存数组，时分秒各占一位
uchar day_two[4];				//日期储存数组，年月日各占一位
uchar time_day[13];				//未计算偏移地址的时间日期
uchar SIZE = 16;						//字体大小选择，16/12

uchar key_check;




//外部中断初始化函数，用于按键检测
void int0_init()
{
	EX0 = 1;
	IT0 = 1;
}

//外部中断0服务函数
void int0_key()  interrupt 0
{

	if(key1 == 0)
		{delay_ms(10);if(key1 == 0)
			key_check = 1;
		}
	if(key2 == 0)
		{delay_ms(10);if(key2 == 0)
			key_check = 2;
		}
	if(key3 == 0)
		{delay_ms(10);if(key3 == 0)
			key_check = 3;
		}
}


void time_day_out()
{
	TR0 = 1;
	time_date(time_one,day_one,time_two,day_two,time_day);  
	OLED_ShowCHinese1(20,1,time_day[0]);// 小时
	OLED_ShowCHinese1(37,1,time_day[1]);
	OLED_ShowCHinese1(52,1,10);//:
	OLED_ShowCHinese1(68,1,time_day[2]);//分钟
	OLED_ShowCHinese1(85,1,time_day[3]);
	SIZE = 12;
	OLED_ShowChar(102,2,time_day[4]+'0',&SIZE);
	OLED_ShowChar(108,2,time_day[5]+'0',&SIZE);
	OLED_ShowString(47,5,day_one,&SIZE);
}

void time_day_seting()
{
	uchar key2_logger = 0;
	SIZE = 16;
	while(1)
	{
	 	OLED_ShowString(8,0,"Please set hour:",&SIZE);
	 	switch(key_check)
	 	{
	 		case 1:break;
			case 2:key2_logger++;break;
			case 3:clock_hour_addone();break;
	 	}
	 	while(key2_logger == 1)
		{
			OLED_ShowString(8,0,"Please set minute:",&SIZE);
			switch(key_check)
	 		{
	 			case 1:break;
				case 2:key2_logger++;break;
				case 3:clock_min_addone();break;
	 		}	
		}
		while(key2_logger == 2)
		{
			OLED_ShowString(8,0,"Please set second:",&SIZE);
			switch(key_check)
	 		{
	 			case 1:break;
				case 2:key2_logger++;break;
				case 3:clock_sec_addone();break;
	 		}	
		}
		while(key2_logger == 3)
		{
			OLED_ShowString(8,0,"Please set year:",&SIZE);
			switch(key_check)
	 		{
	 			case 1:break;
				case 2:key2_logger++;break;
				case 3:clock_year_addone();break;
	 		}	
		}
		while(key2_logger == 4)
		{
			OLED_ShowString(8,0,"Please set month:",&SIZE);
			switch(key_check)
	 		{
	 			case 1:break;
				case 2:key2_logger++;break;
				case 3:clock_mon_addone();break;
	 		}	
		}
		while(key2_logger == 5)
		{
			OLED_ShowString(8,0,"Please set day:",&SIZE);
			switch(key_check)
	 		{
	 			case 1:break;
				case 2:key2_logger++;break;
				case 3:clock_day_addone();break;
	 		}	
		}
		break;	
	}
}


void  main()
{		  
	OLED_Init();			        //初始化OLED  
	OLED_Clear();				
	time_init(); 
/*	OLED_Clear();					//8051测试，FLASH空间4K，测试正常，故省略,开机动画
	delay_ms(200);
	OLED_DrawBMP(0,0,128,8,BMP1);   //图片显示(图片显示慎用，生成的字表较大，会占用较多空间，FLASH空间8K以下慎用)
	delay_ms(500);	*/
	 
	while(1)
	{
		if(key_check != 0)
		{
			switch(key_check)
			{
				case 1:time_day_seting();break;
//				case 2:stopwatch();break;
//				case 3:say_hello;
			}	
		}
		time_day_out();		

//	OLED_ShowNum(56,2,time_two[2],3,&SIZE);
/*	OLED_ShowString(0,6,"ASCII:");  
	OLED_ShowString(63,6,"CODE:");  
	OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 		*/		
	}
}	  
	