#include "nu32dip.h" // constants, functions for startup and UART
#include <string.h>
#include <math.h>
#include "spi.h"
#include "i2c_master_noint.h"

void wait(float waitMs);



unsigned char addrW = 64;
unsigned char addrR = 65;



void write (unsigned char regi, unsigned char mess){
    
    i2c_master_start(); //send start bit
    i2c_master_send(addrW);  //send chip address
    i2c_master_send(regi);   //send which register you wish to access
    i2c_master_send(mess);  //send desired message
    i2c_master_stop();     //stop communication
    wait(500);
      
}

unsigned char read (unsigned char regi){
 
    i2c_master_start(); //send start bit
    i2c_master_send(addrW);  //send chip address
    i2c_master_send(regi);   //send which register you wish to access
    i2c_master_restart();
    i2c_master_send(addrR); //send chip address
    unsigned char r = i2c_master_recv();  //read desired message
    i2c_master_ack(1);     //send acknowledgement
    i2c_master_stop();     //stop communication
    
    return (r);
}



int main(void) {
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init

          
  i2c_master_setup();  //start i2c communication, set baud      
  
  //Make all pins output except GP0
  i2c_master_start();
  i2c_master_send(addrW);
  i2c_master_send(0);
  i2c_master_send(1);
  i2c_master_stop();
  
  
  while (1) {
    //blink yellow LED
    NU32DIP_YELLOW = 0;
    wait(50);
    
    unsigned char a;
    a = read(9);  //Read if button is pressed
    
    //if button is pressed
    if ((a & 1) == 0){
        
        write(10, 128); //Turn light on
        
    }
    else{
        write(10, 0);  //Turn light off
    }
    
    
    //blink yellow LED
    NU32DIP_YELLOW = 1;
    wait(50);
        }
	}
  


//Wait function, received help from Andre Vallieres
void wait(float waitMs) {
    unsigned long t = _CP0_GET_COUNT(); 
    // the core timer ticks at half the SYSCLK, so 24000000 times per second
    // so each millisecond is 24000 ticks
    while(_CP0_GET_COUNT() < t + 24000*waitMs){}
}

		
