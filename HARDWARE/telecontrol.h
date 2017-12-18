#ifndef __telecontrol_H
#define __telecontrol_H
#include "sys.h"

/// Global Variables
extern u32 Channel_1;	//捕获总高电平的时间
extern u32 Channel_2;	//捕获总高电平的时间
extern u32 Channel_3;	//捕获总高电平的时间
extern u32 Channel_4;	//捕获总高电平的时间


/// Function headers
void telecontrol_Init(void);
void telecontrol_Debug(void);

#endif

