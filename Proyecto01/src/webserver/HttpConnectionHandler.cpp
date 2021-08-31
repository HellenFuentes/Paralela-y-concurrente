/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#include "HttpConnectionHandler.hpp"
#include "WebServer.hpp"

HttpConnectionHandler::HttpConnectionHandler(Queue<Socket>* queue
, Socket empty, WebServer* webServer) : Consumer(queue, empty) {
  this->webServer = webServer;
}

void HttpConnectionHandler::consume(const Socket& socket) {
  while (true) {
    Socket client = socket;
    // Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(client);
    // If the request is not valid or an error happened
    if (!httpRequest.parse()) {
    // Non-valid requests are normal after a previous valid request. Do not
    // close the connection yet, because the valid request may take time to
    // be processed. Just stop waiting for more requests
    break;
    }
    // A complete HTTP client request was received. Create an object for the
    // server responds to that client's request
    HttpResponse httpResponse(client);
    // Give subclass a chance to respond the HTTP request
    const bool handled =
    this->webServer->handleHttpRequest(httpRequest, httpResponse);
    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || httpRequest.getHttpVersion() == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      client.close();
      break;
    }
  }
}

int HttpConnectionHandler::run() {
  consumeForever();
  return EXIT_SUCCESS;
}
