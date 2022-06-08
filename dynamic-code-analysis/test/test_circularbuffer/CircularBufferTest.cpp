/*
 * Copyright (c) 2007, Michael Feathers, James Grenning and Bas Vodde
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE EARLIER MENTIONED AUTHORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <copyright holder> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <CircularBuffer.h>
// #include "MockPrinter.h"
#include <unity.h>

static CircularBuffer *buffer;

void setUp(void)
{
    buffer = new CircularBuffer();
}
void tearDown(void)
{
    delete buffer;
}

void fillTheQueue(int seed, int howMany)
{
    for (int i = 0; i < howMany; i++)
    buffer->Put(seed + i);
}
void removeFromQueue(int howMany)
{
    for (int i = 0; i < howMany; i++)
    buffer->Get();
}

void CircularBuffer_EmptyAfterCreation()
{
    TEST_ASSERT_TRUE(buffer->IsEmpty());
}

void CircularBuffer_NotEmpty()
{
    buffer->Put(10046);
    TEST_ASSERT_TRUE(!buffer->IsEmpty());
}

void CircularBuffer_NotEmptyThenEmpty()
{
    buffer->Put(4567);
    TEST_ASSERT_TRUE(!buffer->IsEmpty());
    buffer->Get();
    TEST_ASSERT_TRUE(buffer->IsEmpty());
}

void CircularBuffer_GetPutOneValue()
{
    buffer->Put(4567);
    TEST_ASSERT_EQUAL_INT(4567, buffer->Get());
}

void CircularBuffer_GetPutAFew()
{
    buffer->Put(1);
    buffer->Put(2);
    buffer->Put(3);
    TEST_ASSERT_EQUAL_INT(1, buffer->Get());
    TEST_ASSERT_EQUAL_INT(2, buffer->Get());
    TEST_ASSERT_EQUAL_INT(3, buffer->Get());
}

void CircularBuffer_Capacity()
{
    CircularBuffer b(2);
    TEST_ASSERT_EQUAL_INT(2, b.Capacity());
}

void CircularBuffer_IsFull()
{
    fillTheQueue(0, buffer->Capacity());
    TEST_ASSERT_TRUE(buffer->IsFull());
}

void CircularBuffer_EmptyToFullToEmpty()
{
    fillTheQueue(100, buffer->Capacity());

    TEST_ASSERT_TRUE(buffer->IsFull());

    removeFromQueue(buffer->Capacity());

    TEST_ASSERT_TRUE(buffer->IsEmpty());
}

void CircularBuffer_WrapAround()
{
    fillTheQueue(100, buffer->Capacity());

    TEST_ASSERT_TRUE(buffer->IsFull());
    TEST_ASSERT_EQUAL_INT(100, buffer->Get());
    TEST_ASSERT_TRUE(!buffer->IsFull());
    buffer->Put(1000);
    TEST_ASSERT_TRUE(buffer->IsFull());

    removeFromQueue(buffer->Capacity() - 1);

    TEST_ASSERT_EQUAL_INT(1000, buffer->Get());
    TEST_ASSERT_TRUE(buffer->IsEmpty());
}

void CircularBuffer_PutToFull()
{
    int capacity = buffer->Capacity();
    fillTheQueue(900, capacity);
    buffer->Put(9999);

    for (int i = 0; i < buffer->Capacity() - 1; i++)
        TEST_ASSERT_EQUAL_INT(i+900+1, buffer->Get());

    TEST_ASSERT_EQUAL_INT(9999, buffer->Get());
    TEST_ASSERT_TRUE(buffer->IsEmpty());
}

//Sometime people ask what tests the tests.
//Do you know the answer


void CircularBuffer_GetFromEmpty()
{
    TEST_ASSERT_EQUAL_INT(-1, buffer->Get());
    TEST_ASSERT_TRUE(buffer->IsEmpty());
}

/*
 * the next tests demonstrate using a mock object for
 * capturing output
 *
 */

void CircularBuffer_PrintEmpty()
{
    
    string value = buffer->Print();
    TEST_ASSERT_EQUAL_STRING("Circular buffer content:\n<>\n",
            value.c_str());
}

