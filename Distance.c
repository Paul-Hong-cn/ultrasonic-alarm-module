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
		Trig = 0;//�ȸ�trig����������ߵ�ƽ�ź�
	
		while(!Echo);
		TR1 = 1;//�ȴ�Echo���ָߵ�ƽ��Ȼ��ʱ������
		while(Echo);
		TR1 = 0;//֪��Echo���ֵ͵�ƽ��Ȼ��ʱ���ر�
		time = TH1*256 + TL1;
		s = (time*1.7)/100;//
		/*
			������time��΢�뼶��Ҫ����������ױ�ʾ�ľ��룬��Ҫ���ȳ���10^6Ȼ�����340�����٣���
			����2���õ����ξ��룩���������ʱ��*100���õ�������Ϊ��λ�ľ��룩�����������ǳ���1.7�ٳ���100
		*/
		TH1 = 0;
		TL1 = 0;
		
		return s;
	}
}
