#include <Arduino.h>
#include <main.h>

BLYNK_WORK_MODE_BTN
{
  isAutomatic = !param.asInt();
}

BLYNK_SOLENOID_ZONE_A_BTN
{
  if (param.asInt())
  {
    virtualSolenoidLedZoneA.on();
    solenoidZoneA.on();
  }
  else
  {
    virtualSolenoidLedZoneA.off();
    solenoidZoneA.off();
  }
}

BLYNK_SOLENOID_ZONE_B_BTN
{
  if (param.asInt())
  {
    virtualSolenoidLedZoneB.on();
    solenoidZoneB.on();
  }
  else
  {
    virtualSolenoidLedZoneB.off();
    solenoidZoneB.off();
  }
}

void automaticMode()
{
  if (moistureSensor.dryLimitReach())
  {
    virtualSolenoidLedZoneA.on();
    solenoidZoneA.on();
    virtualSolenoidLedZoneB.on();
    solenoidZoneB.on();
    return;
  }

  if (moistureSensor.wetLimitReach())
  {
    virtualSolenoidLedZoneA.off();
    solenoidZoneA.off();
    virtualSolenoidLedZoneB.off();
    solenoidZoneB.off();
  }
}

void mainEvent()
{
  float moisturePercent = moistureSensor.getPercent();
  Blynk.virtualWrite(VIRTUAL_MOISTURE_GAUGE, moisturePercent);

  if (isAutomatic)
    automaticMode();
}

void setup()
{
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(BLYNK_TIMER_INTERVAL, mainEvent);

  Serial.begin(SERIAL_MONITOR_SPEED);
}

void loop()
{
  Blynk.run();
  timer.run();
}