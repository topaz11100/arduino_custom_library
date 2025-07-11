#include "IO_helper.hpp"

void Ser::flush()
{
	while (ser.available())
		ser.read();
}

char Ser::recv_char(char empty = '?', bool do_flush = false)
{
	if (ser.available())
		empty = ser.read();
	if (do_flush)
		flush();
	return empty;
}

String Ser::recv_str(char end = '\n', char empty = '?', bool do_flush = true)
{
	String result = "";

	if (!ser.available()) return result;

	while (true)
	{
		char temp = recv_char(empty, false);
		if (temp == empty) continue;
		if (temp == end)   break;
		result += temp;
	}

	if (do_flush)
		flush();

	return result;
}

bool Protocol::receive(String& input)
{
	/*
	문자열을 받아 형식에 맞으면 내부 배열에 저장 && true 반환
	그렇지 않은 경우 false 반환 (따로 백업하지는 않음)

	받은 문자열을 순차적으로 읽어나가며 예외처리 / 저장을 한번에 함

	주요 예외 처리
	빈 문자열, 구분자 부족함 -> 앞에 저장은 하지만 false반환
	size보다 많은 토큰이 들어옴 -> size 개수만 저장되나 false반환
	*/

	// 길이 저장, 빈 문자열 처리
	const int len = input.length();
	if (len == 0) return false;
	
	int idx = 0;
	for (int i = 0; i < size; i += 1)
	{
		// 초기화
		str_arr[i] = "";

		while (input[idx] != sep)
		{
			// 여기 걸리면 배열에 다 채우기 전에 끝났다는 뜻이므로 구분자가 부족한 것
			if (idx >= len) return false;
			// 저장후 진행
			str_arr[i] += input[idx];
			idx += 1;
		}
		// 구분자는 건너 뜀
		idx += 1;
	}

	// 두 변수 값이 같아야 정상처리 (len이 더 크면 더 많은 토큰이 들어온것)
	return idx == len;
}

void Protocol::store_int_arr(int target[])
{
	for (int i = 0; i < size; i += 1)
	{
		target[i] = str_arr[i].toInt();
	}
}