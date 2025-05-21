# Gesture Controlled Bot using NodeMCU

## Project Description
This project implements a gesture-controlled robot using two NodeMCU (ESP8266) modules. The sender module reads motion data from an MPU9250 IMU sensor, calculates roll and pitch, and sends this data over WiFi. The receiver module acts as a WiFi access point, receives the roll and pitch data, and controls the robot's motors accordingly.

## Hardware Requirements
- 2 NodeMCU (ESP8266) modules
- MPU9250 IMU sensor
- Motor driver (e.g., L298N)
- 2 DC motors
- Power supply (e.g., LiPo battery)
- Jumper wires
- Breadboard (optional)

## Circuit Diagram/Connections
- **Sender NodeMCU:**
  - Connect MPU9250 SDA to NodeMCU D2 (GPIO4)
  - Connect MPU9250 SCL to NodeMCU D1 (GPIO5)
  - Connect MPU9250 VCC to 3.3V
  - Connect MPU9250 GND to GND

- **Receiver NodeMCU:**
  - Connect motor driver input pins to NodeMCU GPIO pins:
    - PWM1: GPIO14 (D5)
    - DIR1: GPIO12 (D6)
    - PWM2: GPIO13 (D7)
    - DIR2: GPIO9 (SD2)
  - Connect motor driver output pins to DC motors
  - Connect motor driver power supply

## Software Setup
### Library Dependencies
- ESP8266WiFi
- ESP8266WebServer
- MPU9250 (by Brian Taylor)

### How to Flash Code to NodeMCU
1. Install the Arduino IDE and ESP8266 board support.
2. Install required libraries via the Arduino Library Manager.
3. Open the sender.ino and reciever.ino files in the Arduino IDE.
4. Select the correct board (NodeMCU 1.0) and port.
5. Upload the code to the respective NodeMCU modules.

## How it Works
- **Sender Module:**
  - Initializes the MPU9250 IMU and connects to WiFi.
  - Continuously reads accelerometer data, calculates roll and pitch, and sends this data to the receiver module via HTTP GET requests.

- **Receiver Module:**
  - Sets up a WiFi access point and starts an HTTP server.
  - Receives roll and pitch data from the sender module.
  - Controls the robot's motors based on the received data:
    - Forward: Pitch > 5°
    - Backward: Pitch < -5°
    - Left: Roll < -5°
    - Right: Roll > 5°
    - Stop: Otherwise

## Usage Instructions
1. Power on both NodeMCU modules.
2. Connect to the WiFi network created by the receiver module (SSID: "ssid", Password: "password").
3. Move the sender module to control the robot's movement.



 
