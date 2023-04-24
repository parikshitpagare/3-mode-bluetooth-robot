<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234085619-89f5583a-8a69-43eb-86e0-61bb514b173b.png" width="75%" height="75%">
</p>

<p align="center">
   <img src="https://img.shields.io/badge/ARDUINO-UNO-00979D?style=for-the-badge&logo=arduino&logoColor=white" >
   <img src="https://img.shields.io/badge/LICENSE-MIT-green?style=for-the-badge" >
</p>

## 3-Mode Bluetooth Robot

- A robot car developed using Arduino that can operate in 3 modes - Manual, Automatic and Voice. 
- The car is controlled wirelessly via Bluetooth with an android app developed using MIT App Inventor.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086294-57d3f4fe-ab96-4359-a081-fa4919e9680c.png" width="70%" height="70%">
</p>

## Demo



## Features

- Wireless control with Bluetooth
- Dedicated android app
- Manual control using buttons on app
- PWM based 3 levels of motor speed control.
- Ultrasonic sensor based autonomous mode with direction display on the app.
- Voice control using Google Speech Recognizer with obstacle detection feature in car to avoid collision.

## Robot Overview

- The robot car is developed by modifying an existing RC car. 
- The body and motors of the car are kept intact while the included electronics are replaced with new components/modules.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086325-ef9ae5e2-2137-471c-9eaf-baf82c38161e.png" width="70%" height="70%">
</p>

### Hardware

#### Microcontroller

- Arduino Uno

#### Sensor

- Ultrasonic Sensor

#### Motors and Driver

- DC motors
- L298N Motor Driver (Motor driver used in project is custom made)
- Servo motor

#### Miscellaneous

- Robot Chassis
- HC 05 Bluetooth module
- 18650 Lithium Ion Batteries

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086355-16a21c60-dbf4-46fd-9ce0-4ab10e432d53.png" width="70%" height="70%">
</p>
  
<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086376-df6abce0-8574-4ffb-a69b-2c6df463a93d.png" width="70%" height="70%">
</p>

### Programming  

#### Software

- Arduino IDE

#### Libraries

- [Servo](https://github.com/arduino-libraries/Servo)
- [Soft PWM](https://github.com/bhagman/SoftPWM)

## App Overview

- The android app is developed using MIT App Inventor.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086423-0e0004e6-409b-4755-bb82-c423c5a22c3a.png" width="80%" height="80%">
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
- PWM based 3 levels of motor speed control is implemented which enables speed change on the go without delay from the app.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086457-fca23947-3f87-4215-b08a-2cfdbe88fe46.png" width="40%" height="40%">
</p>

### Automatic Mode

- This mode is autonomous where the robot finds its own path detecting obstacles with the help of ultrasonic sensor and servo motor.
- The app displays the direction in which the robot is moving.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086475-ff06c970-0c67-4319-a6ab-c800728ad5b9.png" width="40%" height="40%">
</p>

### Voice Mode

- The robot is controlled using voice commands provided by the user in the app using Google Speech Recognizer. 
- The robot car first scans for obstacle before executing the voice command and then proceeds. 
- It stops when an obstacle is detected by ultrasonic sensor and does not obey the command further displaying 'Obstacle Detected' on the opp.

<p align="center">
  <img src="https://user-images.githubusercontent.com/80714882/234086490-ceb03357-97cd-4b85-9a36-aa113d201047.png" width="40%" height="40%">
</p>

## Creator

**Parikshit Pagare**

<a href="https://linkedin.com/in/parikshitpagare"><img src="https://img.shields.io/badge/Linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white.svg"/></a>
<a href="https://youtube.com/@parikshitpagare"><img src="https://img.shields.io/badge/YouTube-FF0000?style=for-the-badge&logo=YouTube&logoColor=white.svg"/></a>
