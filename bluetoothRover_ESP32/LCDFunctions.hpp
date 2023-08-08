// C++ code
//
// include the library code:
#include <LiquidCrystal.h>

/*
format for creating a custom character:
1. define and initialize array that indicates which pixels will be on/off
2. use the createChar command and pass custom char # and array as parameters
3. use the setCursor command to indicate the box that you want to place the custom char
   pass the coordinates as parameters
   e.g.) top left will be (0, 0), buttom right will be (1, 15)
4. place the custom char by using the write command
   pass the custom char # as parameter
   - If we want to pass the same char but in a different box, you could 
     set the cursor to the desired box and use the write command again passing
     the same custom char #

Other stuff: The max amount of custom characters you can create and display is 8
*/

//Code that indicates the on/off of each pixel in a single box(a.k.a. custom characters)

const int rs = 26, en = 25, d4 = 34, d5 = 39, d6 = 36, d7 = 4;  //pin definition for LCD
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                    //LCD object initialzation
//------------------------------------------------------------------------------------
//fill white pixels to entire box

//Function Definition
void openEyes();
void moveFaceLeft(int k);
void moveFaceRight(int k);
void sweatFace();
void closeEyesFace();
void brokenFace();
void heartFace();
void restSequence();
void smileBlinkSequence();
void sweatingFaceSequence();
void turningRightSequence();
void turningLeftSequence();
void danceFaceSequence();
void sweatSequence(int pos);
void movingEyes(int p);
void setFace(int k, byte arrEyes[]);


byte fillWhite[] = { B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 };

//closed eyes left middle and right side (across three boxes)
byte eyeLeft[] = { B11111, B11111, B11111, B11100, B11100, B11111, B11111, B11111 };
byte eyeMiddle[] = { B11111, B11111, B11111, B00000, B00000, B11111, B11111, B11111 };
byte eyeRight[] = { B11111, B11111, B11111, B00111, B00111, B11111, B11111, B11111 };

//opened eyes (fits in one box)
byte openEye[] = { B11111, B10001, B01100, B01100, B00000, B10001, B11111, B11111 };

byte openEyeLow[] = { B11111, B11111, B10001, B01100, B01100, B00000, B10001, B11111 };

//crying eye left and right versions
byte cryEyeLeft[] = { B11111, B00111, B11001, B11110, B00000, B11110, B11001, B00111 };
byte cryEyeRight[] = { B11111, B11100, B10011, B01111, B00000, B01111, B10011, B11100 };

//broken x mark eye(takes one box)
byte xEyes[] = { B11111, B11111, B01110, B10101, B11011, B10101, B01110, B11111 };
//dance move heart mark eye(takes one box)
byte heartEyes[] = { B11111, B10101, B00000, B00000, B10001, B11011, B11111, B11111 };

//smiles from left to right (across four boxes)
byte smile1[] = { B00111, B00011, B10001, B11000, B11100, B11110, B11111, B11111 };
byte smile2[] = { B11111, B11110, B11100, B11000, B00001, B00011, B00111, B11111 };
byte smile3[] = { B11111, B01111, B00111, B00011, B10000, B11000, B11100, B11111 };
byte smile4[] = { B11100, B11000, B10001, B00011, B00111, B01111, B11111, B11111 };

//unhappy mouth from left to right (across four boxes)
byte cryMouth1[] = { B11111, B11110, B11100, B11000, B10001, B00011, B00111, B11111 };
byte cryMouth2[] = { B00111, B00011, B00001, B11000, B11100, B11110, B11111, B11111 };
byte cryMouth3[] = { B11100, B11000, B10000, B00011, B00111, B01111, B11111, B11111 };
byte cryMouth4[] = { B11111, B01111, B00111, B00011, B10001, B11000, B11100, B11111 };

//sweating mouth (same as cryMouth except middle 2 boxes)
byte sweatMouthMiddle[] = { B11111, B00000, B00000, B11111, B11111, B11111, B11111, B11111 };

