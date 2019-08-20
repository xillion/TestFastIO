#include "mbed.h"
#include "bsp.h"

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
