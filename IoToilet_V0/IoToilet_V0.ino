// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "wifi SSID";
const char* password = "wifi password";

// Set web server port number to 80
WiFiServer server(80);                          

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state 
int LDRRead = 0;
String LDRState = "unoccupied";
// Assign output variables to GPIO pins
const int LDRpin = 14;

void setup() {
  Serial.begin(115200);
  delay(3000); 
  // Initialize the output variables as outputs
  pinMode(LDRpin, INPUT);     

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
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

            LDRRead = digitalRead(LDRpin);
            if (LDRRead == HIGH) {
              // state = high = no light;
              //digitalWrite(LEDpin,LOW);
              //    Serial.println("unoccupied");
              LDRState = "unoccupied";
            }
            else  {
              //  state = low = light present;
              //digitalWrite(LEDpin, HIGH);
                                                                                                              Serial.println("occupied");
              LDRState = "occupied";
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            //client.println("<meta http-equiv=\"refresh\" content=\"30\"></head>");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            //client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            //client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");

            // Web Page Hea1ding
            client.println("<body><h1>IoToilet</h1>");

            // Display current state, and ON/OFF buttons for GPIO 5
            client.println("<p>The Comfort Room is " + LDRState + "</p>");

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
