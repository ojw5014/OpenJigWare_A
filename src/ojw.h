#ifndef _DEF_OJW_H
#define _DEF_OJW_H

#include "arduino.h"
#include <Dynamixel2Arduino.h>

#include <SPI.h>
#include <SD.h>

Dynamixel2Arduino dxl(Serial1);
ParamForSyncReadInst_t sync_read_param;
ParamForSyncWriteInst_t sync_write_param;
RecvInfoFromStatusInst_t read_result;

#define _MAX_DXL_MOTORS 50 //256
const int DXL_DIR_PIN = 2;
class CTimer
{
    private:
        unsigned long unTimer = 0;
        bool IsTimer = false;
    public:
        CTimer(){
            unTimer = 0;
            IsTimer = false;
        }
        ~CTimer(){

        }
    public:
        void Set();
        void Kill();
        unsigned long Get();
};
class CProtocol2
{
    public:
        class CParam_t
        {
            public:
                bool m_bModel_High = false;
                int m_nSet_Operation_Address = 11;
                int m_nSet_Operation_Size = 1;
            //    int m_nSet_GoalCurrent_Address = 11;
            //    int m_nSet_Operation_Size = 1;
                int m_nSet_Torq_Address = 64;
                int m_nSet_Torq_Size = 1;
                int m_nSet_Led_Address = 65;
                int m_nSet_Led_Size = 1;
                int m_nSet_Position_Speed_Address = 112;
                int m_nSet_Position_Speed_Size = 4;
                int m_nSet_Position_Address = 116;
                int m_nSet_Position_Size = 4;
                int m_nSet_Speed_Address = 104;
                int m_nSet_Speed_Size = 4;

                float m_fMechMove = 4096.0f;    // PH54-100 => -501,923 ~ 501,923, H54-200 => -501,923 ~ 501,923
                float m_fCenter = 2048.0f;
                float m_fMechAngle = 360;
                float m_fJointRpm = 0.229f; // ph54-100 = 0.01, H54-200 = 0.01
                bool m_bDirReverse = false;
                float m_fMulti = 1.0f;

                int m_nGet_Position_Address = 132;
                int m_nGet_Position_Size = 4;

                void SetParam_Address_Torq(int nVal = 64) { m_nSet_Torq_Address = nVal; }
                void SetParam_Address_Size_Torq(int nVal = 1) { m_nSet_Torq_Size = nVal; }
                void SetParam_Address_Led(int nVal = 66) { m_nSet_Led_Address = nVal; }
                void SetParam_Address_Size_Led(int nVal = 1) { m_nSet_Led_Size = nVal; }
                void SetParam_Address_PositionSpeed(int nVal = 112) { m_nSet_Position_Speed_Address = nVal; }
                void SetParam_Address_Size_PositionSpeed(int nVal = 4) { m_nSet_Position_Speed_Size = nVal; }
                void SetParam_Address_Position(int nVal = 116) { m_nSet_Position_Address = nVal; }
                void SetParam_Address_Size_Position(int nVal = 4) { m_nSet_Position_Size = nVal; }
                void SetParam_Address_GetPosition(int nVal = 132) { m_nGet_Position_Address = nVal; }
                void SetParam_Address_Size_GetPosition(int nVal = 4) { m_nGet_Position_Size = nVal; }
                void SetParam_Address_Speed(int nVal = 104) { m_nSet_Position_Speed_Address = nVal; }
                void SetParam_Address_Size_Speed(int nVal = 4) { m_nSet_Position_Speed_Size = nVal; }

                void SetParam_Dir(bool bReverse = false) { m_bDirReverse = bReverse; }
                void SetParam_Multi(float fMulti = 1.0f) { m_fMulti = fMulti; if (fMulti == 0) m_fMulti = 1.0f; }

                void SetParam(bool bSetHight = false)
                {
                    if (bSetHight == true) // PH, H54(Pro) ... 
                    {
                        m_bModel_High = true;
                        m_nSet_Torq_Address = 512;
                        m_nSet_Torq_Size = 1;
                        m_nSet_Led_Address = 513;
                        m_nSet_Led_Size = 1;
                        m_nSet_Speed_Address = 552;
                        m_nSet_Speed_Size = 4;
                        m_nSet_Position_Speed_Address = 560;
                        m_nSet_Position_Speed_Size = 4;
                        m_nSet_Position_Address = 564;
                        m_nSet_Position_Size = 4;

                        m_fMechMove = 1003846.0f;    // PH54-100 => -501,923 ~ 501,923, H54-200 => -501,923 ~ 501,923
                        m_fCenter = 0.0f;
                        m_fMechAngle = 360;
                        m_fJointRpm = 0.01f; // ph54-100 = 0.01, H54-200 = 0.01
                        m_bDirReverse = false;
                        m_fMulti = 1.0f;
                        m_nGet_Position_Address = 580;
                        m_nGet_Position_Size = 4;
                    }
                    else
                    {
                        m_bModel_High = false;
                        m_nSet_Torq_Address = 64;
                        m_nSet_Torq_Size = 1;
                        m_nSet_Led_Address = 65;
                        m_nSet_Led_Size = 1;
                        m_nSet_Speed_Address = 104;
                        m_nSet_Speed_Size = 4;
                        m_nSet_Position_Speed_Address = 112;
                        m_nSet_Position_Speed_Size = 4;
                        m_nSet_Position_Address = 116;
                        m_nSet_Position_Size = 4;

                        m_fMechMove = 4096.0f;    // PH54-100 => -501,923 ~ 501,923, H54-200 => -501,923 ~ 501,923
                        m_fCenter = 2048.0f;
                        m_fMechAngle = 360;
                        m_fJointRpm = 0.229f; // ph54-100 = 0.01, H54-200 = 0.01
                        m_bDirReverse = false;
                        m_fMulti = 1.0f;
                        m_nGet_Position_Address = 132;
                        m_nGet_Position_Size = 4;
                    }
                }
        };
        struct SMotorInfo_t // Motor information
        {
            int nMotorID;                    // Motor ID
            int nMotorDir;                   // Direction of Axis (0 - forward, 1 - inverse)
            float fLimit_Up;                 // Max Angle(+)
            float fLimit_Down;               // Min Angle(-)
            int nCenter_Evd;                 // Pulse(Engineering value for 0 degree(Center Position))

