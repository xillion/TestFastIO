#include "mbed.h"
#include "bsp.h"

FastInOut led1(COLLECT_LED);
FastInOut led2(CHARGE_LED);

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
