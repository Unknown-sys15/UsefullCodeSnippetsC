#include <xc.h> // include processor files - each processor file is guarded.  

#define _XTAL_FREQ 8000000
#define LCD_EN_Delay 100                                                        //was initially 500 reduced it to 10 worked for a while until it broke
#define LCD_DATA_PORT_D TRISB
#define LCD_RS_D TRISC1
#define LCD_EN_D TRISC5
#define RS LATC1
#define EN LATC5
#define D4 LATD0
#define D5 LATD1
#define D6 LATD2
#define D7 LATD3

//==============================================
//-----[ Prototypes For All LCD Functions ]-----
 
void LCD_Init(); // Initialize The LCD For 4-Bit Interface
void LCD_Clear(); // Clear The LCD Display
void LCD_SL(); // Shift The Entire Display To The Left
void LCD_SR(); // Shift The Entire Display To The Right
 
void LCD_CMD(unsigned char); // Send Command To LCD
void LCD_DATA(unsigned char); // Send 4-Bit Data To LCD
void LCD_Set_Cursor(unsigned char, unsigned char); // Set Cursor Position
void LCD_Write_Char(char); // Write Character To LCD At Current Position
void LCD_Write_String(char*); // Write A String To LCD

