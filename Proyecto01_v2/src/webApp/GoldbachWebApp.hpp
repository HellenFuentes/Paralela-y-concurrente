/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#ifndef SRC_WEBSERVER_GOLDBACHWEBAPP_HPP_
#define SRC_WEBSERVER_GOLDBACHWEBAPP_HPP_
#include <string>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "GoldbachWork.hpp"
#include "GoldbachCalculator.hpp"
#include "GoldbachNumbersList.hpp"
#include "GoldbachNumber.hpp"
#include "Mathematicians.hpp"
#include "NumbersContainer.hpp"
#include <vector>

class GoldbachWebApp {
 private:
   Queue<NumbersContainer> workForThreads;
   std::vector<Mathematicians*> mathematicians;
   int numberOfCores;

 public:  // constructor
    GoldbachWebApp();
    // destructor
    ~GoldbachWebApp();

    /**
    * @brief inyecta las sumas de Goldbach calculadas, en el html del body del HttpResponse
    */
    void injectHTML(GoldbachWork* goldbachWork);

    /**
    * @brief removes invalid characters that are included in the URI
    * @details parses the URI so that it can receive a string made up of numbers to be processed
    * @param uri as the string of input values of the URI
    * @return URIParseado, string already parsed without invalid values
    */
    std::string parseURI(const std::string& uri);

    /**
    * @brief receives the request and response to process an http query and checks if the data entered is valid
    * @param request HTTP request HttpRequest
    * @param response HTTP response HttpResponce
    * @return requestValid = true if the request is valid, false if not
    */
    bool processRequest(HttpRequest& request, HttpResponse& response);


    void initializeMathematicians();
};

#endif  // SRC_WEBSERVER_GOLDBACHWEBAPP_HPP_
