/******************** (C) COPYRIGHT 2017 ThinkFly Studio  **************************
 * 文件名  ：telecontrol.c
 * 描述    ：4路捕获遥控器4通道信号
 * 硬件连接：------------------------------------------
 *          |  PA00: (TIM5_CH1)   Channl_1  右摇杆滚转|
 *          |  PA01: (TIM5_CH2)   Channl_2  右摇杆俯仰|
 *     	    |  PA02: (TIM5_CH3)   Channl_3  左摇杆油门|
 *          |  PA03: (TIM5_CH4)   Channl_4  左摇杆偏航|
 *          -------------------------------------------
 * 作者    ：William Yu
**********************************************************************************/
#include "function_declare.h"
//#include "telecontrol.h"
/// Global Variables

u8 TIM5CH1_CAPTURE_STA = 0;	//通道1输入捕获标志，高两位做捕获标志，低6位做溢出标志		
u16 TIM5CH1_CAPTURE_UPVAL;
u16 TIM5CH1_CAPTURE_DOWNVAL;

u8 TIM5CH2_CAPTURE_STA = 0;	//通道2输入捕获标志，高两位做捕获标志，低6位做溢出标志		
u16 TIM5CH2_CAPTURE_UPVAL;
u16 TIM5CH2_CAPTURE_DOWNVAL;

u8 TIM5CH3_CAPTURE_STA = 0;	//通道3输入捕获标志，高两位做捕获标志，低6位做溢出标志		
u16 TIM5CH3_CAPTURE_UPVAL;
u16 TIM5CH3_CAPTURE_DOWNVAL;

u8 TIM5CH4_CAPTURE_STA = 0;	//通道4输入捕获标志，高两位做捕获标志，低6位做溢出标志		
u16 TIM5CH4_CAPTURE_UPVAL;
u16 TIM5CH4_CAPTURE_DOWNVAL;

u32 Channel_1 = 0;	//捕获总高电平的时间
u32 Channel_2 = 0;	//捕获总高电平的时间
u32 Channel_3 = 0;	//捕获总高电平的时间
u32 Channel_4 = 0;	//捕获总高电平的时间
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

//TIM5通道1/2/3/4输入捕获配置

void TIM5_Cap_Init(u32 arr, u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_ICInitTypeDef TIM5_ICInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);	//使能TIM5时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  //使能GPIOA时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA0
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //GPIOA1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //GPIOA2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA2
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //GPIOA3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN; //下拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA3
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //PA0复用位定时器5
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM5); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM5); 
  	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM5); 
	
	
	//初始化TIM5	 
	TIM_TimeBaseStructure.TIM_Period = arr; //设定计数器自动重装值 
	TIM_TimeBaseStructure.TIM_Prescaler = psc; 	//预分频器 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

	//初始化TIM5输入捕获参数 通道1
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_1; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //配置输入分频,不分频 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	//初始化TIM5输入捕获参数 通道2
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_2; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //配置输入分频,不分频 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	//初始化TIM5输入捕获参数 通道3
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_3; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //配置输入分频,不分频 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	//初始化TIM5输入捕获参数 通道4
	TIM5_ICInitStructure.TIM_Channel = TIM_Channel_4; //CC1S=01 	选择输入端 IC1映射到TI1上
	TIM5_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM5_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
	TIM5_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	  //配置输入分频,不分频 
	TIM5_ICInitStructure.TIM_ICFilter = 0x00;	  //IC1F=0000 配置输入滤波器 不滤波
	TIM_ICInit(TIM5, &TIM5_ICInitStructure);

	//中断分组初始化
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;  //TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);   //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器 

	TIM_ITConfig(TIM5, TIM_IT_CC1 | TIM_IT_CC2 | TIM_IT_CC3 | TIM_IT_CC4,ENABLE);   //不允许更新中断，允许CC1IE,CC2IE,CC3IE,CC4IE捕获中断	

	TIM_Cmd(TIM5, ENABLE); 		//使能定时器4
}


