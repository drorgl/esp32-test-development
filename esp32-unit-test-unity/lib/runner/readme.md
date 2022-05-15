# Runner
keeps a unified interface for running main

usage:
```C++
#include <runner.h>
MAIN(){
    //code
}
```

# Arduino
Arduino entry point is  void setup() as the entry point, if it ever exists, it will loop forever

# esp-idf
esp-idf entry point is void app_main(), which will call into our main handler

# Native
gcc entry point is int main(argc,argv), which will call into our main handler