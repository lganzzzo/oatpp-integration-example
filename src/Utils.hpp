//
// Created by Leonid  on 2019-08-02.
//

#ifndef MY_PROJECT_UTILS_HPP
#define MY_PROJECT_UTILS_HPP

#include "oatpp/web/protocol/http/outgoing/Response.hpp"
#include "oatpp/web/protocol/http/incoming/Request.hpp"
#include "oatpp/web/server/HttpRouter.hpp"

class Utils {
public:
  typedef oatpp::web::protocol::http::outgoing::Response OutgoingResponse;
  typedef oatpp::web::protocol::http::incoming::Request IncomingRequest;
public:

  static std::shared_ptr<OutgoingResponse> processRequest(const oatpp::String& method,
                                                          const oatpp::String& path,
                                                          const std::shared_ptr<oatpp::web::server::HttpRouter>& router,
                                                          const oatpp::web::protocol::http::Headers& headers,
                                                          const std::shared_ptr<oatpp::data::stream::InputStream>& bodyStream);

  static std::shared_ptr<OutgoingResponse> processRequest(const oatpp::String& method,
                                                          const oatpp::String& path,
                                                          const std::shared_ptr<oatpp::web::server::HttpRouter>& router,
                                                          const oatpp::web::protocol::http::Headers& headers,
                                                          const oatpp::String& body);


};


#endif //MY_PROJECT_UTILS_HPP
