#define BLYNK_TEMPLATE_ID "TMPL3OOHh0piz"
#define BLYNK_TEMPLATE_NAME "nodemcu"
#define BLYNK_AUTH_TOKEN "kTYtbtD4AwxW0b9egheJvKVRowM8fYvh"
// #define BLYNK_TEMPLATE_ID "TMPL3OOHh0piz"
// #define BLYNK_TEMPLATE_NAME "nodemcu"
// #define BLYNK_AUTH_TOKEN "UTjYiNPhQ5OGfCxdOO1q2hW0_A22rWPu"89
#define BLYNK_PRINT Serial   
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


#define BLYNK_PRINT Serial


#define RAIN_SENSOR_PIN D5
#define RAIN_SENSOR_THRESHOLD 100 
#define SOIL_SENSOR_PIN D6
#define SOIL_SENSOR_THRESHOLD 100
char auth[] = BLYNK_AUTH_TOKEN;               
char ssid[] = "Realme X3";                        
char pass[] = "12233456677";                        

BlynkTimer timer;


#include <DHT.h>
#define DHTPIN D4 
#define DHTTYPE DHT11  
#define relay D1
DHT dht(DHTPIN, DHTTYPE);

// void sendSensor()
// {
  
//   int value = analogRead(D6);
//   value = map(value,400,1023,100,0);
//   float h = dht.readHumidity();
//   float t = dht.readTemperature(); 

//   if (isnan(h) || isnan(t)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }
//   if (value < SOIL_SENSOR_THRESHOLD){
//     Blynk.logEvent("wateralert");
//   }

//   int sensorValue = analogRead(RAIN_SENSOR_PIN);
//   sensorValue = map(sensorValue,400,1023,100,0);

//   if (sensorValue > RAIN_SENSOR_THRESHOLD) {
//     Blynk.logEvent("rainalert");
//   }

  
//     Blynk.virtualWrite(V0, sensorValue);
//     Blynk.run();
//     Blynk.virtualWrite(V2, value);
//     Blynk.virtualWrite(V6, t);
//     Blynk.virtualWrite(V5, h);
//     Serial.print("Rain sensor value: ");
//     Serial.println(sensorValue);
//     Serial.print("Soil Moisture : ");
//     Serial.print(value);
//     Serial.print("Temperature : ");
//     Serial.print(t);
//     Serial.print("    Humidity : ");
//     Serial.println(h);
    
// }
// void setup()
// {   
  
//   Serial.begin(115200);
//   pinMode(relay, OUTPUT);
//   digitalWrite(relay, HIGH);
//   Blynk.begin(auth, ssid, pass);
//   dht.begin();
//   timer.setInterval(100L, sendSensor);
 
//   }

// BLYNK_WRITE(V1){
//   if(param.asInt()==1){
//     digitalWrite(relay, HIGH);
//   }else{
//     digitalWrite(relay, LOW);
//   }
// }

// void loop()
// {
//   Blynk.run();
//   timer.run();
//  }
void setup()
{
  Serial.begin(115200);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}
  BLYNK_WRITE(V1){
  if(param.asInt()==1){
    digitalWrite(relay, HIGH);
    }else{
    digitalWrite(relay, LOW);
   }
  }
void loop()
{
  int sensorValue = analogRead(RAIN_SENSOR_PIN);
  Serial.print("Rain sensor value: ");
  Serial.println(sensorValue);

  if (sensorValue < RAIN_SENSOR_THRESHOLD) {
    Blynk.logEvent("rainalert");
  }

  Blynk.virtualWrite(V0, sensorValue);

  Blynk.run();
  delay(1000);
  
  
  int value = analogRead(SOIL_SENSOR_PIN);
  value = map(value,400,1023,100,0);

  Serial.print("Soil sensor value: ");
  Serial.println(value);

  if (value < SOIL_SENSOR_THRESHOLD) {
    Blynk.logEvent("wateralert");
  }

  Blynk.virtualWrite(V2, value);

  Blynk.run();
  delay(1000);
}