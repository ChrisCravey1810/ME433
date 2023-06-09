#include "nu32dip.h" // constants, functions for startup and UART
#include "ws2812b.h"




void blink(int, int); // blink the LEDs function
void wait(float);
//wsColor wsColor;





int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    //ws2812b_setup();  
    
    RPB15Rbits.RPB15R = 0b0101;
    
    while(1){
        

        T2CONbits.TCKPS = 4;     // Timer2 prescaler N=4 (1:4)
        PR2 = 59999;              // period = (PR2+1) * N * (1/48000000) = 6 kHz
        TMR2 = 0;                // initial TMR2 count is 0
        OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
        OC1CONbits.OCTSEL = 0;   // Use timer2
        OC1RS = 3250;             // duty cycle = OC1RS/(PR2+1) = 25%
        OC1R = 3250;              // initialize before turning OC1 on; afterward it is read-only
        T2CONbits.ON = 1;        // turn on Timer2
        OC1CONbits.ON = 1;       // turn on OC1
        
        wait(4000);
        
        T2CONbits.TCKPS = 4;     // Timer2 prescaler N=4 (1:4)
        PR2 = 60000;              // period = (PR2+1) * N * (1/48000000) = 6 kHz
        TMR2 = 0;                // initial TMR2 count is 0
        OC1CONbits.OCM = 0b110;  // PWM mode without fault pin; other OC1CON bits are defaults
        OC1CONbits.OCTSEL = 0;   // Use timer2
        OC1RS = 6250;             // duty cycle = OC1RS/(PR2+1) = 25%
        OC1R = 6250;              // initialize before turning OC1 on; afterward it is read-only
        T2CONbits.ON = 1;        // turn on Timer2
        OC1CONbits.ON = 1;       // turn on OC1
        
        wait(4000);
    }
    
    }
  



// blink the LEDs
void blink(int iterations, int time_ms) {
    int i;
    unsigned int t;
    for (i = 0; i < iterations; i++) {
        NU32DIP_GREEN = 0; // on
        NU32DIP_YELLOW = 1; // off
        t = _CP0_GET_COUNT(); // should really check for overflow here
        // the core timer ticks at half the SYSCLK, so 24000000 times per second
        // so each millisecond is 24000 ticks
        // wait half in each delay
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }

        NU32DIP_GREEN = 1; // off
        NU32DIP_YELLOW = 0; // on
        t = _CP0_GET_COUNT(); // should really check for overflow here
        while (_CP0_GET_COUNT() < t + 12000 * time_ms) {
        }
    }
}


void wait(float waitMs) {
    unsigned long t = _CP0_GET_COUNT(); 
    // the core timer ticks at half the SYSCLK, so 24000000 times per second
    // so each millisecond is 24000 ticks
    while(_CP0_GET_COUNT() < t + 24000*waitMs){}
}

