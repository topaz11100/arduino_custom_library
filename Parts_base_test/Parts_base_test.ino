#include <Parts_base.h>

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

Strip s{';', 2};

void setup(){
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();
}
void loop(){
  String received = receive_String('\n');
  if (received.length() == 0) return;

  String str; int x; int y;
  assign(received, str, x, y);

  lcd_print(lcd, str, x, y);
}

void assign(const String& received, String& str, int& x, int& y){
  s.decomposition(received);
  str = s[0]; x = s[1].toInt(); y = s[2].toInt();
}


