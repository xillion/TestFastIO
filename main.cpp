#include "mbed.h"
#include "bsp.h"

typedef struct
{
    /* data */
    uint8_t bit0 :1;
    uint8_t bit1 :1;
    uint8_t bit2 :1;
    uint8_t bit3 :1;
    uint8_t bit4 :1;
    uint8_t bit5 :1;
    uint8_t bit6 :1;
    uint8_t bit7 :1;
}bit_merge_t;


FastInOut<COLLECT_LED> led1;
FastInOut<CHARGE_LED> led2;

int main() 
{
    while(1)
    {
        wait(0.5);
        led1 = 0;
        led2 = 1;
        wait(0.5);
        led1 = 1;
        led2 = 0;
    }
}
