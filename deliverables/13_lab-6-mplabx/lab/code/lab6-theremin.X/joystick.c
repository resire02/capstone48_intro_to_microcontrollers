#include "mcc_generated_files/system/system.h"
#include "joystick.h"

#define ADDR_IOEX2 0x24

void joystick_init(){
    uint8_t i2c_cmd[2] = {0x00, 0xFF}; 
    size_t cmd_len = 2;

    TWI0_Write(ADDR_IOEX2,&i2c_cmd[0], cmd_len); // Declare all pins as inputs
    while(TWI0_IsBusy());
    
    i2c_cmd[0] = 0x06;          // GPPU
    i2c_cmd[1] = 0xFF;          

    TWI0_Write(ADDR_IOEX2, &i2c_cmd[0], cmd_len); // Enable pullups 
    while(TWI0_IsBusy());
}

bool joystick_left() {
    uint8_t switch_state;
    uint8_t i2c_cmd = 0x09;          // GPIO (current pins state)

    TWI0_Write(ADDR_IOEX2, &i2c_cmd, 1);   // Tell expander I want to read from GPIO
    while (TWI0_IsBusy());

    TWI0_Read(ADDR_IOEX2, &switch_state, 1); // Read current state from GPIO
    while (TWI0_IsBusy());

    return ~((switch_state >> 1) & 0x01); // Not the value since active low, bit position 2 for left
}

bool joystick_right() {
    uint8_t switch_state;
    uint8_t i2c_cmd = 0x09;          // GPIO (current pins state)

    TWI0_Write(ADDR_IOEX2, &i2c_cmd, 1);   // Tell expander I want to read from GPIO
    while (TWI0_IsBusy());

    TWI0_Read(ADDR_IOEX2, &switch_state, 1); // Read current state from GPIO
    while (TWI0_IsBusy());

    return ~((switch_state >> 3) & 0x01); // Not the value since active low, bit position 2 for left
}