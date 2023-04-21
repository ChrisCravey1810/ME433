#include "nu32dip.h" // constants, functions for startup and UART
#include <string.h>
#include <math.h>
//#include "spi.c"
#include "spi.h"


void wait(float waitMs);
//void initSPI();
//unsigned char spi_io(unsigned char o);

int main(void) {
  int size = 100; //How many points to generate
  char message[100];
  double wave[size];
  
  
  for (int i = 0; i < size; i++) {
      wave[i] = ((3.3/2) * sin(((2 * M_PI)*(double)i/size)) + (3.3/2));
  }   //plotter.py creates a window with y-axid from 0 - 3.3. Offset sin wave
      //to have an amplitude of half of 3.3, and shifted up by half of 3.3
  

  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  initSPI();
  LATAbits.LATA0 = 0;
  unsigned short outval = 200;//0 - 1023
  spi_io(0x7000 | (outval << 2));
  LATAbits.LATA0 = 1;
  while (0) {
	if (!NU32DIP_USER){  //True if USER button is pressed
        for (int i = 0; i < size; i++) {
            sprintf(message, "%f\n", wave[i]);
            NU32DIP_WriteUART1(message);
            
            
            wait(1000.0f/size); //wait for the use to stop pressing the button
        }
	}
  }
}
    	
//Wait function, received help from Andre Vallieres
void wait(float waitMs) {
    unsigned long t = _CP0_GET_COUNT(); 
    // the core timer ticks at half the SYSCLK, so 24000000 times per second
    // so each millisecond is 24000 ticks
    while(_CP0_GET_COUNT() < t + 24000*waitMs){}
}

		