            int nMechMove;                   // Maximum Position ( Maximum Pulse value(Evd) )
            float fMechAngle;                // It is a Degree when it moves in Maximum Position

            float fInitAngle;                // Init position which you want it
            float fInitAngle2;               // Init position which you want it(2'st)


            // Interference Axis(No use)
            int nInterference_Axis;          // reserve(No use) - 이게 (-)값이면 간섭 축 없음.
            float fW;                        // reserve(No use) - Side 에 붙은 축의 크기(넓이)
            float fInterference_W;           // reserve(No use) - 간섭축이 앞뒤로 붙었다고 가정하고 해당 간섭축의 크기(넓이)

            float fPos_Right;                // reserve(No use) - 축의 오른쪽 위치
            float fPos_Left;                 // reserve(No use) - 축의 왼쪽 위치

            float fInterference_Pos_Front;   // reserve(No use) - 해당 간섭축의 앞쪽 위치
            float fInterference_Pos_Rear;    // reserve(No use) - 해당 간섭축의 뒤쪽 위치

            // NickName
            String strNickName;              // Nickname(32char)

            int nGroupNumber;                // Group Number

            int nAxis_Mirror;                // 0 ~ 253 : Motor ID of Mirroring one
                                                    // -1      : there is no mirror motor.
                                                    // -2 : there is no mirror motor(but it can has flip-direction(for using center), flip it from '0')

            int nMotorControlType;           // Motor Control type => 0: Position, 1: Speed type
            
            /////////// 추가
            float fRpm;//0.229f); // 기본 rpm 단위
            int nLimitRpm_Raw;//415);
            int nProtocolVersion;//2); // Version 2(0 해도 동일)
            int nHwMotor_Index; // 0 : None, 1 : xl-320, 2 : xl_430(Default), 3 - ax-12 => 지금은 이거아님, Monster2 클래스에서 확인(dicMonster)
            int nHwMotor_Key;//1060); // 0번지에 모델번호 1060, XM430_W210 : 1030, XM430_W350 : 1020
            int nAddr_Max;//146);
            int nAddr_Torq;//64);
            int nAddr_Led;//65);
            int nAddr_Mode;//10); // 430 -> 10 address    [0 : 전류, 1 : 속도, 3(default) : 관절(위치제어), 4 : 확장위치제어(멀티턴:-256 ~ 256회전), 5 : 전류기반 위치제어, 16 : pwm 제어(voltage control mode)]
            int nAddr_Speed;//104); // 430 -> 104 4 bytes
            int nAddr_Speed_Size;//4);
            int nAddr_Pos_Speed;//112); // 430 -> 112 4 bytes
            int nAddr_Pos_Speed_Size;//4);
            int nAddr_Pos;//116); // 430 -> 116 4 bytes
            int nAddr_Pos_Size;//4);
            int nSerialType;  // 0 : Default, 1 : Second ... (동시에 2개 이상의 시리얼에 연결된 경우 사용)

            int nMotorEnable_For_RPTask; // 0: Dontcare, 1: Enable, -1: Disable(이게 -1 이면 로보티즈 모션으로 복사 시 해당 값을 무시한다.)
            int nMotor_Enable; // 0: Dontcare, 1: Enable, -1: Disable => 이게 Disable 이면 모터 표시를 죽인다.
            int nMotionEditor_Index; // 0 이면 사용 안함. 1 부터 사용, 0 이상인 경우 여기의 인덱스를 우선적으로 적용, 하나를 세팅했으면 반드시 다른 하나도 세팅할 것
            int nMotor_HightSpec; // 0 : Default, 1 : HightSpec Motor(Pro)
            int nReserve_4;
            int nReserve_5;
            int nReserve_6;
            int nReserve_7;
            int nReserve_8;
            int nReserve_9;
            float fGearRatio; // 2차 기어비
            float fRobotisConvertingVar; // 로보티즈 모델링 매칭을 위한 컨버팅 변수
            float fReserve_2;
            float fReserve_3;
            float fReserve_4;
            float fReserve_5;
            float fReserve_6;
            float fReserve_7;
            float fReserve_8;
            float fReserve_9;
            ///////////////////////////////
            int nGuide_Event;
            int nGuide_AxisType;
            int nGuide_RingColorType;
            float fGuide_RingSize;
            float fGuide_RingThick;
            int nGuide_RingDir;
            float fGuide_3D_Scale;
            float fGuide_3D_Alpha;

            float afGuide_Pos[6];// = new float[6]; // x/y/z/p/t/s
            int anGuide_Off_IDs[6];// = new int[6]; // x/y/z/p/t/s
            int anGuide_Off_Dir[6];// = new int[6]; // x/y/z/p/t/s
        };
        class CCommand_t
        {
            public:
                int nID = 0;
                float fVal = 0;
                // CCommand_t(int id, float val)
                // {
                //     nID = id;
                //     fVal = val;
                // }
        };
    private:        
    
        int m_nRequest_Address = 0;
        int m_nRequest_Address_Size = 0;

        bool m_bEms = false; // emergency switch
        CCommand_t m_lstCmdIDs[_MAX_DXL_MOTORS];
        bool m_bBreak = false;
        bool m_bBreak2 = false;
        void SetBreak() { m_bBreak = true; }
    public:
        bool m_abMot[_MAX_DXL_MOTORS];
        int m_anMot[_MAX_DXL_MOTORS];
        float m_afMot[_MAX_DXL_MOTORS];
        int m_anMot_Pose[_MAX_DXL_MOTORS];
        float m_afMot_Pose[_MAX_DXL_MOTORS];
        CProtocol2()
        {
            int nLength = (sizeof(m_aCParam)/sizeof(m_aCParam[0]));
            for (int i = 0; i < nLength; i++)
            {
                m_aCParam[i].SetParam(false);
            }
        }
        ~CProtocol2()
        {
            if (IsOpen()) Close();
        }

        bool Load(const String &strFileName)
        {
          File fileMotion;
          if (!SD.begin(4)) { return false; }

          fileMotion = SD.open(strFileName);
          if (fileMotion) {
            char cData;
            String strData = "";
            while (fileMotion.available()) {
              cData = (char)(fileMotion.read());

              if (cData == '\n')
              {
                
                // Serial.println(strData);
                Play(strData);
                strData = "";
              }
              else
                strData += cData;
            }
            fileMotion.close();
            if (strData.length() > 2)
              Play(strData);
          } else {
            // Serial.println("error opening " + strFileName);
          }
          return true;
        }

