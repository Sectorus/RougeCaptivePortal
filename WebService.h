#ifndef WebService_h
#define WebService_h

#include <FS.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>

class WebService {
  public:
    WebService(int webPort, int httpPort);
    DNSServer dnsServer;
    ESP8266WebServer webServer;
    ESP8266WebServer httpServer;
  private:
};

#endif
