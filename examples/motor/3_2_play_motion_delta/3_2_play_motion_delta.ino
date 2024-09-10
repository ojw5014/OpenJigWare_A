#include <stdarg.h>
#include <ojw.h>

CProtocol2 m_CMot;

void setup() {
  Serial.begin(9600); // for println  
  m_CMot.Open(1000000); // serial open, 57600 bps

  m_CMot.SetParam_Dir(1, true);
  m_CMot.SetParam_Dir(2, true);
  m_CMot.SetParam_Dir(3, true);

  m_CMot.Delta_Clear();
  m_CMot.Delta_Add(0, 1,2,3, 55.0f, 100.0f, 215.0f, 24.0f);

  // position read
  m_CMot.SyncRead("1, 2, 3");

}
void loop() {

  m_CMot.SetTorq_On("1, 2, 3"); // Torq On

  int nIndex = 0;
  m_CMot.Move_Delta(nIndex, 60, 0, 220, 1000, 0);
  m_CMot.Move_Delta(nIndex, -60, 0, 220, 1000, 0);
  m_CMot.Move_Delta(nIndex, 0, 0, 250, 1000, 0);
  Serial.println("X moving ... done");
  delay(3000);
  m_CMot.Move_Delta(nIndex, 0, 60, 250, 1000, 0);
  m_CMot.Move_Delta(nIndex, 0, -60, 250, 1000, 0);
  m_CMot.Move_Delta(nIndex, 0, 0, 250, 1000, 0);
  Serial.println("Y moving ... done");
  delay(3000);
  
  
}
