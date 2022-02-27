#include "SoftwareSerial.h"
SoftwareSerial ar(0, 1); // RX of arduino, TX of arduino
void setup() {
  ar.begin(38400);
  ar.println("no");


}

void loop() {
  // put your main code here, to run repeatedly:
  if (ar.available()) {
  ar.print(ar.read());
  }
}
