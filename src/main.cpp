/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi
 
 */

#define maxLength     20  // header length, don't make it to long; Arduino doesn't have much memory

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);

String httpHeader;
int arg = 0, val = 0;        // to store get/post variables from the URL (argument and value, http:\\192.168.1.3\website?p8=1)

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

// GET-vars after "?"   192.168.1.3/?p8=1
// GET /?p1=1 HTTP/1.1
// parse header. Argument starts with p (only p2 .. p9)
// input:  header = HTTPheader from client
// output: a = argument (p8)
// output: v = value (1)
bool parseHeader(String header, int &a, int &v)
{
    Serial.println("DEBUG");
    Serial.println(header.substring(6, 7));
    Serial.println(header.substring(7, 8));
    Serial.println(header.substring(9, 10));
    Serial.println("END DEBUG");


    if (header.substring(6, 7) == "p")
    {
      a = header.substring(7, 8).toInt();
      v = header.substring(9, 10).toInt();
      Serial.println("It's a text-based file");
      return true;
    }
    return false;
}

void setup() {
  // You can use Ethernet.init(pin) to configure the CS pin
  //Ethernet.init(10);  // Most Arduino shields
  //Ethernet.init(5);   // MKR ETH shield
  //Ethernet.init(0);   // Teensy 2.0
  //Ethernet.init(20);  // Teensy++ 2.0
  //Ethernet.init(15);  // ESP8266 with Adafruit Featherwing Ethernet
  //Ethernet.init(33);  // ESP32 with Adafruit Featherwing Ethernet

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Ethernet WebServer Example");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

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

  // start the server
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        //store characters to string
        if (httpHeader.length() < maxLength) httpHeader += c;  // don't need to store the whole Header
        //Serial.write(c);                                     // for debug only
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          //client.println("Refresh: 1");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          //grab commands from the url
          client.println("<P>");
          if (parseHeader(httpHeader, arg, val)) {   // search for argument and value, eg. p8=1
              //Serial.print(arg); Serial.print(" "); Serial.println(val);  // for debug only
              digitalWrite(arg, val);                // Recall: pins 10..13 used for the Ethernet shield
              client.print("Pin ");client.print(arg); client.print(" = "); client.println(val);
          }
          else client.println("No IO-pins to control");
          client.println("</P>");
          
          client.println("</html>");
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
    httpHeader = "";
    Serial.println("client disconnected");
  }
}
