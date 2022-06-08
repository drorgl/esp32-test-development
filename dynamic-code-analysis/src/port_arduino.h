#pragma once


#ifndef ARDUINO
void setup();
void loop();


int main(){
    setup();

#ifndef NATIVE
    while(1)
#endif
    {
        loop();
    }
}
#endif