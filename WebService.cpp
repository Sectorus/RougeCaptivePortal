#include "WebService.h"

WebService::WebService(int webPort, int httpPort) {
 webServer = ESP8266WebServer(webServer);
 httpServer = ESP8266WebServer(httpPort);
}
