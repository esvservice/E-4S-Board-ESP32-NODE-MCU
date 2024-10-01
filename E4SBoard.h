// E4SBoard.h
#ifndef E4S_LIBRARY_H
#define E4S_LIBRARY_H
#include <Arduino.h>
#include <Temperature_LM75_Derived.h>

class E4SClass
{
public:
    E4SClass();
    void Begin();

    // RELAY
    void Relay(int pin, int state);
    // 7SEG
    void Seg7(int dig, int seg, int state);
    void Seg7_numbers(int dig, int num, int dp);
    // RGB
    void RGB(int pin, int state);
    // UPDATE SHIFT REGISTER
    void UpdateSerialOutputs();

    // DI POSITIVE
    int DIp(int pin);
    // DI NEGATIVE
    int DIn(int pin);
    // UPDATE MUX
    void ReadMuxInputs();

    // OBL
    void OBL(int state);
    // OBL INIT
    int OnBoardLed = 2;

    // BEEP
    void Beep(int state);
    // BEEP INIT
    int beep = 12;

    /*// TEMP
      void Temp(int temp);

      // SERIAL
      void Serial();*/
private:
    // SHIFT REGISTER INIT
    int ShiftRegStrb = 13;
    int ShiftRegData = 4;
    int ShiftRegClk = 23;
    bool Serout[24];

    // MUX INIT
    byte MuxA0 = 15;
    byte MuxA1 = 0;
    byte MuxA2 = 5;
    byte MuxA3 = 14;
    byte MuxDin = 39;
    bool MXi[16];
};

#endif

