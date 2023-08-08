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

  switch (uart_receive) {
  case 'w':
  case 's':
    /* moving */
    break;

  case 'a':
  case 'd':
    /* turning */
    break;

  case 'e':
  case 'p':
    /* lifting arm */
    break;

  case 'q':
  case 'i':
    /* lowering arm */
    break;

  default:
    break;
  }

  // uart_receive = 'C'; // Debugging purposes

  delay(20);
}
