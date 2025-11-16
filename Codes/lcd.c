#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "LCD.h"

#define LCD_DATA_DIR   DDRD
#define LCD_DATA_PORT  PORTD    // D4–D7

#define LCD_CTRL_DIR   DDRB
#define LCD_CTRL_PORT  PORTB    // RS, EN
#define RS PB0
#define EN PB1

/*-------------------------------------------*/
/* Send a command to LCD                     */
/*-------------------------------------------*/
void LCD_Command(unsigned char cmd)
{
    // Send upper nibble
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmd & 0xF0);
    LCD_CTRL_PORT &= ~(1 << RS);     // Command mode
    LCD_CTRL_PORT |=  (1 << EN);
    _delay_us(1);
    LCD_CTRL_PORT &= ~(1 << EN);
    _delay_us(200);

    // Send lower nibble
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (cmd << 4);
    LCD_CTRL_PORT |=  (1 << EN);
    _delay_us(1);
    LCD_CTRL_PORT &= ~(1 << EN);
    _delay_ms(2);
}

/*-------------------------------------------*/
/* Send a character to LCD                   */
/*-------------------------------------------*/
void LCD_Char(unsigned char data)
{
    // Send upper nibble
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
    LCD_CTRL_PORT |=  (1 << RS);     // Data mode
    LCD_CTRL_PORT |=  (1 << EN);
    _delay_us(1);
    LCD_CTRL_PORT &= ~(1 << EN);
    _delay_us(200);

    // Send lower nibble
    LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data << 4);
    LCD_CTRL_PORT |=  (1 << EN);
    _delay_us(1);
    LCD_CTRL_PORT &= ~(1 << EN);
    _delay_ms(2);
}

/*-------------------------------------------*/
/* Initialize LCD in 4-bit mode              */
/*-------------------------------------------*/
void LCD_Init(void)
{
    LCD_DATA_DIR |= 0xF0;              // PD4–PD7 outputs
    LCD_CTRL_DIR |= (1 << RS) | (1 << EN);   // PB0, PB1 outputs

    _delay_ms(20);

    LCD_Command(0x02);   // Initialize 4-bit mode
    LCD_Command(0x28);   // 2 lines, 5x7 matrix
    LCD_Command(0x0C);   // Display ON, cursor OFF
    LCD_Command(0x06);   // Auto-increment cursor
    LCD_Command(0x01);   // Clear screen
    _delay_ms(2);
}

/*-------------------------------------------*/
void LCD_String(char *str)
{
    while (*str)
        LCD_Char(*str++);
}

void LCD_String_xy(char row, char pos, char *str)
{
    if (row == 0)
        LCD_Command(0x80 + pos);
    else if (row == 1)
        LCD_Command(0xC0 + pos);

    LCD_String(str);
}

void LCD_Clear()
{
    LCD_Command(0x01);
    _delay_ms(2);
}

/*     Custom Display Function for HMI       */
/*-------------------------------------------*/
void LCD_Display(unsigned int LL, unsigned int LH, unsigned int Sensor)
{
    char buffer[10];

    // Row 1: Sensor reading
    LCD_String_xy(0, 0, "LDR:");
    sprintf(buffer, "%u", Sensor);
    LCD_String(buffer);

    // Row 2: LL and LH
    LCD_String_xy(1, 0, "LL:");
    sprintf(buffer, "%u", LL);
    LCD_String(buffer);

    LCD_String_xy(1, 8, "LH:");
    sprintf(buffer, "%u", LH);
    LCD_String(buffer);

    // Alert Status
    if (Sensor > LL && Sensor < LH)
        LCD_String_xy(0, 10, "ON ");
    else
        LCD_String_xy(0, 10, "OFF");
}


