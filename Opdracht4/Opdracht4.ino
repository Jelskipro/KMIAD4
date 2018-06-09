#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>
#include "ArduinoJson.h"

#define NETWORK_NAME "HKU"
#define NETWORK_PASSWORD "draadloos"

#define LED_PIN 13

void setup() {
  Serial.begin(9600);

  setupESP8266();

  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  
  String response;
  
  DynamicJsonBuffer jsonBuffer(128); // afh. van grootte JSON
  JsonObject& json = jsonBuffer.parse(response);
  if (json.success()) {
    int slider1 = json["slider1"];
    int slider2 = json["slider2"];
    int slider3 = json["slider3"];
  }
  
  // haal stand van switch op
  String request = "/sliders/getall?userid=edwin";

  int result = sendRequest("km4.mobidapt.com", request, response);
  if (result < 0) {
    Serial.println(F("Failed to connect to server."));
  } else {
    Serial.println(response);
  }
  
  // zoek in de response naar 't woord 'off'
  if (response.indexOf("off") >= 0) {
    digitalWrite(LED_PIN, LOW);
  } else { // geen 'off'? dan blijkbaar 'on'...
    digitalWrite(LED_PIN, HIGH);
  }

  delay(500);
  
}

