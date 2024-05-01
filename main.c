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
	
	LCD_Init();
	Time1Init();
	Alarm_Init();
	LCD_ShowString(1,1,"DISTANCE(cm):");
	LCD_ShowString(2,1,"ALARMING(s):");
	while(1)
    {
		
		currentButtonState = P3_0; 
		if (currentButtonState == 1 && lastButtonState == 1)  // 之前没有按下，现在还是没有按下
        {
			if(isEnabled)
			{
				judge_distance(s1);		
				s1 = Distance();
				LCD_ShowNum(1,14,s1,3);
				alarm_time_1 = Alarm1_Play(s1,times);
				LCD_ShowNum(2,13,alarm_time_1,4);
				times = 0;
			}
			
        }
		else if (currentButtonState == 0 && lastButtonState == 1)  // 之前没有按下，现在按下了
        {
			alarm_time_1 = Alarm_Close();
			LCD_ShowNum(2,10,alarm_time_1,6);
			Light_Close();
			Delayxms(100);
			lastButtonState = currentButtonState;
			isEnabled = !isEnabled;
			times ++;
        }
		
		else if (currentButtonState == 1 && lastButtonState == 0)  // 之前按下了，现在没有按下
        {
			alarm_time_1 = Alarm_Close();
			LCD_ShowNum(2,10,alarm_time_1,6);
			Light_Close();
			Delayxms(100);
			lastButtonState = currentButtonState;
        }
		
        
    }
}
