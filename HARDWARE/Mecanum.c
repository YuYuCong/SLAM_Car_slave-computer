/******************** (C) COPYRIGHT 2017 ThinkFly Studio  **************************
 * �ļ���  ��Mecanum.c
 * ����    ������ź�       
 * Ӳ�����ӣ�-------------------------------------------------
 *          |  PC06: (TIM3_CH1)  pwm_leftFront     F0-F1   |
 *          |  PC07: (TIM3_CH2)  pwm_rightFront    F2-F3   |
 *     	    |  PC08: (TIM3_CH3)  pwm_rightBehind   F4-F5   |
 *          |  PC09: (TIM3_CH4)  pwm_leftBehind    F6-F7   |
 *          -------------------------------------------------
 * ����    ��William Yu
**********************************************************************************/

#include "function_declare.h"
//#include "Mecanum.h"

/// Function definitions

/**
*@function TIM3_GPIO_Config  
*@author William Yu
*@brief ��������PWM�źŶ˿�����
*/
void TIM3_GPIO_Config(void) 
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	///ʹ�ܶ˿�ʱ��
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6|GPIO_PinSource7|GPIO_PinSource8|GPIO_PinSource9,GPIO_AF_TIM3); //GPIO����Ϊ��ʱ��

	///��ʼ������
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7|GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //���ù���
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��
	

}

/**
*@function TIM3_Mode_Config  
*@author William Yu
*@brief ��������PWM�źŶ˿�����
*/
static void TIM3_Mode_Config(void)
{
 
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM14ʱ��ʹ��    

	
	/* PWM�źŵ�ƽ����ֵ */
//	u16 CCR1_Val = 500;        
//	u16 CCR2_Val = 375;
//	u16 CCR3_Val = 250;
//	u16 CCR4_Val = 125;
	u16 CCR1_Val = 0;        
	u16 CCR2_Val = 0;
	u16 CCR3_Val = 0;
	u16 CCR4_Val = 0;
 
/* -----------------------------------------------------------------------
    TIM3 Configuration: generate 4 PWM signals with 4 different duty cycles:
    TIM3CLK = 72 MHz, Prescaler = 0x0, TIM3 counter clock = 72 MHz
    TIM3 ARR Register = 999 => TIM3 Frequency = TIM3 counter clock/(ARR + 1)
    TIM3 Frequency = 72 KHz.
    TIM3 Channel1 duty cycle = (TIM3_CCR1/ TIM3_ARR)* 100 = 50%
    TIM3 Channel2 duty cycle = (TIM3_CCR2/ TIM3_ARR)* 100 = 37.5%
    TIM3 Channel3 duty cycle = (TIM3_CCR3/ TIM3_ARR)* 100 = 25%
    TIM3 Channel4 duty cycle = (TIM3_CCR4/ TIM3_ARR)* 100 = 12.5%
  ----------------------------------------------------------------------- */
 
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 999;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
	TIM_TimeBaseStructure.TIM_Prescaler = 0;    //����Ԥ��Ƶ����Ԥ��Ƶ����Ϊ72MHz
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;//����ʱ�ӷ�Ƶϵ��������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
	 
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
 
    /* PWM1 Mode configuration: Channel1 */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;    //����ΪPWMģʽ1
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR1_Val;   //��������ֵ�������������������ֵʱ����ƽ��������
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
    TIM_OC1Init(TIM3, &TIM_OCInitStructure); //ʹ��ͨ��1
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//ʹ��TIM��CCR1�ϵ�Ԥװ�ؼĴ���
 
    /* PWM1 Mode configuration: Channel2 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR2_Val;  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //ʹ��ͨ��2
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
    /* PWM1 Mode configuration: Channel3 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR3_Val;//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
    TIM_OC3Init(TIM3, &TIM_OCInitStructure); //ʹ��ͨ��3
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
    /* PWM1 Mode configuration: Channel4 */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = CCR4_Val;//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);//ʹ��ͨ��4
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
    TIM_ARRPreloadConfig(TIM3, ENABLE); // ʹ��TIM3���ؼĴ���ARR
 
    /* TIM3 enable counter */
    TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3
 
}

/**
*@function TIM3_PWM_Init  
*@author William Yu
*@brief TIM3 ���PWM�źų�ʼ������
*/

void TIM3_PWM_Init(void)
{
	TIM3_GPIO_Config();
	TIM3_Mode_Config();
}




