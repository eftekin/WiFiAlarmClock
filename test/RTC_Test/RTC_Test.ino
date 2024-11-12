#include <Wire.h>
#include <RTClib.h>

// Create an RTC_DS3231 object
RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud rate

  // Initialize the RTC
  if (!rtc.begin()) {
    Serial.println("RTC module not found!");
    while (1);  // Halt the program if the RTC is not found
  }

  // If you want to set the time (run this only once)
  // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Set the RTC to the compile time

  // Alternatively, set the time manually:
  // rtc.adjust(DateTime(2024, 1, 1, 12, 0, 0));  // Set the date and time: (Year, Month, Day, Hour, Minute, Second)
}

void loop() {
  // Get the current time from the RTC
  DateTime now = rtc.now();

  // Print the time to the serial monitor
  Serial.print("Time: ");
  Serial.print(now.hour(), DEC);     // Print the hour
  Serial.print(":");
  Serial.print(now.minute(), DEC);   // Print the minute
  Serial.print(":");
  Serial.print(now.second(), DEC);   // Print the second
  Serial.print("  Date: ");
  Serial.print(now.day(), DEC);      // Print the day
  Serial.print("/");
  Serial.print(now.month(), DEC);    // Print the month
  Serial.print("/");
  Serial.println(now.year(), DEC);   // Print the year

  delay(1000);  // Wait for 1 second before updating the time
}
