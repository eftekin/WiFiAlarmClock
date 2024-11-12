#include <TM1637Display.h>

// Pin definitions for the 7-segment display
#define CLK 2  // Clock pin
#define DIO 3  // Data pin

// Create the display object
TM1637Display display(CLK, DIO);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize the display
  display.setBrightness(7);  // Set maximum brightness
  display.showNumberDec(1234, false);  // Display a test number
}

void loop() {
  // Display numbers from 0 to 9999
  for (int i = 0; i < 10000; i++) {
    display.showNumberDec(i, false);  // Show the number on the display
    delay(50);  // Wait for 1 second before updating the number
  }
}
