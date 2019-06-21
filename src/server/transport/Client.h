//
// Created by andrew on 2/21/17.
//

#pragma once

#include <vector>
#include <string>

typedef std::vector<std::string> MessageQueue;

/* Player's client */
class Client {
    const static int KEYBOARD_FLAG_UP_PRESSED = 1;
    const static int KEYBOARD_FLAG_DOWN_PRESSED = 2;
    const static int KEYBOARD_FLAG_LEFT_PRESSED = 4;
    const static int KEYBOARD_FLAG_RIGHT_PRESSED = 8;

protected:
    int keyboardState_ = 0;

    /* message buffer to send to from server */
    MessageQueue serverMessageQueue_;

public:
    Client() {
    }

    bool IsUpPressed() {
        return (keyboardState_ & KEYBOARD_FLAG_UP_PRESSED) != 0;
    }

    bool IsDownPressed() {
        return (keyboardState_ & KEYBOARD_FLAG_DOWN_PRESSED) != 0;
    }

    bool IsLeftPressed() {
        return (keyboardState_ & KEYBOARD_FLAG_LEFT_PRESSED) != 0;
    }

    bool IsRightPressed() {
        return (keyboardState_ & KEYBOARD_FLAG_RIGHT_PRESSED) != 0;
    }

    MessageQueue& GetServerMessageQueue() {
        return serverMessageQueue_;
    }

    void AddToMessageQueue(std::string& message) {
        serverMessageQueue_.push_back(message);
    }

    void ProcessClientMessage(std::string message) {
        keyboardState_ = std::stoi(message);
    }

    virtual void OnKeyboardStateUpdated() = 0;

};
