#include "Eeprom.h"

typedef enum
{
   state_idle,
   state_Temperature,
   state_Hunmidity,
   state_TempHistereza,
   state_HumHistereza

} SystemStates;
SystemStates Menu_state = state_idle;

unsigned int menuCounter = 0;
// short zelena_temp = 27;
// short zelena_vlaznost = 50;

//////////////////////////////////////////////////////////////////////
int Debounce_count = 0;
unsigned int Get_Button_State(void)
{
   unsigned int result = 0;
   static unsigned int button_1_state = 0; // must be static
   static unsigned int button_2_state = 0;
   static unsigned int button_3_state = 0;

   if (~Btn1)
   {
      if (Debounce_count >= 2 && ~Btn1)
      {
         button_1_state = 1;
         Debounce_count = 0;
      }
   }

   else if (~Btn2)
   {
      if (Debounce_count >= 2 && ~Btn2)
      {
         button_2_state = 1;
         Debounce_count = 0;
      }
   }

   else if (~Btn3)
   {
      if (Debounce_count >= 2 && ~Btn3)
      {
         button_3_state = 1;
         Debounce_count = 0;
      }
   }

   else
   {
      Debounce_count = 0;
      button_1_state = 0;
      button_2_state = 0;
      button_3_state = 0;
   }

   Debounce_count++;
   result |= button_1_state | button_2_state << 1 | button_3_state << 2;

   return result;
}
//-------------------------------------------------------------------------
unsigned int Get_Button_Press(void)
{
   unsigned int result = 0;
   unsigned int state = 0;
   static unsigned int previous_state = 0;

   state = Get_Button_State();
   result = ~state & previous_state;
   previous_state = state;
   return result;
}
//-------------------------------------------------------------------------
// Handle menu transitions (btn3)
// int tmp = 0;
// char tmp_str[6];
unsigned char btn3Counter = 0;
unsigned int HandlePressTick = 0;
void HandlePress()
{
   if ((timerValue - HandlePressTick) >= 781) // every 100ms
   {                                          // run on every tick
      HandlePressTick = timerValue;

      if (~Btn3) // Get_Button_Press() & 0x04)
      {          // check btn3 ->    RE0_bit     0x04
         menuCounter = 0;
         btn3Counter++;
         if (btn3Counter < 5)
            return;

         btn3Counter = 0;
         if (Menu_state == state_idle)
         {
            Menu_state = state_Temperature;
         }
         else if (Menu_state == state_Temperature)
         {
            Menu_state = state_Hunmidity;
         }
         else if (Menu_state == state_Hunmidity)
         {
            Menu_state = state_TempHistereza;
         }
         else if (Menu_state == state_TempHistereza)
         {
            Menu_state = state_HumHistereza;
         }
         else if (Menu_state == state_HumHistereza)
         {
            Menu_state = state_Temperature;
         }
      }
   }
}
static unsigned int ExitTick = 0;
void ExitMenu()
{
   if ((timerValue - ExitTick) >= 781) // run every 100ms
   {                                   // run on every tick
      ExitTick = timerValue;
      menuCounter++;
      if (menuCounter > 50) // exit after 5s
      {                     // 5s no input was detected
         Menu_state = state_idle;
         menuCounter = 0;
         // write to eeprom
         eprom_write(0xA0, 0x00, zelena_temp);
         eprom_write(0xA0, 0x04, zelena_vlaznost);
         eprom_write(0xA0, 0x08, temp_histereza);
         eprom_write(0xA0, 0x0C, hum_histereza);
      }
   }
   //}
}

unsigned int MenuTick = 0;
void Menu() // klici vsakih 100ms in ce je pritisnjen gumb ++
{
   if ((timerValue - MenuTick) >= 781) // 100ms
   {
      MenuTick = timerValue;
      ////tipke menu
      if (Menu_state == state_Temperature)
      {
         if (~Btn1) // Get_Button_Press() & 0x01)
         {
            zelena_temp--;
            menuCounter = 0;
         }
         delay_ms(1); //(Get_Button_Press() & 0x02)
         if (~Btn2)
         {
            zelena_temp++;
            menuCounter = 0;
         }
         sprintf(temp_str, "zelena temp %-3d", zelena_temp);
         sprintf(hum_str, "+      -        ");
      }
      else if (Menu_state == state_Hunmidity)
      {
         if (~Btn1) // Get_Button_Press() & 0x01)
         {
            zelena_vlaznost--;
            menuCounter = 0;
         }
         delay_ms(1); //(Get_Button_Press() & 0x02)
         if (~Btn2)
         {
            zelena_vlaznost++;
            menuCounter = 0;
         }
         sprintf(temp_str, "Humidity    %-4d", zelena_vlaznost);
         sprintf(hum_str, "+      -        ");
      }
      ///////////////////////////////////////////////////////////////////////////////////////////
      else if (Menu_state == state_TempHistereza)
      {
         if (~Btn1) // Get_Button_Press() & 0x01)
         {
            temp_histereza--;
            menuCounter = 0;
         }
         delay_ms(1); //(Get_Button_Press() & 0x02)
         if (~Btn2)
         {
            temp_histereza++;
            menuCounter = 0;
         }
         sprintf(temp_str, "Temp hyst   %-4d", temp_histereza);
         sprintf(hum_str, "+      -        ");
      }
      else if (Menu_state == state_HumHistereza)
      {
         if (~Btn1) // Get_Button_Press() & 0x01)
         {
            hum_histereza--;
            menuCounter = 0;
         }
         delay_ms(1); //(Get_Button_Press() & 0x02)
         if (~Btn2)
         {
            hum_histereza++;
            menuCounter = 0;
         }
         sprintf(temp_str, "Hum hyst    %-4d", hum_histereza);
         sprintf(hum_str, "+      -        ");
      }
   }
}

/*static unsigned int OldMenu = 0;
   if ((Multitask - OldMenu) >= 10)
   { // blink every 100ms
      OldMenu = Multitask;

      if (Menu_state == state_Temperature)
      {
         if (~Btn1)
         {
            zelena_temp--;
            menuCounter = 0;
         }
         delay_ms(1);
         if (~Btn2)
         {
            zelena_temp++;
            menuCounter = 0;
         }
         sprintf(temp_str, "zelena temp %d", zelena_temp);
         sprintf(hum_str, "+      -        ");
         Lcd_Out(1, 1, temp_str); // Print the temperature on the first row             temp_str
         Lcd_Out(2, 1, hum_str);  // Print the humidity on the second row
      }
      if (Menu_state == state_Hunmidity)
      {
         sprintf(temp_str, "Humidity   ");
         sprintf(hum_str, "+      -       7");
      }
   }*/