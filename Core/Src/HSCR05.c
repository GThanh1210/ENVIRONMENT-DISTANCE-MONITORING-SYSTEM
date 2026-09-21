#include "HSCR05.h"


void Delay_us_tim3(uint16_t us) {
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	while (__HAL_TIM_GET_COUNTER(&htim3) < us);
}
void TRIG_ON() {
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 1);
	Delay_us_tim3(12);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, 0);
}

float Read_HSCR05() {
	uint16_t time = 0;
	TRIG_ON();
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == 0) {
		if (__HAL_TIM_GET_COUNTER(&htim3) > 30000) {
			return -1.0f;
		}
	}
	__HAL_TIM_SET_COUNTER(&htim3, 0);
	while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == 1) {
		if (__HAL_TIM_GET_COUNTER(&htim3) > 30000) {
			return -2.0f;
		}
	}
	time = __HAL_TIM_GET_COUNTER(&htim3);
	return (time * 0.034f) / 2.0f;
}
