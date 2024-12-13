/*
 * Button0.c
 *
 *  Created on: Nov 14, 2024
 *      Author: vtrnn
 */
#include "Button0.h"
// 1 = NORMAL_STATE
// 0 = PRESSED_STATE
static int KeyReg0 = 1;
static int KeyReg1 = 1;
static int KeyReg2 = 1;
static int KeyReg3 = 1;
static int Timerforkeypressed = 200;
int button0_trigger = 0;
static void SubKeyProcess()
{
	button0_trigger = 1;
}

void GetkeyInput0()
{
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13);
	if (KeyReg0 == KeyReg1 && KeyReg1 == KeyReg2)
	{
		if (KeyReg3 != KeyReg2)
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
