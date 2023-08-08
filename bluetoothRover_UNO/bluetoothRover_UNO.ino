
// void face1() {
//   Serial.println("Face 1");
// }

// void face2() {
//   Serial.println("Face 2");
// }

// void doNothing() {
//   Serial.println("nothing");
// }

template <typename F>
void dispatch(char signal, F callback) {
  constexpr long SAFE_DELAY = 200;
  static long baseTime = millis();
  static char prevSignal = "\0";

  long now = millis();

  Serial.println(signal);
  if (now - baseTime > SAFE_DELAY) {
    if (prevSignal != signal) {
      callback();
    } 
    prevSignal = signal;
  }
}


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

  // Serial.println("Message Received: ");
  // Serial.println(uart_receive);

  switch (uart_receive) {
  case 'w':
  case 's':
    /* moving */
    dispatch(uart_receive, /*put your function here*/);
    break;

  case 'a':
  case 'd':
    /* turning */
    dispatch(uart_receive, /*put your function here*/);
    break;

  case 'e':
  case 'p':
    /* lifting arm */
    dispatch(uart_receive, /*put your function here*/);
    break;

  case 'q':
  case 'i':
    /* lowering arm */
    dispatch(uart_receive, /*put your function here*/);
    break;

  default:
    // TODO: add null action
    break;
  }

  // uart_receive = 'C'; // Debugging purposes

  delay(20);
}
