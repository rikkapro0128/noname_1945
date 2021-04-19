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

#define _XTAL_FREQ 400000
#include <xc.h>
void main (void)
{
    unsigned char CH,DV;
    const char a[10]={0xC0,0xF9,0x24,0xB0,0x99,0x92,0x83,0xF8,0x80,0x98};
    ANSEL = 0;
    ANSELH = 0;
    TRISC = 0;
    TRISD = 0;
    TRISA4 = 1;
    TMR0 = 0;
    TMR0IF = 0;
    T0CS = 1;
    GIE=PEIE=TMR0IE=1;
    T0SE = 0;
    PSA = 1;
    PS2 = 0;
    PS1 = 0;
    PS0 = 0;
    while(1)
    {   
        if(TMR0==91)
    {
        TMR0=0;
    }
        CH=TMR0/10;
        DV=TMR0%10;
        PORTD=a[DV]; 
        PORTC=a[CH]; 
    }
}