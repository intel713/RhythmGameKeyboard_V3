#define  ENCODER_OPTIMIZE_INTERRUPTS

#include <Keyboard.h>
#include <Encoder.h>
#include <Adafruit_NeoPixel.h>

//==========SETTINGS==========
//=====핀 설정=====
#define LED_PIN 16

int btA = 4;
int btB = 5;
int btC = 6;
int btD = 7;

int fxL = 8;
int fxR = 9;

int start = 10;

int volLkey[2] = {2, 14};
int volRkey[2] = {15, 3};

//=====키 설정=====
//!!대문자 금지!!
int btAkey = 'd';
int btBkey = 'f';
int btCkey = 'j';
int btDkey = 'k';

int fxLkey = 'c';
int fxRkey = 'm';

int startkey = 176; //ENTER / RETURN

int volLcwkey = 's';
int volLccwkey = 'a';
int volRcwkey = ';';
int volRccwkey = 'l';

//=====LED 설정=====
#define LED_COUNT 48
#define LED_BRIGHTNESS 100

//=====노브 감도 설정(수가 커질수록 둔감)=====
#define SENSITIVITY 20

//무지개 모드에서의 색 변화 속도(수가 커질수록 느려짐)
int rainbowSpd = 18;

//버튼 입력 반응 모드
int brTime = 60; //LED 페이드 아웃 길이

//표시 LED 색상 설정
int inpledset[22][3] =
{
  //{R, G, B}
  //-----SDVX-----
  {255, 255, 255}, //btA
  {255, 255, 255}, //btB
  {255, 255, 255}, //btC
  {255, 255, 255}, //btD
  {255, 50, 0}, //fxL
  {255, 50, 0}, //fxR
  {0, 60, 255}, //start
  {0, 130, 230}, //volL cw
  {0, 130, 230}, //volL ccw
  {230, 0, 130}, //volR cw
  {230, 0, 130},  //volR ccw
  //-----ADOFAI-----
  {255, 255, 255}, //btA
  {255, 255, 255}, //btB
  {255, 255, 255}, //btC
  {255, 255, 255}, //btD
  {255, 50, 0}, //fxL
  {255, 50, 0}, //fxR
  {0, 60, 255}, //start
  {0, 130, 230}, //volL cw
  {0, 130, 230}, //volL ccw
  {230, 0, 130}, //volR cw
  {230, 0, 130},  //volR ccw
};

//==========변수 선언==========
int mode = 0; //0:SDVX, 11:ADOFAI

unsigned int time_old = micros();

unsigned long led_count = 0;
unsigned long time_ms;
const int com_num = 9;
int com = 0;

int r = 0, g = 0, b = 0, n = 0;
int rp, gp, bp;
int br = 0;
int prs = 0;
int inp[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
//btA, btB, btC, btD, fxA, fxB, start, volL, volR

Encoder volL(volLkey[0], volLkey[1]);
Encoder volR(volRkey[0], volRkey[1]);
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  pinMode(btA, INPUT_PULLUP);
  pinMode(btB, INPUT_PULLUP);
  pinMode(btC, INPUT_PULLUP);
  pinMode(btD, INPUT_PULLUP);
  pinMode(fxL, INPUT_PULLUP);
  pinMode(fxR, INPUT_PULLUP);
  pinMode(start, INPUT_PULLUP);
  pinMode(16, OUTPUT);
  //Keyboard.begin()
  strip.begin();
  strip.clear();
  strip.setBrightness(LED_BRIGHTNESS);

  //start 키를 누른 채로 전원 인가시 ADOFAI 키로 설정
  if (digitalRead(start) == LOW) {
    brTime = 50;
    mode = 11;
    btAkey = 'd';
    btBkey = 216;
    btCkey = 215;
    btDkey = 'k';

    //start 키와 fxL과 fxR을 동시에 누른 채로 전원 인가시 btB와 btC 키 변경
    if(digitalRead(fxL) == LOW && digitalRead(fxR) == LOW)
    {
      btBkey = 'a';
      btCkey = 'b';
    }
    
    fxLkey = 'c';
    fxRkey = 'p';
    
    startkey = 177;
    
    volLcwkey = 217;
    volLccwkey = 218;
    volRcwkey = 218;
    volRccwkey = 217;
  }
  
  while (digitalRead(start) == LOW) {
    //모드 변경 후 start버튼 입력을 중지할 때 까지 대기
  }
}

long int volL_old = volL.read();
long int volR_old = volR.read();

