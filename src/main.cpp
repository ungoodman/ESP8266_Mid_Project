#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Settings
#define BLYNK_TEMPLATE_ID "TMPLVDbaUwQu"
#define BLYNK_DEVICE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "bf-lKokYljeG2vgtxaxU5pQLluIvNcjE"
#define BLYNK_PRINT Serial

#define BLYNK_PUSH_DATA_INTERVAL 1000L

#define VIRTUAL_MOISTURE_PIN V5

#define WIFI_SSID ""
#define WIFI_PASS ""

#define MOISTURE_SENSOR_PIN 4
#define SOLENOID_01_PIN 16
#define SOLENOID_02_PIN 5

#define TIMER_INTERVAL 1000

#define DRY_LIMIT 700
#define MOISTURE_LIMIT 400

BlynkTimer timer;

char ssid[] = WIFI_SSID;
char pass[] = WIFI_PASS;

int relayPin1 = 16;        // ตั้งขาสัญญาณ relay ที่ ขา D1
int relayPin2 = 5;         // ตั้งขาสัญญาณ relay ที่ ขา D0
int moistureSensorPin = 4; // ตั้งค่าสัญญาณ เซนเซอร์วัดความชื้นในดิ้น ที่ ขา D2

bool flagMoisture;
float moisturePercent = 0;

unsigned long currentMsTime = 0;

bool solenoid01Status;
bool solenoid02Status;

void setSolenoidValue(bool status)
{
  digitalWrite(SOLENOID_01_PIN, status);
}

void setMoisturePercent(int moistureRawValue)
{
  moisturePercent = 1024 / moistureRawValue;
}

void pushMoistureDataToBlynk()
{
  Blynk.virtualWrite(V1, solenoid01Status);
  Blynk.virtualWrite(V2, solenoid01Status);
  Blynk.virtualWrite(A0, moisturePercent);
}

void setup()
{ // การทำงานเพียงครั้งเดียว
  Serial.begin(115200);

  Serial.println("Program Start!");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  pinMode(relayPin1, OUTPUT);        // การตั้งค่าสั่งให้ตัว relayPin1 เป็นสัญญาณแบบส่ง "ออก"
  pinMode(relayPin2, OUTPUT);        // การตั้งค่าสั่งให้ตัว relayPin2 เป็นสัญญาณแบบส่ง "ออก"
  pinMode(moistureSensorPin, INPUT); // การตั้งค่าสั่งให้ตัว moistureSensorPin เป็นสัญญาณแบบ "รับเข้ามา"

  timer.setInterval(BLYNK_PUSH_DATA_INTERVAL, pushMoistureDataToBlynk);
}

void loop()
{ // การทำงานซ้ำๆ เลื่อยๆ

  Blynk.run();
  timer.run();

  if (millis() - currentMsTime > TIMER_INTERVAL)
  {
    int moistureRawValue = analogRead(MOISTURE_SENSOR_PIN);
    setMoisturePercent(moistureRawValue);

    Serial.println("Raw Moisture: " + String(moistureRawValue));
    Serial.println("Percent Moisture: " + String(moisturePercent));

    if (moistureRawValue > DRY_LIMIT && !flagMoisture) // ถ้า ค่า moistureVal หรือ ค่าความชื้น มากกว่า 700
    {
      digitalWrite(SOLENOID_01_PIN, LOW); // กำการทำงานของ Pin ที่ต้องสถานะ ลอจิก เป็น 0 LOW ซึ่งจะ "ทำงาน"
      flagMoisture = true;
    }

    if (moistureRawValue < 400 && flagMoisture)
    {                                      // และถ้า ไม่ตรงเงื่อนไง ของ if
      digitalWrite(SOLENOID_01_PIN, HIGH); // กำการทำงานของ Pin ที่ต้องสถานะ ลอจิก เป็น 1 HIGH ซึ่งจะ "ไม่ทำงาน"
      flagMoisture = false;
    }

    currentMsTime = millis();
  }
}

// thanakorn

// - ตั้งเวลาควบคุมการให้นํ้าพืช อัตโนมัติตามที่กำหนด
//   - ค่าเกิน 700 ให้รดน้ำ 5 วิ
//   - ค่าเกิน 700 ให้รดน้ำ จนกว่าจะเปียกเกิน ....
//   - รดน้ำตามเวลาที่ตั้ง เช่น 11 โมง ให้รด 1 นาที

// - ควบคุมการให้นํ้าพืชอัตโนมัติโดยการตรวจสอบค่าความชื้นที่เหมาะสม
//   - แห้งไม่เกิน 700
//   - เปียกไม่เกิน xxx

// - รายงานค่าความชื้นในแปลงพืช

// - รายงานสถานะการทำงานของปั๊มนํ้า