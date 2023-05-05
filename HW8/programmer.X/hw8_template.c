#include "nu32dip.h" // constants, functions for startup and UART
#include "i2c_master_noint.h"
#include "mpu6050.h"
#include <stdio.h>
#include <string.h>
#include "font.h"
#include "ssd1306.h"

void blink(int, int); // blink the LEDs function
void wait(float);
void drawChar(unsigned char, unsigned char, unsigned char);






int main(void) {
    NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
    i2c_master_setup();
    ssd1306_setup();
    init_mpu6050();
    
    ssd1306_clear();
    //ssd1306_drawPixel(0b00001010, 0b00001010, 0b00000001);
    ssd1306_update();  //Clear Screen of any previous text
    blink(5,100);  //Blink LED to know no problems with initializing
    
    
    
    unsigned char m[100];
    sprintf(m, "Project start:");
    drawString(m,10,10);
    ssd1306_update();
    
    
    unsigned char d[14];
    float ax, ay, az, gx, gy, gz, t;
    unsigned int t1;
    unsigned int t2;
    
    
    while(1){
        
        ssd1306_clear();
        
        
        
        // read IMU
        burst_read_mpu6050(d);
		// convert data
        //ax = conv_xXL(d);
        //ay = conv_yXL(d);
        az = conv_zXL(d);
        //gx = conv_xG(d);
        //gy = conv_yG(d);
        //gz = conv_zG(d);
        //t = conv_temp(d);
        
        unsigned char s[100];
        sprintf(s,"az: %f\r\n", az);
        
        drawString(s,10,0);
        
        t2 = _CP0_GET_COUNT();
        
        float frame_time = t2 - t1;
        float fps = 24000000/frame_time;
        
        t1 = _CP0_GET_COUNT();
        
        unsigned char timer[15];
        sprintf(timer, "fps: %f\r\n", fps);
        drawString(timer,50,20);
        ssd1306_update();
        
        
    }
	
   
}


void drawChar(unsigned char letter,unsigned char x, unsigned char y ){
    
    
    for (int j=0; j<5; j++){
        unsigned char col = ASCII[letter - 32][j];
        for(int i=0; i<8; i++){
            ssd1306_drawPixel(x+j,y+i, (col>>i) & 0b1);
        }
    }
    
}

void drawString(unsigned char *m, unsigned char x, unsigned char y){
    int k = 0;
    while(m[k]!= 0){
        drawChar(m[k],x + (6*k),y);
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
