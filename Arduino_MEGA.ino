#include <SPI.h>
#include <DMD2.h>
#include <fonts/SystemFont5x7.h>
#include <fonts/Arial14.h>
#include "Arial_Black_16_ISO_8859_1.h"

// Set Width to the number of displays wide you have
char MESSAGE[100]="Welcome to CMU Display ";
char *P10_MESSAGE;
const int WIDTH = 2; /*2 is Set number of display panel*/
String speed_display="100"; /*Seed of display panel*/
String ESP8266_data;     /* a String to hold incoming data from esp8266 */
String ESP8266_data_buffer = "";     /* a String to hold incoming data from esp8266 */
String Bluetooth_data = "";   /* a String to hold incoming data from Bluetooth */
String Message_appened="";       /* a String appened esp8266 data and bluetooth data */
boolean esp8266_even = false;   /* whether the string from esp8266 is complete */
boolean bluetooth_even = false;   /* whether the string from esp8266 is complete */
const uint8_t *FONT_Arial14 = Arial14; /* set front variable */
const uint8_t *FONT_SystemFont5x7 = SystemFont5x7; /* set front variable*/
const uint8_t *FONT_Arial_Black_16_ISO_8859_1 = Arial_Black_16_ISO_8859_1; /* set front variable*/
int i;  

SoftDMD dmd(WIDTH,1);  /* DMD controls the entire display */
DMD_TextBox box(dmd);  /* "box" provides a text box to automatically write to/scroll the display */

// the setup routine runs once when you press reset:
void setup() 
{
  Serial.begin(19200);// for monitor
  Serial1.begin(19200);// connect ESP8266
  Serial2.begin(19200);// connect BlueTooth
  dmd.setBrightness(255);
  dmd.selectFont(FONT_Arial_Black_16_ISO_8859_1);
  dmd.begin();
P10_MESSAGE=MESSAGE;
}

/*======= the loop routine runs over and over again forever: =====*/
void loop() 
{
  
   if (bluetooth_even) 
   {
      Serial.print("Serial Bluetooth=");
      Serial.print(Bluetooth_data);
      Serial.print(" Lenght=");
      Serial.println(Bluetooth_data.length());
      Message_appened=Bluetooth_data;
      Bluetooth_data = "";
      bluetooth_even = false;
   }

  while (Serial1.available()) 
  {
    char inChar = (char)Serial1.read();
    if (inChar == '\n') 
    {
      esp8266_even = true;
    }
    else
    {
      ESP8266_data_buffer += inChar;
    }
  }
   if (esp8266_even) 
   {
      String Lenght_Str_IN;
      Serial.print("Serial in=");
      Serial.print(ESP8266_data_buffer);
      Lenght_Str_IN=ESP8266_data_buffer.substring(ESP8266_data_buffer.indexOf(';')+1, ESP8266_data_buffer.indexOf('!'));
      ESP8266_data=ESP8266_data_buffer.substring(1, Lenght_Str_IN.toInt());
      speed_display=ESP8266_data.substring(ESP8266_data.indexOf('[')+1, ESP8266_data.indexOf(']'));
      switch(speed_display.toInt()) 
      {
        case 1:
          speed_display="50"; break;
        case 2:
          speed_display="100"; break;
        case 3:
          speed_display="200"; break;
        default:
          speed_display="200"; break;
      }
      Message_appened=ESP8266_data.substring(1, ESP8266_data.indexOf('[')+1);
      Serial.print("Lenght_Str_I=");
      Serial.print(Lenght_Str_IN);
      Serial.print(" Message_appened=");
      Serial.print(Message_appened);
      Serial.print(" speed_display=");
      Serial.print(speed_display);
      Serial.print(" Lenght Message_appened=");
      Serial.println(Message_appened.length());
      ESP8266_data_buffer="";  
      esp8266_even = false;
   }
      
  Message_appened.toCharArray(MESSAGE, Message_appened.length());
  P10_MESSAGE=MESSAGE;
  while(*P10_MESSAGE) 
  {
    //Serial.print(*P10_MESSAGE);
    box.print(*P10_MESSAGE);
    delay(speed_display.toInt());
    P10_MESSAGE++;
  }
  Message_appened="";
}

/*====================== Get data from BlueTooth ===================*/
void serialEvent2() 
{
  while (Serial2.available()) 
  {
    char inChar = (char)Serial2.read();
    if (inChar == '\n') 
    {
      bluetooth_even = true;
    }
    else
    {
      Bluetooth_data += inChar;
    }    
  }
}
