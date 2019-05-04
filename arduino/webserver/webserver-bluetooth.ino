#include <SPI.h>
#include <Ethernet.h>
#include <SoftwareSerial.h>

// The IP address will be dependent on your local network:
// Sticker: 90-A2-DA-0F-1D-D3
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x1D, 0xD3 };
IPAddress ip(192, 168, 137, 128);

EthernetServer server(80); // (port 80 is default for HTTP):

SoftwareSerial BTSerial(5, 6);

String data = "";
String tmpData = "";
char tmp;

void setup() {
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  
  Serial.begin(9600);
  BTSerial.begin(38400);
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();

  if(BTSerial.available() > 0) { 
    Serial.print(".");
    tmp = BTSerial.read();
    if(tmp == '`') {
      Serial.print("I recieved: ");
      Serial.println(tmpData);
      data = tmpData;
      tmpData = "";
    } else {
      tmpData.concat(tmp);
    }
  }
  
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Access-Control-Allow-Origin: *");
          client.println();

          client.println(data);
          
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}