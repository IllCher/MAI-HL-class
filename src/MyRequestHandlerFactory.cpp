#include "MyRequestHandlerFactory.h"
#include "MyRequestHandler.h"

HTTPRequestHandler* MyRequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request) {
    if (request.getURI() == "/api/user") {
        return new MyRequestHandler<User>(myApi);
    } else if (request.getURI() == "/api/wall") {
        return new MyRequestHandler<Wall>(myApi);
    } else if (request.getURI() == "/api/chat") {
        return new MyRequestHandler<ChatMessage>(myApi);
    } else {
        return nullptr;
    }
}
