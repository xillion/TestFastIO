
#ifndef BSP_H
#define BSP_H

#include "mbed.h"
#include "FastIO/FastIO.h"

/**
 * Periferal definitions
*/
#define COLLECT_LED     PC_2
#define CHARGE_LED      PC_1
#define COLLECT_BTN     PC_3
#define CHARGE_BTN      PC_0

#define timing0         PC_8
#define timing1         PC_9
#define timing2         PC_6
#define timing3         PC_5
#define timing4         PA_12
#define timing5         PA_11
#define timing6         PB_12
#define timing7         PB_11

#define sell_counter    PC_11
#define item_selector0  PA_0
#define item_selector1  PC_12


#define BUS_READ_CONST 10

#endif