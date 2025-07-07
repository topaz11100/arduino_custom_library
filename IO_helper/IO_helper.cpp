#include "IO_helper.hpp"

char receive_char(char error_char)
{
	if ( Serial.available() ) return Serial.read();
	else return error_char;
}
String receive_String(char terminal_char, char error_char = '?')
{
	String result = "";
	if ( !(Serial.available()) ) return result;
	while (true)
	{
		char temp = receive_char(error_char);
		if (temp == terminal_char) break;
		if (temp == error_char)    continue;
		result += String(temp);
	}
	return result;
}

bool Protocol::receive(String& input)
{
	const int limit = input.length();
	int idx = 0;
	for (int i = 0; i < size; i += 1)
	{
		//이전 내용 초기화
		str_arr[i] = "";

		//구분자 전 까지는 채우기
		while (input[idx] != sep)
		{
			str_arr[i] += input[idx];
			idx += 1;
			// 여기 걸리면 형식 안맞는 문자열
			if (idx >= limit) return false;
		}
		//구분자는 넘어가기
		idx += 1;
	}
	// 성공
	return true;
}

void Protocol::store_int_arr(int target[])
{
	for (int i = 0; i < size; i += 1)
	{
		target[i] = str_arr[i].toInt();
	}
}