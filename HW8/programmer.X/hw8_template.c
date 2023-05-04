#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
//#include "mpu6050.h"
#include <stdio.h>
#include <string.h>
#include "font.h"
#include "ssd1306.h"

void blink(int, int); // blink the LEDs function
void wait(float);

int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    i2c_master_setup();
    ssd1306_setup();
    
    ssd1306_drawPixel(0b00001010, 0b00001010, 0b00000001);
    
    ssd1306_update();
    wait(1000);
    ssd1306_clear();
    ssd1306_update();
    blink(10,100);
    //1 character is 5/8
    
    unsigned char m[100];
    sprintf(m, "hello");
    drawChar(m[0],x,y);
	
   
}


void drawChar(unsigned char letter,unsigned char x, unsigned char y ){
    for (j=0; j<5; j++){
        unsigned char col = ASCII[letter -0x20, j];
        for(i=0; i<8; i++){
            drawPixel(x+j,y+i, (col>>i) & 0b1);
        }
    }
    
}

void drawString(unsigned char *m, unsigned char x, unsigned char y){
    int k = 0;
    while(m[k]!=0){
        drawChar(m[k],x + (5*k),y);
        k++;
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
