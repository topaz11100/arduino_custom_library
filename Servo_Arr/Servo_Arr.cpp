#include "Servo_Arr.hpp"

void Servo_Arr::attach(int pin[])
{
	for (int i = 0; i < size; i += 1)
		sv[i].attach(pin[i]);
}

void Servo_Arr::move_arr(int target[], int speed)
{
	uint16_t flag = 0;
	while (flag != (1 << size) - 1)
	{
		flag = 0;
		for (int i = 0; i < size; i += 1)
		{
			if 		(angle[i] > target[i]) angle[i] -= 1;
			else if (angle[i] < target[i]) angle[i] += 1;
			else						   flag |= 1 << i;
		}

		for (int i = 0; i < size; i += 1)
			sv[i].write(angle[i]);

		delayMicroseconds(speed);
	}
}

void Servo_Arr::move_one(int n, int target, int speed)
{
	while (angle[n] != target)
	{
		if 		(angle[n] > target) angle[n] -= 1;
		else if (angle[n] < target) angle[n] += 1;
		sv[n].write(angle[n]);

		delayMicroseconds(speed);
	}
}

bool Servo_Arr::is_same_pos(int target[])
{
	for (int i = 0; i < size; i += 1)
		if (angle[i] != target[i])
			return false;
	return true;
}