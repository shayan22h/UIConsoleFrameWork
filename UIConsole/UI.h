#ifndef UI_H
#define UI_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>
#include <thread>
#include <functional>

using namespace std;

class UI{
    public:
        UI();
        ~UI();
        void UI_Start(void);
        void UI_Stop(void);
        void UI_SendMessageToUIFramework(const std::string& msg);
        std::function <void(const std::string&)> UserMessage_CallbackToApplication;

    private:
        void UI_App_Task(void);
        void UI_Console_Task(void);
        std::thread consoleThread;
        std::thread appThread;
        bool running = true;

        std::mutex queueMutex;
        std::condition_variable msgCondVar;
        std::queue<std::string> incomingMessages;

};

#endif // UI_H