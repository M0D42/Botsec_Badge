# Botsec Badge

This repository contains code for an ESP8266-based badge that creates a WiFi access point. It serves a web page welcoming users to the BotSec community and provides a link to the BotSec website.

## Components

- ESP8266 module (e.g., NodeMCU, Wemos D1 Mini)
- LED
- Wires and breadboard
- Power supply

## Wiring

- Connect an LED to GPIO pin 2 on the ESP8266.

## Code Explanation

The code includes the following functionalities:

- Setting up the ESP8266 as a WiFi access point with a specific SSID and password.
- Running a DNS server to handle DNS requests and redirect them to the access point.
- Running a web server to serve a welcome HTML page.
- Controlling an LED based on the number of connected clients.

### Code Breakdown

1. **Include Libraries**
    ```cpp
    #include <Arduino.h>
    #include <ESP8266WiFi.h>
    #include <DNSServer.h>
    #include <ESP8266WebServer.h>
    ```

2. **Define Network and Server Variables**
    ```cpp
    IPAddress ap(192, 168, 1, 1); // The IP address of the AP
    const byte DNS_PORT = 53; // Port for DNS server
    DNSServer dns_server; // DNS server
    ESP8266WebServer webserver(80); // Web server on port 80
    ```

3. **Define Hardware and HTML Content**
    ```cpp
    #define LED 2 // Pin for LED

    String response_html = R"rawliteral(
    <!DOCTYPE html>
    <html>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <head>
      <title>welcome to new members ,botsec :) </title>
    </head>
    <body>
      <h3>Hi  welcome to BotSec you can join here in the website and browse a bit ;) </h3>
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
    ```

4. **Setup Function**
    ```cpp
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
        digitalWrite(LED, HIGH);
        digitalWrite(LED, LOW);
        webserver.begin(); // Start web server
    }
    ```

5. **Loop Function**
    ```cpp
    void loop() {
        dns_server.processNextRequest(); // Handle DNS requests
        webserver.handleClient(); // Handle web server requests

        int connected = WiFi.softAPgetStationNum(); // Get number of connected stations

        // Turn the LED on if there are connected clients, off otherwise
        digitalWrite(LED, connected - 1 > 0 ? HIGH : LOW);
    }
    ```

## How to Use

1. Upload the code to the ESP8266 module.
2. Connect the hardware components as per the wiring instructions.
3. Power the ESP8266 module.
4. The ESP8266 will create a WiFi access point with the SSID "Hacking Challenge hack to join" and password "123456789".
5. Connect to the access point from a WiFi-enabled device.
6. Open any web browser and visit any URL, you will be redirected to a welcome page with a link to the BotSec website.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
