#include <stdarg.h>
//#include <ojw.h>
#include "ojw.h"
CProtocol2 m_CMot;

void setup() {
  Serial.begin(9600); // for println  
  m_CMot.Open(1000000); // serial open, 57600 bps

  m_CMot.SetParam_Model(1, _Y_DEFAULT);
  m_CMot.SetParam_Model(4, _Y_DEFAULT);

  // position read
  m_CMot.SyncRead("1, 2, 3");
}
void loop() {

  Serial.println("On");          
  
  m_CMot.SetTorq_On("1, 2, 3"); // Torq On
  m_CMot.SetLed_On("1, 2, 3"); // Led On

  m_CMot.Play("3000, 0, 1, 10, 2, 10, 3,10");
  // ID 1, 2, 3 -> move to 0 degree, (1000 ms, 0 ms delay)
  Serial.println("play 1 -> 0 degree");
  m_CMot.Play("3000, 0, 1, 0, 2, 0, 3,0");

  Serial.println("Off");   
  m_CMot.SetLed_Off("1, 2, 3"); // Led Off
  m_CMot.SetTorq_Off("1, 2, 3"); // Torq Off
  delay(3000);
  
}
