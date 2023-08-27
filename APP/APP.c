/*
 * APP.c
 *
 * Created: 8/27/2023 3:00:31 PM
 *  Author: dell
 */ 

#include "APP.h"
u_int8 hours=0,minutes=0,seconds=0,first_digitm=NOTPRESSED,second_digitm=NOTPRESSED,first_digith=NOTPRESSED,second_digith=NOTPRESSED;
u_int8 frame[12];
u_int8 i=0;
u_int8 readKeypad=NOTPRESSED;

void display_time()
{
	//function to display the time on the screen
	u_int8 arr[]="time: ";
	LCD_set_cursor(1, 14);
	LCD_write_string(arr);
	LCD_Write_Data((hours/10+'0'));
	LCD_Write_Data((hours%10+'0'));
	LCD_Write_Data(':');
	LCD_Write_Data((minutes/10+'0'));
	LCD_Write_Data((minutes%10+'0'));
	LCD_Write_Data(':');
	LCD_Write_Data((seconds/10+'0'));
	LCD_Write_Data((seconds%10+'0'));
	
}
void DISPLAY_RES()
{
	//display the speed information and angle information
	cli();
	u_int8 arr1[]="        speed: ";
	u_int8 arr2[]="angle: ";
	LCD_set_cursor(0,6);
	LCD_write_string(arr1);
	LCD_Write_Data(frame[0]);
	LCD_Write_Data(frame[1]);
	LCD_Write_Data(frame[2]);
	LCD_Write_Data('%');
	LCD_Write_Data(' ');
	LCD_write_string(arr2);
	if(frame[6]=='L'||frame[6]=='l')
	{
		LCD_Write_Data('-');
		LCD_Write_Data(frame[4]);
		LCD_Write_Data(frame[5]);
	}
	else
	{
		LCD_Write_Data(frame[4]);
		LCD_Write_Data(frame[5]);
	}
	sei();
	LCD_Write_Data(' ');
	LCD_Write_Data(' ');
	LCD_Write_Data(' ');
	LCD_Write_Data(' ');
}
void change_time()
{
	//function to change the time displayed on the LCD after initialization
	cli();

	if (readKeypad !=NOTPRESSED)
	{
		delay_ms(300);
		if (readKeypad=='1')
		{
			LCD_CLRR();
			u_int8 arr1[]="hours=--";
			LCD_set_cursor(0,0);
			LCD_write_string(&arr1);
			
			while(first_digith==NOTPRESSED)
			first_digith=KEYPAD_READ();
			
			LCD_set_cursor(0,6);
			LCD_Write_Data(first_digith);
			delay_ms(300);
			while(second_digith==NOTPRESSED)
			second_digith=KEYPAD_READ();
			
			LCD_set_cursor(0,7);
			LCD_Write_Data(second_digith);
			delay_ms(300);
			hours=(first_digith-'0')*10+(second_digith-'0');
			LCD_CLRR();
			first_digith=NOTPRESSED;
			second_digith=NOTPRESSED;
			u_int8 arr2[]="minutes=--";
			LCD_set_cursor(0,0);
			LCD_write_string(&arr2);
			
			while(first_digitm==NOTPRESSED)
			first_digitm=KEYPAD_READ();
			
			delay_ms(300);
			LCD_set_cursor(0,8);
			LCD_Write_Data(first_digitm);
			
			
			while(second_digitm==NOTPRESSED)
			second_digitm=KEYPAD_READ();
			LCD_set_cursor(0,9);
			LCD_Write_Data(second_digitm);
			delay_ms(300);
			minutes=(first_digitm-'0')*10+(second_digitm-'0');
			second_digitm=NOTPRESSED;
			first_digitm=NOTPRESSED;
			LCD_CLRR();
		}
	}
	sei();

}

void APP_DO()
{
	LCD_init(); //initialize LCD with
	UART_INIT(9600); //initialize UART mode
	DC_INIT(); //initialize IO pins for DC motor
	T2_NM_DF_OSC(); //initialize timer 2
	stepper_motor_init(); //initialize IO pins for stepper
	KEYPAD_INIT(); //initialize KEYPAD
	u_int8 arr[]="press 1 to change time";
	LCD_set_cursor(0,1);
	LCD_write_string(&arr);
	while(KEYPAD_READ()==NOTPRESSED); //wait until press button
	readKeypad= KEYPAD_READ(); //read the input(work only if one)
	change_time(); //change Time shown on LCD
	LCD_CLRR();
	u_int8 arr2[]="please select a speed and angle";
	cli();
	LCD_set_cursor(0,6);
	LCD_write_string(arr2);
	sei();
	while(1)
	{
		
		
		for(i=0;i<=7;i++)
		{
			//for loop to get the input from User
			frame[i]=UART_REV();
			if (frame[i]=='E'||frame[i]=='e')
			{
				break;
			}
		}
		//all if conditions to check if the frame is correct
		if (i==7)
		{
			
			if (frame[0]=='1'||frame[0]=='0')
			{
				if (frame[1]>='0'&&frame[1]<='9')
				{
					if (frame[2]>='0'&&frame[2]<='9')
					{
						if (frame[3]=='f'||frame[3]=='F'||frame[3]=='b'||frame[3]=='B')
						{
							if (frame[4]>='0'&&frame[4]<='4')
							{
								if (frame[5]>='0'||frame[5]<='9')
								{
									if (frame[6]=='l'||frame[6]=='L'||frame[6]=='R'||frame[6]=='r')
									{
										if (frame[7]=='E'||frame[7]=='e')
										{
											DISPLAY_RES();
											DC_MOVE((frame[0]-'0')*100+(frame[1]-'0')*10+frame[2]-'0', frame[3]);
											change_direction((frame[4]-'0')*10+frame[5]-'0',frame[6]);
											
										}
									}
								}
							}
						}
					}
				}

			}
			
			
		}

		
	}
	
	
	
}