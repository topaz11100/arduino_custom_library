#include "IO_helper.h"

char receive_char(char error_char)
{
	if ( Serial.available() ) return Serial.read();
	else return error_char;
}
String receive_String(char terminal_char)
{
	String result = "";
	if ( !(Serial.available()) ) return result;
	while (true)
	{
		char temp = receive_char('?');
		if (temp == terminal_char) break;
		if (temp == '?') continue;
		result += String(temp);
	}
	return result;
}

void Protocol::strip(const String& str)
{
	// 구분자 위치 배열 생성, 배열에 위치 담기
	int* interval = new int[sep_count];
	int mark = 0;
	for (int i = 0; i < sep_count; i += 1)
	{
		interval[i] = str.indexOf(sep, mark);
		mark = interval[i] + 1;
	}
	// 스트링 필드에 구분자 위치로 생성한 부분 문자열 채워넣기
	s[0] = str.substring(0, interval[0]);
	for (int i = 1; i < sep_count; i += 1)
	{
		s[i] = str.substring(interval[i - 1] + 1, interval[i]);
	}
	s[sep_count] = str.substring(interval[sep_count - 1] + 1);
	delete[] interval;
}

void Protocol::fillintarr(int arr[])
{
	for (int i = 0; i <= sep_count; i += 1)
	{
		arr[i] = s[i].toInt();
	}
}