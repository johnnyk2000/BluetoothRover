#include <ESP32Servo.h>

#include "BluetoothSerial.h"
#include "Navigator.hpp"

#if !defined(CONFIG_BT_ENABLED) ||                                             \
    !defined(CONFIG_BLUEDROID_ENABLED) // error catching
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // declares the Bluetooth object

constexpr int LEFT_SERVO_PIN = 14;
constexpr int RIGHT_SERVO_PIN = 26;

constexpr int EN_A_PIN = 13;
constexpr int IN_1_PIN = 27;
constexpr int IN_2_PIN = 33;
constexpr int IN_3_PIN = 15;
constexpr int IN_4_PIN = 32;
constexpr int EN_B_PIN = 12;

Navigator mainAxle;
Servo leftArm;
Servo rightArm;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // begins Bluetooth Serial connection
  Serial.println("Started successfully.");
  Serial1.begin(115200);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  leftArm.setPeriodHertz(50); // standard 50 hz servo
  leftArm.attach(LEFT_SERVO_PIN, 500, 2400);
  rightArm.setPeriodHertz(50);    // standard 50 hz servo
  rightArm.attach(RIGHT_SERVO_PIN, 500, 2400);

  mainAxle.begin(EN_A_PIN, IN_1_PIN, IN_2_PIN, IN_3_PIN, IN_4_PIN, EN_B_PIN);
}

char readIn = ' ';

void loop() {
  constexpr int angleDelta = 10;
  static int angleLeft = 10;
  static int angleRight = 10;

  // if there are bytes available in the buffer
  if (SerialBT.available()) {
    readIn = char(SerialBT.read()); // read in one and store it in readIn
  }

  Serial1.print(readIn);

  switch (readIn) {
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

  case 'q':
    angleLeft = max(angleLeft - angleDelta, 10);
    mainAxle.stop();
    leftArm.write(angleLeft);
    break;

  case 'e':
    angleLeft = min(angleLeft + angleDelta, 170);
    mainAxle.stop();
    leftArm.write(angleLeft);
    break;

  case 'i':
    angleRight = max(angleRight - angleDelta, 10);
    mainAxle.stop();
    rightArm.write(angleRight);
    break;

  case 'p':
    angleRight = min(angleRight + angleDelta, 170);
    mainAxle.stop();
    rightArm.write(angleRight);
    break;

  case ' ':
    mainAxle.stop();
    break;

  default:
    break;
  }

  delay(40);
}
