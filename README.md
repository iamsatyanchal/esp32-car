# 🚗 ESP32 Car - WiFi Remote Control

A smart car based on ESP32 that can be controlled via WiFi from any mobile phone or computer.

## 📋 Table of Contents 
- [Project Overview](#-project-overview)
- [Features](#-features--विशेषताएं)
- [Components Required](#-components-required)
- [Circuit Diagram](#-circuit-diagram)
- [Installation](#-installation)
- [Usage](#-usage)
- [How It Works](#-how-it-works)
- [Troubleshooting](#-troubleshooting)

## 🎯 Project Overview

### English
This project is a remote control car based on ESP32 microcontroller. You can control this car from your mobile phone or laptop via WiFi. The ESP32 creates a web server that provides a beautiful web interface with:
- Forward, Backward, Left, Right movement buttons
- Stop button
- Speed control slider

## ✨ Features / विशेषताएं

- 📱 **Web-based Remote Control** 
- 🎮 **Easy Controls** 
- ⚡ **Speed Control** 
- 📶 **WiFi Connectivity** 
- 🎨 **Responsive Design** 
- 🔄 **Real-time Control** 

## 🛠️ Components Required 

### Electronics 
1. **ESP32 Development Board** (1x) 
2. **L298N Motor Driver Module** (1x) 
3. **DC Gear Motors** (4x or 2x) 
4. **Robot Car Chassis** (1x) 
5. **Wheels** (4x)
6. **18650 Batteries** (2x) या **9V Battery** (1x) 
7. **Battery Holder** (1x)
8. **Jumper Wires** 
9. **Breadboard** (Optional) 

### Tools 
- Soldering Iron (optional)
- Screwdriver
- Wire Stripper

## 🔌 Circuit Diagram 

### Pin Connections 

#### ESP32 to L298N Motor Driver
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

#### L298N to Motors
```
OUT1, OUT2   →    Left Motors
OUT3, OUT4   →    Right Motors
```

#### Power Supply
```
Battery (+)  →    L298N 12V Input
Battery (-)  →    L298N GND
L298N 5V Out →    ESP32 5V
```

### Wiring Diagram 
```
                    ESP32
                   ┌─────┐
                   │     │
    GPIO27 ────────┤     │
    GPIO26 ────────┤     │
    GPIO25 ────────┤     │
    GPIO33 ────────┤     │
    GPIO14 ────────┤     │
    GPIO12 ────────┤     │
    GND ───────────┤     │
                   └─────┘
                      │
                      ↓
                   L298N
                   ┌─────┐
    IN1 ───────────┤     ├─── OUT1 ──┐
    IN2 ───────────┤     ├─── OUT2 ──┼─→ Left Motors
    IN3 ───────────┤     ├─── OUT3 ──┤
    IN4 ───────────┤     ├─── OUT4 ──┼─→ Right Motors
    ENA ───────────┤     │           │
    ENB ───────────┤     │           │
    GND ───────────┤     │           │
    12V ───────────┤     │           │
                   └─────┘           │
                      ↑              │
                      │              │
                   Battery           │
                  (7.4-12V)         │
```

## 💻 Installation 

### Step 1: Arduino IDE Setup / Arduino IDE 

1. **Arduino IDE डाउनलोड करें**
   - https://www.arduino.cc/en/software से डाउनलोड करें

2. **ESP32 Board Manager Add करें**
   - Arduino IDE खोलें
   - File → Preferences जाएं
   - "Additional Board Manager URLs" में यह URL डालें:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - OK क्लिक करें

3. **ESP32 Board Install करें**
   - Tools → Board → Boards Manager जाएं
   - "esp32" सर्च करें
   - "ESP32 by Espressif Systems" इंस्टॉल करें

### Step 2: Upload Code / कोड अपलोड करें

1. **Code खोलें**
   - `esp32_car_remote.ino` फाइल को Arduino IDE में खोलें

2. **WiFi Credentials बदलें**
   - Code में ये लाइनें खोजें:
     ```cpp
     const char* ssid = "YOUR_WIFI_SSID";
     const char* password = "YOUR_WIFI_PASSWORD";
     ```
   - अपने WiFi का नाम और पासवर्ड डालें

3. **Board Select करें**
   - Tools → Board → ESP32 Arduino → "ESP32 Dev Module" चुनें

4. **Port Select करें**
   - ESP32 को USB से कनेक्ट करें
   - Tools → Port → COM port चुनें

5. **Upload करें**
   - Upload बटन (→) दबाएं
   - Upload Complete का इंतजार करें

### Step 3: Hardware Assembly / हार्डवेयर असेंबली

1. **Chassis पर Components Mount करें**
   - Motors को chassis पर लगाएं
   - Wheels मोटर से अटैच करें
   - ESP32 और L298N को chassis पर secure करें

2. **Wiring करें**
   - ऊपर दिए गए circuit diagram के अनुसार सभी connections करें
   - सभी connections को ठीक से check करें

3. **Power Supply Connect करें**
   - Battery को L298N से connect करें
   - ESP32 को power दें

## 🎮 Usage / उपयोग

### Starting the Car / कार स्टार्ट करना

1. **Power On**
   - Battery को on करें
   - ESP32 boot होगा और WiFi से connect होगा

2. **Find IP Address / IP Address खोजें**
   - Arduino IDE में Serial Monitor खोलें (Tools → Serial Monitor)
   - Baud Rate को 115200 सेट करें
   - IP address नोट करें (उदाहरण: 192.168.1.100)

3. **Connect to Web Interface**
   - अपने मोबाइल/लैपटॉप को same WiFi network से connect करें
   - Browser में IP address टाइप करें
   - Control interface खुल जाएगा

### Controlling the Car / कार को कंट्रोल करना

**Control Buttons:**
- **▲ Forward** - कार आगे चलेगी
- **▼ Backward** - कार पीछे चलेगी
- **◄ Left** - कार बाएं मुड़ेगी
- **► Right** - कार दाएं मुड़ेगी
- **⬛ STOP** - कार रुक जाएगी
- **Speed Slider** - गति नियंत्रण (100-255)

**Tips:**
- मोबाइल में buttons को press करके रखें, release करने पर कार रुक जाएगी
- Speed slider से गति बढ़ा या घटा सकते हैं
- STOP button से emergency में कार रोक सकते हैं

## 🔧 How It Works / यह कैसे काम करता है

### Hindi / हिंदी में
1. **ESP32 WiFi से Connect होता है** और एक Web Server बनाता है
2. **आप ब्राउज़र में IP address खोलते हैं** और control interface देखते हैं
3. **जब आप button दबाते हैं**, ब्राउज़र ESP32 को HTTP request भेजता है
4. **ESP32 request receive करता है** और motor pins को control करता है
5. **L298N motor driver** signals को amplify करके motors को चलाता है
6. **Motors घूमते हैं** और कार मूव करती है

### English
1. **ESP32 connects to WiFi** and creates a Web Server
2. **You open the IP address in browser** and see the control interface
3. **When you press a button**, browser sends HTTP request to ESP32
4. **ESP32 receives the request** and controls motor pins
5. **L298N motor driver** amplifies signals and drives the motors
6. **Motors rotate** and car moves

## 🐛 Troubleshooting / समस्या निवारण

### Problem: ESP32 WiFi से connect नहीं हो रहा
**Solution:**
- WiFi credentials check करें (SSID और Password)
- WiFi signal strong है check करें
- Router के पास रहें
- Serial Monitor में error messages देखें

### Problem: Car चल नहीं रही
**Solution:**
- सभी connections check करें
- Battery charged है check करें
- Motor driver के LED on हैं check करें
- Pin numbers code में सही हैं verify करें

### Problem: IP Address नहीं मिल रहा
**Solution:**
- Serial Monitor baud rate 115200 पर set करें
- ESP32 को reset करें
- USB cable और port check करें

### Problem: Web Interface नहीं खुल रहा
**Solution:**
- Same WiFi network पर हैं check करें
- Browser में http:// के साथ IP address डालें
- Cache clear करें या incognito mode use करें

### Problem: Speed बहुत slow या fast है
**Solution:**
- Web interface में speed slider adjust करें
- Code में initial `dutyCycle` value बदलें (line 30)
- Battery voltage check करें

## 📚 Code Customization / कोड कस्टमाइज़ेशन

### Change Initial Speed / शुरुआती गति बदलें
```cpp
int dutyCycle = 200;  // 0-255 के बीच कोई value (डिफ़ॉल्ट: 200)
```

### Change Pin Numbers / पिन नंबर बदलें
```cpp
const int motor1Pin1 = 27;  // अपने pins के अनुसार बदलें
const int motor1Pin2 = 26;
// ... etc
```

### Change WiFi Mode to AP (Access Point)
अगर आप चाहते हैं कि ESP32 अपना खुद का WiFi network बनाए:
```cpp
// WiFi.begin() की जगह ये code use करें:
WiFi.softAP("ESP32_Car", "12345678");
IPAddress IP = WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.println(IP);
```

## 🎓 Learning Resources / सीखने के संसाधन

- [ESP32 Official Documentation](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/)
- [Arduino ESP32 Guide](https://github.com/espressif/arduino-esp32)
- [L298N Motor Driver Tutorial](https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/)

## 🤝 Contributing / योगदान

Feel free to fork this project and submit pull requests. For major changes, please open an issue first.

## 📝 License / लाइसेंस

This project is open source and available for educational purposes.

## 👨‍💻 Author / लेखक

Created with ❤️ for ESP32 enthusiasts

## 🆘 Support / सहायता

अगर कोई समस्या आए या सवाल हो, तो GitHub issues में पूछें।

If you face any issues or have questions, please open a GitHub issue.

---

**Happy Building! 🚗💨**

**मजे से बनाइए! 🚗💨**
