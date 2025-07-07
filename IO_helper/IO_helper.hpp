#ifndef IO_helper_h
#define IO_helper_h

#include "Arduino.h"

char receive_char(char error_char);
String receive_String(char terminal_char, char error_char = '?');

class Protocol
{
    /*
    규격화된 문자열에 대해 문자열 배열처럼 행동함
    !!!!! 예외처리 안해서 반드시 규격 지켜야함 !!!!!
    규격(괄호 무시) : (문자열)(구분자) * size <- 마지막 토큰에도 구분자가 붙어야함
    */
public:
    Protocol(int s, char c): str_arr{new String[s]}, size{s}, sep{c} {}
    ~Protocol() { delete[] str_arr; }

    const String &operator[](int n) const { return str_arr[n]; }

    bool receive(String& input);
    void store_int_arr(int target[]);
private:
    String* str_arr;
    int size;

    char sep;
};

#endif
