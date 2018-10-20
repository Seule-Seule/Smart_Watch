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
#include "key_c/key.h"

uchar time_one[6];				//ʱ�䰴λ�ֽ�,ÿ������ռһλ
uchar day_one[11];				//���ڰ�λ�ֽ�,ÿ������ռһλ
uchar time_two[4];				//ʱ�䴢�����飬ʱ�����ռһλ
uchar day_two[4];				//���ڴ������飬�����ո�ռһλ
uchar time_day[13];				//δ����ƫ�Ƶ�ַ��ʱ������
uchar SIZE;						//�����Сѡ��16/12
uchar key[3] = 1;					//������⺯��
uchar key_lest;                 //������ⷵ��ֵ


void time_day_out(uchar *p)
{

	SIZE = *p;
	time_date(time_one,day_one,time_two,day_two,time_day);  
	OLED_ShowCHinese1(20,1,time_day[0]);// Сʱ
	OLED_ShowCHinese1(37,1,time_day[1]);
	OLED_ShowCHinese1(52,1,10);//:
	OLED_ShowCHinese1(68,1,time_day[2]);//����
	OLED_ShowCHinese1(85,1,time_day[3]);
	OLED_ShowChar(102,2,time_day[4]+'0',&SIZE);
	OLED_ShowChar(108,2,time_day[5]+'0',&SIZE);
	SIZE = 12;
	OLED_ShowString(47,5,day_one,&SIZE);
}

void  main()
{		  
	OLED_Init();			        //��ʼ��OLED  
	OLED_Clear();
	time_init(); 
/*	OLED_Clear();					//8051���ԣ�FLASH�ռ�4K��������������ʡ��,��������
	delay_ms(200);
	OLED_DrawBMP(0,0,128,8,BMP1);   //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ�ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
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
	OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ 		*/		
	}
}	  
	