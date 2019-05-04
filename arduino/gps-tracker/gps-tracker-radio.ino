#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <nRF905.h>

#define RXADDR 0xFE4CA6E5 // Address of this device
#define TXADDR 0x586F2E10 // Address of device to send to

#define TIMEOUT 1000 // 1 second ping timeout

#define PACKET_NONE    0
#define PACKET_OK   1
#define PACKET_INVALID  2

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
String seperator = "-";

TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(9600);
  Serial.println(F("Client started"));
  
  nRF905_init(); 
  ss.begin(GPSBaud);
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
          
      Serial.print(F("Sending data: "));
      Serial.println(payload);
      
      char data[payload.length() + 1];
      payload.toCharArray(data, payload.length());

      while(!nRF905_TX(TXADDR, data, sizeof(data), NRF905_NEXTMODE_RX));
      
      Serial.println("Data sent\nWaiting");
      delay(1000);
      payload = "";
      Serial.println("----------------------\n\n");
    }  
  }
}