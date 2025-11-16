#include <stdbool.h>
#include <util/delay.h>

#include "DIO.h"   // Include the DIO header file

/*-----------------------------*/
/*       DIO INITIALIZATION    */
/*-----------------------------*/
void DIO_Init(void)
{
    LED_DDR |= (1 << LED_PIN);      // Configure LED pin as output

    // Configure push buttons as inputs
    PUSH1_DDR &= ~(1 << PUSH1_BIT);
    PUSH2_DDR &= ~(1 << PUSH2_BIT);
    PUSH3_DDR &= ~(1 << PUSH3_BIT);
    PUSH4_DDR &= ~(1 << PUSH4_BIT);

    // Enable internal pull-ups (unpressed = HIGH)
    PUSH1_PORT |= (1 << PUSH1_BIT);
    PUSH2_PORT |= (1 << PUSH2_BIT);
    PUSH3_PORT |= (1 << PUSH3_BIT);
    PUSH4_PORT |= (1 << PUSH4_BIT);
}

/*-----------------------------*/
/*            LED CONTROL      */
/*-----------------------------*/
void LED_ON(void)
{
    LED_PORT |= (1 << LED_PIN);     // Set LED pin HIGH
}

void LED_OFF(void)
{
    LED_PORT &= ~(1 << LED_PIN);    // Set LED pin LOW
}

/*-----------------------------*/
/*         BUTTON READS        */
/*-----------------------------*/

bool Button1(void)
{
    if ((PUSH1_PIN & (1 << PUSH1_BIT)) == 0)     // Check if pressed (active low)
    {
        _delay_ms(50);                           // Debounce
        if ((PUSH1_PIN & (1 << PUSH1_BIT)) == 0)
        {
            return true;
        }
    }
    return false;
}

bool Button2(void)
{
    if ((PUSH2_PIN & (1 << PUSH2_BIT)) == 0)
    {
        _delay_ms(50);
        if ((PUSH2_PIN & (1 << PUSH2_BIT)) == 0)
        {
            return true;
        }
    }
    return false;
}

bool Button3(void)
{
    if ((PUSH3_PIN & (1 << PUSH3_BIT)) == 0)
    {
        _delay_ms(50);
        if ((PUSH3_PIN & (1 << PUSH3_BIT)) == 0)
        {
            return true;
        }
    }
    return false;
}

bool Button4(void)
{
    if ((PUSH4_PIN & (1 << PUSH4_BIT)) == 0)
    {
        _delay_ms(50);
        if ((PUSH4_PIN & (1 << PUSH4_BIT)) == 0)
        {
            return true;
        }
    }
    return false;
}