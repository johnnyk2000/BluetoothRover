void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  delay(200);
}

char uart_receive; // Define char variable that will store char from ESP32

void loop() {
  if (Serial.available()) {
    uart_receive = char(Serial.read()); // Reading characters
  }

  Serial.println("Message Received: ");
  Serial.println(uart_receive);
  uart_receive = 'C'; // Debugging purposes

  delay(20);
}