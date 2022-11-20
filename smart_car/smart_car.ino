#include <L298N.h>
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// motorRight
const unsigned int EN_A = 3;
const unsigned int IN1 = 4;
const unsigned int IN2 = 5;

// motorLeft
const unsigned int IN3 = 6;
const unsigned int IN4 = 7;
const unsigned int EN_B = 9;

L298N motorRight(EN_A, IN1, IN2);
L298N motorLeft(EN_B, IN3, IN4);

FreeSixIMU sixDOF = FreeSixIMU();
float measureValues[6];  // acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z
float EulerAngles[3];    // yaw pitch, roll

double kp = 10;
double kd = 0.2
;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    // wait for serial monitor to be opened
  }

  Wire.begin();
  delay(100);

   // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  sixDOF.init();
  delay(2000);

  // set 0 speed
  motorLeft.setSpeed(0);
  motorRight.setSpeed(0);
}

void loop() {

  // read IMU
  sixDOF.getValues(measureValues);
  sixDOF.getEuler(EulerAngles);

  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK); // Draw 'inverse' text
  display.setCursor(0,0);    
  display.print("X: ");  
  display.println(EulerAngles[2]);
  display.print("Y: ");  
  display.println(EulerAngles[1]);
  display.print("Z: ");  
  display.println(EulerAngles[0]);
  display.println();
  display.display();
//  Serial.print(EulerAngles[0]);
//  Serial.print("\t");
//  Serial.print(EulerAngles[1]);
//  Serial.print("\t");
//  Serial.print(EulerAngles[2]);
//  Serial.println();

//  Serial.print(measureValues[3]);
//  Serial.print("\t");
//  Serial.print(measureValues[4]);
//  Serial.print("\t");
//  Serial.print(measureValues[5]);
//  Serial.println();

  double uLeft = 0;
  double uRight = 0;

  double offSet = 89;
//  if (EulerAngles[2]>0) {
//    offSet = 89;
//  } else {
//    offSet = -91;
//  }

  double roll = EulerAngles[2] - offSet;
  
  if (abs(roll) > 40) {
    uLeft = 0;
    uRight = 0;
  } else {
    // limit signal
    if (abs(roll) > 20) {
      roll = 20*roll/abs(roll);
    }
    if (abs(measureValues[3]) > 160) {
      measureValues[3] = 160*measureValues[3]/abs(measureValues[3]);
    }
  
    // kp*roll + kd*gyro_x
     uLeft = -kp * (0 - roll) - kd * (0 + measureValues[3]);
     uRight = -kp * (0 - roll) - kd * (0 + measureValues[3]);
  }
  int16_t PWMLeft = satU(uLeft);
  int16_t PWMRight = satU(uRight);

  // set motor
  motorLeft.setSpeed(abs(PWMLeft));
  motorRight.setSpeed(abs(PWMRight));
  if (PWMLeft >= 0) {
    motorLeft.forward();
  } else {
    motorLeft.backward();
  }
  if (PWMRight >= 0) {
    motorRight.forward();
  } else {
    motorRight.backward(); 
  }

  delay(10);
}

int16_t satU(double u) {
  int16_t PWM = (u <= 255) ? (int16_t)u : 255;
  return PWM;
}
