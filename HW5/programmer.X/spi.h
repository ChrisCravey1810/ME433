#ifndef SPI__H__
#define SPI__H__

#include<xc.h>           // processor SFR definitions
#include<sys/attribs.h>  // __ISR macro
#include <stdio.h>

void initSPI();
unsigned short spi_io(unsigned short o);

#endif // SPI__H__