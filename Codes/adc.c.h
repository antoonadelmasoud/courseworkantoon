6#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>   // Needed for ADC registers

/* 
 * Initializes the ADC:
 * - Selects reference voltage
 * - Sets prescaler
 * - Enables ADC module
 */
void ADC_Init(void);

/*
 * Reads analog value from a given ADC channel (0–7)
 * Returns: 10-bit ADC result (0–1023)
 */
unsigned short ADC_ReadChannel(unsigned char ch);

#endif /* ADC_H_ */
