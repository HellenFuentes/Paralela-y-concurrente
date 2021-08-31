/**
* @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
* @author Jean Carlo Quesada Abarca <jean.quesadaabarca@ucr.ac.cr>
* @author Andrés Zamora Víquez <andres.zamoraviquez@ucr.ac.cr>
* @author Hellen Fuentes Artavia <hellen.fuentesartavia@ucr.ac.cr>
*/
#ifndef SRC_WEBSERVER_GOLDBACHWORK_HPP_
#define SRC_WEBSERVER_GOLDBACHWORK_HPP_
#include <string>
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "GoldbachNumbersList.hpp"

/**
* @brief GoldbachWork Class
*/
class GoldbachWork {
 public:
    std::string input;
    HttpRequest& request;
    HttpResponse& response;

    /**
    * @brief class constructor
    * @param input string of the included data
    * @param request HttpRequest
    * @param response HttpResponse
    */
    GoldbachWork(std::string& input, HttpRequest& request,
    HttpResponse& response);

    // destructor
    ~GoldbachWork();

    /**
    * @brief returns the list of numbers
    * @return goldbachNumbersList
    */
    GoldbachNumbersList* getGoldbachNumbersList();

 private:
    // private variables
    GoldbachNumbersList* goldbachNumbersList;
};

#endif  // SRC_WEBSERVER_GOLDBACHWORK_HPP_
