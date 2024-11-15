# Wi-Fi Alarm Clock ⏰

A **Wi-Fi-enabled alarm clock** powered by the Wemos D1 R32 (ESP32), DS3231 RTC module, TM1637 7-segment display, and a buzzer. Set the alarm remotely via a sleek web interface and stop it with a button. 🚨

---

## 🌟 Features

- **Wi-Fi Connectivity**: Set alarms remotely through a browser.
- **Accurate Timekeeping**: Powered by the DS3231 RTC module.
- **Clear Display**: 7-segment display shows the current time in 24-hour format.
- **Web Interface**: User-friendly webpage for alarm setup.
- **Alarm Functionality**: Buzzer rings when the alarm time is reached.
- **Stop Button**: Press a physical button to turn off the alarm.

---

## 🛠️ Getting Started

### 1. Arduino IDE Setup

1. Open the Arduino IDE and navigate to **Settings**.
2. In the **Additional Board Manager URLs** field, add the following link:  
   [https://espressif.github.io/arduino-esp32/package_esp32_index.json](https://espressif.github.io/arduino-esp32/package_esp32_index.json)
3. Go to **Tools > Board > Boards Manager**, search for `ESP32`, and install the package.

### 2. Hardware Connections

Connect the components as follows:

| Component             | Pin on ESP32             |
| --------------------- | ------------------------ |
| **RTC (DS3231)**      | SDA to IO18, SCL to IO19 |
| **7-Segment Display** | CLK to IO26, DIO to IO25 |
| **Buzzer**            | IO16                     |
| **Button**            | IO17                     |

Refer to the included **circuit diagram** below for a visual guide.

### 3. Uploading the Code

1. Install the following libraries in Arduino IDE:

   - `Wire.h`
   - `RTClib.h`
   - `WiFi.h`
   - `WebServer.h`
   - `TM1637Display.h`

2. Replace `ssid` and `password` in the code with your Wi-Fi credentials.
3. Upload the code to your Wemos D1 R32 board.

### 4. Running the Project

1. Open the **Serial Monitor** to find the ESP32's IP address.
2. Enter the IP address in your browser to access the alarm setup interface.
3. Set the desired alarm time through the webpage.
4. When the time is reached, the buzzer will sound. Press the button to stop it.

---

## 🔌 Circuit Diagram

Below is the **circuit diagram** created in Fritzing. Click the image to view or download the file:

<img src="https://github.com/user-attachments/assets/e6565743-5f55-40f7-8bf3-edaf4fd62857" alt="smartwifi" width="400"/>

---

## 📂 Test Files

Test individual components of the project using these files from the [test folder](https://github.com/eftekin/WiFiAlarmClock/tree/main/test):

- **[Demo_Without_Wifi](https://github.com/eftekin/WiFiAlarmClock/blob/main/test/Demo_Without_Wifi)**: Simulates the project’s functionality without Wi-Fi.
- **[Display_Test](https://github.com/eftekin/WiFiAlarmClock/blob/main/test/Display_Test)**: Tests the 7-segment display.
- **[RTC_Test](https://github.com/eftekin/WiFiAlarmClock/blob/main/test/RTC_Test)**: Ensures the RTC module works correctly.
- **[Wemos_Test](https://github.com/eftekin/WiFiAlarmClock/blob/main/test/Wemos_Test)**: Tests Wemos hardware integration.

---

## 📜 License

This project is licensed under the **MIT License**.
