#include "key_c/key.h"
#include "delay_c/delay.h"


//������⺯����������·��ذ�����ţ����򷵻�4
uchar key_check(uchar *key)
{
	uchar i;
	for(i = 0;i < 3;i++)
	{
		if((*(key+i)) == 0)
		{
			delay_ms(10);
			if((*(key+i)) == 0)
			return i;
		}
	else return 4;
	}
}