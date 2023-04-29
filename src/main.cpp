#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "motor_control.h"
#include "web_server.h"

const char* ssid PROGMEM = "";
const char* password PROGMEM = "";

void notFound(AsyncWebServerRequest* request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  /* Open serial connection */
  Serial.begin(115200);

  /* Setup motor */
  setupMotor();

  /* Wifi setup */
  WiFi.begin(ssid, password);

  /* Wait for connection */
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.printf("\nConnected to %s\n", ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  /* Setup web pages */
  setupWebServer();

  Serial.println("HTTP server started");
}

void loop() {}