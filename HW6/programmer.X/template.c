#include "nu32dip.h" // constants, functions for startup and UART
#include <string.h>
#include <math.h>
//#include "spi.c"
#include "spi.h"

double PI = 3.1415926;
void wait(float waitMs);


unsigned short sinwav(int t){
  unsigned short outval = 0;//0 - 1032
  unsigned char a_or_b;
  outval = 7 << 12;
  a_or_b = 0;
  outval = outval| (a_or_b<<15);
  
  unsigned short val;
  val = (sin(t*((M_PI * 2)/1023))+1) * 511;
  
  outval = outval| (val<<2);
  
  return outval;
}


unsigned short triwav(int t){
  unsigned short outval = 0;//0 - 1032
  unsigned char a_or_b;
  outval = 7 << 12;
  a_or_b = 1;
  outval = outval| (a_or_b<<15);
  
  unsigned short val;
  val = abs((t % 2046) - 1023);
  
  outval = outval| (val<<2);
  return outval;
}





int main(void) {
  int size = 2047; //How many points to generate
  short swave[size];
  short twave[size];
  
  
  for (int i = 0; i < size; i++) {
      swave[i] = sinwav(i);
      twave[i] = triwav(i);
  }   //plotter.py creates a window with y-axid from 0 - 3.3. Offset sin wave
      //to have an amplitude of half of 3.3, and shifted up by half of 3.3
  

  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  initSPI();
  
  
  //LATAbits.LATA0 = 0;        
  //spi_io(sinwav(-1)>>8);
  //spi_io(sinwav(-1));
  //LATAbits.LATA0 = 1;
  
  
  while (1) {
	if (!NU32DIP_USER){  //True if USER button is pressed
        for (int i = 0; i < size; i++) {
            LATAbits.LATA0 = 0;        
            spi_io(swave[i]>>8);
            spi_io(swave[i]);
            LATAbits.LATA0 = 1;
            
            LATAbits.LATA0 = 0;
            spi_io(twave[i]>>8);
            spi_io(twave[i]);
            LATAbits.LATA0 = 1;
            
            //wait(1000.0f/size); //wait for the use to stop pressing the button
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

		
