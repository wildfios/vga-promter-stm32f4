#ifndef __vga_hal__
#define __vga_hal__

#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "misc.h"

#define		h_sync_hi	GPIOD->BSRRL = 1 << 8;
#define		h_sync_lo	GPIOD->BSRRH = 1 << 8;

#define		v_sync_hi	GPIOD->BSRRL = 1 << 15;
#define		v_sync_lo	GPIOD->BSRRH = 1 << 15;

#define		signal_hi	GPIOD->BSRRL = 1 << 14;
#define		signal_lo	GPIOD->BSRRH = 1 << 14;

void	vga_init_timer	(void);
void	vga_init_gpio		(void);

void	vga_init_gpio		(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);  
	
	GPIOD->MODER   =  0x55555555;
	GPIOD->OTYPER  =  0x00000000;
	GPIOD->OSPEEDR =  0xFFFFFFFF;
	GPIOD->PUPDR   =  0x55555555;
}

void vga_init_timer (void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);	 
	
	TIM_InternalClockConfig(TIM2);

	TIM_TimeBaseStructure.TIM_Period = 0x000017E0;   
	TIM_TimeBaseStructure.TIM_Prescaler = 0x00;       
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down; 
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);	  
	TIM_Cmd(TIM2, ENABLE);


 
}

#endif
