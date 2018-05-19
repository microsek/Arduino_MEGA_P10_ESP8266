#if defined(ESP8266)
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#else
#include <WiFi.h>          //https://github.com/esp8266/Arduino
#endif

//needed for library
#include <DNSServer.h>
#if defined(ESP8266)
#include <ESP8266WebServer.h>
#else
#include <WebServer.h>
#endif
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false; 
String payload;
String url="";
void setup() 
{

    Serial.begin(19200);
    for(uint8_t t = 4; t > 0; t--) 
    {
        delay(1000);
    }
    WiFiManager wifiManager;
    wifiManager.autoConnect("P10-CMU");
    Serial.println("Connected");
}

void loop() 
{
   while (Serial.available()) 
  {
    char inChar = (char)Serial.read();    
    if (inChar == '\n' ) 
    {
        stringComplete = true; 
    }
    else
    {
      inputString += inChar;
    }
  }
  
  if (stringComplete ) 
  {   
    url=inputString+".php";    
    if((WiFiMulti.run() == WL_CONNECTED)) 
    {
        HTTPClient http;
        http.begin(url);
        int httpCode = http.GET();
        if(httpCode > 0) 
        {
            if(httpCode == HTTP_CODE_OK) 
            {
                payload = http.getString();
                Serial.print(payload);
                Serial.print(";");
                Serial.print(payload.length());
                Serial.println("!");
                url="";
            }
            else
            {
              Serial.println("NULL1");
              url="";
            }
        } 
        else 
        {
            Serial.println("NULL");
            url="";
        }

        http.end();
    }
    inputString = "";
    stringComplete = false;
  }
}


