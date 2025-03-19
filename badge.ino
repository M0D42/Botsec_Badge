#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

IPAddress ap(192, 168, 1, 1); // The IP address of the AP
const byte DNS_PORT = 53; // Port for DNS server
DNSServer dns_server; // DNS server
ESP8266WebServer webserver(80); // Web server on port 80

#define LED 2 // Pin for LED

// HTML response string
String response_html = R"rawliteral(
<!DOCTYPE html>
<html>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
<head>
  <title>welcome to new menbers ,botsec :) </title>
</head>
<body>
  <h3>Hi  welcome to BotSec you can join heres in the website and browse a bit ;) </h3>
  <a href="https://s1gnal42.github.io/botsec/index.html">Click or drag click on iphone</a>
</body>
<style>
  Body{
    background-color: black;
    text-align: center;
    color:aliceblue ;
    font-family:monospace;
  }
  a{
    color: green;
    text-decoration: none;
    font-family:monospace;
    font-size: larger;
  }
</style>
</html>
)rawliteral";

const char* password = "123456789"; // Password for the AP
const char* ssid = "Hacking Challenge hack to join"; // SSID of the AP

void setup() {
    Serial.begin(9600);
    WiFi.mode(WIFI_AP); // Set WiFi mode to Access Point
    WiFi.softAPConfig(ap, ap, IPAddress(255, 255, 255, 0));
    WiFi.softAP(ssid, password); // Create wireless access point

    dns_server.start(DNS_PORT, "*", ap); // Start DNS server to redirect all DNS requests to the AP

    webserver.onNotFound([]() {
        webserver.send(200, "text/html", response_html); // Serve HTML page
    });

    pinMode(LED, OUTPUT); // Set LED pin as output
    digitalWrite(LED,HIGH);
      digitalWrite(LED,LOW);
    webserver.begin(); // Start web server
}

void loop() {
    dns_server.processNextRequest(); // Handle DNS requests
    webserver.handleClient(); // Handle web server requests

    int connected = WiFi.softAPgetStationNum(); // Get number of connected stations

    // Turn the LED on if there are connected clients, off otherwise
    digitalWrite(LED, connected-1 > 0 ? HIGH : LOW);

}

