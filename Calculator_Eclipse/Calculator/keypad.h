/******************************************************************************
 * [Module]      : KEYPAD
 * [File Name]   : keypad.h
 * [Description] : Header file for the Keypad driver
 * [Author]      : Ziad Emad
 *******************************************************************************/
#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define KEYPAD_NUM_COLS                   4
#define KEYPAD_NUM_ROWS                   4

/* Keypad Port Configurations */
#define KEYPAD_ROW_PORT_ID                PORTA_ID
#define KEYPAD_FIRST_ROW_PIN_ID           PIN0_ID

#define KEYPAD_COL_PORT_ID                PORTA_ID
#define KEYPAD_FIRST_COL_PIN_ID           PIN4_ID

/* Keypad button logic configurations */
#define KEYPAD_BUTTON_PRESSED            LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED           LOGIC_HIGH

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 *****************************************************************************************************
[Function Name]	: KEYPAD_getPressedKey
[Description]  	: Get the Keypad pressed button.
[Arguments]    	: This Function take no Arguments.
[Returns]      	: This Function return nothing

 ****************************************************************************************************/
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
