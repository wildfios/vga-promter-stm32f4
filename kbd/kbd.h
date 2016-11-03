#ifndef __keyboard_bj__
#define __keyboard_bj__

#include "STM32F4xx.h"

void	btn_init(void);
int		btn_get (void);

void btn_init() 
{
	RCC->AHB1ENR  |= ((1UL <<  0) );              /* Enable GPIOA clock         */

	GPIOA->MODER    &= ~((3UL << 2*0)  );         /* PA.0 is input              */
	GPIOA->OSPEEDR  &= ~((3UL << 2*0)  );          /* PA.0 is 50MHz Fast Speed   */
	GPIOA->OSPEEDR  |=  ((2UL << 2*0)  ); 
	GPIOA->PUPDR    &= ~((3UL << 2*0)  );         /* PA.0 is no Pull up         */
}

int btn_get(void) 
{
	return (GPIOA->IDR & (1UL << 0));
}

#endif
