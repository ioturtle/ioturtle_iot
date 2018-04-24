#include <ESP8266WiFi.h>

#include <ArduinoJson.h>

const char* ssid = "WiFi_SSID";
const char* password = "WiFi_Password";

///////////////// Edit these to Line to Match your server configuration ////////////////////////////
const char* host = "ioturtle.com"; // Your domain

String path = "/api/status/YOYR_API_KEY";

//****************************************************************************************************
// Define Your Digital Pin Here ///////////////////////////////////////////////////////////////////

 

#define device1 D0

#define device2 D1

#define device3 D2

#define device4 D3

//****************************************************************************************************
void setup() {

pinMode(device1, OUTPUT);pinMode(device2, OUTPUT);pinMode(device3, OUTPUT);pinMode(device4, OUTPUT);\

digitalWrite(device1, HIGH);digitalWrite(device2, HIGH);digitalWrite(device3, HIGH);digitalWrite(device4, HIGH);

Serial.begin(115200); delay(10);


Serial.print("Connecting to ");

Serial.println(ssid);

 

WiFi.begin(ssid, password);

int wifi_ctr = 0;

while (WiFi.status() != WL_CONNECTED) {

delay(500);

//digitalWrite(2,1);

Serial.print(".");

}

 

Serial.println("WiFi connected");

Serial.println("IP address: " + WiFi.localIP());

//digitalWrite(2,0);

}

 

void loop() {

Serial.print("connecting to ");

Serial.println(host);

WiFiClient client;

const int httpPort = 80;

if (!client.connect(host, httpPort)) {

Serial.println("connection failed");

return;

}

client.print(String("GET ") + path + " HTTP/1.0\r\n" +

"Host: " + host + "\r\n" +

"Connection: keep-alive\r\n\r\n");

 

delay(3000); // wait for server to respond

 

// read response

String section="header";

while(client.available()){

String line = client.readStringUntil('\r');

// Serial.print(line);

// well parse the HTML body here

if (section=="header") { // headers..

Serial.print(".");

if (line=="\n") { // skips the empty space at the beginning

section="json";

}

}

else if (section=="json") { // print the good stuff

section="ignore";

String result = line.substring(1);

 

// Parse JSON

int size = result.length() + 1;

char json[size];

result.toCharArray(json, size);

StaticJsonBuffer<200> jsonBuffer;

JsonObject& json_parsed = jsonBuffer.parseObject(json);

if (!json_parsed.success())

{

Serial.println("parseObject() failed");

return;

}
//#####################################################################################################################

if (strcmp(json_parsed["status1"], "off") == 0)

{

digitalWrite(device1, HIGH);

Serial.println("First Device Off");

}

else {

digitalWrite(device1, LOW); Serial.println("First Device On");

}
if (strcmp(json_parsed["status2"], "off") == 0)

{

digitalWrite(device2, HIGH);

Serial.println("Second Device Off");

}

else {

digitalWrite(device2, LOW); Serial.println("Second Device On");

}
if (strcmp(json_parsed["status3"], "off") == 0)

{

digitalWrite(device3, HIGH);

Serial.println("Third Device Off");

}

else {

digitalWrite(device3, LOW); Serial.println("Third Device On");

}

if (strcmp(json_parsed["status4"], "off") == 0)

{

digitalWrite(device4, HIGH);

Serial.println("Fourth Device Off");

}

else {

digitalWrite(device4, LOW); Serial.println("Fourth Device On");

}

//#######################################################################################################################

}

}

Serial.print("closing connection. ");

}
