#include "intrins.h"
#include "reg51.h"
#define  uchar unsigned char 
#define  uint unsigned int 
#define  usint unsigned short int  
/***********************************************************
 *					��ʱ����
 * 		  �����徧����12MHZ�ģ�ÿ����������1us
*************************************************************/

#define delay1us()	_nop_();_nop_()         //��ʱ2us

void delay1ms();							//��ʱ1ms
void delay_ms(usint s);			            //��ʱs ms