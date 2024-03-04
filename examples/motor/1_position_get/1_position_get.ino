#include <stdarg.h>
#include <ojw.h>

CProtocol2 m_CMot;

int nID1, nID2;
String strID1, strID2, strID_All;
void setup() {
  nID1 = 1; // ID 1
  nID2 = 2; // ID 2
  
  strID1 = String(nID1); // "1"
  strID2 = String(nID2); // "2"
  strID_All =  strID1 + "," + strID2; // "1,2"
  
  Serial.begin(9600); // for println  
  m_CMot.Open(57600); // serial open, 57600 bps
}

void loop() {
  m_CMot.SyncRead(strID_All);
  Serial.println(strID1 + ": " + String(m_CMot.GetAngle(nID1)));
  Serial.println(strID2 + ": " + String(m_CMot.GetAngle(nID2)));
  delay(1000); 
}
