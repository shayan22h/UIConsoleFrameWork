// DummyApplication.cpp
#include "DummyApp.h"
#include "../UIConsole/UI.h"

#include <iostream>

DummyApp::DummyApp(UI& uiRef) : ui(uiRef) {
    ui.UserMessage_CallbackToApplication = [this](const std::string& msg) {
        onUserMessage(msg);
    };
}

void DummyApp::onUserMessage(const std::string& msg) {
    std::cout << "[DummyApp] Received from UI: " << msg 
    << std::endl;
    // Optionally process, then send something back
}

void DummyApp::sendToUI() {
    ui.UI_SendMessageToUIFramework("Hello from DummyApp!");
}