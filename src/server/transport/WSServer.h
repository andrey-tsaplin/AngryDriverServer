//
// Created by andrew on 2/19/17.
//

#pragma once

#include "libwebsockets.h"
#include "WSClient.h"
#include "../game/Engine.h"

class WSServer
{
    struct lws_context *context_ = NULL;
    Engine *engine_;

public:
    WSServer(int port, Engine *engine);

    void Service();

    int gameProtocolCallback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);

    int httpProtocolCallback(lws *wsi, lws_callback_reasons reason, void *user, void *in, size_t len);
};

struct session_data_game
{
    WSClient *ws_client;
};

static int gameProtocolCallbackWrapper(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in,
                                       size_t len)
{
    return static_cast<WSServer *> (lws_context_user(lws_get_context(wsi)))->gameProtocolCallback(wsi, reason, user, in,
                                                                                                  len);
}

static int httpProtocolCallbackWrapper(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in,
                                       size_t len)
{
    return static_cast<WSServer *> (lws_context_user(lws_get_context(wsi)))->httpProtocolCallback(wsi, reason, user, in,
                                                                                                  len);
}

const struct lws_extension exts[] = {
        {
                "permessage-deflate",
                      lws_extension_callback_pm_deflate,
                            "permessage-deflate"
        },
        {
                "deflate-frame",
                      lws_extension_callback_pm_deflate,
                            "deflate_frame"
        },
        {       NULL, NULL, NULL /* terminator */ }
};

static struct lws_protocols protocols[] = {
        {
                "http-only",                /* name */
                      httpProtocolCallbackWrapper,/* callback */
                            0,                          /* per_session_data_size */
                               0,                          /* max frame size / rx buffer */
        },
        {
                "ad-game-protocol",                   /* name */
                      gameProtocolCallbackWrapper,          /* callback */
                            sizeof(struct session_data_game),      /* per_session_data_size */
                8000,                                 /* max frame size / rx buffer */
        },
        {       NULL, NULL, 0, 0} /* terminator */
};
