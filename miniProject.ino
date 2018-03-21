#include "DHT.h"
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>

#define WIFI_SSID       "JIA-2409"
#define WIFI_PASSWORD   "27791462"

#define FIREBASE_HOST "miniproject-2560.firebaseio.com"
#define FIREBASE_KEY "KRo5ya1izH6Ae7CXbqAUT62UMRScvnkrlqZ5ZPYg"

DHT dht;

void setup()
{
  Serial.begin(9600);
  Serial.println(WiFi.localIP());
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);

  Serial.println();
  Serial.println("Status \tHumidity (%)\tTemperature (C)\t(F)");

  dht.setup(4); // data pin 2
}

void loop()
{

  float Time = millis()/1000;
  
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ

  Firebase.setFloat("Times", Time);
  Firebase.setFloat("Humidity", humidity);
  Firebase.setFloat("Temp", temperature);
  
  Serial.print(Time);
  Serial.print(" s\t");
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.println(dht.toFahrenheit(temperature), 1);
}
