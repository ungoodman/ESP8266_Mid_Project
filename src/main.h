#include <Arduino.h>
#include <Solenoid.h>
#include <MoistureSensor.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPLVDbaUwQu"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "Nyj2ZFPQeyVJXnAhXNngAl3yGJBMVfJK"
#define BLYNK_PRINT Serial
#define BLYNK_TIMER_INTERVAL 1000L

#define SERIAL_MONITOR_SPEED 115200

#define MOISTURE_SENSOR_PIN A4
#define SOLENOID_PIN_ZONE_A 16
#define SOLENOID_PIN_ZONE_B 5
#define WORKMODE_LED_PIN 17

#define BLYNK_MOISTURE_GAUGE V4

#define BLYNK_WORK_MODE_BTN BLYNK_WRITE(V0)
#define BLYNK_SOLENOID_ZONE_A_BTN BLYNK_WRITE(V5)
#define BLYNK_SOLENOID_ZONE_B_BTN BLYNK_WRITE(V6)

#ifndef ACTIVE_LOW
Solenoid solenoidZoneA(SOLENOID_PIN_ZONE_A);
Solenoid solenoidZoneB(SOLENOID_PIN_ZONE_B);
#else
Solenoid solenoidZoneA(SOLENOID_PIN_ZONE_A, LOW);
Solenoid solenoidZoneB(SOLENOID_PIN_ZONE_B, LOW);
#endif

MoistureSensor moistureSensor(MOISTURE_SENSOR_PIN);

WidgetLED blynkSolenoidLedZoneA(V1);
WidgetLED blynkSolenoidLedZoneB(V2);

BlynkTimer timer;

// Wifi
char ssid[] = "JIGJUNEE_2.4G";
char pass[] = "0920120321";

bool isAutomatic = true;

// Moisture Sensor
float moisturePercent;