/*
 * Button1.c
 *
 *  Created on: Nov 13, 2023
 *      Author: quoca
 */
#include "Button1.h"
// 1 = NORMAL_STATE
// 0 = PRESSED_STATE
static int KeyReg0 = 1;
static int KeyReg1 = 1;
static int KeyReg2 = 1;
static int KeyReg3 = 1;
static int Timerforkeypressed = 100;

int button1_trigger = 0;
int button1_trigger_long = 0;

static void SubKeyProcess()
{
	button1_trigger = 1;
}
static void SubKeyProcessLong()
{
	button1_trigger_long = 1;
}
void GetkeyInput1()
{
	KeyReg0 = KeyReg1;
	KeyReg1 = KeyReg2;
	KeyReg2 = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14);
	if (KeyReg0 == KeyReg1 && KeyReg1 == KeyReg2)
	{
		if(KeyReg3 != KeyReg2)
		{
			KeyReg3 = KeyReg2;
			if (KeyReg2 == 0)
			{
				SubKeyProcess();
				Timerforkeypressed = 100;			 
			}
		}
		else
		{
			Timerforkeypressed--;
			if (Timerforkeypressed == 0)
			{
				if (KeyReg2 == 0)
				{
					SubKeyProcessLong();
				}
				Timerforkeypressed = 100;						 
			}
		}
		if (KeyReg2 == 1 && button1_trigger_long == 1)
		{
			button1_trigger_long = 0;
		}
	}
	
}

