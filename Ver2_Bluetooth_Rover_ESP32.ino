#include <ESP32Servo.h>
#include "Navigator.hpp"
#include "BluetoothSerial.h"

// for error catching bluetooth connection
#if !defined(CONFIG_BT_ENABLED) ||                                             \
    !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

//Pin Number Constant Definitions
const int SERVO_PIN = 14;
const int MOTOR_EN_A_PIN = 13;
const int MOTOR_IN_1_PIN = 12;
const int MOTOR_IN_2_PIN = 27;
const int MOTOR_IN_3_PIN = 33;
const int MOTOR_IN_4_PIN = 15;
const int MOTOR_EN_B_PIN = 32;


//Objects Initializations
Servo arm;                  //for servo (both arms)
Navigator mainAxle;         //for motor driver
BluetoothSerial SerialBT;   //for bluetooth

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin("ESP32Number2");
  arm.attach(SERVO_PIN);
  mainAxle.begin(MOTOR_EN_A_PIN, MOTOR_IN_1_PIN, MOTOR_IN_2_PIN, MOTOR_IN_3_PIN, MOTOR_IN_4_PIN, MOTOR_EN_B_PIN);
}

const int maxAngle = 180;
const int minAngle = 0;
const int angleDelta = 0;

int servoValue;
char action;

void loop() {
  // put your main code here, to run repeatedly:

  // Test/debug code using serial input
  // if (Serial.available() > 0)
  //   action = Serial.read();

  //fetching keyboard char from processing
  action = '\0';

  if (SerialBT.available())
  {
    action = char(SerialBT.read());
  }

  switch (action)
  {
  case 'q':
    arm.write(0);
    break;
  case 'e':
    arm.write(180);
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

  delay(50);
}
