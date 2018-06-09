#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

#define NETWORK_NAME "HSWConsulting24"
#define NETWORK_PASSWORD "RoelofWasHier"

String request;
String request2;

void setup() {
  Serial.begin(9600);

  setupESP8266();
  
}

void loop() {
  ESP8266Client client;

  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  request = "/sliders?userid=jelle&sliderid=slider3&value=";
  request +=  sensorValue;
  request2 = "/switches?userid=jelle&switchid=switch1";

  
  int result = client.connect("km4.mobidapt.com", 80);
  if (result <= 0) {
    Serial.println("Failed to connect to server.");
    delay(300);
  } 
  else {

    Serial.println("Send HTTP request...");
    //let op spaties ervoor 
    client.println("GET " + request + " HTTP/1.1\n"
                   "Host: km4.mobidapt.com\n"
                   "Connection: close\n");
                   
    Serial.println("Response from server");
    String response;
    while (client.available()) {
      response += (char)client.read();
    }
    Serial.println(response);
  }

  int result2 = client.connect("km4.mobidapt.com", 80);
  if (result2 <= 0) {
    Serial.println("Failed to connect to server.");
    delay(300);
  } 
  else {

    Serial.println("Send HTTP request...");
    //let op spaties ervoor 
    client.println("GET " + request2 + " HTTP/1.1\n"
                   "Host: km4.mobidapt.com\n"
                   "Connection: close\n");
                   
    Serial.println("Response from server");
    String response2;
    while (client.available()) {
      response2 += (char)client.read();
    }
    Serial.println(response2);

    if(response2.indexOf("off") >0){
      digitalWrite(13, LOW);
    }
    else
    {
      digitalWrite(13, HIGH);

    }
  }
  
  if (client.connected()) {
    client.stop();
  }

  delay(1000);
}
