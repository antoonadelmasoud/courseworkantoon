

#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "DIO.h"
#include "LcdCW2.h"
#include "AdcCW2.h"

#define MIN_LIMIT 0
#define MAX_LIMIT 1023

int main(void)
{
    LCD_Init();      // Initialize LCD
    ADC_Init();      // Initialize ADC
    DIO_Init();      // Initialize digital I/O

    unsigned short LH = 1000;   // High limit
    unsigned short LL = 500;    // Low limit

    while (1)
    {
        unsigned short Sensor = ADC_ReadChannel(0);  // Read LDR or sensor

        /*---------------------- BUTTON CONTROL -----------------------*/
        if (Button1())     // Increase High Limit
        {
            if (LH < MAX_LIMIT)
                LH += 10;
        }

        if (Button2())     // Decrease High Limit
        {
            if (LH > MIN_LIMIT)
                LH -= 10;
        }

        if (Button3())     // Increase Low Limit
        {
            if (LL < MAX_LIMIT)
                LL += 10;
        }

        if (Button4())     // Decrease Low Limit
        {
            if (LL > MIN_LIMIT)
                LL -= 10;
        }

        /*---------------------- LED CONTROL ---------------------------*/
        if (Sensor > LL && Sensor < LH)
        {
            LED_ON();
        }
        else
        {
            LED_OFF();
        }

        /*---------------------- LCD DISPLAY ---------------------------*/
        LCD_Display(LL, LH, Sensor);

        _delay_ms(100);   // Stability refresh delay
    }
}

