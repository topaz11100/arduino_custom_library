#include <Parts_base.h>

Joystick j2;

void setup() {
  Serial.begin(9600);

  j2.init( A2,A3,4,200 );
}

void loop() {
  Serial.println( "x : " + String(j2.x_read()) +
                  " trix : " + String(j2.x_triread()) +
                  " y : " + String(j2.y_read()) +
                  " triy : " + String(j2.y_triread()) +
                  " z : " + String(j2.z_read()) );
}
