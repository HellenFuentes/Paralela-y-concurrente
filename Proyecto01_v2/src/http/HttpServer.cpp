// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>

#include "HttpServer.hpp"

HttpServer::HttpServer() {
  this->numbersOfSocketConsumers = sysconf(_SC_NPROCESSORS_ONLN);
}

HttpServer::~HttpServer() {
  for (int index = 0; index < this->connectionQueueCapacity; ++index) {
    delete socketConsumers[index];
  }
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::handleClientConnection(Socket &client) {
  queue.push(client);
}
void HttpServer::initializeSoketsConsumers(int number){
  if(number!= 0){
    numbersOfSocketConsumers = number;
  }
  this->socketConsumers.resize(numbersOfSocketConsumers);
  for (int index = 0; index < numbersOfSocketConsumers; ++index) {
    this->socketConsumers[index] =
      new HttpConnectionHandler(&queue, Socket(), this);
    assert(this->socketConsumers[index]);
    this->socketConsumers[index]->startThread();
  }
}
void HttpServer::finishSocketConsumers(){
  for (size_t i=0 ; i < socketConsumers.size() ; i++) {
    this->queue.push(Socket());
  }
  for (size_t i=0 ; i< socketConsumers.size() ; i++) {
    socketConsumers[i]->waitToFinish();
  }
}