void loop() {
  //BT 버튼 입력 처리
  if (digitalRead(btA) == LOW) {
    Keyboard.press(btAkey);
    inp[0] = 1;
  }
  else {
    Keyboard.release(btAkey);
    inp[0] = 0;
  }
  
  if (digitalRead(btB) == LOW) {
    Keyboard.press(btBkey);
    inp[1] = 1;
  }
  else {
    Keyboard.release(btBkey);
    inp[1] = 0;
  }

  if (digitalRead(btC) == LOW) {
    Keyboard.press(btCkey);
    inp[2] = 1;
  }
  else {
    Keyboard.release(btCkey);
    inp[2] = 0;
  }

  if (digitalRead(btD) == LOW) {
    Keyboard.press(btDkey);
    inp[3] = 1;
  }
  else {
    Keyboard.release(btDkey);
    inp[3] = 0;
  }
  
  //FX 버튼 입력 처리
  if (digitalRead(fxL) == LOW) {
    Keyboard.press(fxLkey);
    inp[4] = 1;
  }
  else {
    Keyboard.release(fxLkey);
    inp[4] = 0;
  }
  if (digitalRead(fxR) == LOW) {
    Keyboard.press(fxRkey);
    inp[5] = 1;
  }
  else {
    Keyboard.release(fxRkey);
    inp[5] = 0;
  }
  
  //Start 버튼 입력 처리
  if (digitalRead(start) == LOW) {
    Keyboard.press(startkey);
    inp[6] = 1;
  }
  else {
    Keyboard.release(startkey);
    inp[6] = 0;
  }
  
  //아날로그 디바이스 입력 처리
  if (mode == 0) {
    //노브 값을 시간에 대해 미분
    int volL_current = volL.read();
    int volR_current = volR.read();
    unsigned int dt = micros() - time_old;
    float dLdt = 100000.0 * (volL_current - volL_old) / dt;
    float dRdt = 100000.0 * (volR_current - volR_old) / dt;

    //volL 엔코더 입력 처리
    if (dLdt > SENSITIVITY) {
      Keyboard.release(volLccwkey);
      Keyboard.press(volLcwkey);
      inp[7] = 1;
    }
    else if (dLdt < -SENSITIVITY) {
      Keyboard.release(volLcwkey);
      Keyboard.press(volLccwkey);
      inp[7] = -1;
    }
    else {
      Keyboard.release(volLcwkey);
      Keyboard.release(volLccwkey);
      inp[7] = 0;
    }
    volL_old = volL_current;
    //volR 엔코더 입력 처리
    if (dRdt > SENSITIVITY) {
      Keyboard.release(volRccwkey);
      Keyboard.press(volRcwkey);
      inp[8] = 1;
    }
    else if (dRdt < -SENSITIVITY) {
      Keyboard.release(volRcwkey);
      Keyboard.press(volRccwkey);
      inp[8] = -1;
    }
    else {
      Keyboard.release(volRcwkey);
      Keyboard.release(volRccwkey);
      inp[8] = 0;
    }
    volR_old = volR_current;
  }
  time_old = micros();
  ledCheck();
}

void ledCheck()
{
  strip.setBrightness(LED_BRIGHTNESS);
  int a = analogRead(A0);
  if(a < 100) {
    strip.clear();
    strip.show();
  }
  else if(100 <= a && a < 350) {
    if(mode == 0) {
      inputled();
    }
    else {
      inputrain(rainbowSpd);
    }
  }
  else if(350 <= a && a < 400) {
    poten(400);
  }
  else if(400 <= a && a < 1000) {
    poten(a);
  }
  else if(a >= 1000) {
    rainbow(rainbowSpd);
  }
}

void inputrain(int del)
{
  prs = 0;
  for (int i = 0; i < 7; i++) {
    if (inp[i] != 0) {
      prs = 1;
      break;
    }
  }
  
  if (prs == 0 && br > 0) {
    br = br - 1;
  }
    
  if(prs == 1) {
    br = brTime;
  }
  
  strip.setBrightness(map(br, brTime, 0, LED_BRIGHTNESS, 0));
  rainbow(del);
}

void inputled()
{
  strip.clear();
  n = 0;
  for (int j = 0; j < 9; j++) {
    if(inp[j] != 0) {
      r = 0;
      g = 0;
      b = 0;
    }
  }
  for (int j = 0; j < 7; j++) {
    if (inp[j] == 1) {
      r = r + inpledset[j+mode][0];
      g = g + inpledset[j+mode][1];
      b = b + inpledset[j+mode][2];
      n = n + 1;
    }
  }

  if (mode == 0) {
    if (inp[7] == 1) {
      r = r + inpledset[7+mode][0];
      g = g + inpledset[7+mode][1];
      b = b + inpledset[7+mode][2];
      n = n + 1;
    }
    else if(inp[7] == -1) {
      r = r + inpledset[8+mode][0];
      g = g + inpledset[8+mode][1];
      b = b + inpledset[8+mode][2];
      n = n + 1;
    }
    if (inp[8] == 1) {
      r = r + inpledset[9+mode][0];
      g = g + inpledset[9+mode][1];
      b = b + inpledset[9+mode][2];
      n = n + 1;
    }
    else if(inp[8] == -1) {
      r = r + inpledset[10+mode][0];
      g = g + inpledset[10+mode][1];
      b = b + inpledset[10+mode][2];
      n = n + 1;
    }
  }
  
  if(n == 0 && br > 0) {
    br = br - 1;
  }
    
  if(n != 0) {
    br = brTime;
    r = r / n;
    g = g / n;
    b = b / n;
  }
  
  for (int j = 0; j < strip.numPixels(); j++) {
    strip.setPixelColor(j, r, g, b);
  }
  strip.setBrightness(map(br, brTime, 0, LED_BRIGHTNESS, 0));
  strip.show();
}

void poten(int analog)
{
  int r, g, b;
  if(400 <= analog && analog < 600) {
    g = map(analog, 400, 599, 0, 255);
    r = 255 - g;
    b = 0;
  }
  else if(600 <= analog && analog < 800) {
    b = map(analog, 600, 799, 0, 255);
    g = 255 - b;
    r = 0;
  }
  else if(800 <= analog && analog < 1000){
    r = map(analog, 800, 999, 0, 255);
    b = 255 - r;
    g = 0;
  }
  for(int j = 0; j < strip.numPixels(); j++) {
    strip.setPixelColor(j, r, g, b);
  }
  strip.show();
}

void rainbow(uint8_t wait) {
  if(millis() > time_ms + wait) {
    time_ms = millis();
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+led_count) & 255));
    }
    strip.show();
    led_count++;
    if(led_count>=256) {
      led_count = 0;
      com++;
      if(com > com_num) {
        com = 0;
      }
    }
  }
}

uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
