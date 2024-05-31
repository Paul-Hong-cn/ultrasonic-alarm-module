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
	TMOD &= 0x0F; // 清除T1相关的高四位，保持T0设置不变
	TMOD |= 0x10; // 设置T1为模式1
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
		Trig = 0;//先给trig持续两毫秒高电平信号
	
		while(!Echo);
		TR1 = 1;//等待Echo出现高电平，然后定时器开启
		while(Echo);
		TR1 = 0;//知道Echo出现低电平，然后定时器关闭
		time = TH1*256 + TL1;
		s = (time*1.7)/100;//
		/*
			这里测的time是微秒级别，要计算成以厘米表示的距离，需要首先除以10^6然后乘以340（声速），
			除以2（得到单次距离），计算出的时间*100（得到以厘米为单位的距离），合下来就是乘以1.7再除以100
		*/
		TH1 = 0;
		TL1 = 0;
		
		return s;
	}
}
