#ifndef SENSORS_H_
#define SENSORS_H_

#define LM35_MAX_READ  1500
#define LM35_VREF      5000
#define LM35_CHANNEL CH_0

void LM35_void_Init (void);
u8 LM35_u16_ReadTemp(ADC_Chanel_type channel,u16 * Temp);

#endif