#ifndef Servo_Arr_h
#define Servo_Arr_h

#include "Arduino.h"
#include "Servo.h"

class Servo_Arr
{
public:
    Servo_Arr(int s) : sv{new Servo[s]}, angle{new int[s]}, size{s} {}
    ~Servo_Arr() { delete[] sv; delete[] angle; }

    void attach(int pin[]);

    Servo& operator[](int n) { return sv[n]; }
    int angle_at(int n) const { return angle[n]; }
    
    void move_arr(int target[], int speed);
    void move_one(int n, int target, int speed);

    bool is_same_pos(int target[]);
private:
    Servo* sv;
    int* angle;
    int size;
};

#endif
