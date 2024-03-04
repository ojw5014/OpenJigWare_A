#include <stdarg.h>
#include <ojw.h>

CProtocol2 m_CMot;

void setup() {
  Serial.begin(9600); // for println  
  m_CMot.Open(57600); // serial open, 57600 bps
}
String m_strCmd = "";
void loop() {
  Serial.println("TorqOn");  
  m_CMot.SetTorq(true);
  delay(3000);

  Serial.println("TorqOff");  
  m_CMot.SetTorq(false);
  delay(3000);
}
