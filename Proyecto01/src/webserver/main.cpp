// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0
// Serial web server's initial code for parallelization

#ifdef WEBSERVER
#include <signal.h>
#include <mutex>
#include <thread>
#include <cstring>
#include "WebServer.hpp"

std::mutex mutexKiller;

void serverKiller(WebServer* web) {
  mutexKiller.lock();
  web->end();  // end the server
  mutexKiller.unlock();
}

void signalKill(int) {
  mutexKiller.unlock();
}

int main(int argc, char* argv[]) {
  mutexKiller.lock();
  WebServer* web = WebServer::getInstance();

  struct sigaction signalReporter;
  memset(&signalReporter, 0, sizeof(signalReporter));

  signalReporter.sa_handler = signalKill;

  sigaction(SIGINT, &signalReporter, NULL);
  std::thread killer(serverKiller, web);

  int status = web->start(argc, argv);
  killer.join();

  return status;
}

#endif  // WEBSERVER
