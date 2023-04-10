#include "nu32dip.h" // constants, functions for startup and UART
#include <string.h>
void blink(int, int); // blink the LEDs function

int main(void) {
  char message[100];
  char message2[100];
  char input1;
  int input2;
  
  NU32DIP_Startup(); // cache on, interrupts on, LED/button init, UART init
  while (1) {  
    char speak[1000] = "The LED will blink this many times: ";
    char speak2[1000] = "They will blink for this long: ";
    NU32DIP_ReadUART1(message, 100); // wait here until get message from computer
    strcat(speak, message); //make message
    NU32DIP_WriteUART1(speak); // send message back
    NU32DIP_WriteUART1("\r\n"); // carriage return and newline
    NU32DIP_ReadUART1(message2, 100);// wait here until get message from computer
    strcat(speak2, message2); // make message
    NU32DIP_WriteUART1(speak2); //send message back
    input1 = atoi(message);  //convert input to integers
    input2 = atoi(message2);
    NU32DIP_WriteUART1("\r\n"); // carriage return and newline
    strcpy(speak, "");
    strcpy(speak2, "");
	if (NU32DIP_USER){
		blink(input1, input2); //Use user input to set (#blink, #duration in ms)
	}
  }
}

// blink the LEDs
void blink(int iterations, int time_ms){
	int i;
	unsigned int t;
	for (i=0; i< iterations; i++){
		NU32DIP_GREEN = 0; // on
		NU32DIP_YELLOW = 1; // off
		t = _CP0_GET_COUNT(); // should really check for overflow here
		// the core timer ticks at half the SYSCLK, so 24000000 times per second
		// so each millisecond is 24000 ticks
		// wait half in each delay
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
		
		NU32DIP_GREEN = 1; // off
		NU32DIP_YELLOW = 0; // on
		t = _CP0_GET_COUNT(); // should really check for overflow here
		while(_CP0_GET_COUNT() < t + 12000*time_ms){}
	}
}
		
