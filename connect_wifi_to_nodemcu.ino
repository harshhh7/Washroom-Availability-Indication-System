#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "ThingSpeak.h"

const char *ssid =  "YOUR-WIFI-NAME";
const char *pass =  "YOUR-WIFI-PASSWORD";

#include <SoftwareSerial.h>
#include <ArduinoJson.h>

WiFiClient client;

unsigned long myChannelNumber=1;
const char* myWriteAPIKey="G27P24W5FVDW9OJZ";

SoftwareSerial nodemcu(D6, D5);
//D6-Rx d5 -Tx
void setup() 
{
       Serial.begin(9600);
       delay(10);
       nodemcu.begin(9600);
       //while (!Serial) continue;
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
       WiFi.begin(ssid, pass); 
       //Serial.println("hlo");
       while (WiFi.status() != WL_CONNECTED) 
          {
            delay(500);
            Serial.print(".");
          }
      Serial.println("");
      Serial.println("WiFi connected"); 
      WiFi.mode(WIFI_STA);   
      ThingSpeak.begin(client);
      Serial.println("hello");
}
 
void loop() 
{      
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);
  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }
  Serial.println("JSON Object Recieved");
  int a = data["IR1"];
  int b = data["IR2"];
  int c = data["IR3"];
  int d = data["IR4"];
  int e = data["IR5"];
  int f = data["IR6"];
  Serial.println("-----------------------------------------");
  Serial.print("IR1 :");Serial.print(a);
  Serial.print("IR2 :");Serial.println(b);
  Serial.print("IR3 :");Serial.print(c);
  Serial.print("IR4 :");Serial.println(d);
  Serial.print("IR5 :");Serial.print(e);
  Serial.print("IR6 :");Serial.println(f);
   ThingSpeak.setField(1, a);
   ThingSpeak.setField(2, b);
    ThingSpeak.setField(3, c);
   ThingSpeak.setField(4, d);
    ThingSpeak.setField(5, e);
   ThingSpeak.setField(6, f);
   ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
   Serial.println("ths");
   
   //ThingSpeak.writeField(myChannelNumber, 1, a, myWriteAPIKey);
   //ThingSpeak.writeField(myChannelNumber, 2, b, myWriteAPIKey);
  delay(100);
}
