#include <Servo.h>
// initialize x axis motor
Servo x;
int servoX = 0;
int servoXLimitHigh = 45;
int servoXLimitLow = 0;

// initialize y axis motor
Servo y;
int servoY = 0; 
int servoYLimitHigh = 180;
int servoYLimitLow = 0;

// assign LDR pins
int ldrTopL = 3; // top left
int ldrTopR = 2; // top right 
int ldrBottomL = 1; // bottom left 
int ldrBottomR = 0; // bottom right 

// attach motors in setup and establish loop delay
void setup() {
  x.attach(10);
  y.attach(9);
  delay(500);
}

void loop() {
  // read values of servomotors
  servoX = x.read();
  servoY = y.read();
  
  // read values from each LDR
  int topL = analogRead(ldrTopL);
  int topR = analogRead(ldrTopR);
  int bottomL = analogRead(ldrBottomL);
  int bottomR = analogRead(ldrBottomR);
  
  // calculating average LDR values in each direction
  int avgTop = (topL + topR) / 2; // average of top LDRs
  int avgBottom = (bottomL + bottomR) / 2; // average of bottom LDRs
  int avgLeft = (topL + bottomL) / 2; // average of left LDRs
  int avgRight = (topR + bottomR) / 2; // average of right LDRs

  // compare brightnesses of top/bottom to determine x movement
  // case 1: bottom brighter than top
  if (avgTop < avgBottom) {
    if (servoX > servoXLimitHigh) {
      // keep servoX speed within range
      servoX = servoXLimitHigh;
    } else {
      // move toward bottom
      x.write(servoX - 2);
    }
  // case 2: top brighter than bottom
  } else if (avgBottom < avgTop) {
    if (servoX < servoXLimitLow) {
      // keep servoX speed within range
      servoX = servoXLimitLow;
    } else {
      // rotate toward top
      x.write(servoX + 2);
    }
  } else {
    x.write(servoX);
  }

  // compare brightnesses of left/right to determine y movement
  // case 1: left brighter than right
  if (avgLeft > avgRight) {
    if (servoY > servoYLimitHigh) {
      // keep servoY speed within range
      servoY = servoYLimitHigh;
    } else {
      // move toward left
      y.write(servoY - 2);
    }
  // case 2: right brighter than left
  } else if (avgRight > avgLeft) {
    if (servoY < servoYLimitLow) {
      // keep servoY speed within range
      servoY = servoYLimitLow;
    } else {
      // move toward right
      y.write(servoY + 2);
    }
  } else {
    y.write(servoY);
  }

  // cooldown before next calibration
  delay(50);
}
