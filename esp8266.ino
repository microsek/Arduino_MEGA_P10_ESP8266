#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {

    Serial.begin(19200);
    for(uint8_t t = 4; t > 0; t--) {
        delay(1000);
    }
    WiFi.mode(WIFI_STA);
    WiFiMulti.addAP("Microsek-WIFI", "0810243789");
}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {
        HTTPClient http;
        http.begin("http://192.168.1.5/cmd5.php"); //HTTP
        int httpCode = http.GET();
        if(httpCode > 0) 
        {
            if(httpCode == HTTP_CODE_OK) 
            {
                String payload = http.getString();
                Serial.print(payload);
                Serial.print(";");
                Serial.print(payload.length());
                Serial.println("!");
                //Serial.print(";");
            }
        } 
        else 
        {
            //Serial.println("NULL");
            //Serial.print(";");
        }

        http.end();
    }

    delay(2000);
}

