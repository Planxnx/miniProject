#include "DHT.h"
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>

#define WIFI_SSID       "Planxnx"
#define WIFI_PASSWORD   "planxthanee"
#define DHTTYPE DHT22
#define FIREBASE_HOST "miniproject-2560.firebaseio.com"
#define FIREBASE_KEY "KRo5ya1izH6Ae7CXbqAUT62UMRScvnkrlqZ5ZPYg"
#define DHTPIN 4  
DHT dht(DHTPIN, DHTTYPE);

int rounds=0;
int process=0;
float arTemp[61],avgTemp,tTemp;
void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  
  dht.begin();
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
}
void loop()
{
  rounds++;
  
  unsigned long Time = millis();//หาร1พันได้1วิ
  
  float x = Time;// เปลี่ยนค่าเวลาให้เป็นทศนิยม
  float times = x/1000;//แปลงหน่วย
  /*float humidity = dht.getHumidity(); // ดึงค่าความชื้น*/
  float temperature = dht.readTemperature(); // ดึงค่าอุณหภูมิ
  process = (rounds*100)/60;
  Firebase.setInt("Times", times);
  Firebase.setFloat("Temp", temperature);
  Firebase.setFloat("timeCounts", process);
  Serial.print(process);
  Serial.print("  ");
  Serial.print(rounds);
  Serial.print("  ");
  Serial.print(times);
  Serial.print("s \t");
  Serial.print("\t");
  Serial.print(temperature, 1);
  Serial.println("C\t\t");
  arTemp[rounds]=dht.readTemperature();
  if(rounds%2==0){
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else{
    digitalWrite(LED_BUILTIN, LOW);
  }
  if(rounds%60==0){
    for(int i=1;i<=60;i++){
      tTemp+=arTemp[i];
    }
    avgTemp = tTemp/60;
    Firebase.setFloat("AvgTemp", avgTemp);
    Serial.print(avgTemp);
    Serial.println("C (avg)");
    findPlants(avgTemp);  
    rounds=0;
    tTemp=0;
  }
}
void findPlants(float avT){

  Serial.println("fuction findPlants : working...");
  if(avT<19){
    Firebase.setString("Plants", "ไม่มีพืชผักที่สามรปลูกได้*");}
    else if(avT>=19&&avT<22){
      Firebase.setString("Plants", "ผักขม ,เห็ด");}
    else if(avT>=22&&avT<25){
      Firebase.setString("Plants", "พาสลีย์ ,ผักกาดหอม ,แครรอท");}
    else if(avT>=25&&avT<28){
      Firebase.setString("Plants", "หอมหัวใหญ่ ,พืชตระกูลถั่ว ,พริก");}
    else if(avT>=28&&avT<31){
      Firebase.setString("Plants", "มะเขือเทศ ,กะหล่ำปลี ,มะเขือยาว");}
    else if(avT>=31&&avT<33){
      Firebase.setString("Plants", "ฟักทอง ,ถั่วฝักยาว ,ข้าวโพดหวาน");}
    else if(avT>=33&&avT<35){
      Firebase.setString("Plants", "แตงโม ,แตงกวา ,แตงไทย");}
    else if(avT>=35){
      Firebase.setString("Plants", "ไม่มีพืชผักที่สามรปลูกได้*");}  
   //*ข้อมูลพืชที่มีในข้อมูลของโปรแกรมเท่านั้น  
 }
