#include <stdarg.h>
#include <ojw.h>

CProtocol2 m_CMot;

void setup() {
  Serial.begin(9600); // for println  
  m_CMot.Open(57600); // serial open, 57600 bps

  m_CMot.SetTorq(true); // Torq On
  // position read
  m_CMot.SyncRead("1,2");
}
void loop() {
  // first way. ////////////////////////////////////////////
  Serial.println("play 1, 2 -> 45 degree");
  // ID 1, 2 -> move to 45 degree, (1000 ms, 0 ms delay)
  m_CMot.Play("1000, 0, 1, 45, 2, 45");
  // ID 1, 2 -> move to 0 degree, (1000 ms, 0 ms delay)
  m_CMot.Play("1000, 0, 1, 0, 2, 0");
  //////////////////////////////////////////////////////////

  // another way. //////////////////////////////////////////
  // another way.
  Serial.println("play 1, 2 -> -45 degree");
  // ID 1 -> move to -45 degree, (1000 ms)
  m_CMot.Play("1000, 0, 1, -45", true); // true allows the command to proceed without waiting. (Commands on other lines are executed simultaneously.)
  // ID 2 -> move to -45 degree, (1000 ms, delay 2000 ms), It starts at the same time as the command line above.
  m_CMot.Play("1000, 2000, 2, -45"); 
  // Move motors 1 and 2 to the 0 degree position and delay for 2000 ms after stopping.
  m_CMot.Play("1000, 2000, 1, 0, 2, 0"); 
  //////////////////////////////////////////////////////////
}
