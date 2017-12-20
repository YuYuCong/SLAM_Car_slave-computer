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
	delay_init(168);               //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);       //设置NVIC中断分组2
	uart_init(115200);	//串口初始化为115200
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


