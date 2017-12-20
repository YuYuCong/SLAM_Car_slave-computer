#include "function_declare.h"

/// Global Variables


/// Function definitions
/**
*@function main  
*@author William Yu
*@brief 
*/
int main(void)
{
	delay_init(168);               //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);       //����NVIC�жϷ���2
	uart_init(115200);	//���ڳ�ʼ��Ϊ115200
	LED_Init();
	Mecanum_Init();
	telecontrol_Init();
	
	
	while(1)
	{
		Mecanum_Debug();
		telecontrol_Debug();

	}
}

/*************************   (C) COPYRIGHT 2017 William Yu  ******************************
*************************************      END OF FILE     ******************************/


