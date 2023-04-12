#include "mbed.h"

const float _C4=261.6;
const float _B3=246.9;
const float _A3=220.0;
const float _G3=196.0;
const float _F3=174.6;
const float _E3=164.8;
const float _D3=146.8;
const float _C3=130.8;

const double pi = 3.141592653589793238462;
const double amplitude = 1.f;
const double offset = 65535. / 3;

AnalogOut aout(PA_4);

// main() runs in its own thread in the OS
int main()
{
    double rads = 0.0;
    uint16_t sample[128];
    int count = 0;
    for (int i = 0; i < 128; i++){
        rads = (pi * i) / 180.0f;
        sample[i] = (uint16_t)(amplitude * (offset * (cos(rads + pi))) + offset);
    }
    
    while (true) {
        for (int i = 0; i < 128; i++){
            aout.write_u16(sample[i]);
            ThisThread::sleep_for(10ms);
        }
        
    }
}

