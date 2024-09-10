/*

*/
#include <stdarg.h>
#include <ojw.h>

const int buttonPin = 3;  // the number of the pushbutton pin
const int magneticPin = 0;    // the number of the LED pin
int buttonState = 0;

CProtocol2 m_CMot;

void setup() {
  // put your setup code here, to run once:
  pinMode(magneticPin, OUTPUT);
  pinMode(buttonPin, INPUT);



  Serial.begin(9600);
  m_CMot.Open(1000000);
  m_CMot.SetTorq(true);
  m_CMot.SyncRead("1,2,3,4");
}
String m_strCmd = "";
void loop() {
  // put your main code here, to run repeatedly:
  // Serial.println(m_CMot.m_aCParam[0].m_fMechMove);
  
  

  
  // 통신으로 제어하기 위해 사용
  m_CMot.Stream(Serial);

  // 3번 핀은 이용한 버튼을 누르면 동작
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("버튼눌림");
    m_CMot.Play("1000,0,2,0,3,0,4,0")

    //m_CMot.Load("test_home.txt");


    m_CMot.Load("test_1.txt");
    digitalWrite(ledPin, HIGH);
    delay(3000);

    
    m_CMot.Load("test_home.txt");    
    m_CMot.Load("test_2.txt");
    digitalWrite(ledPin, LOW);

    m_CMot.Load("test_home.txt");    

    // m_CMot.Play("1000, 0, 1, 10, 2, 10");
    // m_CMot.Play("1000, 0, 1, 0, 2, 0");
  }

  // Serial.println("Delay");
  // delay(3000);

  /*m_CMot.Play("0,0,3,2");
  m_CMot.Play("1000, 0, 1, 10", true);
  m_CMot.Play("1000, 0, 2, 10");
  m_CMot.Play("0,0,3,-2");
  m_CMot.Play("1000, 0, 1, -10", true);
  m_CMot.Play("1000, 0, 2, -10");
  delay(3000);
  m_CMot.Play("0,0,3,0");
  delay(3000);*/

  /*m_CMot.Play("0,0,1,10,2,10,3,10");
  delay(6000);
  m_CMot.Play("0,0,1,-10,2,-10,3,-10");
  delay(6000);
  m_CMot.Play("0,0,1,0,2,0,3,0");
  delay(3000);*/
  /*float afDatas[8] = {0, 0, 1, 10, 2, 10,3,10};
  float afDatas0[8] = {0, 0, 1, 0, 2, 0,3,0};
  m_CMot.SetSpeed(afDatas,8);
  // m_CMot.Load("test.txt");
  delay(10000);
  m_CMot.SetSpeed(afDatas0, 8);
  delay(1000);
*/


 /* m_CMot.Load("test.txt");
  delay(3000);
  Serial.println("delay 3000");
  m_CMot.Play("1000,0,1,-10,2,-10,3,-10");
  Serial.println("0");*/
/*
  //test(3, 10.5, 21, 33.3, 55.0, 54.3);
  //float afDatas[6] = {1000, 0, 1, 90, 2, 90};
  delay(1000);
  Serial.println("ready");
  m_CMot.SyncRead("1,2,3");
  Serial.println("do it");
  m_CMot.Move("1000,0,1,90,2,90,3,90");
  Serial.println("90");
  delay(1000);
  m_CMot.Move("1000,0,1,0,2,0,3,0");
  Serial.println("0");
  delay(1000);
  */
}
/////////////////////
