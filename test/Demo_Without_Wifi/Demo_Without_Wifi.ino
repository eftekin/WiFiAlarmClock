#include <Wire.h>
#include <RTClib.h>
#include <TM1637Display.h>

// Pin definitions
#define CLK 2          // TM1637 Clock pin
#define DIO 3          // TM1637 Data pin
#define BUZZER_PIN 4   // Buzzer pin
#define BUTTON_PIN 5   // Button pin

// Create TM1637 and RTC objects
TM1637Display display(CLK, DIO);
RTC_DS3231 rtc;

// Variables for alarm time
const int alarmHour = 22;   // Alarm hour (e.g., 22:50)
const int alarmMinute = 50;
bool alarmActive = true;    // Variable to check if the alarm is active

// Define melody and durations
const int melody[] = {262, 294, 330, 349, 392, 440, 494, 523}; // Frequencies of notes (C4, D4, E4, F4, G4, A4, B4, C5)
const int noteDurations[] = {500, 500, 500, 500, 500, 500, 500, 500}; // Duration of each note (in milliseconds)

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("RTC module not found!");
    while (1);
  }

  // Initialize TM1637 display
  display.setBrightness(7);  // Maximum brightness

  // Set up buzzer and button pins
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);  // Start with buzzer off
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Use internal pull-up resistor
}

void playMelody() {
  unsigned long startMillis = millis();  // Start the timer
  int noteCount = sizeof(melody) / sizeof(melody[0]);

  for (int i = 0; i < noteCount; i++) {
    // Stop melody if button is pressed
    if (digitalRead(BUTTON_PIN) == LOW) {
      alarmActive = false;  // Deactivate the alarm
      noTone(BUZZER_PIN);   // Turn off the buzzer
      Serial.println("Alarm Stopped!");
      return;
    }

    tone(BUZZER_PIN, melody[i]);         // Play note on the buzzer
    delay(noteDurations[i]);             // Wait for the note duration
    noTone(BUZZER_PIN);                  // Stop the note
    delay(50);                           // Short delay between notes

    // Stop the alarm if 1 minute has passed
    if (millis() - startMillis >= 60000) {
      noTone(BUZZER_PIN);                // Turn off the buzzer
      alarmActive = false;               // Deactivate the alarm
      Serial.println("Alarm duration expired, stopping!");
      return;
    }
  }
}

void loop() {
  // Get the time from RTC
  DateTime now = rtc.now();

  // Display the hour and minute in "HHMM" format
  int displayTime = (now.hour() * 100) + now.minute();
  display.showNumberDecEx(displayTime, 0b01000000, true);

  // Print the time to the serial monitor
  Serial.print("Time: ");
  Serial.print(now.hour());
  Serial.print(":");
  Serial.println(now.minute());

  // Check if it's time for the alarm
  if (alarmActive && now.hour() == alarmHour && now.minute() == alarmMinute) {
    playMelody();  // Play the melody
  }

  delay(1000);  // Check every second
}
