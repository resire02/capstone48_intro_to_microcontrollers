#include "mcc_generated_files/system/system.h"
#include <xc.h>

#define VNCL_I2C_ADDR 0x51
#define VNCL_PS_CONF1_CONF2_REG 0x03
#define VNCL_DATA_PS_REG 0x08

static uint8_t read_data[2] = { 0x00, 0x00 };

void vcnl_init()
{
    // enable proximity sensor through PS_CONF1
    // write_data[1]: PS_CONF1, turns on PS, using 4T PS_IT
    //      1T: 0x00    1.5T: 0x02  2T: 0x04    4T: 0x06
    //      using 2T as it has ideal sample rate for motion detection
    // write_data[2]: PS_CONF1, default value 0x00
    static uint8_t write_data[3] = { VNCL_PS_CONF1_CONF2_REG, 0x06, 0x00};

    while(TWI0_IsBusy());
    TWI0_Write(VNCL_I2C_ADDR, write_data, 3);
}

uint16_t vncl_read_ps()
{
    static uint8_t write_cmd = VNCL_DATA_PS_REG;
    
    while(TWI0_IsBusy());
    TWI0_WriteRead(VNCL_I2C_ADDR, &write_cmd, 1, read_data, 2);
    // produces a maximum read value of 4095
    return (read_data[1] << 8) | read_data[0];
}