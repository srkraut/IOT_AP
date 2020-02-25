#include <ESP8266WiFi.h>
// Replace with your network credentials
// to create its own wifi network
const char* ssid     = "HAMRO";
const char* password = "hamro123";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
//this pins for esp32 
//change the pins for esp8266
String batti1State = "off";
String batti2State = "off";
String batti3State = "off";
String batti4State = "off";

// Assign output variables to GPIO pins
const int batti1 = D5;
const int batti2 = D6;
const int batti3 = D7;
const int batti4 = D8;


void setup() {
  Serial.begin(9600);
  // Initialize the output variables as outputs
  pinMode(batti1, OUTPUT);
  pinMode(batti2, OUTPUT);
  pinMode(batti3, OUTPUT);
  pinMode(batti4, OUTPUT);
 
  // Set outputs to high because we are using active low type relay module
  digitalWrite(batti1, LOW);
  digitalWrite(batti2, LOW);
  digitalWrite(batti3, LOW);
  digitalWrite(batti4, LOW);


  // Connect to Wi-Fi network with SSID and password
  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            //foe GPIO12
            if (header.indexOf("GET /12/on") >= 0) 
            {
              Serial.println("GPIO 12 on");
              batti1State = "on";
              digitalWrite(batti1, HIGH);
            } 
            else if (header.indexOf("GET /12/off") >= 0) 
            {
              Serial.println("GPIO 12 off");
              batti1State = "off";
              digitalWrite(batti1, LOW);
            }

            //for GPIO13
            else if (header.indexOf("GET /13/on") >= 0)
            {
              Serial.println("GPIO 13 on");
              batti2State = "on";
              digitalWrite(batti2, HIGH);
            } 
            else if (header.indexOf("GET /13/off") >= 0)
            {
              Serial.println("GPIO 13 off");
              batti2State = "off";
              digitalWrite(batti2, LOW);
            }
            
             
             
             //for GPIO14
             else if (header.indexOf("GET /14/on") >= 0)
            {
              Serial.println("GPIO 14 on");
              batti3State = "on";
              digitalWrite(batti3, HIGH);
            } 
            else if (header.indexOf("GET /14/off") >= 0)
            {
              Serial.println("GPIO 14 off");
              batti3State = "off";
              digitalWrite(batti3, LOW);
            }

          
            
            
            //for GPIO27
            else if (header.indexOf("GET /27/on") >= 0)
            {
              Serial.println("GPIO 27 on");
              batti4State = "on";
              digitalWrite(batti4, HIGH);
            } 
            else if (header.indexOf("GET /27/off") >= 0)
            {
              Serial.println("GPIO 27 off");
              batti4State = "off";
              digitalWrite(batti4, LOW);
            }
          
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Hamro Home Automation </h1>");
            
           
                 
            // Display current state, and ON/OFF buttons for GPIO 12  
            client.println("<p>Batti 1 - State " + batti1State + "</p>");
            // If the batti1State is off, it displays the ON button       
            if (batti1State=="off") {
              client.println("<p><a href=\"/12/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
    // Display current state, and ON/OFF buttons for GPIO 13 
            client.println("<p>Batti 2 - State " + batti2State + "</p>");
            // If the batti2State is off, it displays the ON button       
            if (batti2State=="off") {
              client.println("<p><a href=\"/13/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/13/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

    // Display current state, and ON/OFF buttons for GPIO 14  
            client.println("<p>Batti 3 - State " + batti3State + "</p>");
            // If the batti3State is off, it displays the ON button       
            if (batti3State=="off") {
              client.println("<p><a href=\"/14/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/14/off\"><button class=\"button button2\">OFF</button></a></p>");
            }


               client.println("<p>Batti 4 - State " + batti4State + "</p>");
            // If the batti4State is off, it displays the ON button       
            if (batti4State=="off") {
              client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            }

            
         client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}