#include <Parts_base.h>



void setup() {
  Serial.begin(9600);
}

void loop() {
  String s = receive_String('\n');
  if (s.length() != 0) Serial.println(s);
}
