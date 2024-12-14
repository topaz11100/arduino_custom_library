#include "base_part.h"

void Joystick::init(int x, int y, int z, int s)
{
	xPin = y;
	yPin = x;
	zPin = z;
	pinMode(xPin, INPUT);
	pinMode(yPin, INPUT);
	pinMode(zPin, INPUT_PULLUP);
	sense = s;
}

int Joystick::x_triread()
{
	int temp = x_read();
	if (temp < (512 - sense)) return -1;
	else if (temp > (512 + sense)) return 1;
	else return 0;
}

int Joystick::y_triread()
{
	int temp = y_read();
	if (temp < (512 - sense)) return -1;
	else if (temp > (512 + sense)) return 1;
	else return 0;
}

void Ultrasonic::init(int trig, int echo)
{
	trigPin = trig;
	echoPin = echo;
	pinMode(echoPin, INPUT);
	pinMode(trigPin, OUTPUT);
}

float Ultrasonic::distance()
{
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	long duration = pulseIn(echoPin, HIGH);
	float result = ((float)(340 * duration) / 1000) / 2;
	return result;
}