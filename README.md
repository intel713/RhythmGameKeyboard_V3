# RhythmGameKeyboard_V3
자작 사볼콘 3세대<br>
`atmega32u4` 기반 아두이노를 사용한 리듬게임용 키보드.<br>
`BT 버튼` 4개, `FX 버튼` 2개, `START 버튼` 1개, `아날로그 노브` 2개로 구성되어 있음.<br>
<br>
`START 버튼`을 누른 채로 아두이노에 전원을 인가하면 `ADOFAI(A Dance Of Fire And Ice) 모드`로, 그렇지 않으면 `SDVX(사운드 볼텍스) 모드`로 진입.<br>
<br>
`START 버튼`과 `FX-L 버튼`과 `FX-R 버튼`을 누른 채로 아두이노에 전원을 인가하면 `ADOFAI 모드` 진입과 동시에 `BT-B`와 `BT-C`에 할당된 키를 좌우 방향키에서 `a키`와 `b키`로 변경함.<br>
(얼불춤 에디터에서 플레이 시 방향키 씹힘 버그 방지를 위함)<br>

# 사용 부품
1 * `Sparkfun Pro Micro`<br>
2 * 로터리 엔코더(`38S6G5-B-G24N`, **_정확히 5.0V 이상부터 작동_**)<br>
6 * 키보드 갈축 스위치<br>
1 * 키보드 흑축 스위치<br>
1 * 1U 키캡<br>
4 * 1.5U 키캡<br>
2 * 2U 키캡<br>
1 * 가변저항 (10KΩ)<br>
1 * 스텝 업 컨버터(아두이노의 5V 핀에서 나오는 4.8V대의 전압을 5.3V로 승압하여 엔코더로 전원 공급)<br>

# 핀 정보
`BT-A`, `BT-B`, `BT-C`, `BT-D` : `D4`, `D5`, `D6`, `D7`<br>
`FX-L`, `FX-R` : `D8`, `D9`<br>
`START` : `D10`<br>
`VOL-L`, `VOL-R` : {2, 14}, {3, 15}(디지털 핀, 순서 중요)<br>
LED 가변저항 : `A0`<br>

# 참고사항
필요 라이브러리:<br>
`Keyboard.h`<br>
`Encoder.h`<br>
`Adafruit_NeoPixel.h`<br>
