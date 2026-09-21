
//  TIM3 -> HCSR05 -> PA8->TRIG, PA9->ECHO
#ifndef HSCR05_H
#define HSCR05_H
#include "main.h"

#define TRIG_PIN   GPIO_PIN_8
#define TRIG_PORT  GPIOB
#define ECHO_PIN   GPIO_PIN_9
#define ECHO_PORT  GPIOB
#define GPIO_PIN_RESET    0
#define GPIO_PIN_SET      1

extern TIM_HandleTypeDef htim3;
void Delay_us(uint16_t us);
void TRIG_ON();
float Read_HSCR05();
#endif
