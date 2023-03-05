#include <Arduino.h>
#include <main.h>

BLYNK_WORK_MODE_BTN
{
  isAutomatic = !param.asInt();

  if (!isAutomatic)
  {
    digitalWrite(WORKMODE_LED_PIN, LOW);
    setSolenoid(blynkSolenoidLedZoneA, solenoidZoneA, LOW);
    setSolenoid(blynkSolenoidLedZoneB, solenoidZoneB, LOW);
  }
  else digitalWrite(WORKMODE_LED_PIN, HIGH);
}

BLYNK_SOLENOID_ZONE_A_BTN
{
  manualMode(param.asInt(), blynkSolenoidLedZoneA, solenoidZoneA);
}

BLYNK_SOLENOID_ZONE_B_BTN
{
  manualMode(param.asInt(), blynkSolenoidLedZoneB, solenoidZoneB);
}

void setSolenoid(WidgetLED blynkLED, Solenoid solenoid, bool signal) {
  if (signal)
  {
    blynkLED.on();
    solenoid.on();
  }
  else
  {
    blynkLED.off();
    solenoid.off();
  }
}

void manualMode(int blynkSignal, WidgetLED blynkLED, Solenoid solenoid) {
  if (isAutomatic)
    return;

  setSolenoid(blynkLED, solenoid, blynkSignal);
}

void automaticMode()
{
  if (!isAutomatic)
    return;

  if (moistureSensor.dryLimitReach())
  {
    setSolenoid(blynkSolenoidLedZoneA, solenoidZoneA, HIGH);
    setSolenoid(blynkSolenoidLedZoneB, solenoidZoneB, HIGH);
  }
  if (moistureSensor.wetLimitReach())
  {
    setSolenoid(blynkSolenoidLedZoneA, solenoidZoneA, LOW);
    setSolenoid(blynkSolenoidLedZoneB, solenoidZoneB, LOW);
  }
}

void timerEvent()
{
  automaticMode();

  Blynk.virtualWrite(BLYNK_MOISTURE_GAUGE, moistureSensor.getPercent());
}

void setup()
{
  pinMode(WORKMODE_LED_PIN, OUTPUT);

  Serial.begin(SERIAL_MONITOR_SPEED);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(BLYNK_TIMER_INTERVAL, timerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}