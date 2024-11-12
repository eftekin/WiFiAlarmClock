#include <TM1637Display.h>

// 7-Segment Display Pin Definitions
#define CLK 2  // Clock Pin
#define DIO 3  // Data Pin

// Initialize the TM1637 display
TM1637Display display(CLK, DIO);

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Start the TM1637 display (no additional setup required)
}

void loop() {
  // Display numbers from 0000 to 9999 on the 7-segment display
  for (int i = 0; i < 10000; i++) {
    display.showNumberDec(i);  // Display the number on the screen
    delay(50);  // Show each number for 50ms
  }
}
