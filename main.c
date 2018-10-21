//////////////////////////////////////////////////////////////////////////////////	 
//              SSD1306_OLED_128*64˵��(ѡ��SPI�ӿ�): 
//              ----------------------------------------------------------------
//              GND    ��Դ��
//              VCC  ��5V��3.3v��Դ
//              D0   P1^0��SCL��
//              D1   P1^1��SDA��
//              RES  ��P12
//              DC   ��P13
//              CS   ��P14               
//              ----------------------------------------------------------------
//******************************************************************************/
#include "reg51.h"
#include "header_file/oled.h"
//#include "header_file/bmp.h"			  //51���ԣ���ʡ�ռ�					  
#include "clock_c/clock.h"
#include "delay_c/delay.h"

//��������
sbit key1 = P1^5;
sbit key2 = P1^6;
sbit key3 = P1^7;
sbit int0 = P3^2;

uchar time_one[6];				//ʱ�䰴λ�ֽ�,ÿ������ռһλ
uchar day_one[11];				//���ڰ�λ�ֽ�,ÿ������ռһλ
uchar time_two[4];				//ʱ�䴢�����飬ʱ�����ռһλ
uchar day_two[4];				//���ڴ������飬�����ո�ռһλ
uchar time_day[13];				//δ����ƫ�Ƶ�ַ��ʱ������
uchar SIZE = 16;						//�����Сѡ��16/12

uchar key_check;




//�ⲿ�жϳ�ʼ�����������ڰ������
void int0_init()
{
	EX0 = 1;
	IT0 = 1;
	EA = 1;
}

//�ⲿ�ж�0������
void int_0()  interrupt 0
{
	EX0 = 0;
	if(key1 == 0)
		{delay_ms(100);if(key1 == 0)
			key_check = 1;
		}
	if(key2 == 0)
		{delay_ms(100);if(key2 == 0)
			key_check = 2;
		}
	if(key3 == 0)
		{delay_ms(100);if(key3 == 0)
			key_check = 3;
		}
	EX0 = 1;
}


void time_day_out()
{
	TR0 = 1;
	time_date(time_one,day_one,time_two,day_two,time_day);  
	OLED_ShowCHinese1(20,1,time_day[0]);// Сʱ
	OLED_ShowCHinese1(37,1,time_day[1]);
	OLED_ShowCHinese1(52,1,10);//:
	OLED_ShowCHinese1(68,1,time_day[2]);//����
	OLED_ShowCHinese1(85,1,time_day[3]);
	SIZE = 12;
	OLED_ShowChar(102,2,time_day[4]+'0',&SIZE);
	OLED_ShowChar(108,2,time_day[5]+'0',&SIZE);
	OLED_ShowString(47,5,day_one,&SIZE);
}

void time_day_seting()
{
	uint key2_logger = 0;
	OLED_Clear();
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
	OLED_Init();			        //��ʼ��OLED  
	OLED_Clear();				
	time_init(); 
	int0_init();
	PX0 = 1;
	PT0 = 0;
/*	OLED_Clear();					//8051���ԣ�FLASH�ռ�4K��������������ʡ��,��������
	delay_ms(200);
	OLED_DrawBMP(0,0,128,8,BMP1);   //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
	delay_ms(500);	*/
	 
	while(1)
	{
		while(key_check)
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
	OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ 		*/		
	}
}	  
	