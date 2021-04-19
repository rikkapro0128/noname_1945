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
const int led[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
void init()
{
    ANSEL=ANSELH=0;
    TRISD=0x07;
    TRISC=TRISD=0x00;
    PORTD=PORTC=0xff;
    nRBPU=0;
    WPUB=0x07;
    RBIF=0;
    RBIE=1;
    IOCB=0x07;
    GIE=1;
}
void delay_timer_100us(void)
{
    TMR0=231;
    TMR0IF=0;
    T0CS=0;
    GIE=PEIE=TMR0IE=0;
    PSA = 0; PS2 = 0; PS1 = 0; PS0 = 1;
    while(TMR0IF=0);
}
void delay_ms(int delay)
{
    delay=delay*10;
    while(delay--)
    {
        delay_timer_100us();
    }
}
void __interrupt() isr(void)
{
    PORTB;
    delay_ms(10);
    if(RB0==0)
    {
        delay_ms(10);
        int time=5;
        int check=1;
        while(1)
        {
            if(!RB2)
                {
                    PORTC=PORTD=0xff;
                    return;
                }
            if(check==1)
            {
                PORTC=PORTD=led[8];
                check=0;
                delay_ms(400);
            }
            else
            {
                PORTC=PORTD=0xff;
                check=1;
                delay_ms(400);
            }
             if(time==0)
            {
                PORTC=PORTD=0xff;
                break;
            }
            time--;
        }    
    }
    else if(!RB1)
    {
        delay_ms(10);
        for(int i=88;i>=0;i--)
        {
             if(!RB2)
                {
                    PORTC=PORTD=0xff;
                    return;
                }
                
                
            
            PORTC=led[i/10];
            PORTD=led[i%10];
            delay_ms(400);
        }
        PORTC=PORTD=0xff;
    }
     RBIF=0;
}
void main(void) 
{
    init();
    PORTB;
    while(1)
    return;
}