        String m_strCmd = "";
        void Stream(Stream &serial)
        {
          if (serial.available() > 0) {
            char cData;
            while (serial.available()) {
              cData = (char)(serial.read());
              if (cData == '\r') { }
              else if (cData == '\n') { }
              else if (cData == ';')
              {
                if ((m_strCmd.length()) > 0)
                {
                  //// Do it ////
                  // serial.println("[Received] => " + m_strCmd);
                  Play(m_strCmd);
                  ///////////////

                  m_strCmd = "";
                }
                m_strCmd = "";
              }
              else
                m_strCmd += cData;
            }
          }
        }
        bool m_bOpen = false;
        bool IsOpen() { return m_bOpen; }
        bool Open(int nBaudRate)
        {
            // DXL
            if (m_bOpen == false)
            {
              dxl.begin(nBaudRate);
              dxl.scan();
            }
            m_bOpen = true;
        }
        void Close()
        {
            m_bOpen = false;
        }
        void SetParam(SMotorInfo_t aSParams[])
        {
            int nLength = (sizeof(aSParams)/sizeof(aSParams[0]));
            for (int i = 0; i < nLength; i++)
            {
                SetParam(aSParams[i].nMotorID, ((aSParams[i].nMotorDir == 0) ? false : true), ((aSParams[i].fGearRatio == 0) ? 1.0f : aSParams[i].fGearRatio), ((aSParams[i].nMotor_HightSpec == 0) ? false : true));
            }
        }
        void SetParam(int nID, bool bDirReverse = false, float fMulti = 1.0f, bool bHigh = false)
        {
            m_aCParam[nID].SetParam(bHigh);
            m_aCParam[nID].m_bDirReverse = bDirReverse;
            m_aCParam[nID].m_fMulti = fMulti;
        }

        // public void Ems()
        // {
        //     m_bEms = true;
        //     Send(254, 0x03, 64, 0);
        //     Send(254, 0x03, 512, 0);

        //     Send(254, 0x03, 64, 1);
        //     Send(254, 0x03, 512, 1);
        // }
        // public void Reboot(int nMotor = 254)
        // {
        //     if (nMotor == 254) { for (int i = 0; i < m_abMot.Length; i++) { m_abMot[i] = false; } }
        //     else { m_abMot[nMotor] = false; }
        //     Send_Command(nMotor, 0x08);
        // }
        // public void Send_Command(int nMotor, int nCommand)
        // {
        //     Send(nMotor, nCommand, 0, null);
        // }
        
        //////////////// calc ///////////////////
        float CalcEvd2Angle(int nID, int nValue)
        {
            float fMul = m_aCParam[nID].m_fMulti * ((m_aCParam[nID].m_bDirReverse == false) ? 1 : -1);
            if (fMul == 0) fMul = 1;
            float fMechMove = m_aCParam[nID].m_fMechMove;//4096.0;
            float fCenterPos = m_aCParam[nID].m_fCenter;//2048.0;
            float fMechAngle = m_aCParam[nID].m_fMechAngle;//360.0;

            return (((fMechAngle * ((float)nValue - fCenterPos)) / fMechMove) * fMul);
        }
        int CalcAngle2Evd(int nID, float fValue)
        {
            float fMul = m_aCParam[nID].m_fMulti * ((m_aCParam[nID].m_bDirReverse == false) ? 1 : -1);
            if (fMul == 0) fMul = 1;

            float fMechMove = m_aCParam[nID].m_fMechMove;//4096.0;
            float fCenterPos = m_aCParam[nID].m_fCenter;//2048.0;
            float fMechAngle = m_aCParam[nID].m_fMechAngle;//360.0;
            return (int)round(((fMechMove * fValue) / fMechAngle * fMul + fCenterPos));
        }
        int CalcPosition_Time(int nAxis, int nTime, int nDelay, float fAngle)
        {
            //float fPer = 1f;
            //if (nDelay < 0) fPer = ((float)(nTime + nDelay) / (float)nTime); 

            float fRpm = (float)abs(CalcTime2Rpm(abs(fAngle - m_afMot_Pose[nAxis]), (float)nTime));
            //float fRpm = (float)abs(CalcTime2Rpm(abs(fAngle - m_afMot[nAxis]) * fPer, (float)nTime));
            return CalcRpm2Raw(nAxis, fRpm);
        }
        float CalcRaw2Rpm(int nID, int nValue) { return (float)nValue * m_aCParam[nID].m_fJointRpm; }
        int CalcRpm2Raw(int nID, float fRpm) { return (int)round(fRpm / m_aCParam[nID].m_fJointRpm); }
        float CalcTime2Rpm(float fDeltaAngle, float fTime)
        {
            //if (fDeltaAngle == 0) fDeltaAngle = (float)CMath._ZERO;
            //#region Kor
            // 1도 이동시간 => fTime / fDeltaAngle

            // 60 초 동안 _MAX_RPM 을 회전하는 것이 RPM, 1도 움직이는 것을 체크하려면 여기에 360 도 회전값을 고려해 주어야 한다.
            // _MAX_RPM 은 1분(60초) 동안 _MAX_RPM 바퀴 (즉, 360 * _MAX_RPM) 를 회전한 값
            // _MAX_RPM * 360 : 60 seconds => 480(_MAX_EV_RPM) 일때 
            // => 1초간 6 * _MAX_RPM 도 회전, 1ms => _MAX_RPM * 360도 / 60000ms = 0.65952 도 이동
            // => 1도 움직이는데 60000 / (_MAX_RPM * 360) = 1.516254246 ms 가 필요

            // 1도 이동시간 => 60000 / (Rpm * 360)
            // 이동각도 당 이동시간 계산 => 1도 이동시간 * fDeltaAngle
            //#endregion Kor
            //return 60000 / (fTime / fDeltaAngle * 360.0f);
            return (60.0f * fDeltaAngle * 1000.0f) / (360.0f * fTime);
        }
        //////////////// calc ///////////////////
        int m_nSize_Command = 0;
        void Command_Clear() { m_nSize_Command = 0; }
        void Command_Set(int nID, float fValue) 
        { 
          m_lstCmdIDs[m_nSize_Command].nID = nID;
          m_lstCmdIDs[m_nSize_Command++].fVal = fValue; 
        }
        void Command_Set_Rpm(int nID, float fRpm) { Command_Set(nID, CalcRpm2Raw(nID, fRpm)); }
        void Clear() { Command_Clear(); }
        
