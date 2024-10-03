
#define LED 2

void setup() {
  // Set pin mode
  pinMode(LED,OUTPUT);
  Serial.println("Hello, ESP32!");
}

void loop() {
  delay(2000);
  digitalWrite(LED,HIGH);
  delay(2000);
  digitalWrite(LED,LOW);
}
