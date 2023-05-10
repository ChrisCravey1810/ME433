#include "nu32dip.h" // constants, functions for startup and UART
#include "ws2812b.h"
#include <stdio.h>



void blink(int, int); // blink the LEDs function
void wait(float);
//wsColor wsColor;





int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    ws2812b_setup();  
    
    
    int num_LED = 3;
    wsColor arr[2];
    

    while(1){
        for (int i=0; i <=360; i++){
            for(int j=0; j <= num_LED; j++){
                
                int hue = (60*j + i)%360;
                arr[j] = HSBtoRGB(hue, 1.0, 0.5);
 
            }
            
            ws2812b_setColor(arr, num_LED);
            wait(3);
        }  
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
