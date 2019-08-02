//
// Created by Leonid  on 2019-08-02.
//

#include "Utils.hpp"

#include "oatpp/web/protocol/http/incoming/SimpleBodyDecoder.hpp"
#include "oatpp/core/data/stream/BufferInputStream.hpp"

std::shared_ptr<Utils::OutgoingResponse> Utils::processRequest(const oatpp::String& method,
                                                               const oatpp::String& path,
                                                               const std::shared_ptr<oatpp::web::server::HttpRouter>& router,
                                                               const oatpp::web::protocol::http::Headers& headers,
                                                               const std::shared_ptr<oatpp::data::stream::InputStream>& bodyStream)
{
  /* No need to create BodyDecoder for each code. Body decoder can be created once */
  /* You may just put it in config. Do not make it static. */
  auto bodyDecoder = std::make_shared<oatpp::web::protocol::http::incoming::SimpleBodyDecoder>();

  auto route = router->getRoute(method, path);

  if(route) {
    oatpp::web::protocol::http::RequestStartingLine startingLine{method, path, "HTTP/1.1"};
    auto request = IncomingRequest::createShared(startingLine, route.matchMap, headers, bodyStream, bodyDecoder);
    return route.getEndpoint()->handle(request);
  } else {
    return nullptr; // No Endpoint found for given path.
  }

}

std::shared_ptr<Utils::OutgoingResponse> Utils::processRequest(const oatpp::String& method,
                                                               const oatpp::String& path,
                                                               const std::shared_ptr<oatpp::web::server::HttpRouter>& router,
                                                               const oatpp::web::protocol::http::Headers& headers,
                                                               const oatpp::String& body)
{
  auto stream = std::make_shared<oatpp::data::stream::BufferInputStream>(body.getPtr(), body->getData(), body->getSize());
  return processRequest(method, path, router, headers, stream);
}