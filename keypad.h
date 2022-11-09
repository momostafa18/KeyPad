/******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Mohamed Mostafa
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "std_types.h"
#include "gpio.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/* If we are using standard keypad */
#undef STANDARAD_KEYPAD
/* Setting the technique of the resistors used*/
#define PULLUP_RESISTORS                                 0
#define PULLDOWN_RESISTORS                               1
#define KEYPAD_RESISTORS_TECHNIQUE               PULLDOWN_RESISTORS
/* Setting number of columns and rows in the keypad*/
#define NUMBER_OF_KEYPAD_COLUMNS                         3
#define NUMBER_OF_KEYPAD_ROWS                            4
#if((NUMBER_OF_KEYPAD_COLUMNS !=3 && NUMBER_OF_KEYPAD_COLUMNS !=4) || NUMBER_OF_KEYPAD_ROWS!=4 )
#error "You dumb ass mf, no keypad is found with this size"
#endif
/* Setting keypad Columns port and first pin*/
#define KEYPAD_COLUMNS_PORT_ID                          PORTB_ID
#define KEYPAD_COLUMNS_FIRST_PIN_ID                     PIN4_ID
/* Setting keypad Rows port and first pin*/
#define KEYPAD_ROWS_PORT_ID                             PORTB_ID
#define KEYPAD_ROWS_FIRST_PIN_ID                        PIN0_ID
/* Setting the value of the button pressed depending on the technique of the resistors used*/
#if (KEYPAD_RESISTORS_TECHNIQUE == PULLDOWN_RESISTORS)
#define BUTTON_PRESSED                                     1
#define BUTTON_RELEASED                                    0
#elif (KEYPAD_RESISTORS_TECHNIQUE == PULLUP_RESISTORS)
#define BUTTON_PRESSED                                     0
#define BUTTON_RELEASED                                    1
#endif

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 Get the key pressed and display it
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