//moving eyes
byte movingEyesTopLeft[] = { B11111, B10001, B01100, B01100, B00000, B10001, B11111, B11111 };
byte movingEyesTopRight[] = { B11111, B10001, B00110, B00110, B00000, B10001, B11111, B11111 };
byte movingEyesBottomRight[] = { B11111, B10001, B00000, B00110, B00110, B10001, B11111, B11111 };
byte movingEyesBottomLeft[] = { B11111, B10001, B00000, B01100, B01100, B10001, B11111, B11111 };

//sweating sequence ver2 for upper row box
byte sweat[24][8] = {
{ B11011, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B10001, B11011, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B10001, B10001, B11011, B11111, B11111, B11111, B11111, B11111 },
{ B11011, B10001, B10001, B11011, B11111, B11111, B11111, B11111 },
{ B11011, B11011, B10001, B10001, B11011, B11111, B11111, B11111 },
{ B11111, B11011, B11011, B10001, B10001, B11011, B11111, B11111 },
{ B11111, B11111, B11011, B11011, B10001, B10001, B11011, B11111 },
{ B11111, B11111, B11111, B11011, B11011, B10001, B10001, B11011 },
{ B11111, B11111, B11111, B11111, B11011, B11011, B10001, B10001 },
{ B11111, B11111, B11111, B11111, B11111, B11011, B11011, B10001 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11011, B11011 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11011 },

{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 }
};

//sweating sequence ver2 for lower row box
byte sweat2[24][8] = {
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
  
{ B11011, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B10001, B11011, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B10001, B10001, B11011, B11111, B11111, B11111, B11111, B11111 },
{ B11011, B10001, B10001, B11011, B11111, B11111, B11111, B11111 },
{ B11011, B11011, B10001, B10001, B11011, B11111, B11111, B11111 },
{ B11111, B11011, B11011, B10001, B10001, B11011, B11111, B11111 },
{ B11111, B11111, B11011, B11011, B10001, B10001, B11011, B11111 },
{ B11111, B11111, B11111, B11011, B11011, B10001, B10001, B11011 },
{ B11111, B11111, B11111, B11111, B11011, B11011, B10001, B10001 },
{ B11111, B11111, B11111, B11111, B11111, B11011, B11011, B10001 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11011, B11011 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11011 },
  
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },  
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
{ B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
};
//-----------------------------------------------------------------------------------------

void setupLCD() {
  lcd.begin(16, 2);
  lcd.home();
}

//--------------------------------------------------------------
//static face for opened eyes
void openEyes()
{
  //code for the eyes
  lcd.createChar(1, openEye);
  lcd.setCursor(5, 0);
  lcd.write(1);
  lcd.setCursor(10, 0);
  lcd.write(1);
  
  lcd.createChar(4, smile1);
  lcd.setCursor(6, 1);
  lcd.write(4);
  
  lcd.createChar(5, smile2);
  lcd.setCursor(7, 1);
  lcd.write(5);
  
  lcd.createChar(6, smile3);
  lcd.setCursor(8, 1);
  lcd.write(6);
  
  lcd.createChar(7, smile4);
  lcd.setCursor(9, 1);
  lcd.write(7);
  
  //holds the num of boxes that has to be filled with white
  int row1FillNum = 14;
  int row2FillNum = 12;
  
  //array of int that hold the position of boxes that has to be filled with white
  int row1Fill[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 15};
  int row2Fill[] = {0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15};
  
  lcd.createChar(8, fillWhite);
  
  //for loop to simplfy process
  for(int i = 0; i < row1FillNum; i++)
  {
    lcd.setCursor(row1Fill[i], 0);
    lcd.write(8);
  }
  
  for(int i = 0; i < row2FillNum; i++)
  {
    lcd.setCursor(row2Fill[i], 1);
    lcd.write(8);
  }  
}

