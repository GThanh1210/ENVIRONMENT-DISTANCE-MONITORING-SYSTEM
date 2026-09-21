#ifndef DHT11_H
#define DHT11_H
#include "main.h"

extern TIM_HandleTypeDef htim2;

typedef struct
{
	uint8_t  Tem;
	uint8_t  RH;
}TemRH_t;
extern volatile uint8_t int_RH, float_RH, int_T, float_T, check_sum;
void SetToInput();
void SetToOutput();
void DHT11_Start();
uint8_t Read_Data_DTH11();
TemRH_t DHT11_Handle();




#endif
