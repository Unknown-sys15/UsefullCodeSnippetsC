/*
 * File:   main.c
 * Author: janra
 *
 * Created on August 21, 2024, 2:20 PM
 */
// test
#include <xc.h>
#include "config.h"
#include "lcd.h"
#include "makePinsInput.h"

// Lcd pinout settings
/*bit LCD_RS at RC1_bit;
bit LCD_EN at RC5_bit;
bit LCD_D7 at RD3_bit;
bit LCD_D6 at RD2_bit;
bit LCD_D5 at RD1_bit;
bit LCD_D4 at RD0_bit;*/
// Pin direction
/*
bit LCD_RS_Direction at TRISC1_bit;
bit LCD_EN_Direction at TRISC5_bit;
bit LCD_D7_Direction at TRISD3_bit;
bit LCD_D6_Direction at TRISD2_bit;
bit LCD_D5_Direction at TRISD1_bit;
bit LCD_D4_Direction at TRISD0_bit;
*/
////////////////////////////////////////////////
/*
bit Osvetli at RC2_bit; // osvetlitev displeya
bit Btn1 at RE1_bit;    // Prikljucki tipk
bit Btn2 at RE2_bit;
bit Btn3 at RE0_bit;
bit Test_led at RB3_bit;
*/

#define Osvetli LATC2
#define TestLed LATB3

void Initialize_Ports()
{
  TRISA = 0b11111111; // Smer pinou
  TRISB = 0b11100111; // rb3 in rb4 output
  TRISC = 0b10000001;
  TRISD = 0b00000000;
  TRISE = 0b11111111;
  ANSELB = 0x00; // Nastavitev analognih oz digitalnih IO
  ANSELD = 0x00;
  ANSELC = 0x00;
  ANSELE = 0x00;
  ANSELA = 0x00;
  //C1ON_bit = 0; // Izklopi komparatorje
  //C2ON_bit = 0;

  OSCCON = 0b01100010; // Nastavi frekv oscilatorja

  TestLed = 0;
  Osvetli = 1;
}



void main(void)
{
    MakeAllPinsInputs();                                                        //clears all pins (defines them as input)
    Initialize_Ports();
    
    LCD_Init();
    __delay_ms(100);
    LCD_Clear();
    __delay_ms(100);
    LCD_Set_Cursor(2,2);
    __delay_ms(100);
    LCD_Write_String("tralala");
    __delay_ms(100);
    
    Osvetli = 1;
    while(1){
        TestLed = 1;
        __delay_ms(500);
        TestLed = 0;
        __delay_ms(500);
    }
    return;
}
