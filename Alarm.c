#include <REGX52.H>
#include "Delayxms.h"
#include "LCD1602.h"

sbit Buzzer = P2^5;
#define SPEED 500

#define P0  0
#define L1  1
#define L1_ 2
#define L2  3
#define L2_ 4
#define L3  5
#define L4  6
#define L4_ 7
#define L5  8
#define L5_ 9
#define L6  10
#define L6_ 11
#define L7  12
#define M1  13
#define M1_ 14
#define M2  15
#define M2_ 16
#define M3  17
#define M4  18
#define M4_ 19
#define M5  20
#define M5_ 21
#define M6  22
#define M6_ 23
#define M7  24
#define H1  25
#define H1_ 26
#define H2  27
#define H2_ 28
#define H3  29
#define H4  30
#define H4_ 31
#define H5  32
#define H5_ 33
#define H6  34
#define H6_ 35
#define H7  36


unsigned int FreqTable[] = {
    0,
	63628, 63731, 63835, 63928, 64021, 64103, 64185, 64260, 64331, 64400, 64463, 64524,
    64580, 64633, 64684, 64732, 64777, 64820, 64860, 64898, 64934, 64968, 65000, 65030,
    65058, 65085, 65110, 65134, 65157, 65178, 65198, 65217, 65235, 65252, 65268, 65283,
    
};
unsigned char code Alarm1[]={
	M5,2,
	M7,2,
	H1,2,
	M5,2,
	M7,2,
	H1,2,
	M5,2,
	M7,2,
	
	M5,2,
	M7,2,
	H1,2,
	M5,2,
	M7,2,
	H1,2,
	M5,2,
	M7,2,
	
	M5,2,
	M7,2,
	H1,2,
	M5,2,
	M7,2,
	H1,2,
	M5,2,
	M7,2,
	
	M5,2,
	H1,2,
	H2,2,
	M5,2,
	H1,2,
	H2,2,
	M5,2,
	H1,2
	
};//天气之子
unsigned char code Alarm2[]={
	M5,2,
	M6,2,
	H2,2,
	M5,2,
	M6,2,
	H2,2,
	M5,2,
	M6,2,
	M5,2,
	M6,2,
	H1,2,
	M5,2,
	M6,2,
	
	M6,2,
	H1,2,
	H3,2,
	M6,2,
	H1,2,
	H3,2,
	M6,2,
	H1,2,
	M6,2,
	H1,2,
	H2,2,
	M6,2,
	H1,2,
	H2,2,
	M6,2,
	H1,2,
	
	M6,2,
	H1,2,
	H2,2,
	M6,2,
	H1,2,
	H2,2,
	M6,2,
	H1,2,
	M5,2,
	M6,2,
	H1,2,
	M5,2,
	M6,2,
	H1,2,
	M5,2,
	M6,2,
	
	M5,2,
	H1,2,
	H5,2,
	M5,2,
	H1,2,
	H5,2,
	M5,2,
	H1,2,
	M6,2,
	H1,2,
	H2,2,
	M6,2,
	H1,2,
	H2,2,
	M6,2,
	H1,2
};//Time to Pretend
unsigned char code Alarm3[]={
	//1
	H3,2,
	H2_,2,
	
	H3,2,
	H2_,2,
	H3,2,
	M7,2,
	H2_,2,
	H1,2,
	
	M6,4,
	P0,2,
	M1,2,
	M3,2,
	M6,2,
	
	M7,4,
	P0,2,
	M3,2,
	M5_,2,
	M7,2,
	//2
	H1,4,
	P0,4,
	H3,2,
	H2_,2,
	
	H3,2,
	H2_,2,
	H3,2,
	M7,2,
	H2_,2,
	H1,2,
	
	M6,4,
	P0,2,
	M1,2,
	M3,2,
	M6,2,
	//3
	M7,4,
	P0,2,
	M3,2,
	H1,2,
	M7,2,
	
	M6,4,
	P0,2,
	M7,2,
	H1,2,
	H2,2,
	
	H3,4,
	P0,2,
	M5,2,
	H4,2,
	H3,2,
	//4
	H2,4,
	P0,2,
	M4,2,
	H3,2,
	H2,2,
	
	H1,4,
	P0,2,
	M3,2,
	H2,2,
	H1,2,
	M7,4+4+4
};//致爱丽丝
xdata unsigned char FreqSelect, Alarm1Select,Alarm2Select,Alarm3Select;
xdata unsigned int s2,s3;
xdata unsigned int Alarm_on ;
xdata unsigned int alarm_time_0 = 0;
xdata unsigned int alarm_time_2 = 0;
/*
这里是有三组音乐，根据简谱和C调频率表转换成对应的频率，我在程序中已经定义好C调频率表的对应频率，
只需要调动常量即可，具体请看B站视频。从距离来看由近至远天空之城，回家，致爱丽丝
*/
void Alarm_Init()
{
	TMOD &= 0xF0;	// 清除T0相关的低四位，保持T1设置不变	
	TMOD |= 0x01;	// 设置T0为模式1	
	TL0 = 0x18;		
	TH0 = 0xFC;		//定时1ms
	TF0 = 0;		
	TR0 = 1;		//定时器0开始计时
	ET0=1;//允许定时器0中断
	EA=1;//允许全局中断
	PT0=1;	//定时器0优先级为高优先级
    Alarm1Select = 0;
	Alarm2Select = 0;
	Alarm3Select = 0;
	Alarm_on = 0;
}

