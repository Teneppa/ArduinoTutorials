// Sup dis code will listen for numbers with a semicolon after them
// and converts them to the brightness for the LED

void setup() {
  // Open the serial port with the baudrate of 115200
  Serial.begin(115200);

  // Set pin 3 as output (the LED goes here)
  pinMode(3, OUTPUT);
}

void loop() {
  // If there's some data coming through
  if (Serial.available() > 0) {
    // Get the message (I made it to end with a semicolon so that
    // we don't need to listen for the message the entire day)
    String msg = Serial.readStringUntil(';');
    Serial.flush();

    // Convert the message to an integer and save it to this variable
    uint8_t brightness = msg.toInt();

    // Update the LED's brightness
    analogWrite(3, brightness);
  }
}