//--------------------------------------------------------------
//initial position: openEyes() but eyes looking to the left
//takes integer as input and shifts k positions to the left
//use when turing left
void moveFaceLeft(int k)
{
  lcd.createChar(1, movingEyesTopRight);
  lcd.setCursor((5 + k) % 16, 0);
  lcd.write(1);
  lcd.setCursor((10 + k) % 16, 0);
  lcd.write(1);
  
  lcd.createChar(4, smile1);
  lcd.setCursor((6 + k) % 16, 1);
  lcd.write(4);
  
  lcd.createChar(5, smile2);
  lcd.setCursor((7 + k) % 16, 1);
  lcd.write(5);
  
  lcd.createChar(6, smile3);
  lcd.setCursor((8 + k) % 16, 1);
  lcd.write(6);
  
  lcd.createChar(7, smile4);
  lcd.setCursor((9 + k) % 16, 1);
  lcd.write(7);
  
  //holds the num of boxes that has to be filled with white
  int row1FillNum = 14;
  int row2FillNum = 12;
  
  //array of int that hold the position of boxes that has to be filled with white
  int row1Fill[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 15};
  int row2Fill[] = {0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15};
  
  lcd.createChar(8, fillWhite);
  
  //for loop to simplfy process
  for(int i = 0; i < row1FillNum; i++)
  { 
    lcd.setCursor((row1Fill[i] + k) % 16, 0);
    lcd.write(8);
  }
  
  for(int i = 0; i < row2FillNum; i++)
  {
    lcd.setCursor((row2Fill[i] + k) % 16, 1);
    lcd.write(8);
  }  
}

//--------------------------------------------------------------
//initial position: openEyes() but eyes looking to the right
//takes integer as input and shifts face k positions to the left
//use when turing left
void moveFaceRight(int k)
{
  /*
  In order to use the same code as openEyesLeft() 
  we need to solve the problem that when k is negative,
  there could be a negative coordinate which would be invalid
  solution: shift the coordinate 16 to the right before hand so
  that there will never be a negative number
    - add m = 16 to every coordinate indicator code
  */
  int m = 16;
  lcd.createChar(1, movingEyesTopLeft);
  lcd.setCursor((m + 5 + k) % 16, 0);
  lcd.write(1);
  lcd.setCursor((m + 10 + k) % 16, 0);
  lcd.write(1);
  
  lcd.createChar(4, smile1);
  lcd.setCursor((m + 6 + k) % 16, 1);
  lcd.write(4);
  
  lcd.createChar(5, smile2);
  lcd.setCursor((m + 7 + k) % 16, 1);
  lcd.write(5);
  
  lcd.createChar(6, smile3);
  lcd.setCursor((m + 8 + k) % 16, 1);
  lcd.write(6);
  
  lcd.createChar(7, smile4);
  lcd.setCursor((m + 9 + k) % 16, 1);
  lcd.write(7);
  
  //holds the num of boxes that has to be filled with white
  int row1FillNum = 14;
  int row2FillNum = 12;
  
  //array of int that hold the position of boxes that has to be filled with white
  int row1Fill[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 15};
  int row2Fill[] = {0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15};
  
  lcd.createChar(8, fillWhite);
  
  //for loop to simplfy process
  for(int i = 0; i < row1FillNum; i++)
  { 
    lcd.setCursor((m + row1Fill[i] + k) % 16, 0);
    lcd.write(8);
  }
  
  for(int i = 0; i < row2FillNum; i++)
  {
    lcd.setCursor((m + row2Fill[i] + k) % 16, 1);
    lcd.write(8);
  }  
}

//--------------------------------------------------------------
//Static face for robot sweating, 
//used when robot is picking up parts
void sweatFace()
{
  //code for the eyes
  lcd.createChar(1, cryEyeLeft);
  lcd.setCursor(5, 0);
  lcd.write(1);
  
  lcd.createChar(2, cryEyeRight);
  lcd.setCursor(10, 0);
  lcd.write(2);
  
  lcd.createChar(3, cryMouth1);
  lcd.setCursor(6, 1);
  lcd.write(3);
  
  lcd.createChar(4, sweatMouthMiddle);
  lcd.setCursor(7, 1);
  lcd.write(4);
  lcd.setCursor(8, 1);
  lcd.write(4);
  
  lcd.createChar(5, cryMouth4);
  lcd.setCursor(9, 1);
  lcd.write(5);
  
  //holds the num of boxes that has to be filled with white
  int row1FillNum = 14;
  int row2FillNum = 12;
  
  //array of int that hold the position of boxes that has to be filled with white
  int row1Fill[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 15};
  int row2Fill[] = {0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15};
  
  lcd.createChar(8, fillWhite);
  
  //for loop to simplfy process
  for(int i = 0; i < row1FillNum; i++)
  {
    lcd.setCursor(row1Fill[i], 0);
    lcd.write(8);
  }
  
  for(int i = 0; i < row2FillNum; i++)
  {
    lcd.setCursor(row2Fill[i], 1);
    lcd.write(8);
  }  
}

