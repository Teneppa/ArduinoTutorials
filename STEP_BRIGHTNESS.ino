
// Store the current brightness of the LED (0 - 255)
uint8_t brightness = 0;

// Store the last state that the button was in
bool oldButton = false;

/* =============== THIS THING RUNS ONCE WHEN BOOTING =============== */
void setup() {
  
  // Set the button as an input and activate
  // the internal pull-up resistor (when we press the button it connects to ground [LOW]),
  // and when whe relase it the pullup resistor pulls it back up to HIGH
  pinMode(2, INPUT_PULLUP);

  // Set the LED as an output
  pinMode(3, OUTPUT);
}

/* =============== THIS THING LOOPS AROUND UNTIL THE POWER IS CUT =============== */
void loop() {
  // Read the state of the button, invert it, and then store it to the variable
  // called "button"
  bool button = !digitalRead(2);

  // If the button has changed it's state
  if(button != oldButton) {

    // If the button was pressed, NOT RELEASED
    if(button == true) {
      
      // If less than 224, increase by 32
      // 0, 32, 64, 96, 128, 160, 192, but NOT 224
      if(brightness < 224) {
        brightness += 32;
      }
      
      // If the brightness is at max set it to 0
      if(brightness == 255) {
        brightness = 0;
      }
      
      // If the brightness is at 224, set it to max
      if(brightness == 224) {
        brightness = 255;
      }
    }

    // Update the LED's brightness
    analogWrite(3, brightness);

    // Save the state that the button is in
    oldButton = button;
  }
}
