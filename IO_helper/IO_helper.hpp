#ifndef IO_helper_h
#define IO_helper_h

#include "Arduino.h"

class Ser
{
public:
    Ser() : ser{Serial} {}

    void begin(int boud) { ser.begin(boud); }

    void flush();
    char recv_char(char empty = '?', bool do_flush = false);
    String recv_str(char end = '\n', char empty = '?', bool do_flush = true);

private:
    HardwareSerial &ser;
};

class Log
{
public:
    Log() : ser{Serial} {}

    template <class STRINGABLE>
    void var(const String &name, const STRINGABLE &var)
    {
        ser.print(name + " : ");

        ser.print(String(var));

        ser.println();
    }

    template <class STRINGABLE>
    void arr(const String &name, const STRINGABLE arr[], int size)
    {
        ser.print(name + " : ");

        for (int i = 0; i < size; i += 1)
            ser.print(String(arr[i]) + "/");

        ser.println();
    }

private:
    HardwareSerial &ser;
};

class Protocol
{
    /*
    규격화된 문자열에 대해 문자열 배열처럼 행동함
    !!!!! 예외처리 안해서 반드시 규격 지켜야함 !!!!!
    규격(괄호 무시) : (문자열)(구분자) * size <- 마지막 토큰에도 구분자가 붙어야함

    한 프로젝트 안에 전역으로 하나의 인스턴스만 놓고 사용
    따라서 복사 대입, 복사 생성 제거
    */
public:
    Protocol(int s, char c): str_arr{new String[s]}, size{s}, sep{c} {}
    ~Protocol() { delete[] str_arr; }

    // 전역으로 하나의 인스턴스만 놓고 사용
    Protocol(const Protocol &) = delete;
    Protocol& operator=(const Protocol &) = delete;

    const String& operator[](int n) const { return str_arr[n]; }

    bool receive(String& input);
    void store_int_arr(int target[]);
private:
    String* str_arr;
    int size;
    char sep;
};

#endif
