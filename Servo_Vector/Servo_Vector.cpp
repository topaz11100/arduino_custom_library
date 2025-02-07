#include "Servo_vector.h"

void Servo_vector::attach(int pin[])
{
	for (int i = 0; i < size; i += 1)
	{
		sv[i].attach(pin[i]);
	}
}

bool Servo_vector::issame(int angle[])
{
	for (int i = 0; i < size; i += 1)
	{
		if (sv[i].read() != angle[i]) return false;
	}
	return true;
}

void Servo_vector::move_arr(int angle[], int speed)
{
	while ( !issame(angle) )
	{
		for (int i = 0; i < size; i += 1)
		{
			int temp = sv[i].read();
			if		(temp > angle[i]) sv[i].write(temp - 1);
			else if (temp < angle[i]) sv[i].write(temp + 1);
		}
		delayMicroseconds(speed);
	}
}

void Servo_vector::move_one(int n, int angle, int speed)
{
	while (true)
	{
		int temp = sv[n].read();
		if      (temp > angle) sv[n].write(temp - 1);
		else if (temp < angle) sv[n].write(temp + 1);
		else return;
		delayMicroseconds(speed);
	}
}
