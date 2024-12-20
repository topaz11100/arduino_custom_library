#ifndef IO_helper_h
#define IO_helper_h

#include "Arduino.h"

char receive_char(char error_char);
String receive_String(char terminal_char);

class Protocol
{
public:
    Protocol(char c, int n) :s{ new String[n] }, sep{ c }, sep_count{ n - 1 } {}
    void strip(const String& str);
    const String& operator[](int n) { return s[n]; }
    void fillintarr(int arr[]);
    ~Protocol() { delete[] s; }
private:
    String* s;
    char sep;
    int sep_count;
};

#endif
