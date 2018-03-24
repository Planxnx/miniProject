#include "DHT.h"
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>

#define WIFI_SSID       "Planx"
#define WIFI_PASSWORD   "planxthanee"

#define FIREBASE_HOST "miniproject-2560.firebaseio.com"
#define FIREBASE_KEY "KRo5ya1izH6Ae7CXbqAUT62UMRScvnkrlqZ5ZPYg"

DHT dht;//สร้างออบเจกค
int rounds=0;
float arTemp[61],avgTemp,tTemp;

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
  
  //Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  
  dht.setup(4); // data pin 2
}

void loop()
{
  rounds++;

  unsigned long Time = millis();//หาร1พันได้1วิ
  
  float x = Time;// เปลี่ยนค่าเวลาให้เป็นทศนิยม
  float times = x/1000;//แปลงหน่วย
  float humidity = dht.getHumidity(); // ดึงค่าความชื้น
  float temperature = dht.getTemperature(); // ดึงค่าอุณหภูมิ
  
  Firebase.setInt("Times", times);
  Firebase.setFloat("Humidity", humidity);
  Firebase.setFloat("Temp", temperature);
  
  Serial.print(rounds);
  Serial.print("  ");
  Serial.print(times);
  Serial.print("s \t");
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("C\t\t");
  Serial.print(dht.toFahrenheit(temperature), 1);
  Serial.println("F\t\t");

  arTemp[rounds]=dht.getTemperature();
  if(rounds%60==0){
    for(int i=1;i<=60;i++){
      tTemp+=arTemp[i];
    }
    avgTemp = tTemp/60;
    Firebase.setFloat("AvgTemp", avgTemp);
    Serial.print(avgTemp);
    Serial.println("C (avg)");
    rounds=0;
    tTemp=0;
  }
  
  //delay(dht.getMinimumSamplingPeriod());
}
