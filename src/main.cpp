#include <Arduino.h>
/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPLNkJ1LwdT"
#define BLYNK_TEMPLATE_NAME "Quickstart Device"
#define BLYNK_AUTH_TOKEN "ZjlFnFMb_n3lW9SnwSZ8tnKuIVeQ243I"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "3bb-wlan_2.4GHz";
char pass[] = "1111100000";

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

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void checkSoilMoisture(int rawMoistureValue)
{
  // Serial.println("Flag Dry: " + String(flagDryLimit));
  // Serial.print("Sole 1: " + String(!solenoidStatus1));
  // Serial.println(" Sole 2: " + String(!solenoidStatus2));
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

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
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