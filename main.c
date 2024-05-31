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
	
	LCD_Init();//��ʼ��LCD��Ļ
	Time1Init();//���ģ���ʼ�������ģ��ʹ�ö�ʱ��1������������Time1Init��Ϊ������
	Alarm_Init();//����ģ���ʼ��
	LCD_ShowString(1,1,"DISTANCE(cm):");//LCD����ʾDISTANCE
	LCD_ShowString(2,1,"ALARMING(s):");//LCD����ʾALARMING
	while(1)
    {
		currentButtonState = P3_0; //ȷ�ϵ�ǰ����״̬
		if(currentButtonState != lastButtonState)
		{
			Delayxms(50);//ȥ����
			
		    if (currentButtonState == 0 && lastButtonState == 1)  // ֮ǰû�а��£����ڰ�����
			{
				alarm_time_1 = Alarm_Close();//�رձ���ģ�飬����ʱ�����
				LCD_ShowNum(2,13,alarm_time_1,4);//��ʾ���㱨��ʱ��
				Light_Close();//LED��Ϩ��
				Delayxms(100);
				lastButtonState = currentButtonState;//�ı䵱ǰ״̬���������������
				isEnabled = !isEnabled;//ʹ���ź�Ϊ�㣬����ģ�鲻����
				times ++;//����times��Ϊ�㣬�����˵����±���ʱ����Ҫ��ͷ��ʼ����
			}
			
			else if (currentButtonState == 1 && lastButtonState == 0)  // ֮ǰ�����ˣ�����û�а���
			{
				alarm_time_1 = Alarm_Close();
				LCD_ShowNum(2,13,alarm_time_1,4);
				Light_Close();
				Delayxms(100);
				lastButtonState = currentButtonState;//�ı䵱ǰ״̬�������һ������
				times ++;
			}
		}
		else if (currentButtonState == 1 && lastButtonState == 1)  // ֮ǰû�а��£����ڻ���û�а���
        {
			if(isEnabled)//���Ϊ1��˵��֮ǰû�а�����ͣ�������Ϊ0����˵��֮ǰ��ͣ�����¹�����Ҫ�ٰ�һ����ܽ��뱨��ģ�飬�ȴ����º����ڶ�������
			{
				
				s1 = Distance();//���
				judge_distance(s1);	//ͨ����õľ������LED�����������ﺯ��ǰ��˳��ûʲô��ϵ	
				LCD_ShowNum(1,14,s1,3);//��ʾ�������
				alarm_time_1 = Alarm1_Play(s1,times);//���㱨��ʱ��
				LCD_ShowNum(2,13,alarm_time_1,4);//��ʾ����ʱ��
				times = 0;//��������ģ���Ƿ�Ҫ��ͷ�������ֵĹؼ�����
			}
			
        }
		
        
    }
}
