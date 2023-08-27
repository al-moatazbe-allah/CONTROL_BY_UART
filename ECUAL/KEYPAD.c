/*
 * KEYPAD.c
 *
 * Created: 8/23/2023 7:49:13 PM
 *  Author: dell
 */ 
#include "KEYPAD.h"
void KEYPAD_INIT()
{
	
	for(u_int8 i=0;i<4;i++)
	{
		DIO_set_bit_direction('C',i,1);
	}
	DIO_set_bit_direction('D',4,0);
	DIO_set_bit_direction('D',5,0);
	DIO_set_bit_direction('D',2,0);
	DIO_set_bit_direction('D',3,0);
	DIO_Set_Bit('d',4);
	DIO_Set_Bit('d',5);
	DIO_Set_Bit('D',2);
	DIO_Set_Bit('D',3);
}
u_int8 KEYPAD_READ()
{
	 {
		 u_int8 arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}};
		 u_int8 row,coloumn,x;
		 u_int8 returnval=EMPTY;
		 for(row=0;row<4;row++)
		 {
			 DIO_Set_Bit('c',0);
			 DIO_Set_Bit('c',1);
			 DIO_Set_Bit('c',2);
			 DIO_Set_Bit('c',3);
			 DIO_CLR_Bit('c',row);
			 for(coloumn=0;coloumn<4;coloumn++)
			 {
				 x=DIO_get_bit('D',(coloumn+2));
				 if(x==0)
				 {
					 returnval=arr[row][coloumn];
					 break;
				 }
			 }
			 if(x==0)
			 {
				 break;
			 }
		 }
		 return returnval ;
	 }

}
