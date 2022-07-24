# include "HCSR04.h"

const int trigPin = 9;
const int echoPin = 10;
int delayT = 500;

HCSR04 myHcsr04;

void setup() {
  	// put your setup code here, to run once:
	Serial.begin(9600);
	myHcsr04.SetTrigPin(trigPin);
	myHcsr04.SetEchoPin(echoPin);
}

void loop() {
  	// put your main code here, to run repeatedly:
	myHcsr04.getDistanceInCentimeters(delayT);
}
