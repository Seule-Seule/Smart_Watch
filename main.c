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
#include "key_c/key.h"

uchar time_one[6];				//时间按位分解,每个数字占一位
uchar day_one[11];				//日期按位分解,每个数字占一位
uchar time_two[4];				//时间储存数组，时分秒各占一位
uchar day_two[4];				//日期储存数组，年月日各占一位
uchar time_day[13];				//未计算偏移地址的时间日期
uchar SIZE;						//字体大小选择，16/12
uchar key[3] = 1;					//按键检测函数
uchar key_lest;                 //按键检测返回值


void time_day_out(uchar *p)
{

	SIZE = *p;
	time_date(time_one,day_one,time_two,day_two,time_day);  
	OLED_ShowCHinese1(20,1,time_day[0]);// 小时
	OLED_ShowCHinese1(37,1,time_day[1]);
	OLED_ShowCHinese1(52,1,10);//:
	OLED_ShowCHinese1(68,1,time_day[2]);//分钟
	OLED_ShowCHinese1(85,1,time_day[3]);
	OLED_ShowChar(102,2,time_day[4]+'0',&SIZE);
	OLED_ShowChar(108,2,time_day[5]+'0',&SIZE);
	SIZE = 12;
	OLED_ShowString(47,5,day_one,&SIZE);
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
	time_day_out(&SIZE);
	key_lest = key_check(key);
	switch(key_lest)
	{
		case 0:
		case 1:
		case 2:
	}
//	OLED_ShowNum(56,2,time_two[2],3,&SIZE);
/*	OLED_ShowString(0,6,"ASCII:");  
	OLED_ShowString(63,6,"CODE:");  
	OLED_ShowNum(103,6,t,3,16);//显示ASCII字符的码值 		*/		
	}
}	  
	