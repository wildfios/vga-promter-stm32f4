#ifndef __ADC_DRIVER__
#define __ADC_DRIVER__

void adc_init ()
{
	ADC_InitTypeDef			ADC_InitStr;
	ADC_CommonInitTypeDef	ADC_CISruct;
	GPIO_InitTypeDef		GPIO_InitStructure;

   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,  ENABLE);

   /* Configure ADC3 Channel12 pin as analog input ******************************/
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

   /* ADC Common Init **********************************************************/
   ADC_CISruct.ADC_Mode = ADC_Mode_Independent;
   ADC_CISruct.ADC_Prescaler = ADC_Prescaler_Div2;
   ADC_CISruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
   ADC_CISruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
   ADC_CommonInit(&ADC_CISruct);
   
   /* ADC3 Init ****************************************************************/
   ADC_InitStr.ADC_Resolution = ADC_Resolution_8b;
   ADC_InitStr.ADC_ScanConvMode = DISABLE;
   ADC_InitStr.ADC_ContinuousConvMode = DISABLE;
   ADC_InitStr.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
   ADC_InitStr.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T8_TRGO;
   ADC_InitStr.ADC_DataAlign = ADC_DataAlign_Right;
   ADC_InitStr.ADC_NbrOfConversion = 0;
   ADC_Init(ADC1, &ADC_InitStr);
   
   /* ADC3 regular channel12 configuration *************************************/
   ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_3Cycles);
   
   /* Enable ADC3 */
   ADC_Cmd(ADC1, ENABLE);
}

int adc_get ()
{
 		ADC_SoftwareStartConv (ADC1);   
 		while ((ADC1->SR & 0x02) == 0);	      
 		
	return ADC1->DR;		
}


#endif
