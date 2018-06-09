#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

#define NETWORK_NAME "EdwinAP"
#define NETWORK_PASSWORD "edwinapkm4"

void setup() {
  setupESP8266();
//  Serial.begin(9600);
//  
//  int found = esp8266.begin();
//  if (found) {
//    Serial.println("ESP8266 shield found! Hoera!");
//  } else {
//    Serial.println("Geen contact met ESP8266 shield :(");
//    while(1);
//  }
//
//  int result = esp8266.connect(NETWORK_NAME, NETWORK_PASSWORD);
//  if (result < 0) {
//    Serial.print("Error connecting: ");
//    Serial.println(result);
//    while(1);
//  }
//
//  IPAddress mijnIP = esp8266.localIP();
//  Serial.print("Mijn IP: ");
//  Serial.println(mijnIP);
} 

void loop() {

}
