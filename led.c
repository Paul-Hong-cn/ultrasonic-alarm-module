#include <REGX52.H>

void judge_distance(unsigned int distance)
{
	if (distance>=0 && distance < 20 )  
	{                     //���1
		P2_0 = 0; // �͵�ƽ����
		P2_1 = 0;
		P2_2 = 0;
		P2_3 = 0;
		P2_4 = 0;
    }
         
    else if (distance >= 20 && distance < 40 )  
	{                     //���2
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
	{                     //���3
		
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
