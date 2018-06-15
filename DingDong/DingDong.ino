#include <SoftwareSerial.h>
#include <SparkFunESP8266WiFi.h>
#include <LiquidCrystal.h>

#define NETWORK_NAME "WIFInaamhier"
#define NETWORK_PASSWORD "WIFIwachtwoordhier"

#define BUTTON_PIN 13

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int buttonState = 0;
int pressed = 0;

//De request voor de smiley opvragen
String request = "/~jelle.hoogenberg/IAD4/getsmiley?id=1&password=wachtwoord123";
//De request voor als je aanbelt. 
String aanbelRequest = "/~jelle.hoogenberg/IAD4/belt.php?PHPSESSID=v9f0mjjv88hb8ie6r10p25cqv2&aanbeller='gerrit'";
//Huidige smiley
String currentSmiley;

void setup() {
  Serial.begin(9600);

  setupESP8266();
  
  pinMode(BUTTON_PIN, INPUT);

  //Set de LCD OP
  lcd.begin(16, 2);
  lcd.print("Starting DingDong...");
}

void loop() {
  String aanbelResponse;
  int aanbelResult;

  buttonState = digitalRead(BUTTON_PIN);

  //Maak de aanbel response leeg zodat hij sneller print.
  aanbelResponse = "";

  //Als je op de knop drukt (aanbelt)
  if (buttonState == HIGH)
  {
     Serial.println("pressed");
     if(pressed == 0)
     {
        //Voer het aanbel request uit
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

  //Maak de response leeg zodat hij sneller print.
  response = "";
  //Voer php script uit dat de smiley opvraagt.
  result = sendRequest("studenthome.hku.nl", request, response);

  //Kijk welke smiley voorkomt in de body.
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

  //Clear de lcd zodat hij maar 1 tegelijk laat zien
  lcd.clear();
  //Laat de huidige smiley zien op de lcd
  lcd.print(currentSmiley);
  
  Serial.println(response);
  delay(50);
  

}



