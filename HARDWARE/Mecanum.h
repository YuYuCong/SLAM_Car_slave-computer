#ifndef __MECANUM_H
#define __MECANUM_H
#include "sys.h"



void Mecanum_Init(void);
void Mecanum_Debug(void);

void Car_Stop(void);
void Car_Go(u16 speed);//12���ӷ���
void Car_Back(u16 speed);//6���ӷ��� 
void Car_Lfet(u16 speed);;//9���ӷ���
void Car_Right(u16 speed);//3���ӷ���
void Car_1_30_Direction(u16 speed);//1��뷽��
void Car_4_30_Direction(u16 speed);//4��뷽��
void Car_7_30_Direction(u16 speed);//7��뷽��
void Car_10_30_Direction(u16 speed);//10��뷽��

void car_telecontrol(int16_t duty1,int16_t duty2,int16_t duty3,int16_t duty4);
	
#endif
