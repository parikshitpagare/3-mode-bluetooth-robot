/*
 * 3-Mode Bluetooth Robot Car
 * 
 * Created on : Sep 16, 2022 
 *
 * Author: Parikshit Pagare
 * github.com/parikshitpagare
 * linkedin.com/in/parikshitpagare 
 * 
 * Project link: github.com/parikshitpagare/3-mode-bluetooth-robot
 * 
 * MIT License 

 * Copyright (c) 2024 Parikshit Pagare

 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include <Servo.h>
#include "SoftPWM.h"

/* Motor pins */
#define motorMovement_1 4
#define motorMovement_2 2
#define motorMovement_pwm A0
#define motorDirection_1 7
#define motorDirection_2 8
#define motorDirection_pwm A1

/* Ultrasonic sensor */
#define trigger 12
#define echo 13
Servo ultrasonicServo;

char input;
volatile bool flag = 1;

uint8_t pwm;
volatile float duration;
volatile float distance;
volatile float leftDistance;
volatile float rightDistance;
const float safeDistance = 40.0;

void setup() {
  /* Setup baud rate for serial communication */
  Serial.begin(9600);
  delay(100);
  
  /* Setup DC motors */
  pinMode(motorMovement_1, OUTPUT);
  pinMode(motorMovement_2, OUTPUT);
  pinMode(motorMovement_pwm, OUTPUT);
  pinMode(motorDirection_1, OUTPUT);
  pinMode(motorDirection_2, OUTPUT);
  pinMode(motorDirection_pwm, OUTPUT);

  /* Setup servo motor */
  ultrasonicServo.attach(9);
  ultrasonicServo.write(90);

  /* Setup ultrasonic sensor pins */
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  /* Setup DC motor pwm */
  SoftPWMBegin(SOFTPWM_NORMAL);
  SoftPWMSet(motorMovement_pwm, 50);
  SoftPWMSet(motorDirection_pwm, 0);
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.read();

    /* Manual mode */
    if (input == 'G' || input == 'H' || input == 'I' || input == 'J' || input == 'K') {
      flag = 1;
      manual();
    }
    /* Automatic mode */
    else if (input == 'A') {
      flag = 1;
      ultrasonicServo.write(90);
      automatic();
    }
    /* Voice mode */
    else if (input == 'F' || input == 'B' || input == 'L' || input == 'R' || input == 'S') {
      flag = 1;
      voice();
    }
    /* Change PWM values */
    else if (input == 'X' || input == 'Y' || input == 'Z') {
      pwmChange();
    }
  }
}

/* Reading char 'O' on serial for stopping current mode */
void modeChange() {
  if (Serial.available() > 0) {
    input = Serial.read();
    
    if (input == 'O') {
      flag = 0;
      reset();        
    }
  }
}

/* Stopping DC motors and bringing servo motor to original position */
void reset() {

  digitalWrite(motorMovement_1, LOW);
  digitalWrite(motorMovement_2, LOW);
  digitalWrite(motorDirection_1, LOW);
  digitalWrite(motorDirection_2, LOW);
  ultrasonicServo.write(90);

  SoftPWMSet(motorMovement_pwm, 50);
  
  while (true) {
    loop();
  }
}

/********************************************* MANUAL MODE ********************************************/

void manual() {
  if (input == 'G') {
    forward();
  } 
  else if (input == 'H') {
    backward();
  } 
  else if (input == 'I') {
    left();
  } 
  else if (input == 'J') {
    right();
  } 
  else if (input == 'K') {
    stop();
  }
}

/******************************************** AUTOMATIC MODE *******************************************/

void automatic() {
  findDistance();
  
  while (true) {
    if (distance > safeDistance) {
      Serial.print("Forward?");
      setForward();
      findDistance();      
    }   
    else if (distance < safeDistance) {
      stop();
      delay(300);
      servoScan();
    }
  }
}

