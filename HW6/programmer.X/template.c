#include "nu32dip.h" // constants, functions for startup and UART
#include <string.h>
#include <math.h>
#include "spi.h"

void wait(float waitMs);







int main(void) {
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init

          
          
  //initSPI();
  
  
  
  while (1) {
    //blink yellow LED
    NU32DIP_YELLOW = 0;
    wait(500);
    NU32DIP_YELLOW = 1;
    wait(500);
      
    if (!NU32DIP_USER){  //True if USER button is pressed
        NU32DIP_YELLOW = 1;
        wait(1000);
        NU32DIP_YELLOW = 0;
        
        }
	}
  }

    	

void GP7ON (){
    //send start bit
    
    
    //send address
    
    
    
}
//Wait function, received help from Andre Vallieres
void wait(float waitMs) {
    unsigned long t = _CP0_GET_COUNT(); 
    // the core timer ticks at half the SYSCLK, so 24000000 times per second
    // so each millisecond is 24000 ticks
    while(_CP0_GET_COUNT() < t + 24000*waitMs){}
}

		
