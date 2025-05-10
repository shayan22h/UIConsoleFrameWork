#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include "UIConsole/UI.h"
#include "DummyApp/DummyApp.h"
using namespace std;

int main() {

    UI UIHandler;
    DummyApp DummyAppObj(UIHandler);

    UIHandler.UI_Start();
    

    while(UIHandler.running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    
    std::cout << "[System] Shutting down UI..." << std::endl;
    UIHandler.UI_Stop();

    return 0;
}