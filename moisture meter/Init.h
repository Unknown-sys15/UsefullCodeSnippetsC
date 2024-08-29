////////////DEFINICIJA IZHODOV LCD////////////
// Lcd pinout settings
sbit LCD_RS at RC1_bit;
sbit LCD_EN at RC5_bit;
sbit LCD_D7 at RD3_bit;
sbit LCD_D6 at RD2_bit;
sbit LCD_D5 at RD1_bit;
sbit LCD_D4 at RD0_bit;
// Pin direction
sbit LCD_RS_Direction at TRISC1_bit;
sbit LCD_EN_Direction at TRISC5_bit;
sbit LCD_D7_Direction at TRISD3_bit;
sbit LCD_D6_Direction at TRISD2_bit;
sbit LCD_D5_Direction at TRISD1_bit;
sbit LCD_D4_Direction at TRISD0_bit;
////////////////////////////////////////////////

sbit Osvetli at RC2_bit; // osvetlitev displeya
sbit Btn1 at RE1_bit;    // Prikljucki tipk
sbit Btn2 at RE2_bit;
sbit Btn3 at RE0_bit;
sbit Test_led at RB3_bit;
sbit Izhod at RB0_bit;

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
  C1ON_bit = 0; // Izklopi komparatorje
  C2ON_bit = 0;

  OSCCON = 0b01100110; // Nastavi frekv oscilatorja

  Test_led = 0;
  Osvetli = 1;
  
  ADCON0 = 0x00;  // Disable ADC module
    ADCON1 = 0x0F;  // All ANx pins as digital I/O
    ADCON2 = 0x00;  // Default ADC settings (not needed if ADC is disabled)
    CM1CON0 = 0x00; // Disable Comparator 1
    CM2CON0 = 0x00; // Disable Comparator 2
    
    TXSTA1 = 0x00; // Disable EUSART1 transmitter
    RCSTA1 = 0x00; // Disable EUSART1 receiver
    TXSTA2 = 0x00; // Disable EUSART2 transmitter
    RCSTA2 = 0x00; // Disable EUSART2 receiver
    
     PIE1 = 0x00;  // Disable all peripheral interrupts in PIE1
    PIE2 = 0x00;  // Disable all peripheral interrupts in PIE2
    PIE3 = 0x00;  // Disable all peripheral interrupts in PIE3
    PIE4 = 0x00;  // Disable all peripheral interrupts in PIE4
    PIE5 = 0x00;  // Disable all peripheral interrupts in PIE5

    //CVRCON_bit = 0x00;  // Disable Voltage Reference module
    CCP1CON = 0x00; // Disable CCP1 module
    CCP2CON = 0x00; // Disable CCP2 module
}