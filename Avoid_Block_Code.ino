#include <Adafruit_NeoPixel.h>
#define PIN 6
//네오픽셀을 사용하기 위해 객체 하나를 생성한다. 
//첫번째 인자값은 네오픽셀의 LED의 개수
//두번째 인자값은 네오픽셀이 연결된 아두이노의 핀번호
//세번째 인자값은 네오픽셀의 타입에 따라 바뀌는 flag
Adafruit_NeoPixel strip = Adafruit_NeoPixel(300, PIN, NEO_GRB + NEO_KHZ800);

int second = 0;
int b_speed = 3000;
int speed = 200;
int level = 3;
int count = 0;
int r_x_d = 0;
int r_y_d = 0;
int b_x_d = 0;
int b_y_d = 0;
int r_head[] = {1,30};
int b_head[] = {10,30};
int hole = 0;
int block_list[] = {1,2,3,4,5,6,7,8,9,10};
int block_y = 0;
int R;
int G;
int B;
int game_start = 0;
int turn = 0;
int r_life = 4;
int b_life = 4;

int check = 1;

int cal(int x, int y) { //300개 버전
  if (x%2 == 1) {
  int local = x*30 - y;
  return local;
  }
  if (x%2 == 0) {
    int local = (x-1)*30 - 1 + y;
    return local;
  }
}

