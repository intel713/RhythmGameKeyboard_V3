# RhythmGameKeyboard_V3
자작 사볼콘 3세대

atmega32u4 기반 아두이노를 사용한 리듬게임용 키보드.

BT버튼 4개, FX버튼 2개, start버튼 1개, 아날로그 노브 2개로 구성되어 있음.
start버튼을 누른 채로 아두이노에 전원을 인가하면 ADOFAI(A Dance Of Fire And Ice)모드로, 그렇지 않으면 SDVX(사운드 볼텍스) 모드로 진입.

# 사용 부품
1 * Arduino Pro Micro

2 * 로터리 엔코더(38S6G5-B-G24N38S6G5-B-G24N)

6 * 키보드 갈축 스위치

1 * 키보드 흑축 스위치

5 * 1.5U 키캡

2 * 2U 키캡

# 참고사항
필요 라이브러리:
Keyboard.h
Encoder.h
Adafruit_NeoPixel.h
