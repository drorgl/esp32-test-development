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



#include <runner.h>

#define CPPUTEST_USE_LONG_LONG 1 //mandatory for cpputest to work with esp32
#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestPlugin.h"
#include "CppUTest/TestRegistry.h"
#include "CppUTestExt/IEEE754ExceptionsPlugin.h"
#include "CppUTestExt/MockSupportPlugin.h"

MAIN(){
    const char * argv_[] = {
        ""
        "",
        "-v",
        "-c",
        "-o",
        "eclipse"
        //"teamcity"//"eclipse"//"junit"
    };
    return CommandLineTestRunner::RunAllTests(5, argv_);
}

#include <calculator.h>

Calculator calc;

TEST_GROUP(Calculator){ };


TEST(Calculator, Addition){
    CHECK(32== calc.add(25, 7));
}

TEST(Calculator, Subtraction){
    CHECK(20 == calc.sub(23, 3));
}

TEST(Calculator, Multiplication){
    CHECK(50 ==  calc.mul(25, 2));
}

TEST(Calculator, Division){
    CHECK(32 == calc.div(96, 3));
}

