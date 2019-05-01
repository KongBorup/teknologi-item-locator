// NOTE: VERY MESSY AND IS TO BE CLEANED UP AND FINISHED

#include <SPI.h>
#include <Ethernet.h>
//#include <SD.h>

// Shown on website
//File website;

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
// Sticker: 90-A2-DA-0F-1D-D3
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x1D, 0xD3 };
IPAddress ip(192,168,137,128); //<<< ENTER YOUR IP ADDRESS HERE!!!

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  /*
  Serial.begin(9600);
  Serial.print("Initializing SD card...");

  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(10, OUTPUT);
   
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  */
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  
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

          /*website = SD.open("index.htm");
          
          if (website) {
            // read from the file until there's nothing else in it:
            while (website.available()) {
              client.write(website.read());
            }
            // close the file:
            website.close();
          } else {
            // if the file didn't open, print an error:
            Serial.println("error opening index.htm");
          }

          client.println();
          
          //client.println("<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"></head><body>fml</body></html>");
          */

          /*
          // White house
          float lat = 38.897957;
          float lon = -77.036560;
          */
          float lat = 15.57364;
          float lon = 108.47403;
          
          client.print("{\"lat\":");
          client.print(lat, 6);
          client.print(",\"long\":");
          client.print(lon, 6);
          client.print("}");
          client.println();
          
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
