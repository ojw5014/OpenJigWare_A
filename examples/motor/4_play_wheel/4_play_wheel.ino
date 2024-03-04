#include <stdarg.h>
#include <ojw.h>

CProtocol2 m_CMot;

void setup() {
  m_CMot.Open(57600);
  m_CMot.SetTorq(true);
}

void loop() {
  // Time 0 ms(it means "set wheel type", delay 0), motor 1 -> 10 rpm
  m_CMot.Play("0,0,1,10");
  delay(3000);
  m_CMot.Play("0,0,1,-10");
  delay(3000);
  // Stop
  m_CMot.Play("0,0,1,0");
  delay(3000);
}
/////////////////////
