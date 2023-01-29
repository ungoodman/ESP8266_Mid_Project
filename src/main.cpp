#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Blynk settings
#define BLYNK_TEMPLATE_ID "TMPLNkJ1LwdT"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "ZjlFnFMb_n3lW9SnwSZ8tnKuIVeQ243I"
#define BLYNK_PRINT Serial
#define Blynk_TIMER_INTERVAL 1000L

// Blynk pin settings
#define SOLENOID_LED_1 V1
#define SOLENOID_LED_2 V2
#define MOISTURE_GAUGE V4

// Hardware pin settings
#define SOLENOID_PIN_1 16
#define SOLENOID_PIN_2 5
#define MOISTURE_SENSOR_PIN A0
#define SERIAL_SPEED 115200

// Moisture settings
#define MOISTURE_LIMIT 400
#define DRY_LIMIT 700

// Wifi settings
#define WIFI_SSID "3bb-wlan_2.4GHz"
#define WIFI_PASS "1111100000"

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASS;

bool flagDryLimit = false;

#define ACTIVE_LOW
#ifdef ACTIVE_LOW
bool solenoidStatus1 = HIGH;
bool solenoidStatus2 = HIGH;
#else
bool solenoidStatus1 = LOW;
bool solenoidStatus2 = LOW;
#endif

BlynkTimer timer;

BLYNK_CONNECTED()
{
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void pushToDashBoard()
{
  int rawMoistureValue = analogRead(MOISTURE_SENSOR_PIN);

  checkSoilMoisture(rawMoistureValue);

  Blynk.virtualWrite(MOISTURE_GAUGE, 1024 / rawMoistureValue);
  Blynk.virtualWrite(SOLENOID_LED_1, solenoidStatus1);
  Blynk.virtualWrite(SOLENOID_LED_2, solenoidStatus2);
}

void checkSoilMoisture(int rawMoistureValue)
{
  if (rawMoistureValue > DRY_LIMIT && !flagDryLimit)
  {
    solenoidStatus1 = LOW;
    solenoidStatus2 = LOW;

    digitalWrite(SOLENOID_PIN_1, solenoidStatus1);
    digitalWrite(SOLENOID_PIN_2, solenoidStatus2);
    
    flagDryLimit = true;
    return;
  }

  if (rawMoistureValue < MOISTURE_LIMIT && flagDryLimit)
  {
    solenoidStatus1 = HIGH;
    solenoidStatus2 = HIGH;
    
    digitalWrite(SOLENOID_PIN_1, solenoidStatus1);
    digitalWrite(SOLENOID_PIN_2, solenoidStatus2);
    
    flagDryLimit = false;
    return;
  }
}

void setup()
{
  pinMode(SOLENOID_PIN_1, OUTPUT);
  pinMode(SOLENOID_PIN_2, OUTPUT);
  pinMode(MOISTURE_SENSOR_PIN, INPUT);

  digitalWrite(SOLENOID_PIN_1, solenoidStatus1);
  digitalWrite(SOLENOID_PIN_2, solenoidStatus2);

  Serial.begin(SERIAL_SPEED);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(Blynk_TIMER_INTERVAL, pushToDashBoard);
}

void loop()
{
  Blynk.run();
  timer.run();
}
