# Wi-Fi Alarm Clock ⏰

A simple Wi-Fi connected alarm clock built with ESP32, RTC (DS3231), 7-segment display, and a buzzer. Set the alarm time through a web interface and stop it with a button. 🚨

## Features:

- **Wi-Fi Connectivity** 🌐: Connect to your network for easy remote alarm setup.
- **RTC Module** 🕒: Accurate timekeeping with DS3231.
- **7-Segment Display** 💡: Displays current time in a 24-hour format.
- **Web Interface** 💻: Set alarm time via an easy-to-use webpage.
- **Alarm Function** 🔊: Buzzer sounds when the alarm time is reached.
- **Button to Stop** 🔘: Turn off the alarm by pressing the button.

## Components Used:

- **ESP32**: Microcontroller running the project.
- **DS3231 RTC**: Precise timekeeping.
- **TM1637 7-Segment Display**: Displays the time.
- **Buzzer**: Sounds the alarm.
- **Button**: Stop the alarm.

## Setup & Installation 🛠️

### Hardware Setup:

1. **RTC Module (DS3231)**:
   - SDA to IO18
   - SCL to IO19
2. **TM1637 Display**:
   - CLK to IO26
   - DIO to IO25
3. **Buzzer**: Connect to IO16.
4. **Button**: Connect to IO17.

### Software Setup:

1. Install libraries:
   - `Wire.h`
   - `RTClib.h`
   - `WiFi.h`
   - `WebServer.h`
   - `TM1637Display.h`
2. Replace Wi-Fi credentials (`ssid` & `password`) with your network details.

### How to Use:

1. Upload the code to your ESP32 via Arduino IDE.
2. Open the serial monitor to get the IP address of the ESP32.
3. Enter the IP address in a browser to access the web interface.
4. Set the alarm time on the webpage.
5. When the time comes, the buzzer will ring. 🔔
6. Press the button to stop the alarm. 🚫

## License 📜

This project is licensed under the MIT License.

## Acknowledgments 🙏

- ESP32 for IoT applications.
- DS3231 for accurate time.
- TM1637 for the display.
- Arduino community for open-source libraries.
