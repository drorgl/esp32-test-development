#include "port_arduino.h"
#ifdef ARDUINO
#include <Arduino.h>
#include <arduino-printf.h>
#else
#include <stdio.h>
#endif

#include <stdlib.h>

extern "C"{
	#include <ProductionCode.h>
}
 

void setup()
{
#ifdef ARDUINO
	Serial.begin(115200);
#endif
	printf("test broken %d\r\n", FindFunction_WhichIsBroken(78));
	float c = rand();
	c = c * c * c * c *c;
	printf("displaying float %.6f", c);
}

void loop()
{
	//controller.dump();
}
 