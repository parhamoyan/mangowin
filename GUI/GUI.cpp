// GUI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Window.h"
#include <chrono>
#include <thread>

int main()
{
    Window window = Window();
    window.set_window_title("GUI test");
    window.resize(1000, 1000);
    window.show();

    bool running = true;
    while (running) {
        if (!window.ProcessMessages())
            running = false;

        window.paint();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}