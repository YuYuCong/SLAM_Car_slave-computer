SLAM CAR底层控制程序
STM32F407ZGT6开发板
16 位（TIM3 和 TIM4）或 32 位（TIM2 和 TIM5）

左杆前进后退、左右转弯，右杆平移。

pwm_rightFront   =  Channel_3 - Channel_1 - Channel_4;
pwm_rightBehind  =  Channel_3 - Channel_1 + Channel_4;
pwm_leftFront    =  Channel_3 + Channel_1 + Channel_4;
pwm_leftBehind   =  Channel_3 + Channel_1 - Channel_4;


WheelSpeed[0]=10*(-carSpeedy+carSpeedx-carSpeedw);
WheelSpeed[1]=10*(+carSpeedy+carSpeedx-carSpeedw);
WheelSpeed[2]=10*(-carSpeedy-carSpeedx-carSpeedw);
WheelSpeed[3]=10*(+carSpeedy-carSpeedx-carSpeedw);
