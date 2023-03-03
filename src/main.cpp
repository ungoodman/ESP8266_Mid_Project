#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define BLYNK_TEMPLATE_ID "TMPLNkJ1LwdT"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "ZjlFnFMb_n3lW9SnwSZ8tnKuIVeQ243I"
#define BLYNK_PRINT Serial


char ssid[] = "xxxxx";
char pass[] = "xxxxx";

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

WidgetLED sor1(V5);
WidgetLED sor2(V6);

BLYNK_WRITE(V0)
{
  int value = param.asInt();

  Blynk.virtualWrite(V1, value);
}

BLYNK_CONNECTED()
{
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void checkSoilMoisture(int rawMoistureValue)
{
  if (rawMoistureValue > 700 && flagDryLimit == false)
  {
    solenoidStatus1 = LOW;
    solenoidStatus2 = LOW;

    digitalWrite(16, solenoidStatus1);
    digitalWrite(5, solenoidStatus2);

    sor1.on();
    sor2.on();

    flagDryLimit = true;
    return;
  }

  if (rawMoistureValue < 400 && flagDryLimit == true)
  {
    solenoidStatus1 = HIGH;
    solenoidStatus2 = HIGH;

    digitalWrite(16, solenoidStatus1);
    digitalWrite(5, solenoidStatus2);

    sor1.off();
    sor2.off();

    flagDryLimit = false;
    return;
  }
}

void myTimerEvent()
{
  int analog = analogRead(A0);
  float percent = (102 - (analog / 10));
  checkSoilMoisture(analog);
  Serial.println("Raw: " + String(analog) + " Percent: " + String(percent));
  Blynk.virtualWrite(V4, percent);
}

void setup()
{
  pinMode(A0, OUTPUT);
  pinMode(16, INPUT);
  pinMode(5, INPUT);
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
}