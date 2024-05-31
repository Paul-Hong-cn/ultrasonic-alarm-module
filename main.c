#include <REGX52.H>
#include "LCD1602.h"
#include "Distance.h"
#include "led.h"
#include "Alarm.h"
#include "Delayxms.h"

xdata unsigned int times = 0;
xdata unsigned int s1,currentButtonState;
xdata unsigned int lastButtonState = 1;
xdata unsigned int isEnabled = 1;
xdata unsigned int alarm_time_1 = 0;


void main()
{
	
	LCD_Init();//初始化LCD屏幕
	Time1Init();//测距模块初始化，测距模块使用定时器1，所以这里用Time1Init作为函数名
	Alarm_Init();//报警模块初始化
	LCD_ShowString(1,1,"DISTANCE(cm):");//LCD屏显示DISTANCE
	LCD_ShowString(2,1,"ALARMING(s):");//LCD屏显示ALARMING
	while(1)
    {
		currentButtonState = P3_0; //确认当前按键状态
		if(currentButtonState != lastButtonState)
		{
			Delayxms(50);//去抖动
			
		    if (currentButtonState == 0 && lastButtonState == 1)  // 之前没有按下，现在按下了
			{
				alarm_time_1 = Alarm_Close();//关闭报警模块，报警时间归零
				LCD_ShowNum(2,13,alarm_time_1,4);//显示归零报警时间
				Light_Close();//LED灯熄灭
				Delayxms(100);
				lastButtonState = currentButtonState;//改变当前状态，进入第三个函数
				isEnabled = !isEnabled;//使能信号为零，报警模块不工作
				times ++;//这里times不为零，决定了当重新报警时我需要从头开始播放
			}
			
			else if (currentButtonState == 1 && lastButtonState == 0)  // 之前按下了，现在没有按下
			{
				alarm_time_1 = Alarm_Close();
				LCD_ShowNum(2,13,alarm_time_1,4);
				Light_Close();
				Delayxms(100);
				lastButtonState = currentButtonState;//改变当前状态，进入第一个函数
				times ++;
			}
		}
		else if (currentButtonState == 1 && lastButtonState == 1)  // 之前没有按下，现在还是没有按下
        {
			if(isEnabled)//如果为1，说明之前没有按下暂停键。如果为0，则说明之前暂停键按下过，需要再按一遍才能进入报警模块，等待按下后进入第二个函数
			{
				
				s1 = Distance();//测距
				judge_distance(s1);	//通过测得的距离决定LED灯闪亮，这里函数前后顺序没什么关系	
				LCD_ShowNum(1,14,s1,3);//显示所测距离
				alarm_time_1 = Alarm1_Play(s1,times);//测算报警时间
				LCD_ShowNum(2,13,alarm_time_1,4);//显示报警时间
				times = 0;//决定报警模块是否要从头播放音乐的关键变量
			}
			
        }
		
        
    }
}
