#include <ESP32Servo.h>

#include "Navigator.hpp"
#include "BluetoothSerial.h"


#if !defined(CONFIG_BT_ENABLED) ||                                             \
    !defined(CONFIG_BLUEDROID_ENABLED) // error catching
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // declares the Bluetooth object

constexpr int LEFT_SERVO_PIN = 14;
constexpr int RIGHT_SERVO_PIN = 11;

constexpr int EN_A_PIN = 13;
constexpr int IN_1_PIN = 27;
constexpr int IN_2_PIN = 33;
constexpr int IN_3_PIN = 15;
constexpr int IN_4_PIN = 32;
constexpr int EN_B_PIN = 12;

Navigator mainAxle;
Servo leftArm;
// Servo rightArm;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // begins Bluetooth Serial connection
  Serial.println("Started successfully.");
  Serial1.begin(115200);

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	leftArm.setPeriodHertz(50);    // standard 50 hz servo
	leftArm.attach(LEFT_SERVO_PIN, 500, 2400);
	// rightArm.setPeriodHertz(50);    // standard 50 hz servo
	// rightArm.attach(RIGHT_SERVO_PIN, 500, 2400);
  
  mainAxle.begin(EN_A_PIN, IN_1_PIN, IN_2_PIN, IN_3_PIN, IN_4_PIN, EN_B_PIN);
}

char readIn;

void loop() {
  constexpr int angleDelta = 10;
  static int angleLeft = 0;
  static int angleRight = 0;

  readIn = '\0';
  if (SerialBT.available()) // if there are bytes available in the buffer
    readIn = char(SerialBT.read()); // read in one and store it in readIn
  
  Serial1.print(readIn);
  
  if (readIn == 'w') {
    mainAxle.forward();
  } else if (readIn == 's') {
    mainAxle.backup();
  } else if (readIn == 'a') {
    mainAxle.left();
  } else if (readIn == 'd') {
    mainAxle.right();
  } else {
    mainAxle.stop();
  }

  if (readIn == 'q') {
    angleLeft = max(angleLeft - angleDelta, 0);
    leftArm.write(angleLeft);
  } else if (readIn == 'e') {
    angleLeft = min(angleLeft + angleDelta, 180);
    leftArm.write(angleLeft);
  } else if (readIn == 'i') {
    angleRight = max(angleRight - angleDelta, 0);
    // rightArm.write(angleRight);
  } else if (readIn == 'p') {
    angleRight = min(angleRight + angleDelta, 180);
    // rightArm.write(angleRight);
  }
  delay(20);
}
