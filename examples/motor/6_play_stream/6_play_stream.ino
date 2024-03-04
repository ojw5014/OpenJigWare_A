
#include <stdarg.h>
#include "ojw.h"

CProtocol2 m_CMot;

void setup() {
  Serial.begin(9600);
  
  m_CMot.Open(57600);
  m_CMot.SetTorq(true);
  m_CMot.SyncRead("1,2,3,4,5");
}
void loop() {  
  // shoot your command with serial monitor
  // ex) 1000ms, 0 delay, motor 1 -> 45 degree
  // 1000,0,1,45;
  m_CMot.Stream(Serial);
}
/////////////////////
