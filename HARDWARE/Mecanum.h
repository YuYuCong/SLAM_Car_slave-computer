#ifndef __MECANUM_H
#define __MECANUM_H
#include "sys.h"



void Mecanum_Init(void);
void Mecanum_Debug(void);

void Car_Stop(void);
void Car_Go(u16 speed);//12点钟方向
void Car_Back(u16 speed);//6点钟方向 
void Car_Lfet(u16 speed);;//9点钟方向
void Car_Right(u16 speed);//3点钟方向
void Car_1_30_Direction(u16 speed);//1点半方向
void Car_4_30_Direction(u16 speed);//4点半方向
void Car_7_30_Direction(u16 speed);//7点半方向
void Car_10_30_Direction(u16 speed);//10点半方向

void car_telecontrol(int16_t duty1,int16_t duty2,int16_t duty3,int16_t duty4);
	
#endif
