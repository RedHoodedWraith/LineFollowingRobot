/**
 * Title: Line Follower
 * Author: Rowan Rathod
 * Description: This program is designed for the mBot, https://www.makeblock.com/mbot, manuafactured by Makeblock. 
 * This program makes the robot to follow a black line on a white surface no matter how it curves.
 */

#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "colours_LED.hpp"

// Speed Control Variables
float error_score = 0;  // The Proportional Component of a PID Controller
float baseSpeed = 0;  // Default Overall Speed
float leftWheel = 0;  // Speed of the left wheel
float rightWheel = 0; // Speed of the right wheel
float speedChange = 0;  // The Derivative Component of a PID Controller

// Functionality Variables
bool activate = false;

// Physical IO Component Definitions
const int onBoard_btn = A7;  // On-board Button
MeIR ir;  // Remote Control
MeLineFollower linefollower_2(2); // Line Sensor
MeDCMotor motor_9(9); // Left Motor
MeDCMotor motor_10(10); // Right Motor

// LED Light Definitions
MeRGBLed rgbled_7(7, 2);  // On-board Status Lights
LEDset(rgbled_7);

/* 
  Resets the speed configuration
*/
void reset (){
  error_score = 0;
  baseSpeed = 50;
  leftWheel = baseSpeed;
  rightWheel = baseSpeed;
  speedChange = 1;

}

/*
  Turns all the on-board lights off
*/
void allLightsOff (){
  rgbled_7.setColor(0, 0, 0, 0);
  rgbled_7.show();

}

/*
  Stops all the motors and resets its speed configuration
*/
void fullShutdown (){
  motor_9.run(0);
  motor_10.run(0);
  reset();

}

/*
  Updates the motor speed configuration based on data from the line sensor
  Updates on-board lights to reflect current conditions.
*/
void updateMotor (){
  // Case if robot if following the line perfectly
  if(error_score == 0){
      leftWheel = baseSpeed;
      rightWheel = baseSpeed;
      rgbled_7.setColor(0, 0, 255, 0);
      rgbled_7.show();

  }
  else{
      // Case if robot is veering left of line: align motors to move right
      if(error_score < 0){
          allLightsOff();
          rgbled_7.setColor(2, 255, 0, 0);
          rgbled_7.show();
          leftWheel += speedChange;
          rightWheel += ((0 - speedChange));

      }
      // Case if robot is veering right of line: align motors to move left
      else{
          allLightsOff();
          rgbled_7.setColor(1, 255, 0, 0);
          rgbled_7.show();
          rightWheel += speedChange;
          leftWheel += ((0 - speedChange));

      }

  }

}

void pid_n_speed_chech (){
  if(error_score < -2){
      error_score
     = -2;

  }
  if(error_score > 2){
      error_score
     = 2;

  }
  if(leftWheel < 0){
      leftWheel = 0;

  }
  if(leftWheel > baseSpeed){
      leftWheel = baseSpeed;

  }
  if(rightWheel < 0){
      rightWheel = 0;

  }
  if(rightWheel > baseSpeed){
      rightWheel = baseSpeed;

  }

}

void updateState (){
  if((1 ? (2 == 0 ? linefollower_2.readSensors() == 0 :
  (linefollower_2.readSensors() & 2) == 2) :
  (2 == 0 ? linefollower_2.readSensors() == 3 :
  (linefollower_2.readSensors() & 2) == 0))){
      error_score
     += -1;

  }
  if((1 ? (1 == 0 ? linefollower_2.readSensors() == 0 :
  (linefollower_2.readSensors() & 1) == 1) :
  (1 == 0 ? linefollower_2.readSensors() == 3 :
  (linefollower_2.readSensors() & 1) == 0))){
      error_score
     += 1;

  }

}

void shutoffCheck (){
  if((0 ^ (analogRead(A7) > 10 ? 0 : 1)) || ir.keyPressed(21)){
      if(activate){
          rgbled_7.setColor(0, 0, 0, 0);
          rgbled_7.show();
          activate = false;

      }else{
          activate = true;

      }

  }

}
void run (){
  pid_n_speed_chech();
  updateState();
  updateMotor();
  motor_9.run(-1 * (leftWheel / 100.0 * 255));
  motor_10.run(rightWheel / 100.0 * 255);

}

void setup() {
  pinMode(A7, INPUT);
  ir.begin();
  activate = false;
  reset();

}

void loop() {

  // Refreshes the IR Receiver
  ir.loop();

  shutoffCheck();

  if(activate){
      run();

  }else{
      rgbled_7.setColor(0, 0, 0, 0);
      rgbled_7.show();
      fullShutdown();

  }

}

