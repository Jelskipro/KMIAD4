#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>

#define NETWORK_NAME "Jelle_zn_laptop"
#define NETWORK_PASSWORD "ArduinoLol"

bool isGreen1 = false;
bool isGreen2 = true;
bool isRed3 = false;


void setup() {
  setupESP8266();
}
void loop() {
  // put your main code here, to run repeatedly:
  ESP8266Client client;
  int result = client.connect("km4.mobidapt.com", 80);
  if(result <= 0) {
    Serial.println("Failed to connect to server");
    delay(1000);
  } else {
    Serial.println("Send HTTP request");

    //--------------------------------------------
    //light1
    if(isGreen1 == false)
    {
      client.println("GET http://km4.mobidapt.com/jelle/lights/light1/green HTTP/1.1\n"
      
      "Host: km4.mobidapt.com\n"
      "Connection close\n");
      isGreen1 = true;
    }
    if(isGreen1 == true)
    {
      client.println("GET http://km4.mobidapt.com/jelle/lights/light1/red HTTP/1.1\n"
      
      "Host: km4.mobidapt.com\n"
      "Connection close\n");
      isGreen1 = false;
    }
    //--------------------------------------
    //light 2
    if(isGreen2 == false)
    {
      client.println("GET http://km4.mobidapt.com/jelle/lights/light2/green HTTP/1.1\n"
      
      "Host: km4.mobidapt.com\n"
      "Connection close\n");
      isGreen2 = true;
    }
    if(isGreen2 == true)
    {
      client.println("GET http://km4.mobidapt.com/jelle/lights/light2/yellow HTTP/1.1\n"
      
      "Host: km4.mobidapt.com\n"
      "Connection close\n");
      isGreen2 = false;
    }
    //--------------------------------------
    //light 3
    if(isRed3 == false)
    {
      client.println("GET http://km4.mobidapt.com/jelle/lights/light3/red HTTP/1.1\n"
      
      "Host: km4.mobidapt.com\n"
      "Connection close\n");
      isRed3 = true;
    }
    if(isRed3 == true)
    {
      client.println("GET http://km4.mobidapt.com/jelle/lights/light3/yellow HTTP/1.1\n"
      
      "Host: km4.mobidapt.com\n"
      "Connection close\n");
      isRed3 = false;
    }



    
    Serial.println("Response from server:");

    while (client.available()){
      Serial.write(client.read());
      
    }
    if(client.connected()) {
      client.stop();
    }
  }
  delay(4000);

}
