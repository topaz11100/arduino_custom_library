#include "lcd_helper.hpp"

void lcd_print(LiquidCrystal_I2C& lcd, const String& str, int x, int y)
{
	lcd.setCursor(x, y);
	lcd.print(str);
}

String make_space(const String& str, int lcd_width, int mode = 0)
{
	int len_space = lcd_width - str.length();
	if (len_space <= 0) return str;

	String space = "";

	if (mode == 2)
	{
		String space2 = "";
		for (int i = 0; i < len_space / 2; i += 1) space += " ";
		for (int i = 0; i <= len_space / 2; i += 1) space2 += " ";
		return space + str + space2;
	}

	for (int i = 0; i < len_space; i += 1) space += " ";

	if      (mode == 0) return str + space;
	else if (mode == 1) return space + str;
}