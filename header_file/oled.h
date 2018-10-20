//////////////////////////////////////////////////////////////////////////////////	 
//              ËµÃ÷(Ñ¡ÓÃSPI½Ó¿Ú): 
//              ----------------------------------------------------------------
//              GND    µçÔ´µØ
//              VCC  ½Ó5V»ò3.3vµçÔ´
//              D0   P1^0£¨SCL£©
//              D1   P1^1£¨SDA£©
//              RES  ½ÓP12
//              DC   ½ÓP13
//              CS   ½ÓP14               
//              ----------------------------------------------------------------
//******************************************************************************/
#include "reg51.h"
#ifndef __OLED_H
#define __OLED_H			  	 
//#include "sys.h"
//#include "stdlib.h"	  
#define  uchar unsigned char 
#define  uint unsigned int
 
#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý
#define OLED_MODE 0

sbit OLED_CS=P1^4; //Æ¬Ñ¡
sbit OLED_RST =P1^2;//¸´Î»
sbit OLED_DC =P1^3;//Êý¾Ý/ÃüÁî¿ØÖÆ
sbit OLED_SCL=P1^0;//Ê±ÖÓ D0£¨SCLK£
sbit OLED_SDIN=P1^1;//D1£¨MOSI£© Êý¾Ý


#define OLED_CS_Clr()  OLED_CS=0
#define OLED_CS_Set()  OLED_CS=1

#define OLED_RST_Clr() OLED_RST=0
#define OLED_RST_Set() OLED_RST=1

#define OLED_DC_Clr() OLED_DC=0
#define OLED_DC_Set() OLED_DC=1

#define OLED_SCLK_Clr() OLED_SCL=0
#define OLED_SCLK_Set() OLED_SCL=1

#define OLED_SDIN_Clr() OLED_SDIN=0
#define OLED_SDIN_Set() OLED_SDIN=1;



//OLEDÄ£Ê½ÉèÖÃ
//0:4Ïß´®ÐÐÄ£Ê½
//1:²¢ÐÐ8080Ä£Ê½

//#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	    						  
//-----------------OLED¶Ë¿Ú¶¨Òå----------------  					   

//OLED¿ØÖÆÓÃº¯Êý
void OLED_WR_Byte(uchar dat,uchar cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uchar x,uchar y,uchar t);
void OLED_Fill(uchar x1,uchar y1,uchar x2,uchar y2,uchar dot);
void OLED_ShowChar(uchar x,uchar y,uchar chr,uchar *SIZE);
void OLED_ShowNum(uchar x,uchar y,uint num,uchar len,uchar *size2);
void OLED_ShowString(uchar x,uchar y,uchar *chr,uchar *size);	 
void OLED_Set_Pos(uchar x, uchar y);
void OLED_ShowCHinese(uchar x,uchar y,uchar no);
void OLED_DrawBMP(uchar x0, uchar y0,uchar x1, uchar y1,uchar BMP[]);
void OLED_ShowCHinese1(uchar x,uchar y,uchar no);
#endif  
	 



