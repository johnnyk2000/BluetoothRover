#include <ESP32Servo.h>

#include "Navigator.hpp"
#include "BluetoothSerial.h"


#if !defined(CONFIG_BT_ENABLED) ||                                             \
    !defined(CONFIG_BLUEDROID_ENABLED) // error catching
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT; // declares the Bluetooth object

constexpr int lservoPin = 14;

Navigator rearAxle;
Servo grabArm1;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32"); // begins Bluetooth Serial connection
  Serial.println("Started successfully.");
  Serial1.begin(115200);

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	grabArm1.setPeriodHertz(50);    // standard 50 hz servo
	grabArm1.attach(lservoPin, 500, 2400);
  grabArm1.attach(lservoPin);
  rearAxle.begin(13, 27, 33, 15, 32, 12);
}

char readIn;

void loop() {
  constexpr int angleDelta = 10;
  static int angle = 0;

  readIn = '\0';
  if (SerialBT.available()) // if there are bytes available in the buffer
    readIn = char(SerialBT.read()); // read in one and store it in readIn
  
  Serial1.print(readIn);
  
  if (readIn == 'w') {
    rearAxle.forward();
  } else if (readIn == 's') {
    rearAxle.backup();
  } else {
    rearAxle.stop();
  }

  if (readIn == 'q') {
    angle = max(angle - angleDelta, 0);
    grabArm1.write(angle);
  } else if (readIn == 'e') {
    angle = min(angle + angleDelta, 180);
    grabArm1.write(angle);
  }
  delay(20);
}
