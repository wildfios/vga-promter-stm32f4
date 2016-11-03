#include "sd_hal.h"

unsigned char sd_spi_send (unsigned char data)
{          
	SPI_I2S_SendData(SPI3, data);
		while (!(SPI3->SR & SPI_SR_TXE));

	return SPI3->DR;
}

void sd_spi_init ()
{
	SPI_InitTypeDef			SPI_InitStruct;
	GPIO_InitTypeDef		GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,  ENABLE);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI3);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI3);

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);		
			   
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);		

	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	SPI_InitStruct.SPI_Direction	= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode				= SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize		= SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL				= SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA				= SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS				= SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_64;
	SPI_InitStruct.SPI_FirstBit						= SPI_FirstBit_MSB;
	SPI_Init(SPI3, &SPI_InitStruct);
	SPI_Cmd(SPI3, ENABLE);

	sd_cs_hi   
}
void spi_up_speed ()
{
SPI_InitTypeDef			SPI_InitStruct;

	SPI_InitStruct.SPI_Direction	= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode				= SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize		= SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL				= SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA				= SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS				= SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler	= SPI_BaudRatePrescaler_8;
	SPI_InitStruct.SPI_FirstBit						= SPI_FirstBit_MSB;
	SPI_Init(SPI3, &SPI_InitStruct);
	SPI_Cmd(SPI3, ENABLE);
}
