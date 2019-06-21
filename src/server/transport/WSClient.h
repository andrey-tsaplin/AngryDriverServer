//
// Created by andrew on 3/1/17.
//

#pragma once

#include "libwebsockets.h"
#include "Client.h"

class WSClient : public Client
{
protected:
    struct lws *ws_interface_;

public:
    WSClient(struct lws *ws_interface)
    {
        ws_interface_ = ws_interface;
    }

    void OnKeyboardStateUpdated() override
    {

    }
};
