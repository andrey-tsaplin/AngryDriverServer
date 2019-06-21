//
// Created by andrew on 2/19/17.
//

#include <cstdint>
#include <stdexcept>
#include "WSServer.h"
#include "Client.h"
#include "../utils/Logger.h"

WSServer::WSServer(int port, Engine *engine)
{
    engine_ = engine;

    struct lws_context_creation_info info;
    memset(&info, 0, sizeof info);
    info.port = port;
    info.iface = NULL;
    info.protocols = protocols;
    info.ssl_cert_filepath = NULL;
    info.ssl_private_key_filepath = NULL;
    info.extensions = exts;
    info.timeout_secs = 5;
    info.max_http_header_pool = 16;
    info.options = LWS_SERVER_OPTION_VALIDATE_UTF8;
    info.gid = -1;
    info.uid = -1;
    info.user = this;

    context_ = lws_create_context(&info);
    if (context_== NULL)
    {
        Logger::Error("libwebsocket init failed");
        throw std::runtime_error("libwebsocket init failed");
    } else
    {
        Logger::Warning("[WSServer] context created.");
    }
}


int WSServer::httpProtocolCallback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
    return 0;
}

int WSServer::gameProtocolCallback(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{

    struct session_data_game *session_data =
            (struct session_data_game *) user;

    WSClient *client;

    switch (reason)
    {

        case LWS_CALLBACK_ESTABLISHED:
            session_data->ws_client = new WSClient(wsi);
            engine_->AddClient(session_data->ws_client);
            break;

        case LWS_CALLBACK_SERVER_WRITEABLE:
        {
            client = session_data->ws_client;
            MessageQueue &queue = client->GetServerMessageQueue();

            MessageQueue::const_iterator iter = queue.begin();
            while (iter != queue.end())
            {
                std::string data = (*iter);
                size_t size = data.size();
                int written = lws_write(wsi, (unsigned char *) data.c_str(), size, LWS_WRITE_TEXT);

                if (written < size)
                {
                    lwsl_err("ERROR %d writing to di socket\n", written);
                    return -1;
                }

                iter = queue.erase(iter);
            }
        }
            break;

        case LWS_CALLBACK_RECEIVE:
            client = session_data->ws_client;
            client->ProcessClientMessage(std::string((char *) in, len));
            break;

        case LWS_CALLBACK_FILTER_PROTOCOL_CONNECTION:
            /* you could return non-zero here and kill the connection */
            break;

        case LWS_CALLBACK_WS_PEER_INITIATED_CLOSE:
            lwsl_notice("LWS_CALLBACK_WS_PEER_INITIATED_CLOSE: len %lu\n", (unsigned long) len);
            break;

        default:
            break;
    }

    return 0;
}

void WSServer::Service()
{
    lws_service(context_, 0);
    lws_callback_on_writable_all_protocol(context_, &protocols[1]);
}