/* Finding distances on both sides using servo motor and ultrasonic sensor*/
void servoScan() {
  modeChange();
  delay(100);

  if (flag == 1) {
    Serial.print("Scan?");
    delay(100);
    
    /* Finding distance on left side */
    ultrasonicServo.write(180);
    delay(100);
    findDistance();
    delay(300);
    leftDistance = distance;
    delay(300);

    ultrasonicServo.write(90);
    delay(100);

    /* Finding distance on right side */
    ultrasonicServo.write(0);
    delay(100);
    findDistance();
    delay(300);
    rightDistance = distance;
    delay(300);

    ultrasonicServo.write(90);
    delay(100);
    safeZone();
  }
}

/* Comparing distances recieved after scanning by servo motor */
void safeZone() {
  modeChange();
  delay(100);

  if (flag == 1) {
    if ((leftDistance > rightDistance) && (leftDistance > safeDistance)) {
      left:
      setBackward();
      delay(200);
      setLeft();
      findDistance();
      
      while (true) {
        if (distance > safeDistance) {
          setForward();
          findDistance();
        }
        else if (distance < safeDistance) {     
          goto stopA;
        }
      }
      stopA:
      stop();
      delay(300);
      servoScan();
    } 
    else if ((rightDistance > leftDistance) && (rightDistance > safeDistance)) {
      right:
      setBackward();
      delay(200);
      setRight();
      findDistance();
      
      while (true) {   
        if (distance > safeDistance) {
          setForward();
          findDistance();
        }
        else if (distance < safeDistance) {     
          goto stopB;
        }
      }
      stopB:
      stop();
      delay(300);
      servoScan();
    } 
    else if ((leftDistance && rightDistance) > safeDistance) {
      goto right;
    }
    else if ((leftDistance && rightDistance) < safeDistance) {
      setBackward();
      delay(300);
      servoScan();
    }
  }
}

/********************************************** VOICE MODE *********************************************/

void voice() {
  if (input == 'F') {
    voiceForward();
  } 
  else if (input == 'B') {
    voicebackward();
  } 
  else if (input == 'L') {
    voiceLeft();
  } 
  else if (input == 'R') {
    voiceRight();
  } 
  else if (input == 'S') {
    Serial.print("Stop?");
    stop();
  }
}

/* When voice input is "Forward" */
void voiceForward() {
  ultrasonicServo.write(90);
  delay(100);
  findDistance();
  
  while (true) {
    if (distance > safeDistance) {
      Serial.print("No obstacle detected?");
      setForward();
      findDistance();
    }
    else if (distance < safeDistance) {
      goto stop;
    }
  }
  stop:
  stop();
  Serial.print("Obstacle detected?");
}

/* When voice input is "Backward" */
void voicebackward() {
  backward();
  delay(1500);
  stop();
}

/* When voice input is "Left" */
void voiceLeft() {
  ultrasonicServo.write(180);
  delay(100);
  findDistance();
  delay(200);
  ultrasonicServo.write(90);
  delay(100);

  if (distance > safeDistance) {
    Serial.print("No obstacle detected?");
    setBackward();
    delay(200);
    setLeft();    
  }
  while (true) {  
    if (distance > safeDistance) {
      setForward();
      findDistance();
    }
    else if (distance < safeDistance) {
      goto stop;
    } 
  }
  stop:
  stop();
  Serial.print("Obstacle detected?");
}

/* When voice input is "Right" */
void voiceRight() {
  ultrasonicServo.write(0);
  delay(100);
  findDistance();
  delay(200);
  ultrasonicServo.write(90);
  delay(100);

  if (distance > safeDistance) {
    Serial.print("No obstacle detected?");
    setBackward();
    delay(200);
    setRight();
  }
  while (true) {
    if (distance > safeDistance) {
      setForward();
      findDistance();
    }
    else if (distance < safeDistance) {
      goto stop;
    }
  }
  stop:
  stop();
  Serial.print("Obstacle detected?");
}

/***************************************** ULTRASONIC SENSOR ****************************************/

/* Calculating distance measured by ultrasonic sensor */
void findDistance() { 
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    duration = pulseIn(echo, HIGH);
    distance = (duration / 2) * 0.0343;
}

