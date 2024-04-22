/*
    Go to thingspeak.com and create an account if you don't have one already.
    After logging in, click on the "New Channel" button to create a new channel for your data. This is where your data will be stored and displayed.
    Fill in the Name, Description, and other fields for your channel as desired, then click the "Save Channel" button.
    Take note of the "Write API Key" located in the "API keys" tab, this is the key you will use to send data to your channel.
    Replace the channelID from tab "Channel Settings" and privateKey with "Read API Keys" from "API Keys" tab.
    Replace the host variable with the thingspeak server hostname "api.thingspeak.com"
    Upload the sketch to your ESP32 board and make sure that the board is connected to the internet. The ESP32 should now send data to your Thingspeak channel at the intervals specified by the loop function.
    Go to the channel view page on thingspeak and check the "Field1" for the new incoming data.
    You can use the data visualization and analysis tools provided by Thingspeak to display and process your data in various ways.
    Please note, that Thingspeak accepts only integer values.

    You can later check the values at https://thingspeak.com/channels/2005329
    Please note that this public channel can be accessed by anyone and it is possible that more people will write their values.
 */

#include <WiFi.h>
#include <ArduinoJson.h>
#include <ArduinoJson.hpp>


const char* ssid = "ChinaNet-8C79-WiFi5";  // Change this to your WiFi SSID
const char* password = "5a63r364";         // Change this to your WiFi password

const char* host = "192.168.71.139";            // This should not be changed
const int httpPort = 8008;                      // This should not be changed
const String channelID = "2005329";             // Change this to your channel ID
const String writeApiKey = "V6YOTILH9I7D51F9";  // Change this to your Write API key
const String readApiKey = "34W6LGLIFXD56MPM";   // Change this to your Read API key

const int waterPumpPin = 19;
int waterPumpStatus = LOW;

// The default example accepts one data filed named "field1"
// For your own server you can ofcourse create more of them.
int field1 = 0;

int numberOfResults = 3;  // Number of results to be read
int fieldNumber = 1;      // Field number which will be read out

void setup() {
  Serial.begin(115200);
  while (!Serial) { delay(100); }

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println("******************************************************");
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(waterPumpPin, OUTPUT);
}

void readGetUserResponse(WiFiClient* client) {
  unsigned long timeout = millis();
  while (client->available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client->stop();
      return;
    }
  }


  String line;
  // Read all the lines of the reply from server and print them to Serial
  while (client->available()) {
    line = client->readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println(line);

  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, line);
  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  const char* email = doc[0]["email"];
  const char* firstName = doc[0]["first_name"];
  // const uint8_t firstName = doc[0]["first_name"];

  Serial.print("email: ");
  Serial.println(email);

  Serial.print("firstName: ");
  Serial.println(firstName);

  Serial.printf("\nClosing 2 connection\n\n");
}

void getUser(WiFiClient* client) {
  String footer = String(" HTTP/1.1\r\n") + "Host: " + String(host) + "\r\n" + "Connection: close\r\n\r\n";
  client->print("GET /get_users" + footer);
}

void loop() {
  WiFiClient client;

  // WRITE --------------------------------------------------------------------------------------------
  if (!client.connect(host, httpPort)) {
    return;
  }

  getUser(&client);
  readGetUserResponse(&client);

  if (waterPumpStatus == LOW) {
    waterPumpStatus = HIGH;
  } else {
    waterPumpStatus = LOW;
  }
  digitalWrite(waterPumpPin, waterPumpStatus);

  Serial.print("waterPumpStatus: ");
  Serial.println(waterPumpStatus);


  // READ --------------------------------------------------------------------------------------------

  // -------------------------------------------------------------------------------------------------

  ++field1;
  delay(3000);
}