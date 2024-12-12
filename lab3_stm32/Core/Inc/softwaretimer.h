/*
 * softwaretimer.h
 *
 *  Created on: Nov 11, 2023
 *      Author: quoca
 */

#ifndef INC_SOFTWARETIMER_H_
#define INC_SOFTWARETIMER_H_

extern int timerflag0;
void setTimer0(int duration);
void runTimer0();

extern int timerflag1;
void setTimer1(int duration);
void runTimer1();

extern int timerflag2;
void setTimer2(int duration);
void runTimer2();

extern int timerflag3;
void setTimer3(int duration);
void runTimer3();


extern int timerflag4;
void setTimer4(int duration);
void runTimer4();

#endif /* INC_SOFTWARETIMER_H_ */
