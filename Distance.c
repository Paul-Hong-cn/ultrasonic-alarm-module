#include <REGX52.H>
sbit Trig = P1^6;
sbit Echo = P1^7;

unsigned int time;
unsigned int s;
void delayxus(unsigned int xus)
{
	while(xus--);
}
void Time1Init()
{
	TMOD &= 0x0F; // ���T1��صĸ���λ������T0���ò���
	TMOD |= 0x10; // ����T1Ϊģʽ1
	TH1 = 0;
	TL1 = 0;
	TR1 = 0;
}

int Distance()
{
	while(1)
	{
		Trig = 1;
		delayxus(2);
		Trig = 0;
	
		while(!Echo);
		TR1 = 1;
		while(Echo);
		TR1 = 0;
		time = TH1*256 + TL1;
		s = (time*1.7)/100;
		
		TH1 = 0;
		TL1 = 0;
		
		return s;
	}
}
