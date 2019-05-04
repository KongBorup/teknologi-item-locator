#include <nRF905.h> // IMPORTANT: SOURCE CODE HAS BEEN EDITED -- PIN 10 -> PIN 6
#include <SPI.h>
#include <Ethernet.h>

// RADIO VARIABLES
#define RXADDR 0x586F2E10 // Address of this device
#define TXADDR 0xFE4CA6E5 // Address of device to send to

#define PACKET_NONE    0
#define PACKET_OK   1
#define PACKET_INVALID  2

static volatile uint8_t packetStatus;

// WEB SERVER VARIABLES
// Sticker: 90-A2-DA-0F-1D-D3
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0F, 0x1D, 0xD3 };
IPAddress ip(192, 168, 137, 128);

EthernetServer server(80); // (port 80 is default for HTTP)

uint8_t newestCoords[NRF905_MAX_PAYLOAD];

void setup() {
  Serial.begin(115200);
  
  // Start up
  nRF905_init();
  // Set address of this device
  nRF905_setListenAddress(RXADDR);
  // Put into receive mode
  nRF905_RX();
  Serial.println(F("Radio listener started"));
  
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.println(F("Web server started"));
}

void loop() {
  nRF905_RX();

  if (packetStatus == PACKET_OK) {
    packetStatus = PACKET_NONE;

    // resets array in memory
    memset(newestCoords, 0, sizeof(newestCoords));
    // save data buffer
    nRF905_read(newestCoords, sizeof(newestCoords));

    Serial.print(F("Newest coordinates: "));
    Serial.write(newestCoords, sizeof(newestCoords));
    Serial.println();
  } else {
    packetStatus = PACKET_NONE;
    nRF905_RX();
  }
  
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

          for (unsigned int i = 0; i < NRF905_MAX_PAYLOAD; i++)
            client.write(newestCoords[i]);
          client.println();
          
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
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

// RADIO FUNCTIONS
void NRF905_CB_RXCOMPLETE(void) {
  packetStatus = PACKET_OK;
  nRF905_standby();
}

void NRF905_CB_RXINVALID(void) {
  packetStatus = PACKET_INVALID;
  nRF905_standby();
}