        void Set(int nID, float fValue) { Command_Set(nID, fValue); }
        void Set_Rpm(int nID, float fRpm) { Command_Set_Rpm(nID, fRpm); }
        float GetAngle(int nID) { return m_afMot[nID]; }
        
        //void Move(int nCnt, int *IDs, float *values, float fPercent = 1.0f, float fPercent_Delay = 1.0f)
        // void Move(int nCnt, int *IDs, float *values, float fPercent = 1.0f, float fPercent_Delay = 1.0f)
        // {
        //   if (fPercent_Delay == 0)
        //       fPercent_Delay = fPercent;
        //   // Writes(IDs, 116, values, 4, fPercent);
        //   //string str = "";
        //   int *pValues = (int *)malloc(sizeof(int) * nCnt + 1);
        //   pValues[0] = values[0];
        //   for (int i = 1; i <= nCnt; i++)
        //   {
        //     pValues[i] = CalcAngle2Raw(values[i]);
        //   }


        //   #if 0
        //   Serial.print("Result=");
        //   Serial.print(pValues[0]);
        //   Serial.print("=>");
        //   for (int i = 0; i < nCnt; i++)
        //   {
        //     Serial.print(IDs[i]);
        //     Serial.print(":");
        //     Serial.print(pValues[i + 1]);
        //     Serial.print(",");
        //   }
        //   Serial.println();
        //   #else
        //   Writes_Frame(nCnt, IDs, pValues, fPercent);
        //   #endif
        //   // Serial.print("Delay=");
        //   // Serial.println((int)(round(pValues[0] * fPercent_Delay)));

        //   delay((int)(round(pValues[0] * fPercent_Delay)));
        //   free(pValues);
        // }
        

        CParam_t m_aCParam[_MAX_DXL_MOTORS];


