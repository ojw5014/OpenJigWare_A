#include <stdarg.h>
#include <ojw.h>

CProtocol2 m_CMot;

void setup() {
  m_CMot.Open(57600); // serial open, 57600 bps

  m_CMot.SetTorq(true); // Torq On
  // position read
  m_CMot.SyncRead("1,2");
}
void loop() {
  // first way. ////////////////////////////////////////////
  // ID 1, 2 -> move to 45 degree, (1000 ms, 0 ms delay)
  m_CMot.Play("1000, 0, 1, 45, 2, 45");
  // ID 1, 2 -> move to 0 degree, (1000 ms, 0 ms delay)
  m_CMot.Play("1000, 0, 1, 0, 2, 0");
  //////////////////////////////////////////////////////////
}
