#include "ADC.h"   // Use your corrected header file

void ADC_Init(void)
{
    /* Select reference voltage = AVcc with external capacitor at AREF pin */
    ADMUX = (1 << REFS0);   // REFS1 = 0, REFS0 = 1 → AVcc

    /* Enable ADC and set prescaler to 128
       16 MHz / 128 = 125 kHz (valid ADC clock: 50–200 kHz) */
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}


unsigned short ADC_ReadChannel(unsigned char ch)
{
    /* Ensure channel is between 0–7 */
    ch &= 0x07;

    /* Clear previous channel selection (ADMUX lower 3 bits)
       then set new channel */
    ADMUX = (ADMUX & 0xF8) | ch;

    /* Start conversion */
    ADCSRA |= (1 << ADSC);

    /* Wait for conversion to finish (ADSC = 0 when done) */
    while (ADCSRA & (1 << ADSC));

    /* Return ADC result (ADC = ADCW 16-bit register: ADCL + ADCH) */
    return ADC;
}


