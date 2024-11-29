/*
 * timer.c
 *
 *  Created on: Nov 15, 2024
 *      Author: vtrnn
 */

#include "main.h"
#include "input_reading.h"

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM2) {
		button_reading();
	}
}
