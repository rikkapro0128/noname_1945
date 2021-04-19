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

void delay100us(unsigned int n)
{
    while(n--)
    {   
        TMR1H = 255;
        TMR1L =231;
        TMR1IF =0;
        TMR1CS = 0;
        GIE=PEIE =TMR1IE = 0; 
        T1CKPS1 =1;
        T1CKPS0 = 0;
        TMR1ON = 1;
        T1SYNC= 1 ;
        while(TMR1IF==0);
    }
}
void main(void)
{   
    ANSEL=ANSELH=0;
    TRISE = 0;
    while(1)
    {   
        RE1=!RE1;
        if(RE1==1)
        { 
            delay100us(250);
        }        
        if(RE1==0)
        { 
            delay100us(750);
        }
    }
}