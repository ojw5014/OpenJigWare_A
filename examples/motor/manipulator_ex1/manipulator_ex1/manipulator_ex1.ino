
#include <stdarg.h>
#include <ojw.h>


CProtocol2 m_CMot;

const int buttonPin = 3;  // the number of the pushbutton pin
int buttonState = 0;

void setup() {
  Serial.begin(9600);
  
  // Touch
  pinMode(buttonPin, INPUT);

  m_CMot.Open(57600);
  m_CMot.SetTorq(true);
  m_CMot.SyncRead("1,2,4,5");
  m_CMot.Play("2000,0,1,0,2,-90,4,0,5,0,6,0");
}
void loop() {  
  // shoot your command with serial monitor
  // ex) 1000ms, 0 delay, motor 1 -> 45 degree
  // 1000,0,1,45;
  m_CMot.Stream(Serial);
  // 3번 핀은 이용한 버튼을 누르면 동작
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("버튼눌림");
    m_CMot.Load("test.txt");
  }
}
/////////////////////
