import processing.serial.*;  //imports library used for wireless comm with the HC-05
Serial myPort;               // declares Serial Port object from library
String Text = "reading...";

void setup() {
  size(900,1000);                         // create window of this size
  
  String OS = System.getProperty("os.name");
  System.out.println(OS);
  if (OS.contains("Windows")) {
    myPort = new Serial(this, "COM10", 115200);
  } else {
    myPort = new Serial(this, "/dev/tty.ESP32", 115200);
  }
  
  myPort.bufferUntil('\n');               //delays calling serialEvent unitl reaching '\n'
}

void serialEvent(Serial myPort) {        //serialEvent is called whenever data is available
  Text = myPort.readStringUntil('\n');   //reads Serial.println() from Arduino
}

int state = 0;
int x = 0;
void draw() {
  background(237,240,241);        // sets background to a color, parameters correspond to an RGB code
  fill(20,160,133);               // sets color we will use to fill shapes
  stroke(33);                     // sets color used for border around shapes
  strokeWeight(1);                // sets width of stroke when drawing shapes
  
  rect(x,700,50,50,10);           //creates a rectangle at x,y with size width,height
  x += 1;
  if (x == 800)
    x = 0;
  
  fill(0);
  textSize(32);
  text(Text, 400, 700);           //draws text at x,y
  
  if (state == 1) {
    myPort.write('w');            //writes to the Bluetooth Serial port
    state = 0;
  } else if (state == 2) {
    myPort.write('s');
    state = 0;
  } else if (state == 3) {
    myPort.write('a');
    state = 0;
  } else if (state == 4) {
    myPort.write('d');
    state = 0;
  } else if (state == 5) {
    myPort.write('q');
    state = 0;
  } else if (state == 6) {
    myPort.write('e');
    state = 0;
  } else if (state == 7) {
    myPort.write('i');
    state = 0;
  } else if (state == 8) {
    myPort.write('p');
    state = 0;
  } else if (state == 9) {
    myPort.write(' ');
    state = 0;
  }
  
}

void keyPressed() {               //called whenever a key is pressed, key is automatically set to the key that is pressed
  if (key == 'w')
    state = 1;
  else if (key == 's')
    state = 2;
  else if (key == 'a')
    state = 3;
  else if (key == 'd')
    state = 4;
  else if (key == 'q')
    state = 5;
  else if (key == 'e')
    state = 6;
  else if (key == 'i')
    state = 7;
  else if (key == 'p')
    state = 8;
  else if (key == ' ')
    state = 9;
}
