// tips for future: dont access pins form different functions -> lcd breaks
int temp_histereza = 2;
int hum_histereza = 2;
unsigned int timerValue = 0;
int zelena_temp = 0;        // 16 bit
int zelena_vlaznost = 0;    // 16 bit
char temp_str[16] = "init"; // Buffer to hold temperature string
char hum_str[16];           // = "init";  // Buffer to hold humidity string
#include "Init.h"
#include "Timer0.h"
#include "hih7121.h"
#include "Menu.h"
#include "UpdateScreen.h"
#include "Blinkk.h"
#include "OnOffRegulator.h"

//             TO DO
//   temp vlaga nastimaj meni  --> NAJ SE SHRANJUJE V EEPROM
//   vrzi vn izhod s histerezo (on/off regulator) -> poglej ce ma sist mrtvi cas -> torej ko grejes je grele sevedno topu ko ugasnes grelec
//
//

// unsigned int button_state;
unsigned int BlinkTicktest = 0;
void main()
{
    Initialize_Ports();
    Delay_ms(100);
    I2C_Init();    // Initialize I2C module
    Delay_ms(100); // Wait for sensor startup (if necessary)
    Lcd_Init();
    Delay_ms(100);

    Lcd_Cmd(_LCD_CLEAR);      // Clear display
    Lcd_Cmd(_LCD_CURSOR_OFF); // Cursor off
    // Lcd_Cmd(_LCD_CLEAR); // Clear display
    // Delay_ms(100);
    Lcd_Out(1, 1, "MERILEC VLAGE   ");
    // Delay_ms(100);
    Lcd_Out(2, 1, "                ");
    Delay_ms(100);

    Lcd_Cmd(_LCD_CLEAR); // Clear display
    InitTimer0();
    Delay_ms(100);
    zelena_temp = eprom_read(0xA0, 0x00);
    zelena_vlaznost = eprom_read(0xA0, 0x04);
    temp_histereza = eprom_read(0xA0, 0x08);
    hum_histereza = eprom_read(0xA0, 0x0C);

    while (1)
    {
        timerValue = (TMR0H << 8) | TMR0L;
        // Menu()    ;
        HihCall();     // read hih sensor
        HandlePress(); // constant call
        while (Menu_state != state_idle)
        {
            timerValue = (TMR0H << 8) | TMR0L;
            // Blink();       // indikator za menu
            Menu();        // check for change in variables              //
            HandlePress(); // constant call                               //
            ExitMenu();
            // Update();

            // BlinkTicktest = timerValue;
            // sprintf(hum_str, "Timer0: %05u", timerValue);
            Lcd_Out(2, 1, hum_str); // Print the humidity on the second row
            // sprintf(temp_str, "blink: %05u", BlinkTick);                                                  //
            Lcd_Out(1, 1, temp_str); // Print the humidity on the second row
            delay_ms(50);            // delay to allow for update
        }
        // Test_led=0;
        OnOffRegulator();
        OnOffRegulator1();
        // delay_ms(100);
        Update();
    }
}