//--------------------------------------------------------------
//static face for robot closed eyes
//used for resting sequence and blinking sequence
void closeEyesFace()
{
  lcd.createChar(1, eyeLeft);
  lcd.setCursor(4, 0);
  lcd.write(1);
  lcd.setCursor(9, 0);
  lcd.write(1);
  
  lcd.createChar(2, eyeMiddle);
  lcd.setCursor(5, 0);
  lcd.write(2);
  lcd.setCursor(10, 0);
  lcd.write(2);
  
  lcd.createChar(3, eyeRight);
  lcd.setCursor(6, 0);
  lcd.write(3);
  lcd.setCursor(11, 0);
  lcd.write(3);
  
  lcd.createChar(4, smile1);
  lcd.setCursor(6, 1);
  lcd.write(4);
  
  lcd.createChar(5, smile2);
  lcd.setCursor(7, 1);
  lcd.write(5);
  
  lcd.createChar(6, smile3);
  lcd.setCursor(8, 1);
  lcd.write(6);
  
  lcd.createChar(7, smile4);
  lcd.setCursor(9, 1);
  lcd.write(7);
  
  //holds the num of boxes that has to be filled with white
  int row1FillNum = 10;
  int row2FillNum = 12;
  
  //array of int that hold the position of boxes that has to be filled with white
  int row1Fill[] = {0, 1, 2, 3, 7, 8, 12, 13, 14, 15};
  int row2Fill[] = {0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15};
  
  lcd.createChar(8, fillWhite);
  
  //for loop to simplfy process
  for(int i = 0; i < row1FillNum; i++)
  {
    lcd.setCursor(row1Fill[i], 0);
    lcd.write(8);
  }
  
  for(int i = 0; i < row2FillNum; i++)
  {
    lcd.setCursor(row2Fill[i], 1);
    lcd.write(8);
  }  
}

//--------------------------------------------------------------
//static face for brokenFace
void brokenFace()
{
  //code for the eyes
  lcd.createChar(1, xEyes);
  lcd.setCursor(5, 0);
  lcd.write(1);
  
  lcd.createChar(2, openEyeLow);
  lcd.setCursor(10, 0);
  lcd.write(2);
  
  lcd.createChar(3, cryMouth1);
  lcd.setCursor(6, 1);
  lcd.write(3);
  
  lcd.createChar(4, cryMouth2);
  lcd.setCursor(7, 1);
  lcd.write(4);
  
  lcd.createChar(5, cryMouth3);
  lcd.setCursor(8, 1);
  lcd.write(5);
  
  lcd.createChar(6, cryMouth4);
  lcd.setCursor(9, 1);
  lcd.write(6);
  
  //holds the num of boxes that has to be filled with white
  int row1FillNum = 14;
  int row2FillNum = 12;
  
  //array of int that hold the position of boxes that has to be filled with white
  int row1Fill[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 15};
  int row2Fill[] = {0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15};
  
  lcd.createChar(8, fillWhite);
  
  //for loop to simplfy process
  for(int i = 0; i < row1FillNum; i++)
  {
    lcd.setCursor(row1Fill[i], 0);
    lcd.write(8);
  }
  
  for(int i = 0; i < row2FillNum; i++)
  {
    lcd.setCursor(row2Fill[i], 1);
    lcd.write(8);
  }  
}

