/*
 Copyright (c) 2014-present PlatformIO <contact@platformio.org>

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
**/
#include <stdio.h>
#include <calculator.h>
#include <runner.h>

Calculator calc;


void process(){
    printf("Program started!\r\n");

    printf("Addition: %d\r\n",calc.add(25, 17));
    printf("Subtraction: %d\r\n", calc.sub(10, 3));
    printf("Multiplication: %d\r\n",calc.mul(3, 3));
    printf("Division: %d\r\n", calc.div(100, 3));
}

MAIN(){ 
    process(); 
}
