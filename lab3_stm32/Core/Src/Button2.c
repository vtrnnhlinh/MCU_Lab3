/*
 * Button2.c
 *
 *  Created on: Nov 13, 2023
 *      Author: quoca
 */
#include "Button2.h"
// 1 = NORMAL_STATE
// 0 = PRESSED_STATE
static int KeyReg0 = 1;
static int KeyReg1 = 1;
static int KeyReg2 = 1;
static int KeyReg3 = 1;
static int Timerforkeypressed = 200;
int button2_trigger = 0;
static void SubKeyProcess()
{
	button2_trigger = 1;
}

void GetkeyInput2()
{
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15);
	if (KeyReg0 == KeyReg1 && KeyReg1 == KeyReg2)
	{
		if(KeyReg3 != KeyReg2)
		{
			KeyReg3 = KeyReg2;
			if (KeyReg2 == 0)
			{
				SubKeyProcess();
				Timerforkeypressed = 200;			 
			}
		}
		else
		{
			Timerforkeypressed--;
			if (Timerforkeypressed == 0)
			{
				if (KeyReg2 == 0)
				{
					//SubKeyProcess();
				}
				Timerforkeypressed = 200;						 
			}
		}
	}
	
}

