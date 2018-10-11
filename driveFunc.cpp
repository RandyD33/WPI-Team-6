#include"MyRobot.h"

void MyRobot::timeBasedRed() {
  drive(150, 150);
  delay(600);
  drive(90, 90);

}

void MyRobot::timeBasedBlue() {
  drive(150, 150);
  delay(600);
  drive(90, 90);

}

void MyRobot::lightBasedRed() {
  drive(120, 120);
  while (true) {
    if (digitalRead(10) == HIGH) {
      drive(90, 90);
      break;
    }
  }
  drive(45, 135);
  delay(450);
  drive(90, 90);
  drive(120,120);
  delay(400);
  drive(90,90);
}
void MyRobot::lightBasedBlue() {
  drive(120, 120);
  while (true) {
    if (digitalRead(10) == HIGH) {
      drive(90, 90);
      break;
    }
  }
  drive(135, 45);
  delay(450);
  drive(90, 90);
  drive(120, 120);
  delay(400);
  drive(90, 90);
}
