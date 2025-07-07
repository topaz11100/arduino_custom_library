#ifndef Servo_Arr_h
#define Servo_Arr_h

#include "Arduino.h"
#include "Servo.h"

class Servo_Arr
{
public:
    Servo_Arr(int s) : sv{ new Servo[s] }, size{ s } {}
    ~Servo_Arr() { delete[] sv; }

    Servo& operator[](int n) { return sv[n]; }

    void attach(int pin[]);
    void move_arr(int angle[], int speed);
    void move_one(int n, int angle, int speed);
private:
    Servo* sv;
    int size;
    bool issame(int angle[]);
};

#endif
