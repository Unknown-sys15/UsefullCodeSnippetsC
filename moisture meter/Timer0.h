// Timer0
// Prescaler 1:1; TMR0 Preload = 45536; Actual Interrupt Time : 10 ms
//int Multitask = 0;
// Place/Copy this part in declaration section
void InitTimer0()
{
    T0CON = 0x87; // Configure Timer0: 16-bit mode, prescaler 1:1, Timer0 OFF
    TMR0H = 0;    // Clear Timer0 high byte
    TMR0L = 0;    // Clear Timer0 low byte
    TMR0IF_bit = 0;   // Clear Timer0 overflow interrupt flag
    TMR0IE_bit = 0;   // Disable Timer0 interrupt
    TMR0ON_bit = 1;   // Turn on Timer0
}

//1 tick is not 128us
//8s for overflow