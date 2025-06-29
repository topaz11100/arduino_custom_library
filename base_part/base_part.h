#ifndef base_part_h
#define base_part_h

#include "Arduino.h"

class Actuator
{
public:
    Actuator(int p) : pin(p), status(false) {}
    void init() { pinMode(pin, OUTPUT); }
    void write(bool state) { digitalWrite(pin, state); status = state; }
    bool get_status() const { return status; }

private:
    int pin;
    bool status;
};

class AnalogSensor
{
public:
    AnalogSensor(int p, int t) : pin(p), threshold(t) {}
    int read() { return analogRead(pin); }
    bool trigger() { return read() >= threshold; }
    void set_thre(int new_thre) { threshold = new_thre; }

private:
    int pin;
    int threshold;
};

class Button
{
public:
    void init(int p) { pin = p; pinMode(p, INPUT_PULLUP); }

    bool is_pushed() { return !digitalRead(pin); }
    void blocking_neutral() { while (true) { if (!is_pushed()) return; } }
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

    bool z_read() { return Z.is_pushed(); }

    bool is_zero() { return !(x_triread() || y_triread() || z_read()); }
    void blocking_neutral() { while (true) { if (is_zero()) return; } }
private:
    int xPin;
    int yPin;
    Button Z;
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

class Dcmotor
{
public:
    void init(int fPin, int bPin);
    void front();
    void back();
    void stop();
private:
    int frontPin;
    int backPin;
};

#endif
