/*
 * ESP32 Car Remote Control
 * Control your ESP32-based car via WiFi using a web interface
 * 
 * Author: ESP32 Car Project
 * Date: 2024
 */

#include <WiFi.h>
#include <WebServer.h>

// WiFi credentials - Change these to your network
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Create web server on port 80
WebServer server(80);

// Motor Driver Pins (L298N Motor Driver)
const int motor1Pin1 = 27;  // IN1
const int motor1Pin2 = 26;  // IN2
const int motor2Pin1 = 25;  // IN3
const int motor2Pin2 = 33;  // IN4
const int enable1Pin = 14;  // ENA (PWM for speed control)
const int enable2Pin = 12;  // ENB (PWM for speed control)

// PWM properties
const int freq = 5000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int resolution = 8;
int dutyCycle = 200;  // Speed (0-255)

// HTML web page for remote control
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>ESP32 Car Remote Control</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      text-align: center;
      background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
      color: white;
      margin: 0;
      padding: 20px;
    }
    .container {
      max-width: 400px;
      margin: 0 auto;
      background: rgba(255, 255, 255, 0.1);
      padding: 30px;
      border-radius: 20px;
      box-shadow: 0 8px 32px 0 rgba(31, 38, 135, 0.37);
    }
    h1 {
      margin-bottom: 30px;
      font-size: 2em;
    }
    .controls {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 10px;
      margin: 20px 0;
    }
    button {
      padding: 20px;
      font-size: 18px;
      border: none;
      border-radius: 10px;
      background: rgba(255, 255, 255, 0.2);
      color: white;
      cursor: pointer;
      transition: all 0.3s;
      font-weight: bold;
    }
    button:active {
      background: rgba(255, 255, 255, 0.4);
      transform: scale(0.95);
    }
    .forward { grid-column: 2; background: rgba(76, 175, 80, 0.6); }
    .left { grid-column: 1; grid-row: 2; background: rgba(33, 150, 243, 0.6); }
    .stop { grid-column: 2; grid-row: 2; background: rgba(244, 67, 54, 0.6); font-size: 24px; }
    .right { grid-column: 3; grid-row: 2; background: rgba(33, 150, 243, 0.6); }
    .backward { grid-column: 2; grid-row: 3; background: rgba(255, 152, 0, 0.6); }
    .speed-control {
      margin-top: 30px;
    }
    input[type="range"] {
      width: 100%;
      margin: 10px 0;
    }
    .speed-value {
      font-size: 1.2em;
      font-weight: bold;
    }
  </style>
</head>
<body>
  <div class="container">
    <h1>🚗 ESP32 Car</h1>
    <div class="controls">
      <button class="forward" onmousedown="sendCommand('forward')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('forward')" ontouchend="sendCommand('stop')">▲<br>Forward</button>
      <button class="left" onmousedown="sendCommand('left')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('left')" ontouchend="sendCommand('stop')">◄<br>Left</button>
      <button class="stop" onclick="sendCommand('stop')">⬛<br>STOP</button>
      <button class="right" onmousedown="sendCommand('right')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('right')" ontouchend="sendCommand('stop')">►<br>Right</button>
      <button class="backward" onmousedown="sendCommand('backward')" onmouseup="sendCommand('stop')" ontouchstart="sendCommand('backward')" ontouchend="sendCommand('stop')">▼<br>Backward</button>
    </div>
    <div class="speed-control">
      <label>Speed Control</label><br>
      <input type="range" min="100" max="255" value="200" id="speedSlider" oninput="updateSpeed(this.value)">
      <div class="speed-value">Speed: <span id="speedValue">200</span></div>
    </div>
  </div>
  <script>
    function sendCommand(cmd) {
      fetch('/' + cmd)
        .then(response => response.text())
        .then(data => console.log(data))
        .catch(error => console.error('Error:', error));
    }
    function updateSpeed(val) {
      document.getElementById('speedValue').textContent = val;
      fetch('/speed?value=' + val)
        .then(response => response.text())
        .then(data => console.log(data))
        .catch(error => console.error('Error:', error));
    }
  </script>
</body>
</html>
)rawliteral";

// Function to stop all motors
void stopMotors() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
}

// Function to move forward
void moveForward() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
}

// Function to move backward
void moveBackward() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
}

// Function to turn left
void turnLeft() {
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
}

// Function to turn right
void turnRight() {
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);
  ledcWrite(pwmChannel1, dutyCycle);
  ledcWrite(pwmChannel2, dutyCycle);
}

// Handler for root page
void handleRoot() {
  server.send(200, "text/html", index_html);
}

// Handler for forward command
void handleForward() {
  moveForward();
  server.send(200, "text/plain", "Moving Forward");
}

// Handler for backward command
void handleBackward() {
  moveBackward();
  server.send(200, "text/plain", "Moving Backward");
}

// Handler for left command
void handleLeft() {
  turnLeft();
  server.send(200, "text/plain", "Turning Left");
}

// Handler for right command
void handleRight() {
  turnRight();
  server.send(200, "text/plain", "Turning Right");
}

// Handler for stop command
void handleStop() {
  stopMotors();
  server.send(200, "text/plain", "Stopped");
}

// Handler for speed control
void handleSpeed() {
  if (server.hasArg("value")) {
    dutyCycle = server.arg("value").toInt();
    server.send(200, "text/plain", "Speed set to " + String(dutyCycle));
  } else {
    server.send(400, "text/plain", "Missing speed value");
  }
}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Configure motor pins as outputs
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  
  // Configure PWM functionalities
  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);
  
  // Attach the PWM channels to GPIO pins
  ledcAttachPin(enable1Pin, pwmChannel1);
  ledcAttachPin(enable2Pin, pwmChannel2);
  
  // Start with motors stopped
  stopMotors();
  
  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Setup web server routes
  server.on("/", handleRoot);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/left", handleLeft);
  server.on("/right", handleRight);
  server.on("/stop", handleStop);
  server.on("/speed", handleSpeed);
  
  // Start server
  server.begin();
  Serial.println("Web server started!");
  Serial.println("Open your browser and navigate to the IP address above");
}

void loop() {
  // Handle client requests
  server.handleClient();
}