/**********************************************************************************************
*@function Mecanum_GPIO_init  
*@author William Yu
*@brief ����IN1/IN2�˿�����
 * Ӳ�����ӣ�-------------------------------------------------
 *          |  PC06: (TIM3_CH1)  pwm_leftFront     F0-F1   |
 *          |  PC07: (TIM3_CH2)  pwm_rightFront    F2-F3   |
 *     	    |  PC08: (TIM3_CH3)  pwm_rightBehind   F4-F5   |
 *          |  PC09: (TIM3_CH4)  pwm_leftBehind    F6-F7   |
 *          -------------------------------------------------
*/
void Mecanum_GPIO_init(void)
{ 
	GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��

	//GPIO���øߣ����־���ת��
    GPIO_SetBits(GPIOF,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);

}

void Mecanum_Init(void)
{
	TIM3_PWM_Init();
	Mecanum_GPIO_init();
	printf("Mecanum OK!\r\n");
}


	
/*************************   ��ʼ������  *************************/
/*************************   ��ʼ������  *************************/





/*************************   �ײ��˶�����  ***********************/
/*************************   �ײ��˶�����  ***********************/



//�ĸ������ܶ����룬�����е���pwmռ�ձ�
void Motor_leftFront_Go(u16 pwm_leftFront )
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_0 );
	GPIO_SetBits(GPIOF,GPIO_Pin_1 );
	TIM_SetCompare1(TIM3,pwm_leftFront);
}	
void Motor_rightFront_Go(u16 pwm_rightFront)
{	
	GPIO_ResetBits(GPIOF,GPIO_Pin_2 );
	GPIO_SetBits(GPIOF,GPIO_Pin_3 );	
	TIM_SetCompare2(TIM3,pwm_rightFront);	
}
void Motor_rightBehind_Go(u16 pwm_rightBehind )
{ 	
	GPIO_ResetBits(GPIOF,GPIO_Pin_5 );
	GPIO_SetBits(GPIOF,GPIO_Pin_4 );
	TIM_SetCompare3(TIM3,pwm_rightBehind);	
}
void Motor_leftBehind_Go(u16 pwm_leftBehind )
{	
	GPIO_ResetBits(GPIOF,GPIO_Pin_7 );
	GPIO_SetBits(GPIOF,GPIO_Pin_6 );
	TIM_SetCompare4(TIM3,pwm_leftBehind);	
}


//�ĸ����Ӻ��˴��룬������е���ռ�ձ�void Motor_leftFront_Go(int pwm_leftFront )
void Motor_leftFront_Back(u16 pwm_leftFront )
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_1 );
	GPIO_SetBits(GPIOF,GPIO_Pin_0 );
	TIM_SetCompare1(TIM3,pwm_leftFront);	
}	
void Motor_rightFront_Back(u16 pwm_rightFront)
{	
	GPIO_ResetBits(GPIOF,GPIO_Pin_3 );
	GPIO_SetBits(GPIOF,GPIO_Pin_2 );	
	TIM_SetCompare2(TIM3,pwm_rightFront);	
}
void Motor_rightBehind_Back(u16 pwm_rightBehind )
{ 	
	GPIO_ResetBits(GPIOF,GPIO_Pin_4 );
	GPIO_SetBits(GPIOF,GPIO_Pin_5 );
	TIM_SetCompare3(TIM3,pwm_rightBehind);	
}
void Motor_leftBehind_Back(u16 pwm_leftBehind )
{	
	GPIO_ResetBits(GPIOF,GPIO_Pin_6 );
	GPIO_SetBits(GPIOF,GPIO_Pin_7 );
	TIM_SetCompare4(TIM3,pwm_leftBehind);	
}


