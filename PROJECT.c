/*
 * PROJECT.c
 *
 * Created: 8/26/2023 11:21:10 PM
 *  Author: dell
 */ 

#include "APP.h"
#define F_CPU 8000000UL
extern u_int8 hours,minutes,seconds,first_digitm,second_digitm,first_digith,second_digith;
extern u_int8 frame[12];
extern u_int8 i;
extern u_int8 readKeypad;
int main(void)
{
	APP_DO();
	
}


ISR(T2_OVF)
{
	//interrupt for real time clock
	seconds++;
	if (seconds>=60)
	{
		minutes++;
		seconds=0;
	}
	if (minutes>=60)
	{
		hours++;
		minutes=0;
	}
	if(hours>=24)
	{
		hours=0;
	}
	display_time();
}
