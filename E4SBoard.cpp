// 
// 
// 

#include "Arduino.h"
#include "E4SBoard.h"

E4SClass::E4SClass()
{
    pinMode(ShiftRegData, OUTPUT);
    pinMode(ShiftRegClk, OUTPUT);
    pinMode(ShiftRegStrb, OUTPUT);
    pinMode(MuxA0, OUTPUT);
    pinMode(MuxA1, OUTPUT);
    pinMode(MuxA2, OUTPUT);
    pinMode(MuxA3, OUTPUT);
    pinMode(MuxDin, INPUT);
    pinMode(OnBoardLed, OUTPUT);
    pinMode(beep, OUTPUT);
    pinMode(16, OUTPUT);
    pinMode(17, OUTPUT);
    pinMode(18, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(25, INPUT);
    pinMode(27, INPUT);
    pinMode(32, INPUT);
    pinMode(33, INPUT);
}

void E4SClass::Begin()
{
    // *********************************************
    // init serial port
    // *********************************************
    Serial.begin(9600);

    // *********************************************
    // init LCD
    // *********************************************


    // *********************************************
    // init shift reg outputs
    // *********************************************
    for (int k = 0; k < 24; k++) // ALL OFF
    {
        digitalWrite(Serout[k], LOW);
    }
    UpdateSerialOutputs();
    // *********************************************
    // init on board LED
    // *********************************************
    digitalWrite(OnBoardLed, LOW);
    // *********************************************
    // init beeper
    // *********************************************
    digitalWrite(beep, LOW);
}

// RELAY
void E4SClass::Relay(int pin, int state)
{
    int pinRelay = (8 - pin) + 16;
    Serout[pinRelay] = state;
    UpdateSerialOutputs();
}
// 7SEG
void E4SClass::Seg7(int dig, int seg, int state)
{
    int digPos = (5 - dig) + 3;
    int segPos = (8 - seg) + 8;
    for (int i = 3; i < 8; i++)
    {
        Serout[i] = 0;
    }
    Serout[digPos] = 1;
    Serout[segPos] = state;
    UpdateSerialOutputs();
}

void E4SClass::Seg7_numbers(int dig, int num, int dp)
{
    int digPos = (5 - dig) + 3;
    for (int i = 3; i < 8; i++)
    {
        Serout[i] = 0;
    }
    Serout[digPos] = 1;
    switch (num)
    {
    case 0:
    {
        Serout[15] = 1;
        Serout[14] = 1;
        Serout[13] = 1;
        Serout[12] = 1;
        Serout[11] = 1;
        Serout[10] = 1;
        Serout[9] = 0;
        Serout[8] = dp;
        break;
    }
    case 1:
    {
        Serout[15] = 0;
        Serout[14] = 1;
        Serout[13] = 1;
        Serout[12] = 0;
        Serout[11] = 0;
        Serout[10] = 0;
        Serout[9] = 0;
        Serout[8] = dp;
        break;
    }
    case 2:
    {
        Serout[15] = 1;
        Serout[14] = 1;
        Serout[13] = 0;
        Serout[12] = 1;
        Serout[11] = 1;
        Serout[10] = 0;
        Serout[9] = 1;
        Serout[8] = dp;
        break;
    }
    case 3:
    {
        Serout[15] = 1;
        Serout[14] = 1;
        Serout[13] = 1;
        Serout[12] = 1;
        Serout[11] = 0;
        Serout[10] = 0;
        Serout[9] = 1;
        Serout[8] = dp;
        break;
    }
    case 4:
    {
        Serout[15] = 0;
        Serout[14] = 1;
        Serout[13] = 1;
        Serout[12] = 0;
        Serout[11] = 0;
        Serout[10] = 1;
        Serout[9] = 1;
        Serout[8] = dp;
        break;
    }
    case 5:
    {
        Serout[15] = 1;
        Serout[14] = 0;
        Serout[13] = 1;
        Serout[12] = 1;
        Serout[11] = 0;
        Serout[10] = 1;
        Serout[9] = 1;
        Serout[8] = dp;
        break;
    }
    case 6:
    {
        Serout[15] = 1;
        Serout[14] = 0;
        Serout[13] = 1;
        Serout[12] = 1;
        Serout[11] = 1;
        Serout[10] = 1;
        Serout[9] = 1;
        Serout[8] = dp;
        break;
    }
    case 7:
    {
        Serout[15] = 1;
        Serout[14] = 1;
        Serout[13] = 1;
        Serout[12] = 0;
        Serout[11] = 0;
        Serout[10] = 0;
        Serout[9] = 0;
        Serout[8] = dp;
        break;
    }
    case 8:
    {
        Serout[15] = 1;
        Serout[14] = 1;
        Serout[13] = 1;
        Serout[12] = 1;
        Serout[11] = 1;
        Serout[10] = 1;
        Serout[9] = 1;
        Serout[8] = dp;
        break;
    }
    case 9:
    {
        Serout[15] = 1;
        Serout[14] = 1;
        Serout[13] = 1;
        Serout[12] = 1;
        Serout[11] = 0;
        Serout[10] = 1;
        Serout[9] = 1;
        Serout[8] = dp;
        break;
    }
    }
    UpdateSerialOutputs();
}
// RGB
void E4SClass::RGB(int pin, int state)
{
    int pinRGB = (3 - pin);
    Serout[pinRGB] = state;
    UpdateSerialOutputs();
}

// DI POSITIVE
int E4SClass::DIp(int pin)
{
    int pinDIp = pin + 8;
    bool resultPos;
    ReadMuxInputs();
    resultPos = MXi[pinDIp];
    return resultPos;
}

// DI NEGATIVE
int E4SClass::DIn(int pin)
{
    int pinDIn = pin;
    bool resultNeg;
    ReadMuxInputs();
    resultNeg = MXi[pinDIn];
    return resultNeg;
}

// OBL
void E4SClass::OBL(int state)
{
    digitalWrite(OnBoardLed, state);
}

// BEEP
void E4SClass::Beep(int state)
{
    digitalWrite(beep, state);
}

/*// TEMP
  void E4SClass::Temp(int var)
  {

  }*/

  // RELAY - UPDATE SERIAL OUTPUTS
void E4SClass::UpdateSerialOutputs()
{
    digitalWrite(ShiftRegStrb, LOW);
    digitalWrite(ShiftRegClk, LOW);
    for (int i = 0; i < 24; i++) // repeat
    {
        digitalWrite(ShiftRegData, Serout[i]);
        delayMicroseconds(10);
        digitalWrite(ShiftRegClk, HIGH);
        delayMicroseconds(10);
        digitalWrite(ShiftRegClk, LOW);
        delayMicroseconds(10);
    }
    digitalWrite(ShiftRegStrb, HIGH);
}

// DI - READ MUX INPUTS
void E4SClass::ReadMuxInputs()
{
    for (int i = 0; i < 16; i++) // repeat
    {
        switch (i)
        {
        case 0:
            digitalWrite(MuxA0, 0);
            digitalWrite(MuxA1, 0);
            digitalWrite(MuxA2, 0);
            digitalWrite(MuxA3, 0);
            break;
        case 1:
            digitalWrite(MuxA0, 1);
            digitalWrite(MuxA1, 0);
            digitalWrite(MuxA2, 0);
            digitalWrite(MuxA3, 0);
            break;
        case 2:
            digitalWrite(MuxA0, 0);
            digitalWrite(MuxA1, 1);
            digitalWrite(MuxA2, 0);
            digitalWrite(MuxA3, 0);
            break;
        case 3:
            digitalWrite(MuxA0, 1);
            digitalWrite(MuxA1, 1);
            digitalWrite(MuxA2, 0);
            digitalWrite(MuxA3, 0);
            break;
        case 4:
            digitalWrite(MuxA0, 0);
            digitalWrite(MuxA1, 0);
            digitalWrite(MuxA2, 1);
            digitalWrite(MuxA3, 0);
            break;
        case 5:
            digitalWrite(MuxA0, 1);
            digitalWrite(MuxA1, 0);
            digitalWrite(MuxA2, 1);
            digitalWrite(MuxA3, 0);
            break;
        case 6:
            digitalWrite(MuxA0, 0);
            digitalWrite(MuxA1, 1);
            digitalWrite(MuxA2, 1);
            digitalWrite(MuxA3, 0);
            break;
        case 7:
            digitalWrite(MuxA0, 1);
            digitalWrite(MuxA1, 1);
            digitalWrite(MuxA2, 1);
            digitalWrite(MuxA3, 0);
            break;
        case 8:
            digitalWrite(MuxA0, 0);
            digitalWrite(MuxA1, 0);
            digitalWrite(MuxA2, 0);
            digitalWrite(MuxA3, 1);
            break;
        case 9:
            digitalWrite(MuxA0, 1);
            digitalWrite(MuxA1, 0);
            digitalWrite(MuxA2, 0);
            digitalWrite(MuxA3, 1);
            break;
        case 10:
            digitalWrite(MuxA0, 0);
            digitalWrite(MuxA1, 1);
            digitalWrite(MuxA2, 0);
            digitalWrite(MuxA3, 1);
            break;
        case 11:
            digitalWrite(MuxA0, 1);
            digitalWrite(MuxA1, 1);
            digitalWrite(MuxA2, 0);
            digitalWrite(MuxA3, 1);
            break;
        case 12:
            digitalWrite(MuxA0, 0);
            digitalWrite(MuxA1, 0);
            digitalWrite(MuxA2, 1);
            digitalWrite(MuxA3, 1);
            break;
        case 13:
            digitalWrite(MuxA0, 1);
            digitalWrite(MuxA1, 0);
            digitalWrite(MuxA2, 1);
            digitalWrite(MuxA3, 1);
            break;
        case 14:
            digitalWrite(MuxA0, 0);
            digitalWrite(MuxA1, 1);
            digitalWrite(MuxA2, 1);
            digitalWrite(MuxA3, 1);
            break;
        case 15:
            digitalWrite(MuxA0, 1);
            digitalWrite(MuxA1, 1);
            digitalWrite(MuxA2, 1);
            digitalWrite(MuxA3, 1);
            break;
        }
        delayMicroseconds(10);        // wait for stable selectlines
        MXi[i] = digitalRead(MuxDin); // read mux input
    }
}

