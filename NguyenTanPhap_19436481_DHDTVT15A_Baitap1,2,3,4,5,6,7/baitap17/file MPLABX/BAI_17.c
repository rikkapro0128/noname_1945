#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator: High-speed crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF 

#include <xc.h>
#define _XTAL_FREQ 4000000
void counter1_int(void)
{
    TMR1=0;
    TMR1H=0;
    TMR1L=0;
    TMR1IF=0;
    TMR1CS=1;T1OSCEN=0;
    GIE=PEIE=TMR1IE=0;
    T1CKPS1=0;
    T1CKPS0=0;
    T1SYNC=0;
    TMR1ON=1;
}
void main(void)
{
    ANSEL=ANSELH=0;
    TRISC=0;
    TRISD=0;
    PORTD=0X00;
    PORTC=0X00;
    TRISC0=1;
    const unsigned char h[10]={0xC0,0xF9,
    0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
    counter1_int();
    while(1)
    {
        for(TMR1=0;TMR1<=85;)  
        {
            PORTC=h[TMR1/10];
            PORTD=h[TMR1%10];
        }
    }
}