//--------------------------------------------------------------
void heartFace()
{
  //code for the eyes
  lcd.createChar(1, heartEyes);
  lcd.setCursor(5, 0);
  lcd.write(1);
  lcd.setCursor(10, 0);
  lcd.write(1);
  
  lcd.createChar(4, smile1);
  lcd.setCursor(6, 1);
  lcd.write(4);
  
  lcd.createChar(5, smile2);
  lcd.setCursor(7, 1);
  lcd.write(5);
  
  lcd.createChar(6, smile3);
  lcd.setCursor(8, 1);
  lcd.write(6);
  
  lcd.createChar(7, smile4);
  lcd.setCursor(9, 1);
  lcd.write(7);
  
  //holds the num of boxes that has to be filled with white
  int row1FillNum = 14;
  int row2FillNum = 12;
  
  //array of int that hold the position of boxes that has to be filled with white
  int row1Fill[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 15};
  int row2Fill[] = {0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15};
  
  lcd.createChar(8, fillWhite);
  
  //for loop to simplfy process
  for(int i = 0; i < row1FillNum; i++)
  {
    lcd.setCursor(row1Fill[i], 0);
    lcd.write(8);
  }
  
  for(int i = 0; i < row2FillNum; i++)
  {
    lcd.setCursor(row2Fill[i], 1);
    lcd.write(8);
  }  
}
//--------------------------------------------------------------
//animated sequence for robot face while resting
void restSequence()
{
  int closedEyesDur = 5000;
  int openDelay = 250;
  closeEyesFace();
  delay(closedEyesDur);
  openEyes();
  movingEyes(0);
  closeEyesFace();
  delay(1000);
}

//--------------------------------------------------------------
//animated sequence of robot face blinking & smiling while moving
void smileBlinkSequence()
{ 
  int openEyesDur = 5000;
  int blinkDelay = 500;
  openEyes();
  delay(openEyesDur);
  closeEyesFace();
  delay(blinkDelay);
  openEyes();
  delay(blinkDelay);
  closeEyesFace();
  delay(blinkDelay);
  openEyes();
  delay(1000);
}

//--------------------------------------------------------------
//animated sequence of sweating robot face
//a drip of sweat will appear on edges of face
void sweatingFaceSequence()
{
  sweatFace();
  sweatSequence(2);
  sweatFace();
  sweatSequence(13);
  delay(1000);
}

//--------------------------------------------------------------
//animated sequence of robot face shifting to the right
void turningRightSequence()
{
  for(int i = 0; i <= 16; i++)
  {
    moveFaceLeft(i);
    delay(25);
  }
  //delay(1000);
}

//--------------------------------------------------------------
//animated sequence of robot face shifting to the left
void turningLeftSequence()
{
  for(int i = 0; i <= 16; i++)
  {
    moveFaceRight(-i);
    delay(25);
  }
  //delay(1000);
}

//--------------------------------------------------------------
//animated sequence that'll shift robot's face edge to edge while
//changing it's eyes from heartShape, open, closed
void danceFaceSequence()
{
  heartFace();
  for(int i = 0; i < 5; i++)
  {
    setFace(-i,heartEyes);
  }
  delay(1000);
  movingEyes(-4);
  setFace(-4, eyeMiddle);
  delay(1000);
  
  for(int i = -4; i < 5; i++)
  {
    setFace(i,eyeMiddle);
  }
  delay(1000);
  movingEyes(4);
  setFace(4, heartEyes);
  delay(1000);
  
  for(int i = 4; i > 0; i--)
  {
    setFace(i,heartEyes);
  }
  heartFace();
  delay(2000);
}
                    
//--------------------------------------------------------------
//animated sequence for sweat drip, used in 
//use custom char # 6 & 7 to avoid overlap
void sweatSequence(int pos)
{
  for (int i = 0; i < 24; i++)
  {
    lcd.createChar(6, sweat[i]);
    lcd.setCursor(pos,0);
    lcd.write(6);
    lcd.createChar(7, sweat2[i]);
    lcd.setCursor(pos,1);
  lcd.write(7);
    delay(150);
  }
}

