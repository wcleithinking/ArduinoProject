#include <L298N.h>

const unsigned int EN_A = 3;
const unsigned int IN1 = 5;
const unsigned int IN2 = 6;
const unsigned int IN3 = 7;
const unsigned int IN4 = 8;
const unsigned int EN_B = 9;

L298N motor1(EN_A, IN1, IN2);
L298N motor2(EN_B, IN3, IN4);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial monitor to be opened
  }

  motor1.setSpeed(100);
  motor2.setSpeed(100);
  
}

void loop() {
  motor2.run(L298N::FORWARD);
  delay(2000);
  motor2.stop();
  delay(2000);
  // motor2.setSpeed(-255);
  motor2.run(L298N::BACKWARD);
  delay(2000);
  motor2.stop();
  delay(2000);
}