/**********************************************************************************************
*@function   
*@author William Yu
*@brief 
*/
///�����ƶ��ֿش���
void Car_Stop()//
{
	GPIO_ResetBits(GPIOF,GPIO_Pin_0 );
	GPIO_ResetBits(GPIOF,GPIO_Pin_1 );
	TIM_SetCompare1(TIM3,0);

	GPIO_ResetBits(GPIOF,GPIO_Pin_2 );
	GPIO_ResetBits(GPIOF,GPIO_Pin_3 );	
	TIM_SetCompare2(TIM3,0);	

	GPIO_ResetBits(GPIOF,GPIO_Pin_5 );
	GPIO_ResetBits(GPIOF,GPIO_Pin_4 );
	TIM_SetCompare3(TIM3,0);	

	GPIO_ResetBits(GPIOF,GPIO_Pin_7 );
	GPIO_ResetBits(GPIOF,GPIO_Pin_6 );
	TIM_SetCompare4(TIM3,0);	
}
void Car_Go(u16 speed)//12���ӷ��� = ǰ+ǰ+ǰ+ǰ ����ǰ+��ǰ+���+�Һ�
{
	Motor_leftFront_Go(speed);
	Motor_leftBehind_Go(speed);
	Motor_rightFront_Go(speed);
	Motor_rightBehind_Go(speed);
}
void Car_Back(u16 speed)//6���ӷ��� = ��+��+��+��
{
	Motor_leftFront_Back(speed);
	Motor_leftBehind_Back(speed);
	Motor_rightFront_Back(speed);
	Motor_rightBehind_Back(speed);
}
void Car_Lfet(u16 speed)//9���ӷ��� = +++//����������������������������
{
	Motor_leftFront_Go(speed);
	Motor_leftBehind_Back(speed);
	Motor_rightFront_Back(speed);
	Motor_rightBehind_Go(speed);
}
void Car_Right(u16 speed)//3���ӷ��� = +++//����������������������������
{
	Motor_leftFront_Back(speed);
	Motor_leftBehind_Go(speed);
	Motor_rightFront_Go(speed);
	Motor_rightBehind_Back(speed);
}
///б���ƶ�
void Car_1_30_Direction(u16 speed)//1��뷽��
{
	Motor_leftFront_Back(speed);
	Motor_leftBehind_Go(speed);
	Motor_rightFront_Go(speed);
	Motor_rightBehind_Back(speed);
}
void Car_4_30_Direction(u16 speed)//4��뷽��
{
	Motor_leftFront_Back(speed);
	Motor_leftBehind_Go(speed);
	Motor_rightFront_Go(speed);
	Motor_rightBehind_Back(speed);
}
void Car_7_30_Direction(u16 speed)//7��뷽��
{
	Motor_leftFront_Back(speed);
	Motor_leftBehind_Go(speed);
	Motor_rightFront_Go(speed);
	Motor_rightBehind_Back(speed);
}
void Car_10_30_Direction(u16 speed)//10��뷽��
{
	Motor_leftFront_Back(speed);
	Motor_leftBehind_Go(speed);
	Motor_rightFront_Go(speed);
	Motor_rightBehind_Back(speed);
}






void Mecanum_Debug(void)
{
		Car_Go(1000);
			delay_ms(10000);
		Car_Back(800);
			delay_ms(2000);
		Car_Lfet(800);
			delay_ms(10000);
		Car_Right(800);
			delay_ms(10000);
		Car_10_30_Direction(700);
			delay_ms(20000);
		Car_4_30_Direction(700);
			delay_ms(20000);
		Car_1_30_Direction(700);
			delay_ms(20000);
		Car_7_30_Direction(700);
			delay_ms(20000);
}





/*************************   ң��ָ�����  ***********************/
/*************************   ң��ָ�����  ***********************/



/******************************************************************************
����ԭ�ͣ�	void car_telecontrol(int16_t duty1,int16_t duty2,int16_t duty3,int16_t duty4)
��    �ܣ�	�������
*******************************************************************************/ 

//δ�����
void car_telecontrol(int16_t duty1,int16_t duty2,int16_t duty3,int16_t duty4)
{
	u16 pwm_rightFront,pwm_rightBehind,pwm_leftFront,pwm_leftBehind;
	
	if(duty1>1000)	duty1=1000;
	if(duty1<0)		duty1=0;
	if(duty2>1000)	duty2=1000;
	if(duty2<0)		duty2=0;
	if(duty3>1000)	duty3=1000;
	if(duty3<0)		duty3=0;
	if(duty4>1000)	duty4=1000;
	if(duty4<0)		duty4=0;

	duty1 =  10*( - duty1 + duty2 - duty3);
	duty2 =  10*( + duty1 + duty2 - duty3);
	duty3 =  10*( - duty1 - duty2 - duty3);
	duty4 =  10*( + duty1 - duty2 - duty3);
	
	TIM3->CCR1 = pwm_leftFront;
	TIM3->CCR2 = pwm_rightFront;
	TIM3->CCR3 = pwm_rightBehind;
	TIM3->CCR4 = pwm_leftBehind;

}

/*************************   (C) COPYRIGHT 2017 William Yu  ******************************
*************************************      END OF FILE     ******************************/


