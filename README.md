# oatpp-integration-example

Possible way of integration oatpp with other I/O engines.

Simple example how to use oatpp REST framework by "manually" 
substituting `Request` object.

```cpp
  
  // Process request in oatpp by 
  // manually substituting what you have received from your IO engine

  oatpp::String body = "Hello World!!!";

  oatpp::web::protocol::http::Headers headers;
  headers["Content-Length"] = oatpp::utils::conversion::int32ToStr(body->getSize());

  auto response = Utils::processRequest("POST", "/body", router, headers, body);

 
  // Take resultant response and send it back

  oatpp::data::stream::ChunkedBuffer downstream;
  response->send(&downstream);

  oatpp::String responseText = downstream.toString();

  OATPP_LOGD("Example", "downstream:\n%s", responseText->getData());
```
