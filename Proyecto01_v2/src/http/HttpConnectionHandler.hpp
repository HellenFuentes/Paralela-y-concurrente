/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#ifndef SRC_WEBSERVER_HTTPCONNECTIONHANDLER_HPP_
#define SRC_WEBSERVER_HTTPCONNECTIONHANDLER_HPP_
#include "Consumer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"

class HttpServer;

class HttpConnectionHandler: public Consumer<Socket> {
 private:
  HttpServer* httpServer;

 public:
  // HttpConnectionHandler contructor
  HttpConnectionHandler();

  /**
  * @brief constructor of HttpConnectionHandler
  * @param queue of Work with the data to consume
  * @param empty empty socket (means end of work for the thread)
  * @param httpServer pointer to httpServer class
  */
  HttpConnectionHandler(Queue<Socket>* queue,
  const Socket empty, HttpServer* httpServer);

  // HttpConnectionHandler destructor
  ~HttpConnectionHandler() {
  }

  /**
  * @brief consumer of work given by the client
  * @param socket as the work to be done
  */
  void consume(const Socket& socket) override;

  /**
  * @brief consumes until last socket runs out
  */
  int run() override;
};
#endif  // SRC_WEBSERVER_HTTPCONNECTIONHANDLER_HPP_
