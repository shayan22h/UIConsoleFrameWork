#include <iostream>
#include <thread>
#include <string>
#include "UIConsole/UI.h"
#include "DummyApp/DummyApp.h"
using namespace std;
int main() {

    UI UIHandler;
    DummyApp DummyAppObj(UIHandler);

    UIHandler.UI_Start();
    


    std::cout << "UIConsoleFramework \n" << std::endl;
    return 0;
}