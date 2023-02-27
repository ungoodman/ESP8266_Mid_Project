#include <Arduino.h>
#include <Solenoid.h>
#include <MoistureSensor.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPLNkJ1LwdT"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "ZjlFnFMb_n3lW9SnwSZ8tnKuIVeQ243I"
#define BLYNK_PRINT Serial
#define BLYNK_TIMER_INTERVAL 1000L

#define SERIAL_MONITOR_SPEED 115200

#define MOISTURE_SENSOR_PIN A0
#define SOLENOID_PIN_ZONE_A 16
#define SOLENOID_PIN_ZONE_B 5
#define LED_PIN_ZONE_A 8
#define LED_PIN_ZONE_B 9

#define VIRTUAL_MOISTURE_GAUGE V4
#define VIRTUAL_WORK_MODE_PIN V0
#define VIRTUAL_LED_PIN_ZONE_A V1
#define VIRTUAL_LED_PIN_ZONE_B V2
#define VIRTUAL_SOLENOID_PIN_ZONE_A V5
#define VIRTUAL_SOLENOID_PIN_ZONE_B V6

#define BLYNK_WORK_MODE_BTN BLYNK_WRITE(VIRTUAL_WORK_MODE_PIN)
#define BLYNK_SOLENOID_ZONE_A_BTN BLYNK_WRITE(VIRTUAL_SOLENOID_PIN_ZONE_A)
#define BLYNK_SOLENOID_ZONE_B_BTN BLYNK_WRITE(VIRTUAL_SOLENOID_PIN_ZONE_B)

#ifdef ACTIVE_LOW
#define ACTIVE_LOW
Solenoid solenoidZoneA(SOLENOID_PIN_ZONE_A, LED_PIN_ZONE_A, LOW);
Solenoid solenoidZoneB(SOLENOID_PIN_ZONE_B, LED_PIN_ZONE_B, LOW);
#else
Solenoid solenoidZoneA(SOLENOID_PIN_ZONE_A, LED_PIN_ZONE_A);
Solenoid solenoidZoneB(SOLENOID_PIN_ZONE_B, LED_PIN_ZONE_B);
#endif

MoistureSensor moistureSensor(MOISTURE_SENSOR_PIN);

WidgetLED virtualSolenoidLedZoneA(VIRTUAL_LED_PIN_ZONE_A);
WidgetLED virtualSolenoidLedZoneB(VIRTUAL_LED_PIN_ZONE_B);

BlynkTimer timer;

// Wifi
char ssid[] = "3bb-wlan_2.4GHz";
char pass[] = "1111100000";

bool isAutomatic;

// Moisture Sensor
float moisturePercent;