# vga-promter-stm32f4
VGA driver for stm32 realisation. 

This is my sources of TV promter for VGA display. Hardware stm32f407vg (DiscoveryF4) based on ARM Cortex M4 core.

VGA lib lies in ./VGA. It is full realised single buffer VGA driver for embeded MCUs with small RAM size.

Features:
 - 640 x 480 and 800 x 600 modes.
 - Scroll up and down for text output with different speed.
 - In text mode all you need is array of text (no video memory needed, usefull for small MCUs)
 - Easy porting on different MCUs
 - Reads text from SD cards 2GB or less. 
 - Simple file manager
 
Usage:
 - Copy ./VGA to your project dir
 - Change TIM2_IRQHandler in vga.c on timer IRQ heandler of yours MCU.
 - Timer must generates IRQ each 32.5 uS
 - in VGA_hal.h set PIN togle function for MCU you are using
 

Deps: SPL lib and sturtup code for stm32f4. 
