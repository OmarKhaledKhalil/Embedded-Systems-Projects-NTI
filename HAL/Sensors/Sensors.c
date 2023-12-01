#include "StdTypes.h"

#include "ADC_Interface.h"

#include "Sensors.h"

static Sensor_Config LM35_Config;



void LM35_void_Init (void)
{
	LM35_Config.Auto_Trigger=FREE_RURNINIG;
	LM35_Config.Voltage_Refrence=VREF_VCC;
	ADC_void_Init(&LM35_Config,PRE_SCALER_64);
}


u8  LM35_u16_ReadTemp(ADC_Chanel_type channel,u16 * Temp)
{
	u16 volt;
	if(ADC_u16_getVoltageValueSynchNonBlocking(channel,LM35_VREF,&volt)) 
	{
		*Temp= volt/10;
		return 1;
	}
	return 0;
}
