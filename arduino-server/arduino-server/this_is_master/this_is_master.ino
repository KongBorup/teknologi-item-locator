//this is master

#include <SoftwareSerial.h>

SoftwareSerial BTSerial(5, 11);

String recieved = "";
char tmp;
void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);

  Serial.println("Master has started");
}
void loop() 
{
 if(BTSerial.available() > 0)
 { 
    Serial.print(".");
    tmp = BTSerial.read();
    if(tmp == '`') {
      Serial.print("I recieved: ");
      Serial.println(recieved);
      recieved = "";
    } else {
      recieved.concat(tmp);
    }
 }
}
