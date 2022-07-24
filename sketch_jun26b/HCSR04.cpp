# include "HCSR04.h"
# include <Arduino.h>

using namespace std;

void HCSR04::SetTrigPin(const int TrigPin) {
    _TrigPin = TrigPin;
    pinMode(_TrigPin, OUTPUT);
}

void HCSR04::SetEchoPin(const int EchoPin) {
    _EchoPin = EchoPin;
    pinMode(_EchoPin, INPUT);
}

void HCSR04::getDistanceInCentimeters(int delayT) {
    // set trigger signal
    digitalWrite(_TrigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_TrigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_TrigPin, LOW);

    // parse pulse signal 
    duration = pulseIn(_EchoPin, HIGH);

    // convert to distance
    distanceInCentimeters = duration * SOUND_SPEED / 2;

    Serial.print(distanceInCentimeters);
    // Serial.print(" ");
    Serial.print("\n");

    delay(delayT);
}