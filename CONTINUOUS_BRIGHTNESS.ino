// Store the current brightness of the LED (0 - 255)
uint8_t brightness = 0;

// Store the last state that the button was in
bool oldButton = false;

// Store the time on when the button was first pressed so we can figure
// out the duration of the press
long btnTimer = 0;

// If the button is being pressed, we want to keep track on the duration
// so that we can change the brightness
bool bChangeBrightness = false;

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
      // Save the time of when the button was first pressed so that we know how long the button was pressed
      btnTimer = millis();
      bChangeBrightness = true;
    }

    if(button == false) {
      bChangeBrightness = false;    
    }

    // Save the state that the button is in
    oldButton = button;
  }

  // We want to change the brightness here
  if(bChangeBrightness) {
    // How long has the button been pressed (in milliseconds)
    long elapsed = millis() - btnTimer;

    // If the press was shorter than 200 ms, turn the LED OFF
    if(elapsed < 200) {
      brightness = 0;
    }

    // If the press was in the range of 200 to 1000 milliseconds, we want to map the brightness
    // accordingly
    if(elapsed > 200 && elapsed < 1000) {
      brightness = map(elapsed, 200, 1000, 0, 255);
    }

    // If the press was longer than 1000 milliseconds, we want to make sure that the LED
    // is on with the full brightness
    if(elapsed > 1000) {
      brightness = 255;
    }
    
    // Update the LED's brightness
    analogWrite(3, brightness);
  }
  
}
