#include "WiFi.h"  // Include the WiFi library for ESP32

void setup() {
  // Initialize the Serial communication at 115200 baud rate
  Serial.begin(115200);
  
  Serial.println("Initializing WiFi...");
  
  // Set the WiFi mode to station mode (WIFI_STA), so the ESP32 can scan networks
  WiFi.mode(WIFI_STA);
  
  Serial.println("Setup done!");
}

void loop() {
  Serial.println("Scanning...");

  // Scan for nearby WiFi networks and store the number of networks found
  int n = WiFi.scanNetworks();
  
  Serial.println("Scan done!");
  
  // If no networks are found, print a message
  if (n == 0) {
    Serial.println("No networks found.");
  } else {
    // If networks are found, print the number of networks
    Serial.println();
    Serial.print(n);
    Serial.println(" networks found");

    // Loop through each network found
    for (int i = 0; i < n; ++i) {
      // Print the network index (starting from 1), SSID, and RSSI (signal strength)
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));  // Print SSID of the network
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));  // Print RSSI value (signal strength)
      Serial.print(")");
      
      // Check if the network is secured (if it's not open, print an asterisk)
      Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");

      // Small delay to avoid printing too fast
      delay(10);
    }
  }
  // Print an empty line to separate scans
  Serial.println("");
  // Wait 5 seconds before scanning again
  delay(5000);
}