#include "LCDFunctions.hpp"

// void face1() {
//   Serial.println("Open Eyes");
// }
// void face2() {
//   Serial.println("Sweat Face");
// }

template <typename F>
void dispatch(char signal, F callback) {
  static char prevSignal = ' ';

  if (prevSignal != signal) {
    callback();
    prevSignal = signal;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("successful connection");
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  setupLCD();
  delay(200);
}

char uart_receive; // Define char variable that will store char from ESP32

void loop() {
  // if (Serial.available()) {
  //   uart_receive = char(Serial.read()); // Reading characters
  // }

  // Serial.println("Message Received: ");
  // Serial.println(uart_receive);
  
  // uart_receive = 'C'; // Debugging purposes

  delay(20);
}
