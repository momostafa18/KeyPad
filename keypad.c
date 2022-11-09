/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.c
 *
 * Description: Source file for the Keypad driver
 *
 * Author: Mohamed Mostafa
 *
 *******************************************************************************/
#include"std_types.h"
#include"gpio.h"
#include"keypad.h"

/*******************************************************************************
 *                      Functions Prototypes(Private)                          *
 *******************************************************************************/

#ifndef STANDARAD_KEYPAD

#if(NUMBER_OF_KEYPAD_COLUMNS == 3)
/* Function to map the last row in the 4*3 keypad */
static uint8 KEYPAD_4X3_adjustKeyNumber(uint8 button_no);

#elif(NUMBER_OF_KEYPAD_COLUMNS == 4)
/* Function to map the last row in the 4*4 keypad */
static uint8 KEYPAD_4X4_adjustKeyNumber(uint8 button_no);

#endif

#endif

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
uint8 KEYPAD_getPressedKey(void)
{
	uint8 row,col;
	/*
	 1.We define all rows as input
	 2.We define all columns as input
	 3.We define row by row as output and start to check which pushbutton is pressed
	 4.We enter an infinite loop to wait for a push
	 5.At last we redefine the row we defined as output to be again as input and then move to the next one and
	 so on
	 */
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_ROWS_FIRST_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_ROWS_FIRST_PIN_ID+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_ROWS_FIRST_PIN_ID+2,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_ROWS_FIRST_PIN_ID+3,PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_COLUMNS_PORT_ID,KEYPAD_COLUMNS_FIRST_PIN_ID,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COLUMNS_PORT_ID,KEYPAD_COLUMNS_FIRST_PIN_ID+1,PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COLUMNS_PORT_ID,KEYPAD_COLUMNS_FIRST_PIN_ID+2,PIN_INPUT);
    #if(NUMBER_OF_KEYPAD_COLUMNS == 4)
	GPIO_setupPinDirection(KEYPAD_COLUMNS_PORT_ID,KEYPAD_COLUMNS_FIRST_PIN_ID+3,PIN_INPUT);
    #endif
    while(1)
   {
	for(row=0; row<NUMBER_OF_KEYPAD_ROWS ; row++)
	{
		GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_ROWS_FIRST_PIN_ID + row,PIN_OUTPUT);

		GPIO_writePin(KEYPAD_ROWS_PORT_ID,KEYPAD_ROWS_FIRST_PIN_ID + row,BUTTON_PRESSED);

		for(col=0 ; col<NUMBER_OF_KEYPAD_COLUMNS ; col++)
		{
			if(GPIO_readPin(KEYPAD_COLUMNS_PORT_ID,KEYPAD_COLUMNS_FIRST_PIN_ID + col) == BUTTON_PRESSED)
			{
                #if(NUMBER_OF_KEYPAD_COLUMNS == 3)
                #ifdef STANDARAD_KEYPAD
				     return ((row*NUMBER_OF_KEYPAD_COLUMNS)+col+1) ;
                #else
				     return KEYPAD_4X3_adjustKeyNumber((row*NUMBER_OF_KEYPAD_COLUMNS)+col+1);
                #endif
                #elif(NUMBER_OF_KEYPAD_COLUMNS == 4)
                #ifdef STANDARAD_KEYPAD
				     return ((row*NUMBER_OF_KEYPAD_COLUMNS)+col+1) ;
			    #else
				     return KEYPAD_4X4_adjustKeyNumber((row*NUMBER_OF_KEYPAD_COLUMNS)+col+1);
                #endif
                #endif
			}
		}
		GPIO_setupPinDirection(KEYPAD_ROWS_PORT_ID,KEYPAD_ROWS_FIRST_PIN_ID + row,PIN_INPUT);
	}
}
}
#ifndef STANDARAD_KEYPAD

#if(NUMBER_OF_KEYPAD_COLUMNS == 3)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x3 shape
 */

static uint8 KEYPAD_4X3_adjustKeyNumber(uint8 button_no)
{
	uint8 KEYPAD_BUTT;
	switch(button_no)
	{
	case 10:
		KEYPAD_BUTT='*';/* ASCII of * */
		break;
	case 11:
		KEYPAD_BUTT=0;
		break;
	case 12:
		KEYPAD_BUTT='#';/* ASCII of # */
		break;
	}
	return KEYPAD_BUTT;
}

#elif(NUMBER_OF_KEYPAD_COLUMNS == 4)
/*
 * Description :
 * Update the keypad pressed button value with the correct one in keypad 4x4 shape
 */

static uint8 KEYPAD_4X4_adjustKeyNumber(uint8 button_no)
{
	uint8 KEYPAD_BUTT;
	switch(button_no)
	{
	case 1:
		KEYPAD_BUTT=7;
		break;
	case 2:
		KEYPAD_BUTT=8;
		break;
	case 3:
		KEYPAD_BUTT=9;
	    break;
	case 4:
		KEYPAD_BUTT='%'; /* ASCII of % */
		break;
	case 5:
		KEYPAD_BUTT=4;
		break;
	case 6:
		KEYPAD_BUTT=5;
		break;
	case 7:
	    KEYPAD_BUTT=6;
		break;
	case 8:
		KEYPAD_BUTT='*'; /* ASCII of * */
		break;
	case 9:
		KEYPAD_BUTT=1;
		break;
	case 10:
		KEYPAD_BUTT=2;
		break;
	case 11:
		KEYPAD_BUTT=3;
		break;
	case 12:
		KEYPAD_BUTT='-';/* ASCII of - */
		break;
	case 13:
		KEYPAD_BUTT=13;
		break;
	case 14:
		KEYPAD_BUTT=0;
		break;
	case 15:
	    KEYPAD_BUTT='=';/* ASCII of = */
		break;
	case 16:
		KEYPAD_BUTT='+';/* ASCII of + */
		break;
	}
	return KEYPAD_BUTT;
}
#endif      /* Number of Keypad Cols*/
#endif      /* Standard keypad*/
