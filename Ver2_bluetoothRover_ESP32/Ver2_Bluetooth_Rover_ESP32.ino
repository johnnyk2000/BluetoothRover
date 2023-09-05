#include <ESP32Servo.h>
#include "Navigator.hpp"
#include "BluetoothSerial.h"

// for error catching bluetooth connection
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)           //error catching
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Pin Number Constant Definitions
const int LEFT_SERVO_PIN = 12;
const int RIGHT_SERVO_PIN = 13;
const int MOTOR_EN_A_PIN = 6;
const int MOTOR_IN_1_PIN = 7;
const int MOTOR_IN_2_PIN = 8;
const int MOTOR_IN_3_PIN = 9;
const int MOTOR_IN_4_PIN = 10;
const int MOTOR_EN_B_PIN = 11;


//Objects Initializations
Servo leftArm;              //for left servo
Servo rightArm;             //for right servo
Navigator mainAxle;         //for motor driver
BluetoothSerial SerialBT;   //for bluetooth

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);     //for Serial monitor
  Serial1.begin(115200);    //for UART sending message to arduino uno
  SerialBT.begin("ESP32");
  Serial.println("started succesfully");
  leftArm.attach(LEFT_SERVO_PIN);
  rightArm.attach(RIGHT_SERVO_PIN);
  mainAxle.begin(MOTOR_EN_A_PIN, MOTOR_IN_1_PIN, MOTOR_IN_2_PIN, MOTOR_IN_3_PIN, MOTOR_IN_4_PIN, MOTOR_EN_B_PIN);
}

const int maxAngle = 180;
const int minAngle = 0;
const int angleDelta = 10;

char action;
char previousAction = '\0';

void loop() {
  // put your main code here, to run repeatedly:

  // default letter for action
  action = 'g';

  //fetching keyboard char from processing
  if (SerialBT.available())
  {
    action = char(SerialBT.read());
    if (action != previousAction)   //print only when the input recieved differs from previous
    {
      Serial.println(action);
      Serial1.println(action);
      delay(5);  
    }
    previousAction = action;
  }

  switch (action)
  {
  case 'q':
    if (leftArm.read() - angleDelta <= 0)
      leftArm.write(0);
    else
      leftArm.write(leftArm.read() - angleDelta);
    break;
  case 'e':
    if (leftArm.read() + angleDelta >= 180)
      leftArm.write(180);
    else
      leftArm.write(leftArm.read() + angleDelta);
    break;
  case 'i':
    if (rightArm.read() - angleDelta <= 0)
      rightArm.write(0);
    else
      rightArm.write(rightArm.read() - angleDelta);
    break;
  case 'p':
    if (rightArm.read() + angleDelta >= 180)
      rightArm.write(180);
    else
      rightArm.write(rightArm.read() + angleDelta);
    break;
  case 'w':
    mainAxle.forward();
    break;
  case 's':
    mainAxle.backup();
    break;
  case 'a':
    mainAxle.left();
    break;
  case 'd':
    mainAxle.right();
    break;
  default:
    mainAxle.stop();
    break;
  }

  delay(25);
}
