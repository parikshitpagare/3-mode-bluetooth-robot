<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234085619-89f5583a-8a69-43eb-86e0-61bb514b173b.png" width="75%" height="75%">
</p>

<p align="center">
   <img src="https://img.shields.io/badge/ARDUINO-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white" >
   <img src="https://img.shields.io/badge/LICENSE-MIT-green?style=for-the-badge" >
</p>

<p align="center">
Robot car developed using Arduino that can operate in 3 modes - Manual, Automatic and Voice with additional features. The car is controlled wirelessly via Bluetooth with a dedicated Android app.
</p>

&nbsp;

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086294-57d3f4fe-ab96-4359-a081-fa4919e9680c.png" width="75%" height="75%">
</p>

## Recognition
- Awarded **Electromaker of The Month (May 2023)** by [electromaker.io](https://www.electromaker.io/blog/article/electromaker-of-the-month-may-2023-winners)
- Published on **Arduino Blog** - [This robot car accepts voice commands or operates autonomously](https://blog.arduino.cc/2023/05/08/this-robot-car-accepts-voice-commands-or-operates-autonomously/)

## About '3-Mode Bluetooth Robot'

A simple robot car can generally be controlled in one way as it is programmed to operate in certain way. 

> *What if the same robot can switch between 3 modes of control  instantaneously with minimal to no delay?*

- The 3-mode Bluetooth Robot is capable enough to be controlled in any of the 3 modes (Manual, Auto and Voice) instantaneously from one Android app.
- Some more features are included for each mode in the app to enhance the functionality of the robot car.

## Demo

#### Complete Version

- YouTube - [youtu.be/4jAYXDv8F4I](https://youtu.be/4jAYXDv8F4I)

#### Short Version

- Reddit - [reddit.com/bluetooth_robot_car](https://www.reddit.com/r/arduino/comments/134jr0a/developed_a_bluetooth_robot_car_that_can_be/?utm_source=share&utm_medium=web2x&context=3)

## Features

- Wireless control with Bluetooth
- Dedicated Android app
- Manual control using buttons on app
- PWM based 3 levels of motor speed control.
- Ultrasonic sensor based autonomous mode with direction display on the app.
- Voice control using Google Speech Recognizer along with obstacle detection feature to avoid collision.

## Hardware

### Robot Overview

- The robot car is developed by modifying an existing RC car. 
- The body and motors of the car are kept intact while the included electronics are replaced with new components/modules.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086325-ef9ae5e2-2137-471c-9eaf-baf82c38161e.png" width="75%" height="75%">
</p>

### Requirements

- Arduino Uno
- Ultrasonic Sensor
- DC motors
- L298N Motor Driver (Motor driver used in project is custom made)
- Servo motor
- HC 05 Bluetooth module
- 18650 Lithium Ion Batteries
- Robot Chassis

### Setup and Circuit Connections

Robot can be assembled on chassis as shown in the snapshot.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086355-16a21c60-dbf4-46fd-9ce0-4ab10e432d53.png" width="70%" height="70%">
</p>
  
Components can be connected as shown in the circuit diagram.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086376-df6abce0-8574-4ffb-a69b-2c6df463a93d.png" width="70%" height="70%">
</p>

## Software

### IDE

To program the microcontroller **Arduino IDE** is used which is commonly used with Arduino development boards. 

### Libraries
Certain libraries are required for proper functioning of the microcontroller and interfaced components.

- [Servo](https://github.com/arduino-libraries/Servo)
- [Soft PWM](https://github.com/bhagman/SoftPWM)

### Android App

The Android app is developed on [MIT App Inventor](https://appinventor.mit.edu/) platform.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086423-0e0004e6-409b-4755-bb82-c423c5a22c3a.png" width="75%" height="75%">
</p>

## Working

### Connecting to App

- Connect/Disconnect button is provided in the app to connect with the robot car via Bluetooth.
- HC 05 module is used for Bluetooth communication.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086440-aedb9dda-4de2-491c-a628-d215b9942473.png" width="80%" height="80%">
</p> 

### Manual Mode

- The robot is controlled manually using buttons in the app. 
- PWM based 3 levels of motor speed control is implemented in the app which enables speed change on the go without delay.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234435077-7f32987e-2e9f-4732-bb6a-d1afe23e9316.png" width="75%" height="75%">
</p>

### Automatic Mode

- This mode is autonomous where the robot finds its own path detecting obstacles with the help of ultrasonic sensor and servo motor.
- The app displays the direction in which the robot is moving.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234435457-b6c12f2b-c334-4959-996f-b597fc70a0db.png" width="75%" height="75%">
</p>

### Voice Mode

- The robot is controlled using voice commands provided by the user in the app using Google Speech Recognizer. 
- The robot car first scans for obstacle before executing the voice command and then proceeds. 
- It stops when an obstacle is detected by ultrasonic sensor and does not obey the command further displaying 'Obstacle Detected' on the opp.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234435464-4d99a7ac-68f9-4a3d-8193-1522f7e42404.png" width="75%" height="75%">
</p>

## Creator

**Parikshit Pagare**

<a href="https://linkedin.com/in/parikshitpagare"><img src="https://img.shields.io/badge/Linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white.svg"/></a>
<a href="https://youtube.com/@parikshitpagare"><img src="https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=YouTube&logoColor=white.svg"/></a>
<a href="https://www.reddit.com/user/parikshitpagare"><img src="https://img.shields.io/badge/Reddit-DBDBDB?style=for-the-badge&logo=reddit&logoColor=white.svg"/></a>
