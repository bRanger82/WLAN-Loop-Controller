
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

/* Set these to your desired credentials. */
const char *ssid = "ESPap";
const char *password = "test";

const int GPIO0 = 0;
const int GPIO2 = 2;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() 
{
  String s = "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  s += "<link rel=\"icon\" href=\"data:,\">";
  s += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}";
  s += ".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;";
  s += "text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}";
  s += ".button2 {background-color: #77878A;}</style></head>";
  s += "<body><h1>ESP8266 Web Server</h1>";
  s += "<p>GPIO 0 - State</p>";
  if (digitalRead(GPIO0) == HIGH)
  {
    s += "<p><a href=\"/0/off\"><button class=\"button button2\">OFF</button></a></p>";
  } else
  {
    s += "<p><a href=\"/0/on\"><button class=\"button\">ON</button></a></p>";
  }
  s += "<p>GPIO 2 - State</p>";
  if (digitalRead(GPIO2) == HIGH)
  {
    s += "<p><a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>";
  } else
  {
    s += "<p><a href=\"/2/on\"><button class=\"button\">ON</button></a></p>";
  }
  s += "</body></html>";
	server.send(200, "text/html", s);
}

void redirectPage()
{
  String s = "<head>";
  s += "<meta http-equiv=\"refresh\" content=\"0;url=http://192.168.4.1\">"; 
  s += "</html>";
  server.send(200, "text/html", s);server.send(200, "text/html", s);
}

void handleGPIO0Off()
{
  digitalWrite(0, LOW);
  redirectPage();
}

void handleGPIO0On()
{
  digitalWrite(0, HIGH);
  redirectPage();
}

void handleGPIO2Off()
{
  digitalWrite(2, LOW);
  redirectPage();
}

void handleGPIO2On()
{
  digitalWrite(2, HIGH);
  redirectPage();
}

void setup() 
{
  pinMode(GPIO0, OUTPUT);
  pinMode(GPIO2, OUTPUT);
  digitalWrite(GPIO0, LOW);
	digitalWrite(GPIO2, LOW);
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
  server.on("/0/off", handleGPIO0Off);
  server.on("/0/on", handleGPIO0On);
  server.on("/2/off", handleGPIO2Off);
  server.on("/2/on", handleGPIO2On);  
	server.begin();
	Serial.println("HTTP server started");
}

void loop() 
{
	server.handleClient();
}
