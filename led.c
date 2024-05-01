#include <REGX52.H>

void judge_distance(unsigned int distance)
{
	if (distance>=0 && distance < 20 )  
	{                     //情况1
		P2_0 = 0; // 低电平点亮
		P2_1 = 0;
		P2_2 = 0;
		P2_3 = 0;
		P2_4 = 0;
    }
         
    else if (distance >= 20 && distance < 40 )  
	{                     //情况2
		P2_0 = 0;
		P2_1 = 0;
		P2_2 = 0;
		P2_3 = 1;
		P2_4 = 1;
    }
	
	else if (distance >= 40 && distance < 60 )
	{
		P2_0 = 0;
		P2_1 = 1;
		P2_2 = 1;
		P2_3 = 1;
		P2_4 = 1;
	}
    else if (distance >= 60 )  
	{                     //情况3
		
		P2_0=1;
		P2_1=1; 
		P2_2=1;
		P2_3=1; 
		P2_4=1;
		P2_5=1;
    } 
} 

void Light_Close()
{
	P2_0=1;
	P2_1=1; 
	P2_2=1;
	P2_3=1; 
	P2_4=1;
	P2_5=1;
}
