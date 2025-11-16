#ifndef _DIO_H_
#define _DIO_H_

#include <avr/io.h>
#include <stdbool.h>

/*                         LED DEFINITIONS                       */
#define LED_PORT    PORTB
#define LED_DDR     DDRB
#define LED_PIN     PB0         // Update if your LED is on a different pin

/*                    PUSH BUTTON DEFINITIONS                    */
/* Button 1 */
#define PUSH1_PORT  PORTD
#define PUSH1_DDR   DDRD
#define PUSH1_PIN   PIND
#define PUSH1_BIT   PD2

/* Button 2 */
#define PUSH2_PORT  PORTD
#define PUSH2_DDR   DDRD
#define PUSH2_PIN   PIND
#define PUSH2_BIT   PD3

/* Button 3 */
#define PUSH3_PORT  PORTD
#define PUSH3_DDR   DDRD
#define PUSH3_PIN   PIND
#define PUSH3_BIT   PD4

/* Button 4 */
#define PUSH4_PORT  PORTD
#define PUSH4_DDR   DDRD
#define PUSH4_PIN   PIND
#define PUSH4_BIT   PD5

/*                     FUNCTION PROTOTYPES                       */

void DIO_Init(void);

void LED_ON(void);
void LED_OFF(void);

bool Button1(void);
bool Button2(void);
bool Button3(void);
bool Button4(void);

/*----------------------------- DIO.h -----------------------------*/
#endif  // _DIO_H_
