SLAM CAR�ײ���Ƴ���
STM32F407ZGT6������
16 λ��TIM3 �� TIM4���� 32 λ��TIM2 �� TIM5��

���ǰ�����ˡ�����ת�䣬�Ҹ�ƽ�ơ�

pwm_rightFront   =  Channel_3 - Channel_1 - Channel_4;
pwm_rightBehind  =  Channel_3 - Channel_1 + Channel_4;
pwm_leftFront    =  Channel_3 + Channel_1 + Channel_4;
pwm_leftBehind   =  Channel_3 + Channel_1 - Channel_4;


WheelSpeed[0]=10*(-carSpeedy+carSpeedx-carSpeedw);
WheelSpeed[1]=10*(+carSpeedy+carSpeedx-carSpeedw);
WheelSpeed[2]=10*(-carSpeedy-carSpeedx-carSpeedw);
WheelSpeed[3]=10*(+carSpeedy-carSpeedx-carSpeedw);
