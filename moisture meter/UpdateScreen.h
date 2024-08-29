unsigned int UpdateTick = 0;
void Update()
{
  if ((timerValue - UpdateTick) >= 1562 * 2) // 200ms
  {                                          // run on every tick
    UpdateTick = timerValue;
    // Lcd_Cmd(_LCD_CLEAR);

    Lcd_Out(2, 1, hum_str); // Print the humidity on the second rowLcd_Out(1, 1, temp_str); // Print the temperature on the first row             temp_str
    delay_ms(50);
    Lcd_Out(1, 1, temp_str); // Print the temperature on the first row             temp_str
    delay_ms(500);           // short delay to Update lcd
  }

  // Lcd_Out(2, 16, "I");
}