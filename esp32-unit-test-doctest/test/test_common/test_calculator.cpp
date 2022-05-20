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


// #define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_IMPLEMENT
#define DOCTEST_THREAD_LOCAL
#include <doctest/doctest.h>
#include <runner.h>

MAIN(){
    const int argc_ = 3;
    const char *argv_[] = {
        "exe",
        "-d",
        "-s"};
    return doctest::Context(argc_, argv_).run();
}

#include <calculator.h>

Calculator calc;


TEST_CASE("calculator addition"){
    CHECK(32== calc.add(25, 7));
}

TEST_CASE("calculator subtraction"){
    CHECK(20 == calc.sub(23, 3));
}

TEST_CASE("calculator multiplication"){
    CHECK(50 ==  calc.mul(25, 2));
}

TEST_CASE("calculator division"){
    CHECK(32 == calc.div(96, 3));
}

