/******************** (C) COPYRIGHT 2017 ThinkFly Studio  **************************
 * �ļ���  ��telecontrol.c
 * ����    ��4·����ң����4ͨ���ź�
 * Ӳ�����ӣ�------------------------------------------
 *          |  PA00: (TIM5_CH1)   Channl_1  ��ҡ�˹�ת|
 *          |  PA01: (TIM5_CH2)   Channl_2  ��ҡ�˸���|
 *     	    |  PA02: (TIM5_CH3)   Channl_3  ��ҡ������|
 *          |  PA03: (TIM5_CH4)   Channl_4  ��ҡ��ƫ��|
 *          -------------------------------------------
 * ����    ��William Yu
**********************************************************************************/
#include "function_declare.h"
//#include "telecontrol.h"
/// Global Variables

u8 TIM5CH1_CAPTURE_STA = 0;	//ͨ��1���벶���־������λ�������־����6λ�������־		
u16 TIM5CH1_CAPTURE_UPVAL;
u16 TIM5CH1_CAPTURE_DOWNVAL;

u8 TIM5CH2_CAPTURE_STA = 0;	//ͨ��2���벶���־������λ�������־����6λ�������־		
u16 TIM5CH2_CAPTURE_UPVAL;
u16 TIM5CH2_CAPTURE_DOWNVAL;

u8 TIM5CH3_CAPTURE_STA = 0;	//ͨ��3���벶���־������λ�������־����6λ�������־		
u16 TIM5CH3_CAPTURE_UPVAL;
u16 TIM5CH3_CAPTURE_DOWNVAL;

u8 TIM5CH4_CAPTURE_STA = 0;	//ͨ��4���벶���־������λ�������־����6λ�������־		
u16 TIM5CH4_CAPTURE_UPVAL;
u16 TIM5CH4_CAPTURE_DOWNVAL;

u32 Channel_1 = 0;	//�����ܸߵ�ƽ��ʱ��
u32 Channel_2 = 0;	//�����ܸߵ�ƽ��ʱ��
u32 Channel_3 = 0;	//�����ܸߵ�ƽ��ʱ��
u32 Channel_4 = 0;	//�����ܸߵ�ƽ��ʱ��
u32 TIM5_T1;
u32 TIM5_T2;
u32 TIM5_T3;
u32 TIM5_T4;

/// Function definitions

/**
*@function TIM5_Cap_Init  
*@author William Yu
*@brief 
*/

//TIM5ͨ��1/2/3/4���벶������

void TIM5_Cap_Init(u32 arr, u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM5_ICInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//ʹ��TIM5ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //ʹ��GPIOAʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //GPIOA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //GPIOA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA3
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0����λ��ʱ��5
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5); 
  	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); 
	
	
	//��ʼ��TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //�趨�������Զ���װֵ 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//Ԥ��Ƶ�� 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

	//��ʼ��TIM5���벶����� ͨ��1
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	//��ʼ��TIM5���벶����� ͨ��2
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	//��ʼ��TIM5���벶����� ͨ��3
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	//��ʼ��TIM5���벶����� ͨ��4
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //���������Ƶ,����Ƶ 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 ���������˲��� ���˲�
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	//�жϷ����ʼ��
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);   //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ��� 

	TIM_ITConfig(TIM5, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4,ENABLE);   //����������жϣ�����CC1IE,CC2IE,CC3IE,CC4IE�����ж�	

	TIM_Cmd(TIM5, ENABLE); 		//ʹ�ܶ�ʱ��4
}


