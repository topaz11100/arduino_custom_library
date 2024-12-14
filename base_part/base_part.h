#ifndef base_part_h
#define base_part_h

#include "Arduino.h"

class Button
{
public:
    void init(int p) { pin = p; pinMode(p, INPUT_PULLUP); }

    bool is_pushed() { return !digitalRead(pin); }
    void button_neutral() { while (true) { if (!is_pushed()) return; } }
private:
    int pin;
};

class Joystick
{
public:
    void init(int x, int y, int z, int s);
    void set_sense(int s) { sense = s; }

    int x_read() { return 1023 - analogRead(xPin); }
    int x_triread();

    int y_read() { return 1023 - analogRead(yPin); }
    int y_triread();

    bool z_read() { return !digitalRead(zPin); }

    bool is_zero() { return !(x_triread() || y_triread() || z_read()); }
    void joystick_neutral() { while (true) { if (is_zero()) return; } }
private:
    int xPin;
    int yPin;
    int zPin;
    int sense;
};

class Ultrasonic
{
public:
    void init(int trig, int echo);
    float distance();
private:
    int trigPin;
    int echoPin;
};

#endif
