// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "wifi SSID";
const char* password = "wifi password";

// IFTTT setup for Slack
const char *host = "maker.ifttt.com";
String CRloc = "Your Location";
String Maker_Event = "Maker_Event";         //Maker Event for Slack
String Your_Key = "Your_Key";               //Webhook key for Slack

// If you want to add another Maker event and Key:
// IFTTT setup for Twitter
String Maker_Event2 = "Maker_Event2";  //Maker Event for Twitter
String Your_Key2 = "Your_Key2";  //Webhook key for Twitter

// Assign output variables to GPIO pins
const int LDRpin = 14;

// Auxiliar variables to store the current output state
int LDRRead;
int LDRState = 1;
int lastLDRState = 1;
String  printState = "OCCUPIED";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  // Initialize the output variables as outputs
  pinMode(LDRpin, INPUT);
  Serial.begin(115200);
  delay(3000);
  wifiConnect();
}

void loop() {
  LDRRead = digitalRead(LDRpin);
  Serial.print("Read: ");
  Serial.println(LDRRead);
  Serial.print("State: ");
  Serial.println(LDRState);

  // If the switch changed, due to noise or pressing:
  if (LDRRead != lastLDRState) {
    // reset the debouncing timer
    Serial.println("if LDRRead != lastLDRState");
    lastDebounceTime = millis();
  }
  if (LDRRead != lastLDRState) {
    //if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    Serial.println("if (millis() - lastDebounceTime) > debounceDelay");
    // if the button state has changed:
    if (LDRRead != LDRState) {
      Serial.println("if LDRState");
      LDRState = LDRRead;
      slackMessage(LDRState);     // Send http request to Post on Slack
      sendTweet(LDRState);        // Send http request to Post on Twitter
    }
  }
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastLDRState = LDRState;
  Serial.print("Last State: ");
  Serial.println(lastLDRState);
  Serial.println("------------");
  delay(1000);
}

void wifiConnect() {
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
}

void slackMessage(int State) {
  if (State == HIGH) {
    // state = high = no light;
    printState = "VACANT";
    Serial.println(printState);     //for debugging
  }
  else  {
    //  state = low = light present;
    printState = "OCCUPIED";
    Serial.println(printState);     //for debugging    
  }
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  while (!client.connect(host, httpPort)) {
    delay(500);
    Serial.print(".");
  }
  // create URL request
  // https://maker.ifttt.com/trigger/IoToilet/with/key/Your_Key/?value1=LG&value2=unoccupied
  String url = "/trigger/" + Maker_Event + "/with/key/" + Your_Key + "/?value1=" + CRloc + "&value2=" + printState;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  // Read all the lines of the reply from server and print them to Serial
  while (client.connected()) {
    if (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    else {
      // No data yet, wait a bit
      delay(50);
    };
  }
  Serial.println();
  Serial.println("closing connection");
}

void sendTweet(int State) {
  if (State == HIGH) {
    // state = high = no light;
    printState = "VACANT";
    Serial.println(printState);     //for debugging
  }
  else  {
    //  state = low = light present;
    printState = "OCCUPIED";
    Serial.println(printState);     //for debugging
  }
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  while (!client.connect(host, httpPort)) {
    delay(500);
    Serial.print(".");
  }
// create URL request
// https://maker.ifttt.com/trigger/IoToilet_tweet/with/key/Your_Key/?value1=LG&value2=unoccupied
  String url = "/trigger/" + Maker_Event2 + "/with/key/" + Your_Key2 + "/?value1=" + CRloc + "&value2=" + printState;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  // Read all the lines of the reply from server and print them to Serial
  while (client.connected()) {
    if (client.available()) {
      String line = client.readStringUntil('\r');
      Serial.print(line);
    }
    else {
      // No data yet, wait a bit
      delay(50);
    };
  }
  Serial.println();
  Serial.println("closing connection");
}