/**
*@function TIM5_IRQHandler  
*@author William Yu
*@brief ��ʱ���жϷ������
*/
void TIM5_IRQHandler(void)
{
	if ((TIM5CH1_CAPTURE_STA & 0X80) == 0) 		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) 		//����1���������¼�
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC1); 		//����жϱ�־λ
			if (TIM5CH1_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM5CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM5);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM5CH1_CAPTURE_DOWNVAL < TIM5CH1_CAPTURE_UPVAL)
				{
					TIM5_T1 = 65535;
				}
				else
					TIM5_T1 = 0;
				Channel_1 = TIM5CH1_CAPTURE_DOWNVAL - TIM5CH1_CAPTURE_UPVAL
						+ TIM5_T1;		//�õ��ܵĸߵ�ƽ��ʱ��
				TIM5CH1_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM5CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM5);		//��ȡ����������
				TIM5CH1_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}

	if ((TIM5CH2_CAPTURE_STA & 0X80) == 0)		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)		//����2���������¼�
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);		//����жϱ�־λ
			if (TIM5CH2_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM5CH2_CAPTURE_DOWNVAL = TIM_GetCapture2(TIM5);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM5CH2_CAPTURE_DOWNVAL < TIM5CH2_CAPTURE_UPVAL)
				{
					TIM5_T2 = 65535;
				}
				else
					TIM5_T2 = 0;
				Channel_2 = TIM5CH2_CAPTURE_DOWNVAL - TIM5CH2_CAPTURE_UPVAL
						+ TIM5_T2;		//�õ��ܵĸߵ�ƽ��ʱ��
				TIM5CH2_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC2PolarityConfig(TIM5, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM5CH2_CAPTURE_UPVAL = TIM_GetCapture2(TIM5);		//��ȡ����������
				TIM5CH2_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC2PolarityConfig(TIM5, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}

	if ((TIM5CH3_CAPTURE_STA & 0X80) == 0)		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)		//����3���������¼�
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);		//����жϱ�־λ
			if (TIM5CH3_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM5CH3_CAPTURE_DOWNVAL = TIM_GetCapture3(TIM5);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM5CH3_CAPTURE_DOWNVAL < TIM5CH3_CAPTURE_UPVAL)
				{
					TIM5_T3 = 65535;
				}
				else
					TIM5_T3 = 0;
				Channel_3 = TIM5CH3_CAPTURE_DOWNVAL - TIM5CH3_CAPTURE_UPVAL
						+ TIM5_T3;		//�õ��ܵĸߵ�ƽ��ʱ��
				TIM5CH3_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC3PolarityConfig(TIM5, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM5CH3_CAPTURE_UPVAL = TIM_GetCapture3(TIM5);		//��ȡ����������
				TIM5CH3_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC3PolarityConfig(TIM5, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}

	if ((TIM5CH4_CAPTURE_STA & 0X80) == 0)		//��δ�ɹ�����	
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)		//����4���������¼�
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);		//����жϱ�־λ
			if (TIM5CH4_CAPTURE_STA & 0X40)		//����һ���½���
			{
				TIM5CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM5);//��¼�´�ʱ�Ķ�ʱ������ֵ
				if (TIM5CH4_CAPTURE_DOWNVAL < TIM5CH4_CAPTURE_UPVAL)
				{
					TIM5_T4 = 65535;
				}
				else
					TIM5_T4 = 0;
				Channel_4 = TIM5CH4_CAPTURE_DOWNVAL - TIM5CH4_CAPTURE_UPVAL
						+ TIM5_T4;		//�õ��ܵĸߵ�ƽ��ʱ��
				TIM5CH4_CAPTURE_STA = 0;		//�����־λ����
				TIM_OC4PolarityConfig(TIM5, TIM_ICPolarity_Rising); //����Ϊ�����ز���		  
			}
			else //��������ʱ�䵫�����½��أ���һ�β��������أ���¼��ʱ�Ķ�ʱ������ֵ
			{
				TIM5CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM5);		//��ȡ����������
				TIM5CH4_CAPTURE_STA |= 0X40;		//����Ѳ���������
				TIM_OC4PolarityConfig(TIM5, TIM_ICPolarity_Falling);//����Ϊ�½��ز���
			}
		}
	}
}




void telecontrol_Debug(void)
{
		delay_ms(1000);
		printf("Channel 1 : %d us\r\n",Channel_1);
		delay_ms(10);
		printf("Channel 2 : %d us\r\n",Channel_2);
		delay_ms(10);
		printf("Channel 3 : %d us\r\n",Channel_3);
		delay_ms(10);
		printf("Channel 4 : %d us\r\n",Channel_4);
}

	

void telecontrol_Init(void)
{
	TIM5_Cap_Init(0xffff,72-1); //��1Mhz��Ƶ�ʼ���
	printf("Mecanum OK!\r\n");
}


/*************************   ��ʼ������  *************************/
/*************************   ��ʼ������  *************************/





/*************************   (C) COPYRIGHT 2017 William Yu  ******************************
*************************************      END OF FILE     ******************************/