int Alarm1_Play(unsigned int s2,unsigned int times)
{
	
	if (s2 >=0 && s2 < 20 )
	{
		if(times != 0 || Alarm_on != 0)
		{
			/*
			从暂停到报警，音乐需要重新开始
			当我距离从状态A转移到状态B时，也需要重新开始播放
			*/
			Alarm1Select = 0;
			alarm_time_0 = 0;
			alarm_time_2 = 0;
		}
		FreqSelect= Alarm1[Alarm1Select];
		Alarm1Select++;
		Delayxms(125*Alarm1[Alarm1Select]);
		alarm_time_0 += 125*Alarm1[Alarm1Select] ;
		alarm_time_2 = alarm_time_0 / 1000 ;
		Alarm1Select++;
		if(Alarm1Select >= sizeof(Alarm1))
		{
			Alarm1Select  = 0;//如果音乐播放完就从头开始播放
		}
		TR0 = 0;
		Delayxms(5);
		TR0 = 1;
		Alarm_on = 0;
	}
	else if (s2 >= 20 && s2 < 40  )
	{
		if(times != 0 || Alarm_on != 1)
		{
			Alarm2Select = 0;
			alarm_time_0 = 0;
			alarm_time_2 = 0;
		}
		FreqSelect= Alarm2[Alarm2Select];
		Alarm2Select++;
		Delayxms(125*Alarm2[Alarm2Select]);
		alarm_time_0 += 125*Alarm2[Alarm2Select] ;
		alarm_time_2 = alarm_time_0 / 1000 ;
		Alarm2Select++;
		if(Alarm2Select >= sizeof(Alarm2))
		{
			Alarm2Select  = 0;
		}
		TR0 = 0;
		Delayxms(5);
		TR0 = 1;
		Alarm_on = 1;
	}
	else if (s2 >= 40 && s2 < 60  )
	{
		if(times != 0 || Alarm_on != 2)
		{
			Alarm3Select = 0;
			alarm_time_0 = 0;
			alarm_time_2 = 0;
		}
		FreqSelect= Alarm3[Alarm3Select];
		Alarm3Select++;
		Delayxms(125*Alarm3[Alarm3Select]);
		alarm_time_0 += 125*Alarm3[Alarm3Select] ;
		alarm_time_2 = alarm_time_0 / 1000 ;
		Alarm3Select++;
		if(Alarm3Select >= sizeof(Alarm3))
		{
			Alarm3Select  = 0;
		}
		TR0 = 0;
		Delayxms(5);
		
		TR0 = 1;
		Alarm_on = 2;
	}
	else
	{
		Alarm1Select = 0;
		Alarm2Select = 0;
		Alarm3Select = 0;
		TR0 = 0;
		Buzzer = 1;
		Alarm_on = 3;
	}
	return alarm_time_2;
}

void MusicPlayer_TimerRoutine(void) interrupt 1
{
	/*
	这里是通过频率转换实现音调的转换，在Alarm1_Play主函数中音乐数组的索引不断增加，奇索引是音调，偶索引是音调持续的时间。
	*/
    if(TR0)
	{
		if(FreqTable[FreqSelect]) {
			TL0 = FreqTable[FreqSelect] % 256;        
			TH0 = FreqTable[FreqSelect] / 256;        
			Buzzer = !Buzzer;
		}
	}
	else
	{
		Buzzer = 1;
	}
	
}



int Alarm_Close()
{
	TR0 = 0;
	Buzzer = 1;
	alarm_time_0 = 0;
	alarm_time_2 = 0;
	return alarm_time_2;
}