void screen_clear() {
  for (int i = 0; i<300; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

void on(int x,int color1, int color2, int color3) {
  strip.setPixelColor(x, color1, color2, color3);
}
void make_hole() {
  hole =random(1,11);
  for (int i = 1; i<11; i++) {
    if (hole == i) {
      block_list[i-1] = 0;
    }
  }
}

void head_move(int body[], int x_d, int y_d) {
  
  if (body[0]>0 and body[0]<11) { //body의 x축 움직임
    body[0] = body[0] + x_d;
  }
  if (body[0]==0) {
    body[0] = body[0] + 1;
  }
  if (body[0]==11) {
    body[0] = body[0] - 1;
  }

  if (body[1]>0 and body[1]<31) {//body의 y축 움직임
    body[1] = body[1] + y_d;
  }
  if (body[1]==0) {
    body[1] = body[1] + 1;
  }
  if (body[1]==31) {
    body[1] = body[1] - 1;
  }
}

void show_r_life(int life) {
  if (life == 4) {
    on(cal(1,15),120,0,0);
    on(cal(2,15),120,0,0);
    on(cal(3,15),120,0,0);
    on(cal(4,15),120,0,0);
  }
  if (life == 3) {
    on(cal(1,15),120,0,0);
    on(cal(2,15),120,0,0);
    on(cal(3,15),120,0,0);
  }
  if (life == 2) {
    on(cal(1,15),120,0,0);
    on(cal(2,15),120,0,0);
  }
  if (life == 1) {
      on(cal(1,15), 120, 0, 0);
  }
}

void show_b_life(int life) {
  if (life == 4) {
    on(cal(7,15),0,0,120);
    on(cal(8,15),0,0,120);
    on(cal(9,15),0,0,120);
    on(cal(10,15),0,0,120);
  }
  if (life == 3) {
    on(cal(8,15),0,0,120);
    on(cal(9,15),0,0,120);
    on(cal(10,15),0,0,120);
  }
  if (life == 2) {
    on(cal(9,15),0,0,120);
    on(cal(10,15),0,0,120);
    
  }
  if (life == 1) {
      on(cal(10,15), 0, 0, 120);
  }
}

void setup() {
  Serial.begin(9600); 
  strip.begin(); //네오픽셀을 초기화하기 위해 모든LED를 off시킨다
  strip.show(); 
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
}

void loop() {
  if (game_start == 0) {
    if (turn == 0) {
      r_life = 4;
      b_life = 4;
      r_head[0] = {1};
      b_head[0] = {10};
      r_head[1] = {30};
      b_head[1] = {30};
      block_y = 0;
      turn++;
    }
    
  Serial.print(game_start);
  //Serial.print("  ");
  //Serial.println(b_life);
  int R_X = analogRead(A1);
  int R_Y = analogRead(A0);
  int R_Z = digitalRead(8);
  
  int B_X = analogRead(A3);
  int B_Y = analogRead(A2);
  int B_Z = digitalRead(9); 

  
  /*Serial.print(R_X); // X축 값이 표기됩니다.
  Serial.print("  ");           //숫자가 헷깔리지않토록 중간에 공백칸을 두었습니다
  Serial.print(R_Y); // X축 값이 표기 됩니다.
  Serial.print("  ");           //숫자가 헷깔리지않토록 중간에 공백칸을 두었습니다.
  Serial.println(R_Z); // Z축(스위치) 값이 표기됩니다.      

  Serial.print(B_X); // X축 값이 표기됩니다.
  Serial.print("  ");           //숫자가 헷깔리지않토록 중간에 공백칸을 두었습니다
  Serial.print(B_Y); // X축 값이 표기 됩니다.
  Serial.print("  ");           //숫자가 헷깔리지않토록 중간에 공백칸을 두었습니다.
  Serial.println(B_Z); // Z축(스위치) 값이 표기됩니다. */
  
    
  r_x_d = 0;
  r_y_d = 0;
  b_x_d = 0;
  b_y_d = 0;
  
  if (R_X > 600){
    r_x_d = 1;
    }
    
  if (R_X < 200){
    r_x_d = -1;
    }
  
  if (R_Y > 600){
    r_y_d = 1;
    }
    
  if (R_Y < 200){
    r_y_d = -1;
    }

  if (B_X > 600){
    b_x_d = 1;
    }
    
  if (B_X < 200){
    b_x_d = -1;
    }
    
  if (B_Y > 600){
    b_y_d = 1;
    }
    
  if (B_Y < 200){
    b_y_d = -1;
    }

  
  if (second%30000 == 0) {
    if (speed > 45) {
      speed = speed - 10;
    }
  }
  if (count == 0) {
    //block_list[] = {1,2,3,4,5,6,7,8,9,10};
    for (int i = 0; i<10; i++) {
      block_list[i] = i+1;
    }
    block_y = 1;
    make_hole();
    count++;
  }


Serial.print(second);
Serial.print("  ");
Serial.println(speed);

  block_y++;


  head_move(r_head, r_x_d, r_y_d);
  head_move(b_head, b_x_d, b_y_d);


if (block_y == 30) {
  count = 0;
  R = random(0,121);
  G = random(50,121);
  B = random(0,121);
}

for (int i = 0; i<10; i++) { //red가 맞는 경우
  if (cal(block_list[i],block_y) == cal(r_head[0],r_head[1])){
    r_life--;
  }
  else if (cal(block_list[i],block_y-1) == cal(r_head[0],r_head[1])) {
    r_life--;
  }

}

for (int i = 0; i<10; i++) { //blue가 맞는 경우
  if (cal(block_list[i],block_y) == cal(b_head[0],b_head[1])) {
    b_life--;
  }
  else if (cal(block_list[i],block_y-1) == cal(b_head[0],b_head[1])) {
    b_life--;
  }
}
    
    if (check == 1) {
      if (r_life == 0 and b_life == 0) {
        game_start++;
        delay(1000);
        r_life = 4;
        b_life = 4;
        for (int i = 0; i<300; i++) {
        strip.setPixelColor(i, 0, 120, 0); 
        strip.show();
        delay(5);
        }
        delay(1000);
        screen_clear();
        delay(1000);
        turn--;
        game_start--;
        speed = 200;
      }
    else if (r_life == 0) {
      game_start++;
      delay(1000);
      r_life = 4;
      for (int i = 0; i<300; i++) {
      strip.setPixelColor(i, 0, 0, 120); 
      strip.show();
      delay(5);
      }
        delay(1000);
      screen_clear();
      delay(1000);
      turn--;
      game_start--;
        speed = 200;
       }
       
    else if (b_life == 0) {
      game_start++;
      delay(1000);
      b_life = 4;
      for (int i = 0; i<300; i++) {
      strip.setPixelColor(i, 120, 0, 0); 
      strip.show();
      delay(5);
      }
      delay(1000);
      screen_clear();
      delay(1000);
      turn--;
      game_start--;
        speed = 200;
    }
    }
       
show_r_life(r_life);
show_b_life(b_life);


if (cal(r_head[0],r_head[1]) != cal(b_head[0],b_head[1])) {
  on(cal(r_head[0],r_head[1]),120,0,0);
  on(cal(b_head[0],b_head[1]),0,0,120);
}

if (cal(r_head[0],r_head[1]) == cal(b_head[0],b_head[1])) {
  on(cal(r_head[0],r_head[1]),120,0,120);
}
for (int i = 0; i<10; i++) {
  on(cal(block_list[i],block_y), R, 120, B);
}
  second = second + 1000;  
  if (second == 32000) {
    second = 0;
  }
  strip.show();
  delay(speed);
  screen_clear();
  delay(10);
  }
  
}
