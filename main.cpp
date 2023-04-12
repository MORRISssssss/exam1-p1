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
const double offset = 65535. / 2;

AnalogOut aout(PA_4);

// main() runs in its own thread in the OS
int main()
{
    double rads = 0.0;
    uint16_t sample[128];
    double amplitude[200] = {1.};
    int count = 0;
    for (int i = 0; i < 128; i++){
        rads = 2 * pi * i / 128;
        sample[i] = (uint16_t)(amplitude[0] * (offset * (cos(rads + pi))) + offset);
    }
    
    for (int i = 0; i < 200; i++){
        if (i < 50)
            amplitude[i] = (float)i / 50;
        else if (i < 100)
            amplitude[i] = 1. - (i - 50.) / 50 * 0.4;
        else if (i < 150)
            amplitude[i] = 0.6;
        else
            amplitude[i] = 0.6 - 0.6 * (i - 150.) / 50;
    }
    int cnt1 = 0;
    int cnt2 = 0;
    int wait_time = 0;
    float freq = _C4;
    wait_time = 1000000 / freq / 128 - 8;
    while (true) {
        for (int i = 0; i < 128; i++){
            aout.write_u16(sample[i] * amplitude[cnt2]);
            cnt1++;
            if (cnt1 == (int)(freq * 128 / 200 / 20)){
                cnt1 = 0;
                cnt2++;
            }
            if (cnt2 == 200)
                cnt2 = 0;
            wait_us(wait_time);
        }
        
    }
}

