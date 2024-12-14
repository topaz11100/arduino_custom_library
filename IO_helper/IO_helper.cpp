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
	//������ ��ġ �迭 ����, �迭�� ��ġ ���
	int* interval = new int[sep_count];
	int mark = 0;
	for (int i = 0; i < sep_count; i += 1)
	{
		interval[i] = str.indexOf(sep, mark);
		mark = interval[i] + 1;
	}
	//��Ʈ�� �ʵ忡 ������ ��ġ�� ������ �κ� ���ڿ� ä���ֱ�
	s[0] = str.substring(0, interval[0]);
	for (int i = 1; i < sep_count; i += 1)
	{
		s[i] = str.substring(interval[i - 1] + 1, interval[i]);
	}
	s[sep_count] = str.substring(interval[sep_count - 1] + 1);
	delete[] interval;
}
