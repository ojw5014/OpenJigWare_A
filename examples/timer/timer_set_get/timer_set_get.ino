/*

*/
#include <stdarg.h>
#include "ojw.h"

CProtocol2 m_CMot;
CTimer m_CTmr1, m_CTmr2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  m_CTmr1.Set(); // Timer 1 Set(Clear)
  for (int i = 0; i < 3; i++)
  {
    m_CTmr2.Set(); // Timer 2 Set(Clear)
    delay(1000);
    Serial.println(m_CTmr2.Get()); // Check Timer 2
  }
  Serial.println(m_CTmr1.Get()); // Check Timer 1
}
/////////////////////
