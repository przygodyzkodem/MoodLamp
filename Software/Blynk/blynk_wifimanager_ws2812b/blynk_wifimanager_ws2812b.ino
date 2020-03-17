/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#define LED_PIN D9
#define RESET_BUTTON_PIN D3

#define PIXEL_COUNT 36
#define BLYNK_TOKEN_LENGTH 33

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
WiFiManagerParameter blynkToken("Blynk", "blynk token", blynk_token, BLYNK_TOKEN_LENGTH);


int mode = 0;
int red = 255;
int green = 200;
int blue = 170;
int brightness = 255;

void initializeLedStrip() {
  strip.init();
  strip.setBrightness(brightness);
  strip.setColor(red, green, blue);
  strip.setSpeed(200);
  strip.setMode(mode);
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
  digitalWrite(D4, HIGH);

  pinMode(RESET_BUTTON_PIN, INPUT_PULLUP);

  EEPROM.begin(512);
  char blynkTokenEEPROM[BLYNK_TOKEN_LENGTH] = "";
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
  }

  if (blynkToken.getValue()[0] != blynk_token[0]) {
    for (int i = 0; i < BLYNK_TOKEN_LENGTH; i++) {
      blynkTokenEEPROM[i] = blynkToken.getValue()[i];
    }
    Serial.print("Overwriting blynk token in EEPROM: ");
    Serial.println(blynkTokenEEPROM);
    EEPROM.put(0, blynkTokenEEPROM);
    EEPROM.commit();
  }

  //Send to Blynk current lamp state so app reflects it correctly
  Blynk.virtualWrite(V1, red, green, blue);
  Blynk.virtualWrite(V2, brightness);
  Blynk.virtualWrite(V3, LOW);
  Blynk.virtualWrite(V4, mode); 
}

void loop()
{
  Blynk.run();
  strip.service();
  handleResetButton();
}

void handleResetButton() {
  int resetButtonState = digitalRead(RESET_BUTTON_PIN);
  if (resetButtonState == LOW) {
    Serial.println("RESET PRESSED");
    wifiManager.resetSettings();
    delay(1000);
    ESP.restart();
  }
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
