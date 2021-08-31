// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef SRC_WEBSERVER_WEBSERVER_HPP_
#define SRC_WEBSERVER_WEBSERVER_HPP_
#include <vector>
#include "HttpServer.hpp"
#include "HttpConnectionHandler.hpp"
#include "Queue.hpp"
#include "GoldbachWebApp.hpp"

#define DEFAULT_PORT "8080"

class WebServer : public HttpServer {
  DISABLE_COPY(WebServer);

 private:
  GoldbachWebApp* goldbachWebApp;
  int numberThreads;
  /// TCP port where this web server will listen for connections
  const char* port = DEFAULT_PORT;
  /// Constructor
  WebServer();
  /// Destructor
  ~WebServer();
  static WebServer* web;
  std::vector<HttpConnectionHandler*> consumers;

 public:
  /// Start the simulation
  int start(int argc, char* argv[]);
  static WebServer* getInstance();
  /// Start the simulation
    /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;
  void end();

 protected:
  /// Analyze the command line arguments
  /// @return true if program can continue execution, false otherwise
  bool analyzeArguments(int argc, char* argv[]);
  /// This method is called each time a client connection request is accepted.
  void handleClientConnection(Socket& client) override;
  /// Route, that provide an answer according to the URI value
  /// For example, home page is handled different than a number
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Sends a page for a non found resouce in this server
  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);
};

#endif  // SRC_WEBSERVER_WEBSERVER_HPP_
