// Define the pins connected to the seven segments (A-G) of the display
const int segmentPins[] = {16, 17, 18, 19, 21, 22, 23};  // Pins for segments A-G

// Digits 0-9 in binary representation for a common cathode display
const byte digitCodes[10] = {
  // A  B  C  D  E  F  G (bitwise mapping of each segment)
  0b00111111,  // 0
  0b00000110,  // 1
  0b01011011,  // 2
  0b01001111,  // 3
  0b01100110,  // 4
  0b01101101,  // 5
  0b01111101,  // 6
  0b00000111,  // 7
  0b01111111,  // 8
  0b01101111   // 9
};

void setup() {
  // Set each segment pin as an OUTPUT
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {
  // Loop through digits 0 to 9
  for (int digit = 0; digit <= 9; digit++) {
    displayDigit(digit);  // Display the current digit on the seven-segment display
    delay(1000);          // Wait for 1 second before displaying the next digit
  }
}

// Function to display a digit on the seven-segment display
void displayDigit(int digit) {
  byte segments = digitCodes[digit];  // Get the segment code for the digit

  // Loop through each segment (A-G)
  for (int i = 0; i < 7; i++) {
    // Write HIGH or LOW to the segment pins based on the bit in 'segments'
    // For common cathode, HIGH turns on the segment, LOW turns it off
    digitalWrite(segmentPins[i], (segments & (1 << i)) ? HIGH : LOW);
  }
}
