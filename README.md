# Demo Video : https://youtu.be/4lIo-_HLwI4?si=84_xpetgZaO4iB7U
# 🚗 ESP32 Car - WiFi Remote Control

A smart car powered by ESP32 that can be controlled via WiFi from any mobile phone or computer.

## 📋 Table of Contents

* [Project Overview](#-project-overview)
* [Features](#-features)
* [Components Required](#-components-required)
* [Circuit Diagram](#-circuit-diagram)
* [Installation](#-installation)
* [Usage](#-usage)
* [How It Works](#-how-it-works)
* [Troubleshooting](#-troubleshooting)
* [Code Customization](#-code-customization)
* [Learning Resources](#-learning-resources)
* [Contributing](#-contributing)
* [License](#-license)
* [Author](#-author)
* [Support](#-support)

---

## 🎯 Project Overview

This project is a remote-controlled car built using the ESP32 microcontroller. You can control the car via WiFi from your mobile phone or laptop. The ESP32 hosts a web server that provides a simple, responsive interface with:

* Forward, Backward, Left, Right buttons
* Stop button
* Speed control slider

---

## ✨ Features

* 📱 **Web-based Remote Control**
* 🎮 **Easy-to-use Controls**
* ⚡ **Adjustable Speed Control**
* 📶 **WiFi Connectivity**
* 🎨 **Responsive Web Design**
* 🔄 **Real-time Interaction**

---

## 🛠️ Components Required

### Electronics

1. **ESP32 Development Board** (1x)
2. **L298N Motor Driver Module** (1x)
3. **DC Gear Motors** (2x or 4x)
4. **Robot Car Chassis** (1x)
5. **Wheels** (4x)
6. **18650 Batteries** (2x) or **9V Battery** (1x)
7. **Battery Holder** (1x)
8. **Jumper Wires**
9. **Breadboard** (Optional)

### Tools

* Soldering Iron (optional)
* Screwdriver
* Wire Stripper

---

## 🔌 Circuit Diagram

### ESP32 to L298N Motor Driver

```
ESP32 Pin    →    L298N Pin    →    Function
GPIO 27      →    IN1          →    Motor 1 Direction
GPIO 26      →    IN2          →    Motor 1 Direction
GPIO 25      →    IN3          →    Motor 2 Direction
GPIO 33      →    IN4          →    Motor 2 Direction
GPIO 14      →    ENA          →    Motor 1 Speed (PWM)
GPIO 12      →    ENB          →    Motor 2 Speed (PWM)
GND          →    GND          →    Ground
```

### L298N to Motors

```
OUT1, OUT2   →    Left Motors  
OUT3, OUT4   →    Right Motors  
```

### Power Supply

```
Battery (+)  →    L298N 12V Input  
Battery (-)  →    L298N GND  
L298N 5V Out →    ESP32 5V  
```

---

## 💻 Installation

### Step 1: Arduino IDE Setup

1. **Download Arduino IDE**

   * [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

2. **Add ESP32 Board Manager**

   * Open Arduino IDE → File → Preferences
   * In "Additional Board Manager URLs", add:

     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```

3. **Install ESP32 Board**

   * Tools → Board → Boards Manager
   * Search for "esp32"
   * Install **ESP32 by Espressif Systems**

---

### Step 2: Upload Code

1. Open `esp32_car_remote.ino` in Arduino IDE.
2. Replace WiFi credentials:

   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
3. Select the board:

   * Tools → Board → ESP32 Arduino → "ESP32 Dev Module"
4. Select the port (ESP32 connected via USB).
5. Click **Upload** and wait until complete.

---

### Step 3: Hardware Assembly

1. Mount motors, wheels, ESP32, and L298N on the chassis.
2. Connect wires according to the circuit diagram.
3. Connect the power supply (battery).

---

## 🎮 Usage

1. Power on the car.
2. Open **Serial Monitor** in Arduino IDE (baud rate: 115200).
3. Note the ESP32’s **IP address** (e.g., 192.168.1.100).
4. Connect your phone/laptop to the same WiFi.
5. Open the IP address in a web browser.
6. Control the car using the web interface:

   * ▲ Forward
   * ▼ Backward
   * ◄ Left
   * ► Right
   * ⬛ STOP
   * Speed Slider

---

## 🔧 How It Works

1. ESP32 connects to WiFi and starts a web server.
2. You access the server via browser using the ESP32’s IP address.
3. Pressing a button sends an HTTP request to the ESP32.
4. ESP32 interprets the request and sets motor control pins.
5. L298N motor driver amplifies the signal.
6. Motors rotate, and the car moves.

---

## 🐛 Troubleshooting

* **ESP32 not connecting to WiFi** → Check SSID/password, WiFi strength, or move closer to the router.
* **Car not moving** → Verify connections, check battery charge, confirm correct pins in code.
* **No IP address** → Reset ESP32 and recheck Serial Monitor (baud 115200).
* **Web interface not loading** → Ensure same WiFi network, try `http://<IP>`, clear cache.
* **Car speed issues** → Adjust speed slider, change `dutyCycle` in code, or check battery voltage.

---

## 📚 Code Customization

* **Change Initial Speed:**

  ```cpp
  int dutyCycle = 200;  // Value between 0-255 (default: 200)
  ```
* **Change Pin Numbers:**

  ```cpp
  const int motor1Pin1 = 27;
  const int motor1Pin2 = 26;
  ```
* **Switch to AP Mode:**

  ```cpp
  WiFi.softAP("ESP32_Car", "12345678");
  IPAddress IP = WiFi.softAPIP();
  Serial.println(IP);
  ```

---

## 🎓 Learning Resources

* [ESP32 Official Docs](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
* [Arduino ESP32 Guide](https://github.com/espressif/arduino-esp32)
* [L298N Motor Driver Tutorial](https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/)

---

## 🤝 Contributing

Feel free to fork this repo and submit pull requests. For major changes, open an issue first.

---

## 📝 License

This project is open source and available for educational purposes.

---

## 👨‍💻 Author

Created with ❤️ for ESP32 enthusiasts

---

## 🆘 Support

If you face any issues or have questions, please open a GitHub issue.

---

**Happy Building! 🚗💨**

