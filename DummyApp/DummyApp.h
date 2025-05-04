// DummyApp.h
#pragma once
#include <string>

class UI;

class DummyApp {
public:
    DummyApp(UI& uiRef);

    void onUserMessage(const std::string& msg); // Called from UI
    void sendToUI(); // Simulates app sending message to UI

private:
    UI& ui;
};