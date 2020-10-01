 /*ADC Header file to interface ADC STM8S103F easily
 * Website: https://circuitdigest.com
 * Code by: Aswinth Raj
 */
 
 /*#define AIN2		GPIOC, GPIO_PIN_4
 #define AIN3		GPIOD, GPIO_PIN_2
 #define AIN4		GPIOD, GPIO_PIN_3
 #define AIN5 	GPIOD, GPIO_PIN_5
 #define AIN6 	GPIOD, GPIO_PIN_6*/
 
 
 
 typedef enum 
 {
	 AIN2 = ADC1_CHANNEL_2,
	 AIN3 = ADC1_CHANNEL_3,
	 AIN4 = ADC1_CHANNEL_4,
	 AIN5 = ADC1_CHANNEL_5,
	 AIN6 = ADC1_CHANNEL_6
 }ADC_CHANNEL_TypeDef;
 
 unsigned int ADC_Read(ADC_CHANNEL_TypeDef ADC_Channel_Number)
 {
   unsigned int result = 0;

	 ADC1_DeInit();
	 
	 ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, 
             ADC_Channel_Number,
             ADC1_PRESSEL_FCPU_D18, 
             ADC1_EXTTRIG_TIM, 
             DISABLE, 
             ADC1_ALIGN_RIGHT, 
             ADC1_SCHMITTTRIG_ALL, 
             DISABLE);
                                                                                  
   ADC1_Cmd(ENABLE);
	 
	 
	ADC1_StartConversion();
	while(ADC1_GetFlagStatus(ADC1_FLAG_EOC) == FALSE);
                                
  result = ADC1_GetConversionValue();
  ADC1_ClearFlag(ADC1_FLAG_EOC);
	
	ADC1_DeInit();
	
	return result; 
 }
