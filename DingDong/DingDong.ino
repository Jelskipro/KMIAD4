#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>
#include <LiquidCrystal.h>

#define NETWORK_NAME "HSWConsulting24"
#define NETWORK_PASSWORD "RoelofWasHier"

#define BUTTON_PIN 13

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int buttonState = 0;
int pressed = 0;
String request = "/~jelle.hoogenberg/IAD4/getsmiley?id=1&password=wachtwoord123";
String aanbelRequest = "/~jelle.hoogenberg/IAD4/belt.php?PHPSESSID=bpbobptv5f0ueh884n19gj8dk1&aanbeller='gerrit'";
String currentSmiley;

void setup() {
  Serial.begin(9600);

  setupESP8266();

  pinMode(BUTTON_PIN, INPUT);

  lcd.begin(16, 2);
  lcd.print("Starting DingDong...");
}

void loop() {
  String aanbelResponse;
  int aanbelResult;
  
  buttonState = digitalRead(BUTTON_PIN);

  aanbelResponse = "";

  if (buttonState == HIGH)
  {
     Serial.println("pressed");
     if(pressed == 0)
     {
        aanbelResult = sendRequest("studenthome.hku.nl", aanbelRequest, aanbelResponse);
        pressed = 1;
     }
  }
  else
  {
    Serial.println("Not pressed");
    pressed = 0;
  }
  String response;
  int result;

  response = "";
  result = sendRequest("studenthome.hku.nl", request, response);
  
  if (response.indexOf(":)") >= 0) {
     currentSmiley = ":)";
  } 
  else if (response.indexOf(":(") >= 0){
    currentSmiley = ":(";
  }
  else if (response.indexOf(":D") >= 0){
    currentSmiley = ":D";
  }
  
  else if (response.indexOf(":'(") >= 0){
    currentSmiley = ":'(";
  }

  Serial.println("Current smiley:");
  Serial.println(currentSmiley);

  lcd.clear();
  lcd.print(currentSmiley);
  
  Serial.println(response);
  delay(100);
  
  //if (result < 0) {
    //Serial.println(F("Failed to connect to server."));
  //} else {
    //smileyState = getBody(response).toInt();
    
    //Serial.print("response:");
    //Serial.println(response);

    //Serial.print("smileyState:");
    //Serial.println(smileyState);

    //Serial.print("result:");
    //Serial.println(result);
  //}
    

  
  //delay(500);

}

//String getBody(const String& response) {
  //int bodyStart = response.indexOf("\r\n\r\n");
  //int bodyEnd = response.indexOf('\n', bodyStart + 4);
  //response =  response.substring(bodyStart + 4, bodyEnd);
  //response.trim();

  //return response;
//}



