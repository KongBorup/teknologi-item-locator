//this is slave

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <SoftwareSerial.h>

static const int RXPin = 6, TXPin = 5;
static const uint32_t GPSBaud = 9600;

double latDecimalDegree;
int latDegree;
int latMinut;
double latSec;

double lonDecimalDegree;
int lonDegree;
int lonMinut;
double lonSec;

String payload = "";
String seperator = ",";

SoftwareSerial BTSerial(10, 11);
TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);

void setup() 
{
  BTSerial.begin(38400);
  Serial.begin(9600);
  
  ss.begin(GPSBaud);

  Serial.println("Slave has started");
}

void loop() 
{
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.println("Getting data");
      latDecimalDegree = gps.location.lat();
      latDegree = floor(gps.location.rawLat().deg);
      latMinut = floor(60*(latDecimalDegree-latDegree));
      latSec = 3600*(latDecimalDegree-latDegree)-60*latMinut;
      
      lonDecimalDegree = gps.location.lng();
      lonDegree = floor(gps.location.rawLng().deg);
      lonMinut = floor(60*(lonDecimalDegree-lonDegree));
      lonSec = 3600*(lonDecimalDegree-lonDegree)-60*lonMinut;
      
      payload += "[[";
      payload += latDegree;
      payload += seperator;
      payload += latMinut;
      payload += seperator;
      payload += latSec;
      payload += seperator;
      payload += gps.location.rawLat().negative ? "S" : "N";
      payload += "],[";
      
      payload += lonDegree;
      payload += seperator;
      payload += lonMinut;
      payload += seperator;
      payload += lonSec;  
      payload += seperator;
      payload += gps.location.rawLng().negative ? "W" : "E";
      payload += "]]";
      
      char data[payload.length() + 1];
      payload.toCharArray(data, payload.length());
        
      Serial.print(F("Sending data: "));
      Serial.println(data);

      BTSerial.write(data);
      BTSerial.write('`');
      
      Serial.println("Waiting");
      delay(1000);
      payload = "";
      Serial.println("----------------------\n\n");
    }  
  }
}
