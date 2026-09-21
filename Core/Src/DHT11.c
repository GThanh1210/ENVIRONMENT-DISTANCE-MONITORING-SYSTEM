#include "DHT11.h"
volatile uint8_t int_RH=0, float_RH=0, int_T=0, float_T=0, check_sum=0;
void Delay_us_tim2(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while (__HAL_TIM_GET_COUNTER(&htim2) < us);
}
void Delay_ms_tim2(uint16_t ms)
{
	uint16_t i=0;
	while(i < ms)
	{
		Delay_us_tim2(1000);
		i++;
	}
}
void SetToInput()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void SetToOutput()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	__HAL_RCC_GPIOB_CLK_ENABLE();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	GPIO_InitStruct.Pin = GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void DHT11_Start()
{
	// MCU xuat tin hieu de bat dau doc tin hieu DHT11
	SetToOutput();
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 0);
	Delay_ms_tim2(20);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, 1);
	SetToInput();
	Delay_us_tim2(30);
	// DHT11 tra lai tin hieu de bat dau doc
	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 1);
	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0);
	while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 1);
}
uint8_t Read_Data_DTH11()
{
	uint8_t BitS = 0;

	for(int i =0; i < 8;i++)
	{
		while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 0 );
		Delay_us_tim2(50);
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 1)
		{
			BitS = (BitS << 1) | (1 <<0);
		}
		else
		{
			BitS = (BitS << 1) & ~(1 << 0);
		}
		while (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 1);
	}
	return BitS;
}
TemRH_t DHT11_Handle()
{
	TemRH_t data;
	DHT11_Start();
	data.RH = Read_Data_DTH11();
	float_RH = Read_Data_DTH11();
	data.Tem = Read_Data_DTH11();
	float_T = Read_Data_DTH11();
	check_sum = Read_Data_DTH11();
	return data;
}
