/*
 * ADC_Prog.c
 *
 *  Created on: ???/???/????
 *      Author: dell
 */


#include "ADC_Interface.h"
#include "ADC_Private.h"



void M_ADC_Void_ADCInit(void)
{
#if   ADC_V_REF_MODE   ==   AVCC
	CLR_BIT(ADMUX_REG,REFS1_BIT);
	SET_BIT(ADMUX_REG,REFS0_BIT);
#elif ADC_V_REF_MODE   ==   AREF_PIN
	CLR_BIT(ADMUX_REG,REFS1_BIT);
	CLR_BIT(ADMUX_REG,REFS0_BIT);
#elif ADC_V_REF_MODE   ==   _2V5
	SET_BIT(ADMUX_REG,REFS1_BIT);
	SET_BIT(ADMUX_REG,REFS0_BIT);
#endif

	/* TO SELECT RIGHT ADDJUST */
	CLR_BIT(ADMUX_REG,ADLAR_BIT);

#if   ADC_PRESCALER_DV   ==   128
	SET_BIT(ADCSRA_REG,ADPS2_BIT);
	SET_BIT(ADCSRA_REG,ADPS1_BIT);
	SET_BIT(ADCSRA_REG,ADPS0_BIT);
#elif ADC_PRESCALER_DV   ==   64
	SET_BIT(ADCSRA_REG,ADPS2_BIT);
	SET_BIT(ADCSRA_REG,ADPS1_BIT);
	CLR_BIT(ADCSRA_REG,ADPS0_BIT);
#endif

	SET_BIT(ADCSRA_REG,ADATE_BIT);
	/* TO ENABLE ADC CIRCUIT */
	SET_BIT(ADCSRA_REG,ADEN_BIT);
}
u16  M_ADC_U16_ADCRead(u8 Copy_U8_AdcChannel)
{
	u32 Local_U32_Counter = 0;
	switch(Copy_U8_AdcChannel)
	{
	case ADC_CHANNEL_0:
		CLR_BIT(ADMUX_REG,MUX4_BIT);
		CLR_BIT(ADMUX_REG,MUX3_BIT);
		CLR_BIT(ADMUX_REG,MUX2_BIT);
		CLR_BIT(ADMUX_REG,MUX1_BIT);
		CLR_BIT(ADMUX_REG,MUX0_BIT);
		break;
	case ADC_CHANNEL_1:
		CLR_BIT(ADMUX_REG,MUX4_BIT);
		CLR_BIT(ADMUX_REG,MUX3_BIT);
		CLR_BIT(ADMUX_REG,MUX2_BIT);
		CLR_BIT(ADMUX_REG,MUX1_BIT);
		SET_BIT(ADMUX_REG,MUX0_BIT);
		break;
	case ADC_CHANNEL_2:
		CLR_BIT(ADMUX_REG,MUX4_BIT);
		CLR_BIT(ADMUX_REG,MUX3_BIT);
		CLR_BIT(ADMUX_REG,MUX2_BIT);
		SET_BIT(ADMUX_REG,MUX1_BIT);
		CLR_BIT(ADMUX_REG,MUX0_BIT);
		break;
	case ADC_CHANNEL_3:
		CLR_BIT(ADMUX_REG,MUX4_BIT);
		CLR_BIT(ADMUX_REG,MUX3_BIT);
		CLR_BIT(ADMUX_REG,MUX2_BIT);
		SET_BIT(ADMUX_REG,MUX1_BIT);
		SET_BIT(ADMUX_REG,MUX0_BIT);
		break;

	default:  break;
	}
	/* TO START CONVERTION */
	SET_BIT(ADCSRA_REG,ADSC_BIT);

	while(Local_U32_Counter < POLLING_TIME)
	{
		Local_U32_Counter++;
		if(GET_BIT(ADCSRA_REG,ADIF_BIT) == ADC_CONVERSION_COMPLETE)
		{
			break;
		}
	}
	return ADCL_REG;
}





