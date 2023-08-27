/*
 * KEYPAD.h
 *
 * Created: 8/23/2023 7:49:26 PM
 *  Author: dell
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "DIO.h"
#define EMPTY 0xff
void KEYPAD_INIT();
u_int8 KEYPAD_READ();

#endif /* KEYPAD_H_ */