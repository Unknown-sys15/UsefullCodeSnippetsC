#include <xc.h>
#include "lcd.h"

void LCD_DATA(unsigned char Data)
{
  if(Data & 1)
    D4 = 1;
  else
    D4 = 0;
  if(Data & 2)
    D5 = 1;
  else
    D5 = 0;
  if(Data & 4)
    D6 = 1;
  else
    D6 = 0;
  if(Data & 8)
    D7 = 1;
  else
    D7 = 0;
}

void LCD_CMD(unsigned char CMD)
{
  // Select Command Register
  RS = 0;
  // Move The Command Data To LCD
  LCD_DATA(CMD);
  // Send The EN Clock Signal
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
}
/*
void LCD_Init()
{
  // IO Pin Configurations
  //LCD_DATA_PORT_D = 0x00;
  LCD_RS_D = 0;                                                                 // Set RS pin as output
  LCD_EN_D = 0;                                                                 // Set EN pin as output
  // The Init. Procedure
  LCD_DATA(0x00);
  __delay_ms(30);                                                               // Wait for LCD to power up
  __delay_us(LCD_EN_Delay);
  LCD_CMD(0x03);
  __delay_ms(5);
  LCD_CMD(0x03);
  __delay_us(150);
  LCD_CMD(0x03);
  LCD_CMD(0x02);
  LCD_CMD(0x02);
  LCD_CMD(0x08);
  LCD_CMD(0x00);
  LCD_CMD(0x0C);
  LCD_CMD(0x00);
  LCD_CMD(0x06);
}
*/
void LCD_Init()
{
  // IO Pin Configurations
  //LCD_DATA_PORT_D = 0x00;
  LCD_RS_D = 0;                                                                 // Set RS pin as output
  LCD_EN_D = 0;                                                                 // Set EN pin as output
  // The Init. Procedure
  LCD_DATA(0x00);
  __delay_ms(40);                                                               // Wait for LCD to power up
  //__delay_us(LCD_EN_Delay);
  LCD_CMD(0x03);
  __delay_ms(5);                                                                // Wait >4.1ms
  LCD_CMD(0x03);
  __delay_us(150);                                                              // Wait >100µs
  LCD_CMD(0x03);
  
  // Switch to 4-bit mode
  LCD_CMD(0x02);                                                                // Set to 4-bit mode
  
  // Function set: DL=0 (4-bit mode), N=1 (2-line display), F=0 (5x8 dots)
  LCD_CMD(0x02);                                                                // 4-bit mode
  LCD_CMD(0x08);                                                                // 2-line display, 5x8 dots
  
  // Display control: D=1 (display on), C=0 (cursor off), B=0 (blink off)
  LCD_CMD(0x00);
  LCD_CMD(0x0C);                                                                // Display on, cursor off, blink off
  
  // Entry mode: I/D=1 (increment cursor), S=0 (no shift)
  LCD_CMD(0x00);
  LCD_CMD(0x06);                                                                // Entry mode set, increment cursor
}

void LCD_Write_Char(char Data)
{
  char Low4,High4;
  Low4 = Data & 0x0F;
  High4 = Data & 0xF0;
  RS = 1;
  LCD_DATA(High4>>4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
  LCD_DATA(Low4);
  EN = 1;
  __delay_us(LCD_EN_Delay);
  EN = 0;
  __delay_us(LCD_EN_Delay);
}

void LCD_Write_String(char *str)
{
  int i;
  for(i=0;str[i]!='\0';i++)
    LCD_Write_Char(str[i]);
}

void LCD_Clear()
{
  LCD_CMD(0);
  LCD_CMD(1);
}

void LCD_Set_Cursor(unsigned char r, unsigned char c)
{
  unsigned char Temp,Low4,High4;
  if(r == 1)
  {
    Temp = 0x80 + c - 1; //0x80 is used to move the cursor
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
  if(r == 2)
  {
    Temp = 0xC0 + c - 1;
    High4 = Temp >> 4;
    Low4 = Temp & 0x0F;
    LCD_CMD(High4);
    LCD_CMD(Low4);
  }
}

void LCD_SR()
{
  LCD_CMD(0x01);
  LCD_CMD(0x0C);
}

void LCD_SL()
{
  LCD_CMD(0x01);
  LCD_CMD(0x08);
}