void CircularBuffer_PrintAfterOnePut()
{
    buffer->Put(1);
    string value = buffer->Print();
    TEST_ASSERT_EQUAL_STRING("Circular buffer content:\n<1>\n",
            value.c_str());
}

void CircularBuffer_PrintNotYetWrappedOrFull()
{
    buffer->Put(1);
    buffer->Put(2);
    buffer->Put(3);
    string value = buffer->Print();
    TEST_ASSERT_EQUAL_STRING("Circular buffer content:\n<1, 2, 3>\n",
            value.c_str());
}

void CircularBuffer_PrintNotYetWrappedAndIsFull()
{
    

    fillTheQueue(200, buffer->Capacity());

    string value = buffer->Print();
    const char* expected = "Circular buffer content:\n"
        "<200, 201, 202, 203, 204>\n";

    TEST_ASSERT_EQUAL_STRING(expected, value.c_str());
}

void CircularBuffer_PrintWrappedAndIsFullOldestToNewest()
{
    

    fillTheQueue(200, buffer->Capacity());
    buffer->Get();
    buffer->Put(999);

    string value = buffer->Print();
    const char* expected = "Circular buffer content:\n"
        "<201, 202, 203, 204, 999>\n";

    TEST_ASSERT_EQUAL_STRING(expected, value.c_str());
}

void CircularBuffer_PrintWrappedAndFullOverwriteOldest()
{
    

    fillTheQueue(200, buffer->Capacity());
    buffer->Put(9999);

    string value = buffer->Print();
    const char* expected = "Circular buffer content:\n"
        "<201, 202, 203, 204, 9999>\n";

    TEST_ASSERT_EQUAL_STRING(expected, value.c_str());
}

void CircularBuffer_PrintBoundary()
{
    

    fillTheQueue(200, buffer->Capacity());
    removeFromQueue(buffer->Capacity() - 2);
    buffer->Put(888);
    fillTheQueue(300, buffer->Capacity() - 1);

    string value = buffer->Print();
    const char* expected = "Circular buffer content:\n"
        "<888, 300, 301, 302, 303>\n";

    TEST_ASSERT_EQUAL_STRING(expected, value.c_str());
}

void CircularBuffer_FillEmptyThenPrint()
{
    

    fillTheQueue(200, buffer->Capacity());
    removeFromQueue(buffer->Capacity());
    string value = buffer->Print();
    const char* expected = "Circular buffer content:\n"
        "<>\n";

    TEST_ASSERT_EQUAL_STRING(expected, value.c_str());
}



int main(void)
{
  UnityBegin(__FILE__ );
  RUN_TEST(CircularBuffer_EmptyAfterCreation);
  RUN_TEST(CircularBuffer_NotEmpty);
  RUN_TEST(CircularBuffer_NotEmptyThenEmpty);
  RUN_TEST(CircularBuffer_GetPutOneValue);
  RUN_TEST(CircularBuffer_GetPutAFew);
  RUN_TEST(CircularBuffer_Capacity);
  RUN_TEST(CircularBuffer_IsFull);
  RUN_TEST(CircularBuffer_EmptyToFullToEmpty);
  RUN_TEST(CircularBuffer_WrapAround);
  RUN_TEST(CircularBuffer_PutToFull);
  RUN_TEST(CircularBuffer_GetFromEmpty);
  RUN_TEST(CircularBuffer_PrintEmpty);
  RUN_TEST(CircularBuffer_PrintAfterOnePut);
  RUN_TEST(CircularBuffer_PrintNotYetWrappedOrFull);
  RUN_TEST(CircularBuffer_PrintNotYetWrappedAndIsFull);
  RUN_TEST(CircularBuffer_PrintWrappedAndIsFullOldestToNewest);
  RUN_TEST(CircularBuffer_PrintWrappedAndFullOverwriteOldest);
  RUN_TEST(CircularBuffer_PrintBoundary);
  RUN_TEST(CircularBuffer_FillEmptyThenPrint);


  return (UnityEnd());
}


#ifdef ARDUINO
void setup(){
    main();
}
void loop(){

}
#endif