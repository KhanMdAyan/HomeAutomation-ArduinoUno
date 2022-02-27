#include "SoftwareSerial.h"
SoftwareSerial nod(A0, A1); // RX of arduino, TX of arduino
void setup() {
  Serial.begin(9600);
  nod.begin(38400);

}

void loop() {
  // put your main code here, to run repeatedly:

  nod.write(55);
  Serial.print(0);
  

}
