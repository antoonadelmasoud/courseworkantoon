#ifndef _LCD_H_
#define _LCD_H_

/*
 * Sends a command to the LCD (see LCD command table for reference)
 */
void LCD_Command(unsigned char cmd);

/*
 * Sends a single character to the LCD for display
 */
void LCD_Char(unsigned char data);

/*
 * Initializes the LCD in 4-bit mode
 */
void LCD_Init(void);

/*
 * Displays a null-terminated string on the LCD
 */
void LCD_String(char *str);

/*
 * Displays a string on the LCD at a specific row and column
 * row = 0 or 1, pos = 0–15
 */
void LCD_String_xy(char row, char pos, char *str);

/*
 * Clears LCD display and resets cursor to home position
 */
void LCD_Clear(void);

/*
 * Displays LL, LH, and Sensor values in formatted positions
 * Used specifically for CW2 application
 */
void LCD_Display(unsigned int LL, unsigned int LH, unsigned int Sensor);

#endif /* _LCD_H_ */


