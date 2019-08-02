//
//  main.cpp
//  web-starter-project
//
//  Created by Leonid on 2/12/18.
//  Copyright © 2018 oatpp. All rights reserved.
//

#include "./controller/MyController.hpp"
#include "./AppComponent.hpp"

#include "./Utils.hpp"

#include "oatpp/core/utils/ConversionUtils.hpp"

#include <iostream>

void run() {

  /* Register Components in scope of run() method */
  AppComponent components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  /* Create MyController and add all of its endpoints to router */
  auto myController = std::make_shared<MyController>();
  myController->addEndpointsToRouter(router);


  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Process request in oatpp by manually substituting what you have received from your IO engine

  oatpp::String body = "Hello World!!!";

  oatpp::web::protocol::http::Headers headers;
  headers["Content-Length"] = oatpp::utils::conversion::int32ToStr(body->getSize());

  auto response = Utils::processRequest("POST", "/body", router, headers, body);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Take resultant response and send it back

  oatpp::data::stream::ChunkedBuffer downstream;
  response->send(&downstream);

  oatpp::String responseText = downstream.toString();

  OATPP_LOGD("Example", "downstream:\n%s", responseText->getData());
  
}

/**
 *  main
 */
int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();

  run();
  
  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";
  
  oatpp::base::Environment::destroy();
  
  return 0;
}
