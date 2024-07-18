#include <Parts_base.h>

Servo_vector spider{8};
const int spider_pin[8] = {4,5,6,7,8,9,10,11};
Servo turret;

Ultrasonic hc06;

//마이크로초
const int speed = 500;

// limit[위치][모드] = {{앞쪽/서는방향한계, 뒤쪽/눕는방향한계}...}
const int limit[8][2] = { {0, 155}, {30, 180}, {150, 0}, {180, 30},
	                        {180 , 90}, {0, 90}, {180, 90}, {0, 90} };
// 발의경우 뒷 원소 밖의 범위는 올라오는 각도이다

void setup() {
  Serial.begin(9600);
  hc06.init(12, 13);
  init_spider();
}
void init_spider() {
  spider.attach(spider_pin);
  turret.attach(3);
  init_position();
}
void init_position(){
  int init[8] = {(limit[0][0]+limit[0][1])/2,  (limit[1][0]+limit[1][1])/2,  (limit[2][0]+limit[2][1])/2,  (limit[3][0]+limit[3][1])/2,
                 (limit[4][0]+limit[4][1])/2,  (limit[5][0]+limit[5][1])/2,  (limit[6][0]+limit[6][1])/2,  (limit[7][0]+limit[7][1])/2 };
  spider.move_arr(init, speed);
  turret.write(90);
}
void loop() {
  char received = receive_char('?');
  if      (received == 'w') walk();
  else if (received == 's') squat();
  else if (received == 'i') init_position();
  else if (received == 'c') rotate(0);
  else if (received == 'z') rotate(1);
  else if (received == 'h') hello();
  else if (received == 'm') swim();
  else if (received == 't') tank_walk(70);
  else if (received == 'v') avoid_walk(70);
}
void lay() {
  int temp[8] = { spider[0].read(), spider[1].read(), spider[2].read(), spider[3].read(),
                  limit[4][1], limit[5][1], limit[6][1], limit[7][1] };
  spider.move_arr(temp, speed);
}
void stand() {
  int temp[8] = { spider[0].read(), spider[1].read(), spider[2].read(), spider[3].read(),
                  limit[4][0], limit[5][0], limit[6][0], limit[7][0] };
  spider.move_arr(temp, speed);
}
void squat(){
  lay();
  delay(speed/3);
  stand();
}
void walk(){
  int posi1[8]={ limit[0][0],  spider[1].read(),  limit[2][0],  spider[3].read(),
                 limit[4][1],  limit[5][1]-20,   limit[6][1],  limit[7][1]-20 };
  spider.move_arr(posi1, speed);

  int posi2[8] = {(limit[0][0]+limit[0][1])/2,  spider[1].read(),  (limit[2][0]+limit[2][1])/2,  spider[3].read(),
                  limit[4][0],  spider[5].read(),  limit[6][0],  spider[7].read() };
  spider.move_arr(posi2, speed);

  int posi3[8]={ spider[0].read(),  limit[1][0],  spider[2].read(), limit[3][0],
                 limit[4][1]+20,   limit[5][1],  limit[6][1]+20,  limit[7][1] };
  spider.move_arr(posi3, speed);

  int posi4[8] = {spider[0].read(),  (limit[1][0]+limit[1][1])/2,  spider[2].read(),  (limit[3][0]+limit[3][1])/2,
                  spider[4].read(),  limit[5][0],  spider[6].read(),  limit[7][0] };
  spider.move_arr(posi4, speed);
}
// mode 0 : 시계 / mode 1 : 반시계
void rotate(int mode){
  int posi1[8]={ limit[0][mode],  spider[1].read(),  limit[2][1-mode],  spider[3].read(),
                 limit[4][1],  limit[5][1]-20,   limit[6][1],  limit[7][1]-20 };
  spider.move_arr(posi1, speed);

  int posi2[8] = {(limit[0][0]+limit[0][1])/2,  spider[1].read(),  (limit[2][0]+limit[2][1])/2,  spider[3].read(),
                  limit[4][0],  spider[5].read(),  limit[6][0],  spider[7].read() };
  spider.move_arr(posi2, speed);

  int posi3[8]={ spider[0].read(),  limit[1][mode],  spider[2].read(), limit[3][1-mode],
                 limit[4][1]+20,   limit[5][1],  limit[6][1]+20,  limit[7][1] };
  spider.move_arr(posi3, speed);

  int posi4[8] = {spider[0].read(),  (limit[1][0]+limit[1][1])/2,  spider[2].read(),  (limit[3][0]+limit[3][1])/2,
                  spider[4].read(),  limit[5][0],  spider[6].read(),  limit[7][0] };
  spider.move_arr(posi4, speed);
}

void hello(){
  init_position();
  spider.move_one(4, 30, speed);
  spider.move_one(0, limit[0][0], speed);
  delay(speed/2);
  for(int i=0; i<2; i+=1){
    spider.move_one(0, 45, speed);
    delay(speed/2);
    spider.move_one(0, 0, speed);
    delay(speed/2);
  }
  init_position();
}

void swim(){
  int forward[8] = {limit[0][0],limit[1][0],limit[2][0],limit[3][0],
                    limit[4][0],limit[5][0],limit[6][0],limit[7][0]};
  int back[8]    = {limit[0][1],limit[1][1],limit[2][1],limit[3][1],
                    limit[4][1],limit[5][1],limit[6][1],limit[7][1]};
  spider.move_arr(forward, speed);
  stand();
  delay(speed/2);
  spider.move_arr(back, speed);
  lay();
  delay(speed/2);
  init_position();
}

void tank_walk(float s){
  walk();
  if (hc06.distance() < s){ lay(); return; }
}

float find_far_assistant(int angle, float& result){
  turret.write(angle); delay(1);
  float temp = hc06.distance();
  if(temp > result) result = temp;
  delay(1);
}
float find_far(){
  float result = 0;
  for(int i=90 ; i<180; i+=1) find_far_assistant(i, result);
  for(int i=180; i>0  ; i-=1) find_far_assistant(i, result);
  for(int i=0  ; i<90 ; i+=1) find_far_assistant(i, result);
  return result;
}

void avoid_walk(float s){
  walk();
  if( hc06.distance() < s ) return;
  float temp = find_far();
  int n = 1;
  while (true){
    for(int i=0; i<n; i+=1) rotate( n%2 );
    n += 1;
    float d = hc06.distance();
    if( (temp-5 < d) && (d < temp+5) ) {
      walk();
      return;
    }
  }
}





















