/********************************************* DC MOTORS ********************************************/

/* 
 * Motor driver used in project accepts PWM in inverted form 
 * i.e. 0 --> 255 and 255 --> 0
 */ 

/* Forward movement */
void forward() {
  modeChange();
  delay(100);
  
  if (flag == 1) {
    digitalWrite(motorMovement_1, HIGH);
    digitalWrite(motorMovement_2, LOW);
    digitalWrite(motorDirection_1, LOW);
    digitalWrite(motorDirection_2, LOW);
  } 
}

/* Forward movement for auto and voice modes*/
void setForward() {
  modeChange();
  delay(100);
  
  if (flag == 1) {
    SoftPWMSet(motorMovement_pwm, 180);
    digitalWrite(motorMovement_1, HIGH);
    digitalWrite(motorMovement_2, LOW);
    digitalWrite(motorDirection_1, LOW);
    digitalWrite(motorDirection_2, LOW);
  } 
}

/* Backward movement */
void backward() {
  modeChange();
  delay(100);
  
  if (flag == 1) {
    digitalWrite(motorMovement_1, LOW);
    digitalWrite(motorMovement_2, HIGH);
    digitalWrite(motorDirection_1, LOW);
    digitalWrite(motorDirection_2, LOW);
  }
}

/* Backward movement for auto and voice modes*/
void setBackward() {
  modeChange();
  delay(100);
  
  if (flag == 1) {
    SoftPWMSet(motorMovement_pwm, 160);
    Serial.print("Backward?");
    digitalWrite(motorMovement_1, LOW);
    digitalWrite(motorMovement_2, HIGH);
    digitalWrite(motorDirection_1, LOW);
    digitalWrite(motorDirection_2, LOW);
    
    delay(700);
    stop();
  }
}

/* Left movement */
void left() {
  modeChange();
  delay(100);
  
  if (flag == 1) {
    digitalWrite(motorMovement_1, HIGH);
    digitalWrite(motorMovement_2, LOW);
    digitalWrite(motorDirection_1, HIGH);
    digitalWrite(motorDirection_2, LOW);    
  }
}

/* Left movement for auto and voice modes*/
void setLeft() {
  modeChange();
  delay(100);
  
  if (flag == 1) {
    SoftPWMSet(motorMovement_pwm, 150);
    Serial.print("Left?");
    digitalWrite(motorMovement_1, HIGH);
    digitalWrite(motorMovement_2, LOW);
    digitalWrite(motorDirection_1, HIGH);
    digitalWrite(motorDirection_2, LOW);
    delay(1500);
  }
}

/* Right movement */
void right() {
  modeChange();
  delay(100);
  
  if (flag == 1) {
    digitalWrite(motorMovement_1, HIGH);
    digitalWrite(motorMovement_2, LOW);
    digitalWrite(motorDirection_1, LOW);
    digitalWrite(motorDirection_2, HIGH);
  }
}

/* Right movement for auto and voice modes*/
void setRight() {
  modeChange();
  delay(100);
  
  if (flag == 1) {
    SoftPWMSet(motorMovement_pwm, 150);
    Serial.print("Right?");
    digitalWrite(motorMovement_1, HIGH);
    digitalWrite(motorMovement_2, LOW);
    digitalWrite(motorDirection_1, LOW);
    digitalWrite(motorDirection_2, HIGH);
    
    delay(1500);
  }
}

/* Stopping robot */
void stop() {
  modeChange();
  delay(100);
  
  if (flag == 1) {
    digitalWrite(motorMovement_1, LOW);
    digitalWrite(motorMovement_2, LOW);
    digitalWrite(motorDirection_1, LOW);
    digitalWrite(motorDirection_2, LOW);
    ultrasonicServo.write(90);
  }
}

/* Change speed of motors */
void pwmChange() {
  if (input == 'X')
    pwm = 150;
  else if (input == 'Y')
    pwm = 100;
  else if (input == 'Z')
    pwm = 50;

  SoftPWMSet(motorMovement_pwm, pwm);
}