        void Writes_Frame(int nAddress, int nByteLength, int nCnt_Motor, int *pnIDs, int *pnValues)
        {
          // Serial.println("nAddress:" + String(nAddress) + ",Len:" + String(nByteLength) + ",Cnt:" + String(nCnt_Motor));
          // pnValues[0] => speed
          int nSpeed;// = round((float)pnValues[0] * fPercent);
          int i;
          // int nLength = 8;
          sync_write_param.addr = nAddress; //Goal Velocity of DYNAMIXEL-X series
          sync_write_param.length = nByteLength;//nLength;
          
          //int nSub = 13;
          //int nCnt_All = nCnt_Motor;//_CNT_MOT;
          //int nCnt;
          int nPos = 0;
          // while(nCnt_All >= 0)
          // {
            // nCnt = nCnt_All;
            for (i = 0; i < nCnt_Motor; i++) 
            { 
              sync_write_param.xel[i].id = pnIDs[i + nPos]; 
            }
            sync_write_param.id_count = nCnt_Motor;
            for (i = 0; i < nCnt_Motor; i++) 
            {
              int j = nByteLength-1;
              int nVal = pnValues[i + nPos];
              // Serial.print("[" + String(pnIDs[i + nPos]) + "]" + String(nVal) + ",");
              sync_write_param.xel[i].data[j--] = (uint8_t)((nVal >> 24) & 0xff);
              sync_write_param.xel[i].data[j--] = (uint8_t)((nVal >> 16) & 0xff);
              sync_write_param.xel[i].data[j--] = (uint8_t)((nVal >> 8) & 0xff);
              sync_write_param.xel[i].data[j--] = (uint8_t)((nVal >> 0) & 0xff);
              
              // sync_write_param.xel[i].data[j--] = (uint8_t)((nSpeed >> 24) & 0xff);
              // sync_write_param.xel[i].data[j--] = (uint8_t)((nSpeed >> 16) & 0xff);
              // sync_write_param.xel[i].data[j--] = (uint8_t)((nSpeed >> 8) & 0xff);
              // sync_write_param.xel[i].data[j--] = (uint8_t)((nSpeed >> 0) & 0xff);
              
              // Serial.print(i + nPos);
              // Serial.print(":");
              // Serial.print(nVal);
              // Serial.print(" ");
            }
            // Serial.print("Speed:");
            // Serial.println(nSpeed);

            dxl.syncWrite(sync_write_param);
            
          //   nCnt_All -= nSub;
          //   nPos += nCnt;
          // }
        }
        // Move(Time, Delay, [id, angle,] [id, angle,] ...)
        bool Play(const String &strData, bool bNowait = false) 
        {

          int nOffset = 0;
            int start = 0;
            int end = strData.indexOf(',');
            //int nSize = 1;
            float afVals[50];
            // Loop through the string
            int nIndex = 0;
            String strData2;
            // Serial.println("=========" + strData + "==");
            int nCmd = 0;
            bool bWheel = false;
            bool bAngle = false;
            bool bWheel_Rpm = false;
            bool bWrite = false;
            while (end != -1) {
                
                strData2 = strData.substring(start, end);
                if ((strData2.indexOf('s') < 0) && (strData2.indexOf('S') < 0))
                {
                  afVals[nIndex] = strData2.toFloat();//strData.substring(start, end).toFloat();
                  // Serial.print("[" + String(afVals[nIndex]) + "],");
                  if (nIndex == 0) // Time
                  {
                    if (afVals[nIndex] == 0) { bWheel = true; bWheel_Rpm = true; }
                  }
                  else if (nIndex == 1) // Delay
                  {

                  }
                  else
                  {
                    if (nIndex % 2 != 0)
                    {
                      if (bWheel_Rpm == true)
                      {
                        Command_Set_Rpm((int)afVals[nIndex - 1], afVals[nIndex]);
                      }
                    }
                  }
                }
                else
                {
                  strData2.toLowerCase();
                  // Serial.println("문자열");
                  // nCmd = 1;
                  if (strData2.compareTo("s1") == 0)
                  {
                    nCmd = 1;
                  }
                  else if (strData2.compareTo("s2") == 0)
                  {
                    nCmd = 2;
                    bAngle = true;
                  }
                  else if (strData2.compareTo("s3") == 0)
                  {
                    nCmd = 3;
                    bWheel = false;
                  }
                  else if (strData2.compareTo("s4") == 0)
                  {
                    nCmd = 4;
                    bWheel = false;
                    bWheel_Rpm = true;
                  }
                  else if (strData2.compareTo("s5") == 0)
                  {
                    nCmd = 5;
                    bWrite = true;
                  }
                  nOffset = 1; // 2개 패스하고 다음 데이터에서...
                }
                
                if (nCmd == 0)
                {
                  // Serial.print(String(afVals[nIndex]) + ",");
                  
                }
                
                start = end + 1;
                end = strData.indexOf(',', start);
                nIndex++;
                if (nOffset > 0) 
                {
                  nOffset--;
                  nIndex = 0;
                }

                
                
                // delay(1);
            }

            afVals[nIndex] = strData.substring(start, end).toFloat();
            // Serial.println(String(afVals[nIndex]) + ";");
            // Serial.println(strData.substring(start).toFloat());
            // Serial.println(String(nIndex));
            nIndex++;
            // for (int i = 0; i < nIndex; i++)
            // {
            //   Serial.print(String(afVals[i]) + ",");
            // }
            // Serial.println(";");
            if ((nCmd == 0) || (nCmd == 2))
            {
              Move(afVals, nIndex, bNowait);
            }
            else if (bWheel == true)//(nCmd == 3)
            {
              SetSpeed(afVals, nIndex);
            }
        }
        bool Move(float *afVals, int nLength, bool bNowait = false)
        {
          //int nLength = sizeof(afVals) / sizeof(afVals[0]);
          int nLen_Off = nLength % 2;// * 2;
          int nLen = (int)(round(nLength - nLen_Off));// / 2.0f)) * 2;
          
          // Serial.print("test3=>" + String(nLen) + "," +  String(nLength) + ":");
          if (nLen < 4) return false;
          int nTime_ms = (int)afVals[0];
          int nDelay = (int)afVals[1];
          if (nTime_ms > 0)
          {
              CCommand_t aCCommands[nLen / 2 - 1];
              for (int i = 2; i < nLen; i += 2)
              {
                  //strErr += i.ToString() + ","; 
                  aCCommands[i / 2 - 1].nID = (int)afVals[i];
                  aCCommands[i / 2 - 1].fVal = afVals[i + 1];
              }
              // Serial.println("test4");
              Move(nTime_ms, nDelay, aCCommands, nLen / 2 - 1, bNowait); // -1은 Time, Delay 위치를 뺀 값
          }
          else
          {
              Command_Clear();
              for (int i = 2; i < nLen; i += 2) Command_Set_Rpm((int)afVals[i], afVals[i + 1]);
              SetSpeed(m_lstCmdIDs, m_nSize_Command);
          }
          return true;
        }
        void Move(int nTime_ms, int nDelay, CCommand_t aCCommands[], int nSize_Command, bool bNowait = false)
        {
            // Serial.print("test1");
            //m_nWait_Time = 0;
            if (IsOpen() == false) return;
            if (m_bEms == true) return;

            // Serial.print("test2");
            CTimer CTmr;
            CTmr.Set();

            // int nSize_Command = m_nSize_Command;
            CCommand_t CCmd[nSize_Command];
            memcpy(CCmd, aCCommands, sizeof(CCommand_t) * nSize_Command);// = ((aCCommands.Length > 0) ? aCCommands : ((m_lstCmdIDs.Count > 0) ? m_lstCmdIDs.ToArray() : null));
            Command_Clear();
            if (nSize_Command > 0)
            {
              
                  // Serial.print("000");
                if (bNowait == false)
                {
                  float afMot[_MAX_DXL_MOTORS];
                  float afRes[_MAX_DXL_MOTORS];
                  memcpy(afMot, m_afMot, _MAX_DXL_MOTORS);
                  while (true)
                  {
                    // Serial.print("111");
                    if (m_bEms == true)
                    {
                        for (int i = 0; i < nSize_Command; i++) { m_afMot_Pose[CCmd[i].nID] = m_afMot[CCmd[i].nID] = afRes[CCmd[i].nID]; }
                        return;
                    }
                      
                    // Serial.print("222");
                    //int lstIDs[nSize_Command];
                    for (int i = 0; i < nSize_Command; i++) { /*lstIDs[i] = CCmd[i].nID;*/ Command_Set(CCmd[i].nID, 0); } //CalcPosition_Time(CCmd[i].nID, nTime_ms, nDelay, CCmd[i].fVal)); }

                    // Serial.print("===");                    
                    SetPosition_Speed(m_lstCmdIDs, nSize_Command);

                  
                    // Serial.print("333");
                    float fGet = CTmr.Get();
                    float fTmr = (fGet / (float)nTime_ms);
                    if (fTmr > 1.0f) fTmr = 1.0f;

                    // -Delay 탈출
                    //if (bContinue == true)
                    //{
                    //    float fTmr_Sub = (nDelay >= 0) ? 0 : (fGet / (float)(nTime_ms + nDelay));
                    //    if (fTmr_Sub >= 1.0f) break;
                    //}
                    // Serial.println("444");
                    Command_Clear();
                    for (int i = 0; i < nSize_Command; i++) 
                    { 
                      // Serial.print(String(CCmd[i].nID) + ";");
                      afRes[CCmd[i].nID] = afMot[CCmd[i].nID] + (CCmd[i].fVal - afMot[CCmd[i].nID]) * fTmr; 
                      Command_Set(CCmd[i].nID, afRes[CCmd[i].nID]); 
                    }
                    // Serial.println("SetPosition");
                    SetPosition(m_lstCmdIDs, nSize_Command);
                    // Serial.print("-" + String(CCmd[0].nID));
                    if (fTmr >= 1.0f) break;
                    // delay(20);
                    //Ojw.CTimer.DoEvent();
                  }
                  for (int i = 0; i < nSize_Command; i++) { m_afMot_Pose[CCmd[i].nID] = m_afMot[CCmd[i].nID] = afRes[CCmd[i].nID]; }

                  while (true)
                  {
                      if (CTmr.Get() >= (nTime_ms + nDelay)) break;
                      //Ojw.CTimer.DoEvent();
                  }
                }
                else
                {
                  for (int i = 0; i < nSize_Command; i++) { /*lstIDs[i] = CCmd[i].nID;*/ Command_Set(CCmd[i].nID, CalcPosition_Time(CCmd[i].nID, nTime_ms, nDelay, CCmd[i].fVal)); } //; }
                  SetPosition_Speed(m_lstCmdIDs, nSize_Command);
                  Command_Clear();
                  for (int i = 0; i < nSize_Command; i++) 
                  { 
                    Command_Set(CCmd[i].nID, CCmd[i].fVal); 
                    m_afMot_Pose[CCmd[i].nID] = m_afMot[CCmd[i].nID] = CCmd[i].fVal;
                  }
                  SetPosition(m_lstCmdIDs, nSize_Command);
                }
            }
            // Serial.println("test end");
        }
        void SetSpeed(float afVals[], int nLength)
        {
            // int nLength = sizeof(afVals) / sizeof(afVals[0]);
            int nLen_Off = nLength % 2;// * 2;
            int nCnt = (int)(round((nLength - nLen_Off) / 2.0f));
            // int nCnt = round((nLength - 0.5f) / 2.0f);
            int nSize = nCnt * 2;
            int anIDs[nCnt];
            int anDatas[nCnt];
            int nPos = 0;
            for (int i = 0; i < nSize; i += 2) 
            { 
              anIDs[nPos] = (int)afVals[i];
              float fMul = m_aCParam[anIDs[nPos]].m_fMulti * ((m_aCParam[anIDs[nPos]].m_bDirReverse == false) ? 1 : -1);
              anDatas[nPos] = round(afVals[i + 1] * fMul); 
              // Serial.print(String(anIDs[nPos]) + ":" + String(anDatas[nPos]) + ",");
              nPos++;
            }
            // Serial.println("/");
            Writes_Frame(m_aCParam[anIDs[0]].m_nSet_Speed_Address, m_aCParam[anIDs[0]].m_nSet_Speed_Size, nCnt, anIDs, anDatas);
        }
        void SetSpeed(CCommand_t aCCommands[], int nLength)
        {
            // int nLength = sizeof(aCCommands) / sizeof(aCCommands[0]);
            
            //while (true)
            //{
                bool bRes = false;
                if (nLength > 0)
                {
                    int anIDs[nLength];
                    int anDatas[nLength];
                    for (int i = 0; i < nLength; i++)
                    {
                        anIDs[i] = aCCommands[i].nID;
                        // if (m_aCParam[CCmd[0].nID].m_nSet_Position_Speed_Address != m_aCParam[anIDs[i]].m_nSet_Position_Speed_Address)
                        // {
                        //     lstSecond.Add(new CCommand_t(anIDs[i], CCmd[i].fVal));
                        // }
                        // else 
                        //  Sync_Push_Dword(aCCommands[i].nID, (int)round(aCCommands[i].fVal));
                        float fMul = m_aCParam[anIDs[i]].m_fMulti * ((m_aCParam[anIDs[i]].m_bDirReverse == false) ? 1 : -1);
                        anDatas[i] = round(aCCommands[i].fVal * fMul);
                    }
                    //Sync_Flush(m_aCParam[CCmd[0].nID].m_nSet_Position_Speed_Address);
                    Writes_Frame(m_aCParam[anIDs[0]].m_nSet_Speed_Address, m_aCParam[anIDs[0]].m_nSet_Speed_Size, nLength, anIDs, anDatas);
                }
                // if (lstSecond.Count == 0) break;
            //}
            Command_Clear();
        }
        void SetPosition_Speed(float afVals[], int nLength)
        {
            // Serial.print("SetPosition_Speed1, nLength=" + String(nLength));
            // float fLength = sizeof(afVals) / sizeof(afVals[0]);
            // int nCnt = round((fLength - 0.5f) / 2.0f);
            // int nLength = sizeof(afVals) / sizeof(afVals[0]);
            // Serial.println("kkk1");
            int nLen_Off = nLength % 2;// * 2;
            int nCnt = (int)(round((nLength - nLen_Off) / 2.0f));

            int nSize = nCnt * 2;
            int anIDs[nCnt];
            int anDatas[nCnt];
            int nPos = 0;
            for (int i = 0; i < nSize; i += 2) 
            { 
              anIDs[nPos] = (int)afVals[i];
              anDatas[nPos] = round(afVals[i + 1]); 
              nPos++;
            }
            // Serial.println("kkk2");
            Writes_Frame(m_aCParam[anIDs[0]].m_nSet_Position_Speed_Address, m_aCParam[anIDs[0]].m_nSet_Position_Speed_Size, nCnt, anIDs, anDatas);
            
            //SetPosition_Speed(m_aCParam[anIDs[0]].m_nSet_Position_Speed_Address);
        }
        void SetPosition_Speed(CCommand_t aCCommands[], int nLength)
        {
          
            // Serial.print("SetPosition_Speed2, nLength=" + String(nLength));
          // int nLength = sizeof(aCCommands) / sizeof(aCCommands[0]);
            //while (true)
            //{
                bool bRes = false;
                if (nLength > 0)
                {
                    int anIDs[nLength];
                    int anDatas[nLength];
                    for (int i = 0; i < nLength; i++)
                    {
                        // if (m_aCParam[CCmd[0].nID].m_nSet_Position_Speed_Address != m_aCParam[CCmd[i].nID].m_nSet_Position_Speed_Address)
                        // {
                        //     lstSecond.Add(new CCommand_t(CCmd[i].nID, CCmd[i].fVal));
                        // }
                        // else 
                        //  Sync_Push_Dword(aCCommands[i].nID, (int)round(aCCommands[i].fVal));
                        anIDs[i] = aCCommands[i].nID;
                        anDatas[i] = round(aCCommands[i].fVal);
                    }
                    //Sync_Flush(m_aCParam[CCmd[0].nID].m_nSet_Position_Speed_Address);
                    Writes_Frame(m_aCParam[anIDs[0]].m_nSet_Position_Speed_Address, m_aCParam[anIDs[0]].m_nSet_Position_Speed_Size, nLength, anIDs, anDatas);
                }
                // if (lstSecond.Count == 0) break;
            //}
            Command_Clear();
        }
        void SetPosition(float afVals[], int nLength)
        {
          // Serial.print("SetPosition1, nLength=" + String(nLength));
            // float fLength = sizeof(afVals) / sizeof(afVals[0]);
            // int nCnt = round((fLength - 0.5f) / 2.0f);
            
            int nLen_Off = nLength % 2;// * 2;
            int nCnt = (int)(round((nLength - nLen_Off) / 2.0f));

            int nSize = nCnt * 2;
            int anIDs[nCnt];
            int anDatas[nCnt];
            int nPos = 0;
            for (int i = 0; i < nSize; i += 2) 
            { 
              anIDs[nPos] = (int)afVals[i];
              anDatas[nPos] = CalcAngle2Evd(anIDs[i], afVals[i + 1]); 
              nPos++;
            }
            // Serial.println("writes_frame()=" + String(m_aCParam[anIDs[0]].m_nSet_Position_Address));
            Writes_Frame(m_aCParam[anIDs[0]].m_nSet_Position_Address, m_aCParam[anIDs[0]].m_nSet_Position_Size, nCnt, anIDs, anDatas);
        }
        void SetPosition(CCommand_t aCCommands[], int nLength)
        {
          // Serial.print("SetPosition2, nLength=" + String(nLength));
            // int nLength = sizeof(aCCommands) / sizeof(aCCommands[0]);
            //while (true)
            //{
                bool bRes = false;
                if (nLength > 0)
                {
                  // Serial.println("length = " + String(nLength));
                    int anIDs[nLength];
                    int anDatas[nLength];
                    for (int i = 0; i < nLength; i++)
                    {
                        // if (m_aCParam[CCmd[0].nID].m_nSet_Position_Speed_Address != m_aCParam[CCmd[i].nID].m_nSet_Position_Speed_Address)
                        // {
                        //     lstSecond.Add(new CCommand_t(CCmd[i].nID, CCmd[i].fVal));
                        // }
                        // else 
                        //  Sync_Push_Dword(aCCommands[i].nID, (int)round(aCCommands[i].fVal));
                        anIDs[i] = aCCommands[i].nID;
                        anDatas[i] = CalcAngle2Evd(anIDs[i], aCCommands[i].fVal);
                        // Serial.print(String(anDatas[i]) + ",");
                    }
                    //Sync_Flush(m_aCParam[CCmd[0].nID].m_nSet_Position_Speed_Address);
                    Writes_Frame(m_aCParam[anIDs[0]].m_nSet_Position_Address, m_aCParam[anIDs[0]].m_nSet_Position_Size, nLength, anIDs, anDatas);
                }
                // if (lstSecond.Count == 0) break;
            //}
            Command_Clear();
        }
        void SetTorq(bool bOn)
        {
          if (bOn)
          {
            for (int i = 0; i < _MAX_DXL_MOTORS; i++)
            {
              dxl.torqueOn(i);
            }
          }
          else
          {
            for (int i = 0; i < _MAX_DXL_MOTORS; i++)
            {
              dxl.torqueOff(i);
            }
          }
          
          
            //Send(254, 0x03, 64, (byte)((bOn == true) ? 1 : 0));
        }
        // SetTorq(float *afVals)
        // {
        //     int nLen = (int)Math.Round(((float)afVals.Length - 0.5f) / 2.0f);
        //     CCommand_t aCCommands[nLen];
        //     for (int i = 0; i < nLen; i += 2) 
        //     { 
        //       aCCommands[i].nID = (int)afVals[i];
        //       aCCommands[i].fVal = round(afVals[i + 1]); 
        //     }
        //     SetTorq(aCCommands);
        // }
        // void SetTorq(params CCommand_t[] aCCommands)
        // {
        //     List<CCommand_t> lstSecond = new List<CCommand_t>();
        //     //for (int nIter = 0; nIter < 2; nIter++)
        //     while (true)
        //     {
        //         Sync_Clear();
        //         bool bRes = false;
        //         CCommand_t[] CCmd = ((aCCommands.Length > 0) ? aCCommands : ((m_lstCmdIDs.Count > 0) ? m_lstCmdIDs.ToArray() : null));
        //         Command_Clear();
        //         if (lstSecond.Count > 0)
        //         {
        //             CCmd = lstSecond.ToArray();
        //             lstSecond.Clear();
        //         }
        //         if (CCmd == null) break;
        //         if (CCmd.Length > 0)
        //         {
        //             for (int i = 0; i < CCmd.Length; i++)
        //             {
        //                 if (m_aCParam[CCmd[0].nID].m_nSet_Torq_Address != m_aCParam[CCmd[i].nID].m_nSet_Torq_Address)
        //                 {
        //                     lstSecond.Add(new CCommand_t(CCmd[i].nID, CCmd[i].fVal));
        //                 }
        //                 else Sync_Push_Byte(CCmd[i].nID, (int)Math.Round(CCmd[i].fVal));
        //             }
        //             Sync_Flush(m_aCParam[CCmd[0].nID].m_nSet_Torq_Address);
        //         }
        //         if (lstSecond.Count == 0) break;
        //     }
        //     //Command_Clear();
        // }