/**
*@function TIM5_IRQHandler  
*@author William Yu
*@brief 定时器中断服务程序
*/
void TIM5_IRQHandler(void)
{
	if ((TIM5CH1_CAPTURE_STA & 0X80) == 0) 		//还未成功捕获	
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET) 		//捕获1发生捕获事件
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC1); 		//清除中断标志位
			if (TIM5CH1_CAPTURE_STA & 0X40)		//捕获到一个下降沿
			{
				TIM5CH1_CAPTURE_DOWNVAL = TIM_GetCapture1(TIM5);//记录下此时的定时器计数值
				if (TIM5CH1_CAPTURE_DOWNVAL < TIM5CH1_CAPTURE_UPVAL)
				{
					TIM5_T1 = 65535;
				}
				else
					TIM5_T1 = 0;
				Channel_1 = TIM5CH1_CAPTURE_DOWNVAL - TIM5CH1_CAPTURE_UPVAL
						+ TIM5_T1;		//得到总的高电平的时间
				TIM5CH1_CAPTURE_STA = 0;		//捕获标志位清零
				TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising); //设置为上升沿捕获		  
			}
			else //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
			{
				TIM5CH1_CAPTURE_UPVAL = TIM_GetCapture1(TIM5);		//获取上升沿数据
				TIM5CH1_CAPTURE_STA |= 0X40;		//标记已捕获到上升沿
				TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);//设置为下降沿捕获
			}
		}
	}

	if ((TIM5CH2_CAPTURE_STA & 0X80) == 0)		//还未成功捕获	
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)		//捕获2发生捕获事件
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC2);		//清除中断标志位
			if (TIM5CH2_CAPTURE_STA & 0X40)		//捕获到一个下降沿
			{
				TIM5CH2_CAPTURE_DOWNVAL = TIM_GetCapture2(TIM5);//记录下此时的定时器计数值
				if (TIM5CH2_CAPTURE_DOWNVAL < TIM5CH2_CAPTURE_UPVAL)
				{
					TIM5_T2 = 65535;
				}
				else
					TIM5_T2 = 0;
				Channel_2 = TIM5CH2_CAPTURE_DOWNVAL - TIM5CH2_CAPTURE_UPVAL
						+ TIM5_T2;		//得到总的高电平的时间
				TIM5CH2_CAPTURE_STA = 0;		//捕获标志位清零
				TIM_OC2PolarityConfig(TIM5, TIM_ICPolarity_Rising); //设置为上升沿捕获		  
			}
			else //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
			{
				TIM5CH2_CAPTURE_UPVAL = TIM_GetCapture2(TIM5);		//获取上升沿数据
				TIM5CH2_CAPTURE_STA |= 0X40;		//标记已捕获到上升沿
				TIM_OC2PolarityConfig(TIM5, TIM_ICPolarity_Falling);//设置为下降沿捕获
			}
		}
	}

	if ((TIM5CH3_CAPTURE_STA & 0X80) == 0)		//还未成功捕获	
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)		//捕获3发生捕获事件
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC3);		//清除中断标志位
			if (TIM5CH3_CAPTURE_STA & 0X40)		//捕获到一个下降沿
			{
				TIM5CH3_CAPTURE_DOWNVAL = TIM_GetCapture3(TIM5);//记录下此时的定时器计数值
				if (TIM5CH3_CAPTURE_DOWNVAL < TIM5CH3_CAPTURE_UPVAL)
				{
					TIM5_T3 = 65535;
				}
				else
					TIM5_T3 = 0;
				Channel_3 = TIM5CH3_CAPTURE_DOWNVAL - TIM5CH3_CAPTURE_UPVAL
						+ TIM5_T3;		//得到总的高电平的时间
				TIM5CH3_CAPTURE_STA = 0;		//捕获标志位清零
				TIM_OC3PolarityConfig(TIM5, TIM_ICPolarity_Rising); //设置为上升沿捕获		  
			}
			else //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
			{
				TIM5CH3_CAPTURE_UPVAL = TIM_GetCapture3(TIM5);		//获取上升沿数据
				TIM5CH3_CAPTURE_STA |= 0X40;		//标记已捕获到上升沿
				TIM_OC3PolarityConfig(TIM5, TIM_ICPolarity_Falling);//设置为下降沿捕获
			}
		}
	}

	if ((TIM5CH4_CAPTURE_STA & 0X80) == 0)		//还未成功捕获	
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)		//捕获4发生捕获事件
		{
			TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);		//清除中断标志位
			if (TIM5CH4_CAPTURE_STA & 0X40)		//捕获到一个下降沿
			{
				TIM5CH4_CAPTURE_DOWNVAL = TIM_GetCapture4(TIM5);//记录下此时的定时器计数值
				if (TIM5CH4_CAPTURE_DOWNVAL < TIM5CH4_CAPTURE_UPVAL)
				{
					TIM5_T4 = 65535;
				}
				else
					TIM5_T4 = 0;
				Channel_4 = TIM5CH4_CAPTURE_DOWNVAL - TIM5CH4_CAPTURE_UPVAL
						+ TIM5_T4;		//得到总的高电平的时间
				TIM5CH4_CAPTURE_STA = 0;		//捕获标志位清零
				TIM_OC4PolarityConfig(TIM5, TIM_ICPolarity_Rising); //设置为上升沿捕获		  
			}
			else //发生捕获时间但不是下降沿，第一次捕获到上升沿，记录此时的定时器计数值
			{
				TIM5CH4_CAPTURE_UPVAL = TIM_GetCapture4(TIM5);		//获取上升沿数据
				TIM5CH4_CAPTURE_STA |= 0X40;		//标记已捕获到上升沿
				TIM_OC4PolarityConfig(TIM5, TIM_ICPolarity_Falling);//设置为下降沿捕获
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
	TIM5_Cap_Init(0xffff,72-1); //以1Mhz的频率计数
	printf("Mecanum OK!\r\n");
}


/*************************   初始化结束  *************************/
/*************************   初始化结束  *************************/





/*************************   (C) COPYRIGHT 2017 William Yu  ******************************
*************************************      END OF FILE     ******************************/
