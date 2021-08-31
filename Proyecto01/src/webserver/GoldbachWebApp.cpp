/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#include "GoldbachWebApp.hpp"
#include <regex>
#include <iostream>

GoldbachWebApp::GoldbachWebApp() {
  goldbachCalculator = new GoldbachCalculator();
}

GoldbachWebApp::~GoldbachWebApp() {
  delete this->goldbachCalculator;
}

std::string GoldbachWebApp::parseURI(const std::string &uri) {
  std::string URIParseado = "";
  const std::string tipoEntrada = "/goldbach?number=";

  // Posicion de los numeros
  size_t indice = uri.find(tipoEntrada);

  // Para la forma /goldbach?number=n1,n2,n3...
  if (indice != std::string::npos) {
    // Ubicarse en la posicion
    indice += tipoEntrada.size();

    URIParseado = uri.substr(indice);
  } else {  // Para la forma /n1,n2,n3...
    std::smatch matches;

    // Crea una expresion regular para "/"
    std::regex ruta_regex("[^/]*$");

    if (std::regex_search(uri, matches, ruta_regex)) {
      URIParseado = matches[0];
    }
  }

  return URIParseado;
}

bool GoldbachWebApp::processRequest(
  HttpRequest &request, HttpResponse &response) {
  bool solicitudValida = false;

  // Parse URI
  std::string uri = request.getURI();
  std::string parsedUri = this->parseURI(uri);

  if (parsedUri.length() > 0) {
    // Verify that there is at least one number in parsedUri
    std::smatch matches;
    std::regex numeros("[0-9]");
    if (std::regex_search(parsedUri, matches, numeros)) {
      solicitudValida = true;
    }
  }

  // If it's a valid request
  if (solicitudValida) {
    GoldbachWork* goldbachWork = new GoldbachWork(parsedUri,
    request, response);
    // Devuelve una lista con Numeros de Goldbach (clase para trabajar Goldbach)
    GoldbachNumbersList* list = goldbachWork->getGoldbachNumbersList();
    for (int64_t i = 0; i < list->getListSize(); ++i) {
      // Calcule los numeros de goldbach
      // Guardeme las respuestas en la lista
      goldbachCalculator->startGoldbach(list->getGoldbachNumber(i));
    }
    // Inyecte los resultados a html.
    injectHTML(goldbachWork);
  }

  return solicitudValida;
}

void GoldbachWebApp::injectHTML(GoldbachWork* goldbachWork) {
  GoldbachNumbersList* list = goldbachWork->getGoldbachNumbersList();

    // Headers HTTP
    goldbachWork->response.setHeader("Server", "AttoServer v1.0");
    goldbachWork->response.setHeader("Content-type",
     "text/html; charset=ascii");

    // Response body
    std::string titulo = "Goldbach sums for " + goldbachWork->input;
    goldbachWork->response.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << titulo << "</title>\n"
    << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
    << "  <h1>" << titulo << "</h1>\n"
    << "  <ul>\n";

    // Sends results
    goldbachWork->response.body() << *list;

    // Remaining body response
    goldbachWork->response.body() << "  </ul>\n"
    << "  <hr><p><a href=\"/\">Back</a></p>\n"
    << "</html>\n";
    goldbachWork->response.send();
}
