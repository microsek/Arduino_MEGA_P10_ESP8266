#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false; 
String payload;
String url1="http://192.168.1.6/msg1.php";
String url2="http://192.168.1.6/msg2.php";
String url3="http://192.168.1.6/msg3.php";
void setup() 
{

    Serial.begin(19200);
    for(uint8_t t = 4; t > 0; t--) 
    {
        delay(1000);
    }
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("Microsek-WIFI", "0810243789");
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
    if((WiFiMulti.run() == WL_CONNECTED)) 
    {
        HTTPClient http;
       switch(inputString.toInt()) 
       {
        case 1:
          http.begin(url1); //http://192.168.1.6/cmd5.php
          break;
        case 2:
          http.begin(url2); //http://192.168.1.6/cmd5.php
          break;
        case 3:
          http.begin(url3); //http://192.168.1.6/cmd5.php
          break;
       }
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
            }
            else
            {
              Serial.println("NULL");
            }
        } 
        else 
        {
            Serial.println("NULL");
        }

        http.end();
    }
    inputString = "";
    stringComplete = false;

   //delay(2000);
  }

}


