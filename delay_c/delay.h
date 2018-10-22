#include "intrins.h"
#include "reg51.h"
#define  uchar unsigned char 
#define  uint unsigned int 
#define  usint unsigned short int  
/***********************************************************
 *					延时函数
 * 		  开发板晶振是12MHZ的，每个机器周期1us
*************************************************************/

#define delay1us()	_nop_();_nop_()         //延时2us

void delay1ms();							//延时1ms
void delay_ms(usint s);			            //延时s ms