#include <Wire.h>
#include <RTClib.h>
#include <WiFi.h>
#include <WebServer.h>
#include <TM1637Display.h>

#define CLK 26  // TM1637 Clock pin (IO26)
#define DIO 25  // TM1637 Data pin (IO25)

// Wi-Fi credentials
const char* ssid = "asd";
const char* password = "123";

// Alarm hour and minute settings
int alarmHour = 7;    // Default alarm time set to 07:00
int alarmMinute = 0;
bool alarmSet = false; // Is the alarm set?

// Modules
RTC_DS3231 rtc;
TM1637Display display(CLK, DIO);
WebServer server(80);

const int buzzerPin = 16; // Buzzer pin (IO16)
const int buttonPin = 17; // Button pin to stop the alarm (IO17)

// Web page content
String webpage = "<html><head><title>Alarm Setup</title>"
                 "<style>"
                 "body { font-family: Arial, sans-serif; text-align: center; }"
                 "h1 { color: #333; }"
                 "form { margin: 20px auto; width: 300px; padding: 20px; border: 1px solid #ddd; background: #f9f9f9; }"
                 "label { display: block; font-weight: bold; margin: 10px 0 5px; }"
                 "input[type='number'] { width: 100%; padding: 8px; margin: 5px 0 10px; }"
                 "input[type='submit'] { padding: 10px 20px; font-size: 16px; color: #fff; background-color: #5cb85c; border: none; cursor: pointer; }"
                 "</style>"
                 "</head><body><h1>Set Alarm</h1>"
                 "<form action=\"/setalarm\" method=\"POST\">"
                 "<label>Alarm Hour: </label><input type=\"number\" name=\"hour\" min=\"0\" max=\"23\" required><br>"
                 "<label>Alarm Minute: </label><input type=\"number\" name=\"minute\" min=\"0\" max=\"59\" required><br>"
                 "<input type=\"submit\" value=\"Set Alarm\">"
                 "</form><p><a href=\"/\">Home</a></p>";

String alarmSetPage = "<html><body><h2>Alarm Set to: ";

String getAlarmTime() {
  return String(alarmHour) + ":" + (alarmMinute < 10 ? "0" : "") + String(alarmMinute);
}

// Connect to Wi-Fi
void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Display the main webpage
void handleRoot() {
  server.send(200, "text/html", webpage);
}

// Alarm setup function
void handleSetAlarm() {
  if (server.hasArg("hour") && server.hasArg("minute")) {
    alarmHour = server.arg("hour").toInt();
    alarmMinute = server.arg("minute").toInt();
    alarmSet = true;
    Serial.print("Alarm set to ");
    Serial.print(alarmHour);
    Serial.print(":");
    Serial.println(alarmMinute);
    String pageContent = alarmSetPage + getAlarmTime() + "</h2><p><a href=\"/\">Back to Home</a></p></body></html>";
    server.send(200, "text/html", pageContent);
  } else {
    server.send(400, "text/html", "<html><body><h2>Invalid Input</h2><p><a href=\"/\">Back to Home</a></p></body></html>");
  }
}

// Stop the alarm function
void stopAlarm() {
  digitalWrite(buzzerPin, LOW); // Turn off the buzzer
  alarmSet = false;             // Reset the alarm
  Serial.println("Alarm stopped.");
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();

  // Initialize the RTC module
  Wire.begin(18, 19); // RTC: SDA = IO18, SCL = IO19
  if (!rtc.begin()) {
    Serial.println("RTC module not found!");
    while (1);
  }

  // Buzzer and button pin setup
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  // Display setup
  display.setBrightness(0x0f); // Set brightness (0x00 - 0x0f)

  // Web server
  server.on("/", handleRoot);
  server.on("/setalarm", HTTP_POST, handleSetAlarm);
  server.begin();

  Serial.println("Web server active!");
}

void loop() {
  server.handleClient(); // Handle incoming web requests

  // Get the current time from the RTC
  DateTime now = rtc.now();
  int currentHour = now.hour();
  int currentMinute = now.minute();

  // Display the time on the 7-segment display
  int displayTime = (currentHour * 100) + currentMinute;
  display.showNumberDecEx(displayTime, 0b01000000, true);

  // Check the alarm
  static bool alarmTriggered = false; // Flag to track if alarm was triggered
  if (alarmSet && currentHour == alarmHour && currentMinute == alarmMinute) {
    if (!alarmTriggered) {
      digitalWrite(buzzerPin, HIGH); // Activate the alarm sound
      Serial.println("Alarm time!");
      alarmTriggered = true; // Set flag to avoid multiple messages
    }
  }

  // Stop the alarm if the button is pressed
  if (digitalRead(buttonPin) == LOW) {
    stopAlarm();
    alarmTriggered = false; // Reset alarmTriggered flag
  }
}
