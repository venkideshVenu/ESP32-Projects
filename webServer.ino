#include <WiFi.h>           // Include the WiFi library for ESP32
#include <WiFiClient.h>      // Include the WiFiClient library for handling client connections
#include <WebServer.h>       // Include the WebServer library for creating an HTTP server
#include <uri/UriBraces.h>   // Include UriBraces for handling dynamic routes in the web server

#define WIFI_SSID "[Network SSID]"       // Replace with your WiFi SSID
#define WIFI_PASSWORD "[PASSWORD]"       // Replace with your WiFi password
#define WIFI_CHANNEL 6                   // Define the WiFi channel for faster connection

// Create a web server object that listens on port 80 (HTTP)
WebServer server(80);

// Define the pins for the two LEDs
const int LED1 = 18;
const int LED2 = 19;

// Variables to store the state of the LEDs (false = OFF, true = ON)
bool led1State = false;
bool led2State = false;

// Function to send the HTML page to the client
void sendHtml() {
  // HTML response as a multi-line string (R"()" syntax to make it readable)
  String response = R"(
    <!DOCTYPE html><html>
      <head>
        <title>ESP32 Web Server Demo</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          html { font-family: sans-serif; text-align: center; }
          body { display: inline-flex; flex-direction: column; }
          h1 { margin-bottom: 1.2em; } 
          h2 { margin: 0; }
          div { display: grid; grid-template-columns: 1fr 1fr; grid-template-rows: auto auto; grid-auto-flow: column; grid-gap: 1em; }
          .btn { background-color: #5B5; border: none; color: #fff; padding: 0.5em 1em;
                 font-size: 2em; text-decoration: none }
          .btn.OFF { background-color: #333; }
        </style>
      </head>
            
      <body>
        <h1>ESP32 Web Server</h1>

        <div>
          <h2>LED 1</h2>
          <a href="/toggle/1" class="btn LED1_TEXT">LED1_TEXT</a>
          <h2>LED 2</h2>
          <a href="/toggle/2" class="btn LED2_TEXT">LED2_TEXT</a>
        </div>
      </body>
    </html>
  )";

  // Replace placeholders with actual LED states (ON or OFF)
  response.replace("LED1_TEXT", led1State ? "ON" : "OFF");
  response.replace("LED2_TEXT", led2State ? "ON" : "OFF");

  // Send the response to the client with a status code of 200 (OK) and content type "text/html"
  server.send(200, "text/html", response);
}

void setup(void) {
  Serial.begin(115200);  // Initialize the serial monitor with a baud rate of 115200

  // Set the pin modes for the LEDs to OUTPUT
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);

  // Start the WiFi connection using the defined SSID, password, and channel
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
  Serial.print("Connecting to WiFi ");
  Serial.print(WIFI_SSID);

  // Wait until the ESP32 is connected to WiFi
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println(" Connected!");

  // Print the IP address of the ESP32 once connected to WiFi
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Define the root ("/") URL to serve the HTML page
  server.on("/", sendHtml);

  // Define a dynamic route to toggle LEDs using the UriBraces syntax (e.g., /toggle/1, /toggle/2)
  server.on(UriBraces("/toggle/{}"), []() {
    String led = server.pathArg(0);  // Get the argument (LED number) from the URL
    Serial.print("Toggle LED #");
    Serial.println(led);

    // Toggle the state of the selected LED based on its number (1 or 2)
    switch (led.toInt()) {
      case 1:
        led1State = !led1State;  // Toggle LED 1 state
        digitalWrite(LED1, led1State);  // Set the LED 1 state (HIGH or LOW)
        break;
      case 2:
        led2State = !led2State;  // Toggle LED 2 state
        digitalWrite(LED2, led2State);  // Set the LED 2 state (HIGH or LOW)
        break;
    }

    // Send the updated HTML page after toggling the LED
    sendHtml();
  });

  // Start the web server
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  // Handle client requests
  server.handleClient();
  delay(2);  // Small delay to ensure smooth handling of requests
}
