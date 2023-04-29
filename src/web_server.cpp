#include "web_server.h"

#include "index.h"
#include "motor_control.h"

AsyncWebServer server(80);

void setupWebServer() {
  server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/html", MAIN_page);
  });

  server.on("/up", HTTP_GET, [](AsyncWebServerRequest* request) {
    move(Direction::Up);
    request->send(200, "text/plain", "ok");
  });

  server.on("/down", HTTP_GET, [](AsyncWebServerRequest* request) {
    move(Direction::Down);
    request->send(200, "text/plain", "ok");
  });

  server.on("/brake", HTTP_GET, [](AsyncWebServerRequest* request) {
    stopMotor();
    request->send(200, "text/plain", "ok");
  });

  server.on("/reset_turns", HTTP_GET, [](AsyncWebServerRequest* request) {
    turns = 0;
    request->send(200, "text/plain", "ok");
  });

  server.on("/save_turns", HTTP_GET, [](AsyncWebServerRequest* request) {
    saved_turns = turns;
    request->send(200, "text/plain", "ok");
  });

  server.on("/get_turns", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/plain", String(turns));
  });

  server.on("/get_saved_turns", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send(200, "text/plain", String(saved_turns));
  });

  server.onNotFound([](AsyncWebServerRequest* request) {
    request->send(404, "text/plain", "Not found");
  });

  server.begin();
}