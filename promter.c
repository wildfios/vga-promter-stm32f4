#include <stdio.h>
#include "STM32F4xx.h"

#include "stm32f4xx_spi.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_adc.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

#include "vga.h"
#include "adc_drv.h"
#include "pff.h"
#include "stream.h"
#include "menu.h"
#include "kbd.h"

void main_loop ()
{
int speed;
		speed = adc_get();
		if ((speed > 70) && (speed < 130))
			vga_mode(TXT_NO_SCROLL);
		else
			if (speed > 120)
			{
				vga_scroll_speed (380 - speed);
				vga_mode(TXT_SCROLL_DWN);
			}
			else
			{
				vga_scroll_speed (speed + 110);
				vga_mode(TXT_SCROLL_UP);
			}
}

void init_all ()
{
	SystemInit();
	SystemCoreClockUpdate();                       /* Get Core Clock Frequency   */

	adc_init();
	btn_init();
	adc_init();	
}

int main (void) 
{		
FATFS fs;
WORD br1 = 0;
int fl_cnt;

	init_all();
	
	fl_cnt = file_man_count(&fs);

	vga_init(VGA_NONE);
	vga_mode(TXT_STATIC);	

	int suf_index = menu (fl_cnt);
	
	TIM_Cmd(TIM2, DISABLE);

	pf_mount(&fs);		
	pf_open (&fs, vga_get_line(suf_index));
	pf_read (&fs, vga_get_line(1), fs.fsize, &br1);	

	TIM_Cmd(TIM2, ENABLE);	
	get_lines_cnt (fs.fsize);

	while (1)
	{
		main_loop ();
	}
}
