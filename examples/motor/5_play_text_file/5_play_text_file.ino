/*

*/
#include <stdarg.h>
#include <ojw.h>

CProtocol2 m_CMot;

void setup() {
  Serial.begin(9600);
  m_CMot.Open(1000000);
  m_CMot.SetTorq(true);
}

void loop() {

  
  m_CMot.Load("test.txt"); // Play with sd memory
  
}
/////////////////////
