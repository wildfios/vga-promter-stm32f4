#ifndef __sd_hal__
#define	__sd_hal__

#include "STM32F4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"

#define   SD_CS     GPIO_Pin_2
#define   SD_SI	    GPIO_Pin_7
#define   SD_SO     GPIO_Pin_6
#define   SD_CL     GPIO_Pin_5

#define	  sd_cs_hi	GPIOA->BSRRL = 1 << 2;
#define   sd_cs_lo	GPIOA->BSRRH = 1 << 2;

unsigned char	sd_spi_send		(unsigned char data);
void					sd_spi_init		(void);
void					spi_up_speed	(void);

#endif
