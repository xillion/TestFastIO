#include "mbed.h"
#include "bsp.h"
#include "MbedJSONValue.h"
#include <string>


// json strings
const char status[] = "{\"name\":\"state\",\"sensors\":[0,0,0],\"id\":0,\"time\":0,\"hash\":0}";
const char transaction[] = "{\"name\":\"transaction\",\"item\":0,\"id\":0,\"time\":0,\"hash\":0}";
const char collection[] = "{\"name\":\"collection\",\"id\":0,\"time\":0,\"hash\":0}";
const char charging[] = "{\"name\":\"charging\",\"id\":0,\"time\":0,\"hash\":0}";
unsigned long *uid = (unsigned long *)0x1FFF7590;


volatile uint16_t bus_value;
bool isBusCaptured = false;
FastInOut led1(COLLECT_LED);
FastInOut led2(CHARGE_LED);
int bus_read_count;
FastBusIn bus(  timing0,
                timing1,
                timing2,
                timing3,
                timing4,
                timing5,
                timing6,
                timing7);

InterruptIn counter(sell_counter);
InterruptIn itemGroup1(item_selector0);
InterruptIn itemGroup2(item_selector1);

EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread queueThread;
//-----------------------------------------------------------------------------
// Function proto declaration
int isPowerOfTwo(unsigned n);

int findPosition(int unsigned n);

void read_bus_group1();

void read_bus_group2();

void turnoffInterrupt();

void turnonInterrupt();

void startCaptureBus();


//-----------------------------------------------------------------------------
int isPowerOfTwo(unsigned n) 
{ 
    return n && (!(n & (n - 1))); 
} 

int findPosition(int unsigned n) 
{ 
    if (!isPowerOfTwo(n)) 
        return -1; 
  
    unsigned int i = 1, pos = 1; 
  

    while (!(i & n)) { 
        i = i << 1; 
        ++pos; 
    } 
  
    return pos; 
} 

void read_bus_group1()
{
    bus_value = 0xFF&(uint8_t)bus.read();
    if((bus_read_count++) == BUS_READ_CONST)
    {
        queue.call(turnoffInterrupt);
    };
}

void read_bus_group2()
{
    bus_value = (0xFF&(uint8_t)bus.read())<<8;
    if((bus_read_count++) == BUS_READ_CONST)
    {
        queue.call(turnoffInterrupt);
    };
}

void turnoffInterrupt()
{
    itemGroup1.rise(NULL);
    itemGroup2.rise(NULL);
    isBusCaptured = true;
    bus_read_count = 0;
}

void turnonInterrupt()
{
    itemGroup1.rise(read_bus_group1);
    itemGroup2.rise(read_bus_group2);
}

void startCaptureBus()
{
    queue.call(turnonInterrupt);
}

int main() 
{
    printf("Test coffee box");
    MbedCRC<POLY_32BIT_ANSI, 32> ct(0xFFFFFFFF, 0xFFFFFFFF, true, true);
    MbedJSONValue jsonTransaction;
    parse(jsonTransaction, transaction);
    uint32_t jsonCRC = 0;
    std::string jsonString;
    queueThread.start(callback(&queue, &EventQueue::dispatch_forever));
    counter.rise(&startCaptureBus);
    
    while(true){
        while(isBusCaptured)
        {
            jsonTransaction["item"]=findPosition(bus_value);
            jsonTransaction["id"] = (int)uid[2];
            jsonTransaction["time"] = 12;
            jsonTransaction["hash"] = 0;
            jsonString = jsonTransaction.serialize();
            ct.compute((void*)jsonString.data(), jsonString.length(), &jsonCRC);
            jsonTransaction["hash"][0] = (int)jsonCRC;
            jsonString = jsonTransaction.serialize();
            printf("%s\n", jsonString.c_str());
            isBusCaptured = false;
        }
    }

}
