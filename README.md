# Adaptive-Silent-Communication-System-Using-Vibration-Pattern-Recognition


##  Student Details

**Name:** Jhansi Pujari
**Course Opted:** Embedded Systems & IoT
**Instructor/Guide Name:** Ms. Mehak Majeed
**Duration:** 6 Months
**Organization:** SURE Trust, Puttaparthi, Andhra Pradesh

## 🛠️ Technologies & Tools Used

ESP32 • C • ESP-IDF • ESP-NOW • SSD1306 OLED • FreeRTOS • GPIO • Visual Studio Code

## 📝 Project Overview

This project presents a silent wireless communication system designed using two ESP32 microcontrollers. The transmitter converts short and long button presses into predefined communication patterns such as S, L, SL, SLS, and LSS. The generated patterns are transmitted wirelessly to the receiver using ESP-NOW. The receiver recognizes the received pattern, displays the corresponding message on an SSD1306 OLED display, and provides vibration feedback.

## 🚀 Key Technical Features

**ESP-NOW Communication:** Enables direct wireless communication between two ESP32 devices without requiring a Wi-Fi router or Internet connection.

**Short/Long Pattern Generation:** Converts button press duration into S (Short) and L (Long) communication symbols.

**Pattern Recognition:** Matches the received communication pattern with predefined patterns stored in the receiver.

**OLED Display:** Displays the recognized pattern and its corresponding predefined message on an SSD1306 OLED display.

**Vibration Feedback:** Provides tactile feedback after successful pattern recognition.

**Real-Time Processing:** Performs continuous input detection, wireless transmission, pattern recognition, and feedback using ESP32 and FreeRTOS.

## 🧩 Hardware Architecture

**Transmitter Unit:** ESP32 Development Board + Push Button
**Wireless Communication:** ESP-NOW
**Receiver Unit:** ESP32 Development Board
**Display:** SSD1306 128×64 OLED Display
**Feedback:** Vibration Motor
**Interconnection:** Breadboard + Jumper Wires

## ⚙️ Operational Workflow

**Input:** The user generates short and long button presses.

**Pattern Generation:** The transmitter converts the button presses into S and L symbols and forms a predefined communication pattern.

**Wireless Transmission:** The generated pattern is transmitted to the receiver using ESP-NOW.

**Pattern Recognition:** The receiver compares the received pattern with the predefined pattern database.

**Message Display:** The corresponding message is displayed on the SSD1306 OLED display.

**Vibration Feedback:** The vibration motor provides tactile confirmation after successful communication.

**Example:** `SLS → NEED HELP`

## 🔮 Future Enhancements

* Expansion of predefined communication patterns.
* Bidirectional communication between transmitter and receiver.
* Multiple vibration patterns for different messages.
* Improved wireless communication range.
* Compact and portable hardware design.
* Enhanced pattern recognition and customization.
