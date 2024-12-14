#ifndef lcd_helper_h
#define lcd_helper_h

#include "Arduino.h"
#include "LiquidCrystal_I2C.h"

void lcd_print(LiquidCrystal_I2C& lcd, const String& str, int x, int y);

//����ũ�⿡ �°� ������ ä���ִ� ��Ʈ���Լ�
String make_space(const String& str, int lcd_width, int mode = 0);

#endif