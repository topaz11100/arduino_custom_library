#include "base_part.hpp"

void Joystick::init(int x, int y, int z, int s)
{
	xPin = y;
	pinMode(xPin, INPUT);

	yPin = x;
	pinMode(yPin, INPUT);
	
	Z.init(z);
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
	pinMode(trigPin, OUTPUT);

	echoPin = echo;
	pinMode(echoPin, INPUT);
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

void Dcmotor::init(int fPin, int bPin)
{
	frontPin = fPin;
	pinMode(fPin, OUTPUT);

	backPin = bPin;
	pinMode(bPin, OUTPUT);
}

void Dcmotor::front()
{
	digitalWrite(frontPin, HIGH);
	digitalWrite(backPin, LOW);
}

void Dcmotor::back()
{
	digitalWrite(frontPin, LOW);
	digitalWrite(backPin, HIGH);
}

void Dcmotor::stop()
{
	digitalWrite(frontPin, LOW);
	digitalWrite(backPin, LOW);
}