//--------------------------------------------------------------
//moves the eyes, used in restSequence
void movingEyes(int p)
{
  int dur = 500;
  
  lcd.createChar(2, movingEyesTopLeft);
  lcd.setCursor(5 + p, 0);
  lcd.write(2);
  lcd.setCursor(10 + p, 0);
  lcd.write(2);
  delay(dur);
  lcd.createChar(2, movingEyesTopRight);
  lcd.setCursor(5 + p, 0);
  lcd.write(2);
  lcd.setCursor(10 + p, 0);
  lcd.write(2);
  delay(dur);
  lcd.createChar(2, movingEyesBottomRight);
  lcd.setCursor(5 + p, 0);
  lcd.write(2);
  lcd.setCursor(10 + p, 0);
  lcd.write(2);
  delay(dur*2);
  lcd.createChar(2, movingEyesTopRight);
  lcd.setCursor(5 + p, 0);
  lcd.write(2);
  lcd.setCursor(10 + p, 0);
  lcd.write(2);
  delay(dur*2);
  /*
  lcd.createChar(2, movingEyesTopLeft);
  lcd.setCursor(5,0);
  lcd.write(2);
  lcd.setCursor(10, 0);
  lcd.write(2);
  delay(dur);
  */
}
  
//--------------------------------------------------------------
void setFace(int k, byte arrEyes[])
{
  lcd.createChar(1, arrEyes);
  lcd.setCursor((5 + k) % 16, 0);
  lcd.write(1);
  lcd.setCursor((10 + k) % 16, 0);
  lcd.write(1);
  
  lcd.createChar(4, smile1);
  lcd.setCursor((6 + k) % 16, 1);
  lcd.write(4);
  
  lcd.createChar(5, smile2);
  lcd.setCursor((7 + k) % 16, 1);
  lcd.write(5);
  
  lcd.createChar(6, smile3);
  lcd.setCursor((8 + k) % 16, 1);
  lcd.write(6);
  
  lcd.createChar(7, smile4);
  lcd.setCursor((9 + k) % 16, 1);
  lcd.write(7);
  
  //holds the num of boxes that has to be filled with white
  int row1FillNum = 14;
  int row2FillNum = 12;
  
  //array of int that hold the position of boxes that has to be filled with white
  int row1Fill[] = {0, 1, 2, 3, 4, 6, 7, 8, 9, 11, 12, 13, 14, 15};
  int row2Fill[] = {0, 1, 2, 3, 4, 5, 10, 11, 12, 13, 14, 15};
  
  lcd.createChar(8, fillWhite);
  
  //for loop to simplfy process
  for(int i = 0; i < row1FillNum; i++)
  { 
    lcd.setCursor((row1Fill[i] + k) % 16, 0);
    lcd.write(8);
  }
  
  for(int i = 0; i < row2FillNum; i++)
  {
    lcd.setCursor((row2Fill[i] + k) % 16, 1);
    lcd.write(8);
  }    
}

/*
List of functions that will display animated face for different actions

smileBlinkSequence(): Robot face will blink while smiling
  - used when Block-E is moving
    
sweatingFaceSequence(): Robot face will be looking like he's putting in work
            and there will be sweat dripping 
    - Used when Block_E is picking up parts
    
restSequence(): Robot face will be closed and open once in a while. Eyes will
        will move around and check for surrounding before closing again
    - Used when Block-E is not doing anything
    
turningRightSequence(): Robot face will be looking to the right and it will
            shift to the right until it reaches the edge, in which
                        the face will reapear from the left edge. 
                        One loop will be until face returns to original pos
  - Used when Block-E is turing to the right
    
turningLeftSequence(): Robot face will be looking to the left and it will
            shift to the left until it reaches the edge, in which
                        the face will reapear from the right edge. 
                        One loop will be until face returns to original pos
  - Used when Block-E is turing to the left
    
danceSequense

*/

/*
void loop() {
  int d = 4000;
  openEyes();
  delay(d);
  sweatFace();
  delay(d);
  closeEyesFace();
  delay(d);


  smileBlinkSequence();
  sweatingFaceSequence();
  restSequence();
  
  
  
  turningRightSequence();
  turningRightSequence();
  delay(1000);
  turningLeftSequence();
  turningLeftSequence();
  delay(2000);
  danceFaceSequence();
  
}
*/
