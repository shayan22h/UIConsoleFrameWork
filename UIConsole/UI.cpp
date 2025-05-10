#include "UI.h"
#include <iostream>
#include <chrono>

UI::UI() : running(true)
{

}

UI::~UI()
{
    UI_Stop();
}

void UI::UI_Stop() 
{

    running = false;
    msgCondVar.notify_all();
    if (consoleThread.joinable()) consoleThread.join();
    if (appThread.joinable()) appThread.join();
    
}

void UI::UI_Start(void)
{
    consoleThread = std::thread(&UI::UI_Console_Task, this);
    appThread = std::thread(&UI::UI_App_Task, this);
}

void UI::UI_SendMessageToUIFramework(const std::string& msg)
{
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        incomingMessages.push(msg);
    } // lock_guard is destroyed here
    msgCondVar.notify_one();
}

/*
*   @brief: Independent task polls every 100ms for a msg from user
            and then send the msg to AppCenter Comp
*/
void UI::UI_App_Task(void)
{
    std::cout << "[UI] App Task Started\n";
    while(running)
    {
        unique_lock<mutex> lock(queueMutex);
        msgCondVar.wait(lock, [&]() { return !incomingMessages.empty() || !running; });

        while (!incomingMessages.empty()) {
            std::string msg = incomingMessages.front();
            incomingMessages.pop();
            lock.unlock();

            std::cout << "[UI] Message from DummyApp: " << msg << std::endl;

            lock.lock();
        }
    }
}

void UI::UI_Console_Task(void)
{
    std::cout << "[UI] Console Task Started\n";
    while(running)
    {

        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::string stringInput;
        std::getline(std::cin, stringInput);
        if (stringInput == "exit")
        {
            cout << "[UI] Exit command received.\n";
            running = false;
            msgCondVar.notify_all();
            break;
        }

        if(!stringInput.empty() && UserMessage_CallbackToApplication)
        {
            // Send Message to Dummy Application by means of callback
            cout<< "meessage is " << stringInput << endl;
            UserMessage_CallbackToApplication(stringInput);
        }
    }
}