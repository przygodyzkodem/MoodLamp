/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#define LED_PIN D9
#define PIXEL_COUNT 36

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <WiFiManager.h>
#include <EEPROM.h>
#include <WS2812FX.h>


// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char blynk_token[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "wifi_name";
char pass[] = "wifi_password";

WS2812FX strip = WS2812FX(PIXEL_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
WiFiManager wifiManager;
WiFiManagerParameter blynkToken("Blynk", "blynk token", blynk_token, 33);


int mode = 0;
int red = 255;
int green = 255;
int blue = 255;
int brightness = 255;

void initializeLedStrip() {
  strip.init();
  strip.setBrightness(255);
  strip.setColor(255,200,170);
  strip.setSpeed(200);
  strip.setMode(0);
  strip.start();
  strip.service();
}

void connectWiFi() {
  //wifiManager.resetSettings(); //WiFiManager remembers previously connected APs
  wifiManager.addParameter(&blynkToken);
  wifiManager.autoConnect("Lampka");
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  delay(100);
  pinMode(D4, OUTPUT);

  EEPROM.begin(512);
  char blynkTokenEEPROM[34] = "";
  EEPROM.get(0, blynkTokenEEPROM);
  Serial.print("Blynk token read from EEPROM: ");
  Serial.println(blynkTokenEEPROM);
  Serial.println("Blynk token from WebPanel: ");
  Serial.print(blynkToken.getValue());
  Serial.println();
  
  initializeLedStrip();
  connectWiFi();
  
  if (blynkToken.getValue()[0] != blynk_token[0]) {
    Serial.println("Using Blynk token from WebPanel");
    Blynk.config(blynkToken.getValue());  
  } else {
    Serial.print("Using Blynk Token from EEPROM");
    Blynk.config(blynkTokenEEPROM);
  }
  
  if(!Blynk.connect()) {
    Serial.println("Blynk connection timed out.");
    //wifiManager.resetSettings();
    //ESP.restart();
  }

  if (blynkToken.getValue()[0] != blynk_token[0]) {
    for (int i = 0; i < 34 ; i++) { //TODO: Check if array size 33 works good
      blynkTokenEEPROM[i] = blynkToken.getValue()[i];
    }
    Serial.print("Overwriting blynk token in EEPROM: ");
    Serial.println(blynkTokenEEPROM);
    EEPROM.put(0, blynkTokenEEPROM);
    EEPROM.commit();
  }
  
  digitalWrite(D4, LOW);
  Blynk.virtualWrite(V3, LOW);
}

void loop()
{
  Blynk.run();
  strip.service();
}


BLYNK_WRITE(V1) {
  red = param[0].asInt();
  green = param[1].asInt();
  blue = param[2].asInt();
  strip.setColor(red, green, blue);
}

BLYNK_WRITE(V2) {
  brightness = param.asInt();
  strip.setBrightness(brightness);
}


// This function will be called every time button Widget
// in Blynk app writes values to the Virtual Pin V3
BLYNK_WRITE(V3) {
 int pinValue = param.asInt(); // Assigning incoming value from pin V3 to a variable
 if (pinValue == 1) {
    strip.stop();
  } else {
    strip.start();
  }
}

BLYNK_WRITE(V4) {
  mode = param.asInt();
  strip.setMode(mode);
}
