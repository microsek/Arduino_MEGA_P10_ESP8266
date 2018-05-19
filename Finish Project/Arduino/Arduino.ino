#include <DMD3.h>
#include <Arial_Black_16_ISO_8859_1.h>
#include <Mono5x7.h>

#define OE 11
#define Panel 2
#define Brightness 250
#define Max_msg 4

String speed_display="10";
String msg[Max_msg];
String Bluetooth_data="";
String Bluetooth_in="";
bool BlueTooth_even = false;
String Loop_display_bluetooth;
String old_msg[Max_msg];
bool NO_WIFI=false;

DMD3 display(Panel,1);

void drawMarquee(String message_out);
/*================== Interrupt Timer1 ========================================*/
void scan()
{
    display.refreshP10S();
    Timer1.pwm(OE,Brightness);
}
/*=================== Setup ===================================================*/
void setup() 
{
    Timer1.initialize(2000);
    Timer1.attachInterrupt(scan);
    Timer1.pwm(OE,Brightness);
    Serial.begin(9600);  // for monitor debug
    Serial1.begin(9600); // connect to BlueTooth
    Serial2.begin(19200); // Connect to ESP8266
    attachInterrupt(0,serialEvent1, CHANGE);
}
/*==================== loop ====================================================*/
void loop() 
{
    attachInterrupt(0,serialEvent1, CHANGE); // open interrupt 0
    for(int i=1;i<4;i++)                     // loop read message from database
    {
      read_message(i);                       // calll function read database
      if(NO_WIFI)                            // if wifi off show old data
      {
        drawMarquee(old_msg[i]);             // show old data
      }
      delay(100);
    }
}
/*==================== display message =========================================*/
void drawMarquee(String message_out)
{
    char message[100];
    message_out.toCharArray(message, 100);
    int width = display.width();
    display.setFont(Arial_Black_16_ISO_8859_1);
    int msgWidth = display.textWidth(message);
    int fullScroll = msgWidth + width + 1;
    for (int x = 0; x < fullScroll; ++x) 
    {
      display.clear();
      display.drawText(width - x, 0, message);
      delay(speed_display.toInt());
    }
}
/*====================== Get data from BlueTooth on serial1 ================================*/
void serialEvent1() 
{
  detachInterrupt(0);
  while (Serial1.available()) 
  {
    char inChar = (char)Serial1.read();
    if (inChar == '\n') 
    {
      Loop_display_bluetooth=Bluetooth_in.substring(Bluetooth_in.indexOf(';')+1); // Format => "data";loop [Ex:Test Bluetooth;3]
      Bluetooth_data=Bluetooth_in.substring(0, Bluetooth_in.indexOf(';'));        // cut sring from 0 to ;
      for(int l=0;l<Loop_display_bluetooth.toInt();l++)                           // show message from blutooth
      {
        drawMarquee(Bluetooth_data);
      }
      Bluetooth_data = "";
      Bluetooth_in="";
    }
    else
    {
      Bluetooth_in += inChar;
    }    
  }
}
/*===================== Read message from data base via ESP8266 on serial2 =============================*/
void read_message(int cmd)
{
  String message_in="";
  String message="";
  String Lenght_Str_IN;
  String start_string="";
  Serial2.print("http://192.168.1.6/msg"+String(cmd));
  Serial2.write(0x0a);
  while (Serial2.available()) 
  {
    char inChar = (char)Serial2.read();
    if (inChar == '\n') 
    {
        Lenght_Str_IN=message_in.substring(message_in.indexOf(';')+1, message_in.indexOf('!')); /* Lenght of string in */
        message=message_in.substring(1, Lenght_Str_IN.toInt());                                 /* cut message from 1 to lenght */
        speed_display=message.substring(message.indexOf('[')+1, message.indexOf(']'));          /* cut speed */
        switch(speed_display.toInt()) 
        {
          case 1:
            speed_display="30"; break;
          case 2:
            speed_display="20"; break;
          case 3:
            speed_display="10"; break;
          default:
            speed_display="10"; break;
        } 
        start_string=message.substring(message.indexOf('<'),message.indexOf('<')+1);
        if(start_string=="<")
        {
          msg[cmd]=message.substring(message.indexOf('<')+1, message.indexOf("["));               /* cut string to display */
          drawMarquee(msg[cmd]);
          old_msg[cmd]=msg[cmd];
          message="";
          message_in="";  
          NO_WIFI=false;        
        }
        else
        {
          NO_WIFI=true;
        }
    } 
    else
    {
      message_in += inChar;
      msg[cmd]="";
    }    
  }  
}
