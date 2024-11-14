#include <Wire.h>
#include <RTClib.h>
#include <TM1637Display.h>

#define CLK 26  // TM1637 Clock pin (IO26)
#define DIO 25  // TM1637 Data pin (IO25)

RTC_DS3231 rtc;
TM1637Display display(CLK, DIO);

const int buzzerPin = 16; // Buzzer pin (IO16)
const int buttonPin = 17; // Button pin to stop the alarm

int alarmHour = 21;    // Default alarm time set to 07:00
int alarmMinute = 49;  // Default alarm minute
bool alarmSet = true; // Alarm initially set to true for testing

unsigned long lastButtonPress = 0;  // To store the last button press time
const unsigned long debounceDelay = 200; // Debounce delay (200 milliseconds)
bool alarmTriggered = false;  // Flag to track if alarm is currently ringing

void setup() {
  Serial.begin(115200);

  // Initialize RTC module
  Wire.begin(18, 19); // RTC: SDA = IO18, SCL = IO19
  if (!rtc.begin()) {
    Serial.println("RTC module not found!");
    while (1);
  }

  // Buzzer and button pin setup
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Set display brightness
  display.setBrightness(0x0f);

  // Print the initial alarm time to serial
  Serial.print("Alarm set to: ");
  Serial.print(alarmHour);
  Serial.print(":");
  Serial.println(alarmMinute);
}

void loop() {
  // Get the current time from the RTC
  DateTime now = rtc.now();
  int currentHour = now.hour();
  int currentMinute = now.minute();

  // Display the current time on the 7-segment display
  int displayTime = (currentHour * 100) + currentMinute;
  display.showNumberDecEx(displayTime, 0b01000000, true);

  // Check if it's time to trigger the alarm
  if (alarmSet && currentHour == alarmHour && currentMinute == alarmMinute && !alarmTriggered) {
    digitalWrite(buzzerPin, HIGH); // Activate the buzzer
    Serial.println("Alarm triggered!");
    alarmTriggered = true;  // Set the flag to indicate the alarm is ringing
  }

  // Check if the button is pressed to stop the alarm (single press detection with debounce)
  if (alarmTriggered && digitalRead(buttonPin) == LOW && (millis() - lastButtonPress) > debounceDelay) {
    lastButtonPress = millis();  // Update last button press time
    digitalWrite(buzzerPin, LOW); // Turn off the buzzer
    alarmSet = false;             // Completely disable the alarm
    alarmTriggered = false;       // Reset the alarm triggered flag
    Serial.println("Alarm stopped and disabled.");
  }

  delay(100); // Short delay before the next loop iteration
}
