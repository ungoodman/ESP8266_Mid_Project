#include <Arduino.h>

int relayPin1 = 16;                                   // ตั้งขาสัญญาณ relay ที่ ขา D1
int relayPin2 = 5;                                   // ตั้งขาสัญญาณ relay ที่ ขา D0
int soilSensorPin = 4;                               // ตั้งค่าสัญญาณ เซนเซอร์วัดความชื้นในดิ้น ที่ ขา D2

void setup () {                                        // การทำงานเพียงครั้งเดียว 
  pinMode(relayPin1, OUTPUT);                         // การตั้งค่าสั่งให้ตัว relayPin1 เป็นสัญญาณแบบส่ง "ออก"
  pinMode(relayPin2, OUTPUT);                         // การตั้งค่าสั่งให้ตัว relayPin2 เป็นสัญญาณแบบส่ง "ออก"
  pinMode(soilSensorPin ,INPUT);                      // การตั้งค่าสั่งให้ตัว SoilSensorPin เป็นสัญญาณแบบ "รับเข้ามา"
}
 void loop (){                                        // การทำงานซ้ำๆ เลื่อยๆ 
  int moistureVal = analogRead (soilSensorPin);       // อ่านค่าสัญญาณ analog ขา D2 ที่ต่อ soil Moisture Senser
  Serial.print("val = ");                             // เป็นการรับค่าทุกชนิด และ แปลงเป็น int long 
  Serial.println(moistureVal);                        // เป็นการส่งค่าของ moistureVal และขึ้นบรรดทัดใหม่อัตโนมัติ
 if (moistureVal > 700)                               // ถ้า ค่า moistureVal หรือ ค่าความชื้น มากกว่า 700 
 {
  digitalWrite (relayPin1,LOW);                       // กำการทำงานของ Pin ที่ต้องสถานะ ลอจิก เป็น 0 LOW ซึ่งจะ "ทำงาน" 
 }
 else {                                               // และถ้า ไม่ตรงเงื่อนไง ของ if
  digitalWrite (relayPin2,HIGH);                      // กำการทำงานของ Pin ที่ต้องสถานะ ลอจิก เป็น 1 HIGH ซึ่งจะ "ไม่ทำงาน"    
 }
  delay(1000);                                        // เป็นการหน่วงเวลาการทำงานที่ 1000 หรือ 1 วินาที
  }
  
 