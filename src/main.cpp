#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "index.h"


#define MOTOR_SLEEP 16
#define MOTOR_ENABLE 12
#define MOTOR_PHASE 13
#define MOTOR_ENC_A 4
#define MOTOR_ENC_B 5

/* SSID and Password of your WiFi router */
const char* ssid = "";
const char* password = "";

AsyncWebServer server(80);

volatile unsigned int turns = 0;
volatile unsigned int saved_turns = 0;
volatile bool direction = false; // false - forward; true - reverse
bool moving = false;

ICACHE_RAM_ATTR void encoder() {
  /* Increase/decrease total encoder count */
  if (direction) {
    turns++;
  } else {
    if (turns > 0)
      turns--;
  }
  /* Stop motor when reached destination */
  if (moving) {
    if (direction) {
      if (turns >= saved_turns) {
        moving = false;
        digitalWrite(MOTOR_ENABLE, LOW);
      }
    } else {
      if (turns == 0) {
        moving = false;
        digitalWrite(MOTOR_ENABLE, LOW);
      }
    }
  }
}

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void moveDown() {
  if (turns < saved_turns) {
    moving = true;
    direction = true;
    digitalWrite(MOTOR_PHASE, LOW);
    digitalWrite(MOTOR_ENABLE, HIGH);
    //analogWrite(MOTOR_ENABLE, 768); // 75% duty cycle
  }
}

void moveUp() {
  if (turns != 0) {
    moving = true;
    direction = false;
    digitalWrite(MOTOR_PHASE, HIGH);
    digitalWrite(MOTOR_ENABLE, HIGH);
    //analogWrite(MOTOR_ENABLE, 768); // 75% duty cycle
  }
}

void setup() {
  /* Open serial connection */
  Serial.begin(115200);

  /* Set modes for pins */
  pinMode(MOTOR_SLEEP, OUTPUT);
  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(MOTOR_PHASE, OUTPUT);
  pinMode(MOTOR_ENC_A, INPUT);
  pinMode(MOTOR_ENC_B, INPUT);

  /* Start motor */
  digitalWrite(MOTOR_SLEEP, HIGH);
  digitalWrite(MOTOR_PHASE, LOW);
  digitalWrite(MOTOR_ENABLE, LOW);


  /* Interupt setup */
  attachInterrupt(digitalPinToInterrupt(MOTOR_ENC_A), encoder, RISING);
  //attachInterrupt(digitalPinToInterrupt(MOTOR_ENC_B), encoder, RISING);

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
 
  
  /* Web pages */
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", MAIN_page);
  });

  server.on("/forward", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if (!moving) {
      direction = false;
      digitalWrite(MOTOR_PHASE, HIGH);
      digitalWrite(MOTOR_ENABLE, HIGH);
      //analogWrite(MOTOR_ENABLE, 768); // 75% duty cycle
    }
    request->send(200, "text/plain", "ok");
  });
  
  server.on("/reverse", HTTP_GET, [] (AsyncWebServerRequest *request) {
    if (!moving) {
      direction = true;
      digitalWrite(MOTOR_PHASE, LOW);
      digitalWrite(MOTOR_ENABLE, HIGH);
      //analogWrite(MOTOR_ENABLE, 768); // 75% duty cycle
    }
    request->send(200, "text/plain", "ok");
  });

  server.on("/brake", HTTP_GET, [] (AsyncWebServerRequest *request) {
    digitalWrite(MOTOR_ENABLE, LOW);
    request->send(200, "text/plain", "ok");
  });
  
  server.on("/reset_turns", HTTP_GET, [] (AsyncWebServerRequest *request) {
    turns = 0;
    request->send(200, "text/plain", "ok");
  });

  server.on("/save_turns", HTTP_GET, [] (AsyncWebServerRequest *request) {
    saved_turns = turns;
    request->send(200, "text/plain", "ok");
  });

  server.on("/get_turns", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(turns));
  });

  server.on("/get_saved_turns", HTTP_GET, [] (AsyncWebServerRequest *request) {
    request->send(200, "text/plain", String(saved_turns));
  });

  server.on("/move_up", HTTP_GET, [] (AsyncWebServerRequest *request) {
    moveUp();
    request->send(200, "text/plain", "ok");
  });

  server.on("/move_down", HTTP_GET, [] (AsyncWebServerRequest *request) {
    moveDown();
    request->send(200, "text/plain", "ok");
  });

  server.onNotFound(notFound);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {}