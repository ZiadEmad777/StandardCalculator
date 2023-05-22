/*************************************************************************************************
 * [File Name]    : Calculator.c
 * [Description]  : Calculator main program (source File)
 * [Author]       : Ziad Emad
 **************************************************************************************************/
#include "gpio.h"
#include "keypad.h"
#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

/*
 *****************************************************************************************************

[Function Name]	: Calculations
[Description]  	: This function is responsible for calculating the result of the mathematical operation
[Arguments]    	: This function Take the operator type (+\-\*\/) and the two numbers which user entered.
[Returns]      	: This Function return the result of the mathematical operation.

 ****************************************************************************************************/
uint16 Calculations(char Op,uint16 NUM1,uint16 NUM2)
{
	uint8 result;
	switch (Op) {
	case '+':
		result= (NUM1) + (NUM2);
		break;
	case '-':
		result= (NUM1) - (NUM2);
		break;
	case '*':
		result= (uint16)( (NUM1) * (NUM2) );
		break;
	case '%':
		if (NUM2 != 0) {
			result= ((uint16)(NUM1)) / (NUM2);
		}
		else {
			/*to clear the calculation process entered
			 * overwrite on the numbers by space character
			 * then move the cursor to row 2 col 0*/
			LCD_displayStringRowColumn(1, 0, "                ");
			LCD_displayStringRowColumn(2, 0, "                ");
			LCD_moveCursor(1, 0);
			LCD_displayStringRowColumn(1,0, "ERROR: DIV BY 0");
			return 0;
		}

		break;
	}
	return result;
}



int main(){
	/*******************************************************************************
	 *                        Variables of the main Function                       *
	 *******************************************************************************/
	uint8  key=0;
	uint8  operator=0;
	uint16 firstOperand=0;
	uint16 secondOperand=0;
	uint16 secondOperatorFlag=0;
	uint16 Result=0;

	/*******************************************************************************
	 *               Introduction texts in the beginning of the program.           *
	 *******************************************************************************/
	/*Initialize the LCD*/
	LCD_init();

	/*Clear the screen for next string*/
	LCD_clearScreen();

	/*display string in row 0 and col 0 contain "Welcome to"*/
	LCD_displayStringRowColumn(0,3,"Welcome to");

	/*display string in row 1 and col 5 contain "Ziad's"*/
	LCD_displayStringRowColumn(1,5,"Ziad's");

	/*display string in row 2 and col 3 contain "Calculator"*/
	LCD_displayStringRowColumn(2,3,"Calculator");
	_delay_ms(750);

	/*Clear the screen for next string*/
	LCD_clearScreen();
	/*Display in the first two rows an introduction to our calculator*/
	/*putting word "standard" in the first row and first col*/
	LCD_displayStringRowColumn(0,0,"Standard");
	/*putting word "Calculator" in the second row and first col*/
	LCD_displayStringRowColumn(0,12,"Calc");
	/* Move the cursor to the third row */
	LCD_moveCursor(1,0);

	/*******************************************************************************
	 *               Infinite loop which contain the calculation process            *
	 *******************************************************************************/
	while(1)
	{
		/*Receive the number from the user*/
		key=KEYPAD_getPressedKey();


		if( (key >= 0) && (key <= 9) )
		{

			switch (secondOperatorFlag)
			{

			case 0:
				/*Display on the screen the number entered.
				 * then delay for 20ms.
				 * then put the value of the key in the first operand variable*/
				LCD_intgerToString(key);
				firstOperand = ((firstOperand)*10)+key;
				break;

			case 1:
				/*Display on the screen the number entered.
				 * then delay for 20ms.
				 * then put the value of the key in the second operand variable*/
				LCD_intgerToString(key);
				secondOperand= ((secondOperand)*10)+key;
				break;
			}
		}
		else if ((key == '+') || (key == '-') || (key == '*') || (key == '%'))
		{
			/* then put the value of the key in the operator variable*/
			operator=key;
			/*CHANGE FLAGE INTO HIGH TO BE READY FOR SECOND OPERAND*/
			secondOperatorFlag=1;
			/*Display on the screen the number entered.*/
			LCD_displayCharacter(key);
		}
		else if (key == '=')
		{
			Result=Calculations(operator,firstOperand,secondOperand);

			/*Display on the screen the number entered.*/
			LCD_displayCharacter(key);

			/*put the result in row 3 col 0*/
			LCD_moveCursor(2, 0);

			/*Display on the screen the result of the calculation.*/
			LCD_intgerToString(Result);

			/*reset the variables*/
			firstOperand= Result;
			secondOperand=0;

		}
		else if (key == 13)
		{

			/* Reset variables and display initial state */
			firstOperand= 0;
			secondOperand=0;
			Result=0;
			operator=0;
			secondOperatorFlag=0;

			/*to clear the calculation process entered
			 * overwrite on the numbers by space character
			 * then move the cursor to row 2 col 0*/
			LCD_displayStringRowColumn(1, 0, "               ");
			LCD_displayStringRowColumn(2, 0, "               ");
			LCD_moveCursor(1, 0);
		}

		_delay_ms(300); /*Press Time*/

	}

}
