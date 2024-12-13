/*
 * display.c
 *
 *  Created on: Nov 14, 2024
 *      Author: vtrnn
 */

#include "display.h"


void display7SEG(int num) {
	switch (num) {
		case 0:
			HAL_GPIO_WritePin(GPIOB, 0B0111111, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B1000000, GPIO_PIN_SET);
			break;
		case 1:
			HAL_GPIO_WritePin(GPIOB, 0B0000110, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B1111001, GPIO_PIN_SET);
			break;
		case 2:
			HAL_GPIO_WritePin(GPIOB, 0B1011011, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0100100, GPIO_PIN_SET);
			break;
		case 3:
			HAL_GPIO_WritePin(GPIOB, 0B1001111, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0110000, GPIO_PIN_SET);
			break;
		case 4:
			HAL_GPIO_WritePin(GPIOB, 0B1100110, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0011001, GPIO_PIN_SET);
			break;
		case 5:
			HAL_GPIO_WritePin(GPIOB, 0B1101101, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0010010, GPIO_PIN_SET);
			break;
		case 6:
			HAL_GPIO_WritePin(GPIOB, 0B1111101, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0000010, GPIO_PIN_SET);
			break;
		case 7:
			HAL_GPIO_WritePin(GPIOB, 0B0000111, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B1111000, GPIO_PIN_SET);
			break;
		case 8:
			HAL_GPIO_WritePin(GPIOB, 0B1111111, GPIO_PIN_RESET);
			break;
		case 9:
			HAL_GPIO_WritePin(GPIOB, 0B1101111, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, 0B0010000, GPIO_PIN_SET);
			break;
		default:
			HAL_GPIO_WritePin(GPIOB, 0B1111111, GPIO_PIN_SET);
			break;
	}
}

const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1,2,3,4};
void update7SEG(int index){
	display7SEG(led_buffer[index]);
	switch(index){
	case 0:
		// Display the second 7 SEG with led_buffer[0]
		index_led = 1;
		HAL_GPIO_WritePin(P1_GPIO_Port, P1_Pin, RESET);
		HAL_GPIO_WritePin(P2_GPIO_Port, P2_Pin, SET);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, SET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, SET);
		break;
	case 1:
		// Display the second 7 SEG with led_buffer[1]
		index_led = 2;
		HAL_GPIO_WritePin(P1_GPIO_Port, P1_Pin, SET);
		HAL_GPIO_WritePin(P2_GPIO_Port, P2_Pin, RESET);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, SET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, SET);
		break;
	case 2:
		// Display the third 7 SEG with led_buffer[2]
		index_led = 3;
		HAL_GPIO_WritePin(P1_GPIO_Port, P1_Pin, SET);
		HAL_GPIO_WritePin(P2_GPIO_Port, P2_Pin, SET);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, RESET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, SET);
		break;
	case 3:
		// Display the forth 7 SEG with led_buffer[3]
		index_led = 0;
		HAL_GPIO_WritePin(P1_GPIO_Port, P1_Pin, SET);
		HAL_GPIO_WritePin(P2_GPIO_Port, P2_Pin, SET);
		HAL_GPIO_WritePin(L1_GPIO_Port, L1_Pin, SET);
		HAL_GPIO_WritePin(L2_GPIO_Port, L2_Pin, RESET);
		break;
	default:
		break;
	}
}


int counterL = 1, counterP = 1;
void updateClockBufferMode1() {
	// Cap nhat gia tri thoi gian vao trong clockBuffer
	// Doi voi 2 LED 7-SEG Landscape

	/* Den RED-Landscape sang (dem nguoc tu RED-1 -> 0) */
	if (counterL <= RED) {
		led_buffer[0] = (RED - counterL) / 10;
		led_buffer[1] = (RED - counterL) % 10;
	}
	/* Den GREEN-Landscape sang (dem nguoc tu GREEN-1 -> 0) */
	else if (counterL <= (RED + GREEN)) {
		led_buffer[0] = (RED + GREEN - counterL) / 10;
		led_buffer[1] = (RED + GREEN - counterL) % 10;
	}
	/* Den AMBER-Landscape sang (dem nguoc tu AMBER-1 -> 0) */
	else {
		led_buffer[0] = (RED + GREEN + AMBER - counterL) / 10;
		led_buffer[1] = (RED + GREEN + AMBER - counterL) % 10;
	}
	counterL++;
	/* Neu thoi gian AMBER-Landscape ket thuc, quay tro lai setup thoi gian cho RED-Landscape sang lai */
	if (counterL > RED + AMBER + GREEN) counterL = 1;


	// Doi voi 2 LED 7-SEG Portrait
	/* Den GREEN-Portrait sang (dem nguoc tu GREEN-1 -> 0) */
	if (counterP <= GREEN) {
		led_buffer[2] = (GREEN - counterP) / 10;
		led_buffer[3] = (GREEN - counterP) % 10;
	}
	/* Den AMBER-Portrait sang (dem nguoc tu AMBER-1 -> 0) */
	else if (counterP <= (AMBER + GREEN)) {
		led_buffer[2] = (AMBER + GREEN - counterP) / 10;
		led_buffer[3] = (AMBER + GREEN - counterP) % 10;
	}
	/* Den RED-Portrait sang (dem nguoc tu RED-1 -> 0) */
	else {
		led_buffer[2] = (RED + GREEN + AMBER - counterP) / 10;
		led_buffer[3] = (RED + GREEN + AMBER - counterP) % 10;
	}
	counterP++;
	/* Neu thoi gian RED-Portrait ket thuc, quay tro lai setup thoi gian cho GREEN-Portrait sang lai */
	if (counterP > RED + AMBER + GREEN) counterP = 1;
}

void updateClockBufferMode2() {
	// Hien thi mode 2
	led_buffer[0] = 0;
	led_buffer[1] = 2;
	// Hien thi value RED
	led_buffer[2] = RED / 10;
	led_buffer[3] = RED % 10;
}

void updateClockBufferMode3() {
	// Hien thi mode 3
	led_buffer[0] = 0;
	led_buffer[1] = 3;
	// Hien thi value AMBER
	led_buffer[2] = AMBER / 10;
	led_buffer[3] = AMBER % 10;
}

void updateClockBufferMode4() {
	// Hien thi mode 4
	led_buffer[0] = 0;
	led_buffer[1] = 4;
	// Hien thi value GREEN
	led_buffer[2] = GREEN / 10;
	led_buffer[3] = GREEN % 10;
}
