#include <L298N.h>

L298N motorLeft(9, 6, 7);

void setup() {
  // put your setup code here, to run once:
  motorLeft.setSpeed(0);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  motorLeft.setSpeed(100);
  motorLeft.forward();
  delay(2000);
  motorLeft.stop();
  delay(2000);
  motorLeft.setSpeed(200);
  motorLeft.backward();
  delay(2000);
  motorLeft.stop();
  delay(3000);
}
