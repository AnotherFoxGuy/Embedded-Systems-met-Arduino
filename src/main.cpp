#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
IPAddress ip(192, 168, 1, 10);  //fallback ipadress
EthernetServer server(11000);   //server port

void setup()
{
  Serial.begin(9600);  
  //no dhcp >> use ip given above
  if (Ethernet.begin(mac) == 0) {
    Serial.println("No DHCP");
    Ethernet.begin(mac, ip);
  }

   // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }
  
  server.begin();
  Serial.print("Server ip is: "); Serial.println(Ethernet.localIP());
}

void loop()
{
  EthernetClient client = server.available();
  if (client) 
  {
    Serial.println("New client connected");
    while (client.connected()) 
    {       
      if (client.available()) 
      {
        char buffer [256];
        sprintf (buffer, "<TEMP> %d", analogRead(0));
        Serial.println(buffer);
        server.write(buffer);
        client.stop();
      }     
    }
    Serial.println("Client disconnected");
  }
}
