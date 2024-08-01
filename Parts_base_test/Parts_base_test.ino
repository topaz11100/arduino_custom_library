#include <Parts_base.h>



void setup(){
  Serial.begin(9600);

}
void loop(){
  int* v = a();
  Serial.println(String(v[0]) + String(v[1]));
}

int* a(){
  int q[2] = {10, 49};
  return q;
}


