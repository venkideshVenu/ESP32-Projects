void setup() {
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
}

void loop() {
  digitalWrite(18, HIGH); 
  digitalWrite(19, LOW); 
  delay(500);             
  digitalWrite(18, LOW); 
  digitalWrite(19, HIGH);  
  delay(500);    
}