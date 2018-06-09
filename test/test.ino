#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>
#include "ArduinoJson.h"

#define NETWORK_NAME "HSWConsulting24"
#define NETWORK_PASSWORD "RoelofWasHier"

int slider1 = 0;

void setup() {
  Serial.begin(9600);

  setupESP8266();

}

void loop() {
  
  String response;
  
  DynamicJsonBuffer jsonBuffer(128); // afh. van grootte JSON
  JsonObject& json = jsonBuffer.parse(response);
  if (json.success()) {
    slider1 = json["slider1"];
  }
  
  // haal stand van switch op
  String request = "http://studenthome.hku.nl/~jelle.hoogenberg/IAD4/getdata";

  int result = sendRequest("studenthome.hku.nl", request, response);
  if (result < 0) {
    Serial.println(F("Failed to connect to server."));
  } else {
    Serial.println(response);
    Serial.println("slider1:");
    Serial.println(slider1);

  }
  
  // zoek in de response naar 't woord 'off

  delay(500);
  
}

