#ifndef IO_helper_h
#define IO_helper_h

#include "Arduino.h"

namespace Rx
{
    void flush();
    char r_char(char empty = '?', bool do_flush = false);
    String r_str(char end = '\n', char empty = '?', bool do_flush = true);
}

namespace Log
{
    template <class STR_ABLE>
    void var(const String& name, const STR_ABLE& var)
    {
        Serial.print(name + " : ");
        Serial.print(String(var));
        Serial.println();
    }

    // vars base case (재귀 끝)
    inline void vars(const String name[])
    {
        Serial.println();
    }

    // cpp 재귀 Variadic Templates 이용 recursive case
    template <typename STR_ABLE, typename... STR_ABLES>
    void vars(const String name[], const STR_ABLE& var, const STR_ABLES& ...rest)
    {
        Serial.print(name[0] + " : ");
        Serial.print(String(var) + " / ");

        vars(name + 1, rest...);
    }

    template <class STR_ABLE>
    void arr(const String& name, const STR_ABLE arr[], int size)
    {
        Serial.print(name + " : ");
        for (int i = 0; i < size; i += 1)
            Serial.print(String(arr[i]) + " / ");
        Serial.println();
    }
}

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

    bool recv(String& input);
    void store_int_arr(int target[]);
private:
    String* str_arr;
    int size;
    char sep;
};

#endif
