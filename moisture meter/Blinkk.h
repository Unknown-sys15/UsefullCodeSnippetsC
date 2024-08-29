unsigned int BlinkTick = 0;
void Blink()
{
      // TikHih = TMR0L;

      if ((timerValue - BlinkTick) < 6000)
            return; // blink every 1s
      BlinkTick = timerValue;
      if (Test_led)
      {
            Test_led = 0;
      }
      else
      {
            Test_led = 1;
      }
}