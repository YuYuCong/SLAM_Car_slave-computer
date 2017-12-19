#include "function_declare.h"
#include "led.h"
/// Function definitions


/****************************************************************
*@function LED_GPIO_Init  
*@author William Yu
*@brief LED�źŵ�ָʾ
****************************************************************/
//��ʼ��PF9��PF10Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_GPIO_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��
	
  GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10���øߣ�����

}

/****************************************************************
*@function LED_Init  
*@author William Yu
*@brief LED�źŵ�ָʾ
****************************************************************/
void LED_Init(void)
{
	LED_GPIO_Init();
   
	LED1_ON;
	LED0_OFF;
	delay_ms(500);	
	LED1_OFF;
	LED0_ON;
	delay_ms(500);	
	LED1_ON;
	LED0_OFF;
	delay_ms(500);	
	LED1_OFF;
	LED0_ON;
	delay_ms(500);	
	printf("LED_OK!\r\n");
}



/*************************   (C) COPYRIGHT 2017 William Yu  ******************************
*************************************      END OF FILE     ******************************/
