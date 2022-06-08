/*
 ============================================================================
 Description : Main section of Test Suite, Software Analysis - FY2013 (Ansi-style)
 ============================================================================
 */
#include "unity.h"
#include <bufferLibrary.h>

void setUp(){

}

void tearDown(){
	
}

int main(void)
{
	UnityBegin(__FILE__);
	RUN_TEST(dynamic_buffer_overrun_018);
	RUN_TEST(memory_leak_001);
	return (UnityEnd());
}

#ifdef ARDUINO
void setup()
{
	main();
}
void loop()
{
}
#endif