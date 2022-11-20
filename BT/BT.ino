#include <SoftwareSerial.h>
SoftwareSerial myBTSerial(2, 3); // RX | TX
// Connect the HC‐06 TX to the Arduino RX on pin 2.
// Connect the HC‐06 RX to the Arduino TX on pin 3 through a voltage divider.

String command = ""; // Stores response from HC-06 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           //monitor
  myBTSerial.begin(9600);       //bluetooth 

  Serial.println("Now, sent AT+HELP");  
  myBTSerial.print("AT+HELP");                  //PING
  if (myBTSerial.available()) {
    while(myBTSerial.available()) { // While there is more to be read, keep reading.
    delay(3);
    char c = myBTSerial.read();
      command += c;    
    }
  }
  Serial.println(command + "\n");  // print response
  delay(20000);
  command = ""; // No repeats

  Serial.println("Now, sent AT+NAMEwenchaohc_06"); 
  myBTSerial.print("AT+NAMEwenchaohc_06");        //CHANGE NAME
  if (myBTSerial.available()) {
    while(myBTSerial.available()) { // While there is more to be read, keep reading.
        delay(3);
      command += (char)myBTSerial.read();  
    }
  }
  Serial.println(command);  // print response
  delay(20000);
  command = ""; // No repeats
  
  Serial.println("Now, sent AT+PIN1234");
  myBTSerial.print("AT+PIN1234");        //CHANGE PASSWORD
  if (myBTSerial.available()) {
    while(myBTSerial.available()) { // While there is more to be read, keep reading.
        delay(3);
      command += (char)myBTSerial.read();  
    }
  }
  Serial.println(command);  // print response
  delay(20000);
  command = ""; // No repeats

  Serial.println("Now, sent AT+BAUD4\n");  
  myBTSerial.print("AT+BAUD4");               //CHANGE SPEED TO 115K
  if (myBTSerial.available()) {
    while(myBTSerial.available()) { // While there is more to be read, keep reading.
      command += (char)myBTSerial.read();    
    } 
  } 
  Serial.println(command + "\n");  // print response
  delay(10000);
  command = ""; // No repeats
}

void loop(){
//  if (myBTSerial.available()) {
//    while(myBTSerial.available()) { // While there is more to be read, keep reading.
//      command += (char)myBTSerial.read();    
//    } 
//  } 
//  Serial.println(command + "\n");  // print response
}
