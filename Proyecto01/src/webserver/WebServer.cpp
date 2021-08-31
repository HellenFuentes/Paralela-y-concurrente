// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <unistd.h>
#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>


#include "NetworkAddress.hpp"
#include "Socket.hpp"
#include "WebServer.hpp"
WebServer *WebServer::web = NULL;
const char *const usage =
    "Usage: webserv [port] [max_connections]\n"
    "\n"
    "  port             Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
    "  max_connections  Maximum number of allowed client connections\n";

// TODO(you) Make WebServer a singleton class. See the Log class
WebServer::WebServer() {
  this->numberThreads = sysconf(_SC_NPROCESSORS_ONLN);
}

WebServer::~WebServer() {
  for (int index = 0; index < this->connectionQueueCapacity; ++index) {
    delete consumers[index];
  }
  delete this->goldbachWebApp;
}

WebServer *WebServer::getInstance() {
  if (web == NULL) {
    web = new WebServer();
  } return (web);
}

int WebServer::start(int argc, char *argv[]) {
  try {
    if (this->analyzeArguments(argc, argv)) {
      // TODO(you) Handle signal 2 (SIGINT) and 15 (SIGTERM), see man signal
      // Signal handler should call WebServer::stopListening(), send stop
      // conditions and wait for all secondary threads that it created
      this->goldbachWebApp = new GoldbachWebApp();
      this->listenForConnections(this->port);
      const NetworkAddress &address = this->getNetworkAddress();
      std::cout << "web server listening on " << address.getIP()
                << " port " << address.getPort() << "...\n";
      // Create each consumer
      this->consumers.resize(this->numberThreads);
      for (int index = 0; index < this->numberThreads; ++index) {
        this->consumers[index] =
         new HttpConnectionHandler(&queue, Socket(), this);
        assert(this->consumers[index]);
        this->consumers[index]->startThread();
      }
      this->acceptAllConnections();
    }
  }
  catch (const std::runtime_error &error) {
    std::cerr << "error: " << error.what() << std::endl;
  }

  return EXIT_SUCCESS;
}

bool WebServer::analyzeArguments(int argc, char *argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 2) {
    this->port = argv[1];
  }
  if (argc >= 3) {
    this->numberThreads = strtoul(argv[2], NULL, 10);
  }
  return true;
}

bool WebServer::handleHttpRequest(HttpRequest &httpRequest,
                                  HttpResponse &httpResponse) {
  // Print IP and port from client
  const NetworkAddress &address = httpRequest.getNetworkAddress();
  std::cout << "connection established with client " << address.getIP()
            << " port " << address.getPort() << std::endl;

  // Print HTTP request
  std::cout << "  " << httpRequest.getMethod()
            << ' ' << httpRequest.getURI()
            << ' ' << httpRequest.getHttpVersion() << std::endl;

  return this->route(httpRequest, httpResponse);
}

bool WebServer::route(HttpRequest &httpRequest, HttpResponse &httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    return this->serveHomepage(httpRequest, httpResponse);
  }
  // GoldbachWebApp receives and process request
  if (goldbachWebApp->processRequest(httpRequest, httpResponse)) {
    return true;
  }
  return this->serveNotFound(httpRequest, httpResponse);
}

// TODO(you): Fix code redundancy in the following methods

bool WebServer::serveHomepage(
  HttpRequest &httpRequest, HttpResponse &httpResponse) {
  (void)httpRequest;

  // TODO(you) Move form to your view class, e.g GoldbachWebApp

  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Goldbach sums";
  httpResponse.body() << "<!DOCTYPE html>\n"
              << "<html lang=\"en\">\n"
              << "  <meta charset=\"ascii\"/>\n"
              << "  <title>" << title << "</title>\n"
              << "  <style>body {font-family: monospace}</style>\n"
              << "  <h1>" << title << "</h1>\n"
              << "  <form method=\"get\" action=\"/goldbach\">\n"
              << "    <label for=\"number\">Number</label>\n"
              << "    <input type=\"number\" name=\"number\" required/>\n"
              << "    <button type=\"submit\">Calculate</button>\n"
              << "  </form>\n"
              << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

bool WebServer::serveNotFound(
  HttpRequest &httpRequest, HttpResponse &httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setStatusCode(404);
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");

  // Build the body of the response
  std::string title = "Not found";
  httpResponse.body() << "<!DOCTYPE html>\n"
        << "<html lang=\"en\">\n"
        << "  <meta charset=\"ascii\"/>\n"
        << "  <title>" << title << "</title>\n"
        << "  <style>body {font-family: monospace} h1 {color: red}</style>\n"
        << "  <h1>" << title << "</h1>\n"
        << "  <p>The requested resouce was not found in this server.</p>\n"
        << "  <hr><p><a href=\"/\">Homepage</a></p>\n"
        << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}
void WebServer::handleClientConnection(Socket &client) {
  queue.push(client);
}
void WebServer::end() {
  this->stopListening();
  for (size_t i=0 ; i < consumers.size() ; i++) {
    queue.push(Socket());
  }
  for (size_t i=0 ; i< consumers.size() ; i++) {
    consumers[i]->waitToFinish();
  }
}
