/*
 * softwaretimer.c
 *
 *  Created on: Nov 11, 2023
 *      Author: quoca
 */


#include "softwaretimer.h"
int timercounter0 = 0;
int timerflag0 = 0;

void setTimer0(int duration)
{
	timercounter0 = duration;
	timerflag0 = 0;
}

void runTimer0()
{
	if (timercounter0 > 0)
	{
		timercounter0--;
		if (timercounter0 <= 0)
		{
			timerflag0 = 1;
		}
	}
}

int timercounter1 = 0;
int timerflag1 = 0;

void setTimer1(int duration)
{
	timercounter1 = duration;
	timerflag1 = 0;
}

void runTimer1()
{
	if (timercounter1 > 0)
	{
		timercounter1--;
		if (timercounter1 <= 0)
		{
			timerflag1 = 1;
		}
	}
}

int timercounter2 = 0;
int timerflag2 = 0;

void setTimer2(int duration)
{
	timercounter2 = duration;
	timerflag2 = 0;
}

void runTimer2()
{
	if (timercounter2 > 0)
	{
		timercounter2--;
		if (timercounter2 <= 0)
		{
			timerflag2 = 1;
		}
	}
}

int timercounter3 = 0;
int timerflag3 = 0;

void setTimer3(int duration)
{
	timercounter3 = duration;
	timerflag3 = 0;
}

void runTimer3()
{
	if (timercounter3 > 0)
	{
		timercounter3--;
		if (timercounter3 <= 0)
		{
			timerflag3 = 1;
		}
	}
}

int timercounter4 = 0;
int timerflag4 = 0;

void setTimer4(int duration)
{
	timercounter4 = duration;
	timerflag4 = 0;
}

void runTimer4()
{
	if (timercounter4 > 0)
	{
		timercounter4--;
		if (timercounter4 <= 0)
		{
			timerflag4 = 1;
		}
	}
}