        /*
        public void SetTorq(bool bOn)
            {
                Send(254, 0x03, 64, (byte)((bOn == true) ? 1 : 0));
            }
            public void SetTorq(params float [] afVals)
            {
                int nLen = (int)Math.Round(((float)afVals.Length - 0.5f) / 2.0f);
                CCommand_t[] aCCommands = new CCommand_t[nLen];
                for (int i = 0; i < nLen; i += 2) { aCCommands[i] = new CCommand_t((int)afVals[i], afVals[i + 1]); }
                SetTorq(aCCommands);
            }
            public void SetTorq(params CCommand_t[] aCCommands)
            {
                List<CCommand_t> lstSecond = new List<CCommand_t>();
                //for (int nIter = 0; nIter < 2; nIter++)
                while (true)
                {
                    Sync_Clear();
                    bool bRes = false;
                    CCommand_t[] CCmd = ((aCCommands.Length > 0) ? aCCommands : ((m_lstCmdIDs.Count > 0) ? m_lstCmdIDs.ToArray() : null));
                    Command_Clear();
                    if (lstSecond.Count > 0)
                    {
                        CCmd = lstSecond.ToArray();
                        lstSecond.Clear();
                    }
                    if (CCmd == null) break;
                    if (CCmd.Length > 0)
                    {
                        for (int i = 0; i < CCmd.Length; i++)
                        {
                            if (m_aCParam[CCmd[0].nID].m_nSet_Torq_Address != m_aCParam[CCmd[i].nID].m_nSet_Torq_Address)
                            {
                                lstSecond.Add(new CCommand_t(CCmd[i].nID, CCmd[i].fVal));
                            }
                            else Sync_Push_Byte(CCmd[i].nID, (int)Math.Round(CCmd[i].fVal));
                        }
                        Sync_Flush(m_aCParam[CCmd[0].nID].m_nSet_Torq_Address);
                    }
                    if (lstSecond.Count == 0) break;
                }
                //Command_Clear();
            }
            public void SetLed(bool bOn)
            {
                int nID = 254;
                Send(nID, 0x03, m_aCParam[nID].m_nSet_Led_Address, (byte)((bOn == true) ? 1 : 0));
            }
            public void SetLed(params float [] afVals)
            {
                int nLen = (int)Math.Round(((float)afVals.Length - 0.5f) / 2.0f);
                CCommand_t[] aCCommands = new CCommand_t[nLen];
                for (int i = 0; i < nLen; i += 2) { aCCommands[i] = new CCommand_t((int)afVals[i], afVals[i + 1]); }
                SetLed(aCCommands);
            }
            public void SetLed(params CCommand_t[] aCCommands)
            {
                List<CCommand_t> lstSecond = new List<CCommand_t>();
                //for (int nIter = 0; nIter < 2; nIter++)
                while (true)
                {
                    Sync_Clear();
                    bool bRes = false;
                    CCommand_t[] CCmd = ((aCCommands.Length > 0) ? aCCommands : ((m_lstCmdIDs.Count > 0) ? m_lstCmdIDs.ToArray() : null));
                    Command_Clear();
                    if (lstSecond.Count > 0)
                    {
                        CCmd = lstSecond.ToArray();
                        lstSecond.Clear();
                    }
                    if (CCmd == null) break;
                    if (CCmd.Length > 0)
                    {
                        for (int i = 0; i < CCmd.Length; i++)
                        {
                            if (m_aCParam[CCmd[0].nID].m_nSet_Led_Address != m_aCParam[CCmd[i].nID].m_nSet_Led_Address)
                            {
                                lstSecond.Add(new CCommand_t(CCmd[i].nID, CCmd[i].fVal));
                            }
                            else Sync_Push_Byte(CCmd[i].nID, (int)Math.Round(CCmd[i].fVal));
                        }
                        Sync_Flush(m_aCParam[CCmd[0].nID].m_nSet_Led_Address);
                    }
                    if (lstSecond.Count == 0) break;
                }
                //Command_Clear();
            }
            public void SetOperation(int nID=254, int nMode=3)
            {
                SetCommand(nID, m_aCParam[nID].m_nSet_Operation_Address, nMode);
            }
            public void SetCommand(int nID, int nAddress, int nData, int nSize = 1)
            {
                if (nSize <= 1) Send(nID, 0x03, nAddress, (byte)nData);
                else
                {
                    byte[] buffer;
                    if (nSize == 2) 
                        buffer = Ojw.CConvert.ShortToBytes((short)nData);
                    else if (nSize == 4)
                        buffer = Ojw.CConvert.IntToBytes((short)nData);
                    else
                        buffer = Ojw.CConvert.LongToBytes((short)nData);
                    Send(nID, 0x03, nAddress, buffer);
                }
            }
        */
        void SyncRead(const String &strData) 
        {
            int start = 0;
            int end = strData.indexOf(',');
            //int nSize = 1;
            int anVals[50];
            // Loop through the string
            int nIndex = 0;
            while (end != -1) {
                anVals[nIndex] = strData.substring(start, end).toInt();
                // Serial.print(String(anVals[nIndex]) + ",");
                start = end + 1;
                end = strData.indexOf(',', start);
                nIndex++;
                // delay(1);
            }
            anVals[nIndex++] = strData.substring(start, end).toInt();
            // Serial.println(strData.substring(start).toInt());
            // Serial.println(String(nIndex));
            //Move(anVals, nIndex);
            SyncRead(anVals, nIndex);
        }
        void SyncRead(int *anIDs, int nLength)
        {
          
          int nAddress = m_aCParam[0].m_nGet_Position_Address;//132;//116;
          int nAddress_Size = 4;
          sync_read_param.addr = nAddress;
          sync_read_param.length = nAddress_Size;
          
          m_nRequest_Address = nAddress;
          m_nRequest_Address_Size = nAddress_Size;
          for (int i = 0; i < nLength; i++)
          {
            sync_read_param.xel[i].id = anIDs[i];
          }
          sync_read_param.id_count = nLength;
          dxl.syncRead(sync_read_param, read_result);

          // Serial.println("======= Sync Read =======");
          // memcpy(&recv_velocity[0], read_result.xel[0].data, read_result.xel[0].length);
          // memcpy(&recv_velocity[1], read_result.xel[1].data, read_result.xel[1].length);
          // Serial.print("ID: ");
          // Serial.print(read_result.xel[0].id);
          // Serial.print(" ");
          // Serial.print(", Present position: ");
          // Serial.print(recv_velocity[0]);

          int nVal;
          for (int i = 0; i < nLength; i++)
          {
            memcpy(&nVal, read_result.xel[i].data, read_result.xel[i].length);
            if (m_nRequest_Address == m_aCParam[anIDs[i]].m_nSet_Position_Address)
            {
                m_anMot[anIDs[i]] = nVal;
                m_afMot[anIDs[i]] = CalcEvd2Angle(anIDs[i], nVal);
                //Ojw.Log("[Receive]Set:{0}번 -> {1}({2}도)", anIDs[i], nVal, m_afMot[anIDs[i]]);
            }
            else if (m_nRequest_Address == m_aCParam[anIDs[i]].m_nGet_Position_Address)
            {
                m_anMot_Pose[anIDs[i]] = nVal;
                m_afMot_Pose[anIDs[i]] = CalcEvd2Angle(anIDs[i], nVal);

                m_anMot[anIDs[i]] = m_anMot_Pose[anIDs[i]];
                m_afMot[anIDs[i]] = m_afMot_Pose[anIDs[i]];
                //Ojw.Log("[Receive]Get:{0}번 -> {1}({2}도)", anIDs[i], nVal, m_afMot[anIDs[i]]);
            }
            else if (m_nRequest_Address == m_aCParam[anIDs[i]].m_nSet_Torq_Address)
            {
                m_abMot[anIDs[i]] = ((nVal == 0) ? false : true);
            }
          }
          
        }
};

///////////////////////
void CTimer::Set()
{
    unTimer = millis();
    IsTimer = true;
}
void CTimer::Kill()
{
    IsTimer = false;
}
unsigned long CTimer::Get()
{
    if (IsTimer) return millis() - unTimer;
    return 0;
}
//////////////////////////////
#endif // _DEF_OJW_H