#include "mcc_generated_files/system/system.h"
#include <xc.h>

#define VEML_I2C_ADDR 0x10
#define VEML_CLR_CMD_REG 0x04
#define VEML_RED_CMD_REG 0x05
#define VEML_GRN_CMD_REG 0x06
#define VEML_BLU_CMD_REG 0x07
#define VEML_IFR_CMD_REG 0X08
#define VEML_IDL_CMD_REG 0x0c

static uint8_t read_data[2] = { 0x00, 0x00 };

void veml_init()
{
    static uint8_t write_payload[3] = { 0x00, 0x00, 0x00 };
    
    // write default values into VEML3328
    while(TWI0_IsBusy());
    TWI0_Write(VEML_I2C_ADDR, write_payload, 3);
}

void veml_read_colors(uint16_t* color)
{
    static uint8_t write_cmd;
    
    // read R_LSB and R_MSB registers
    write_cmd = VEML_RED_CMD_REG;
    while(TWI0_IsBusy());
    TWI0_WriteRead(VEML_I2C_ADDR, &write_cmd, 1, read_data, 2);
    color[0] = (read_data[1] << 8) | read_data[0];
    
    // read G_LSB and G_MSB registers
    write_cmd = VEML_GRN_CMD_REG;
    while(TWI0_IsBusy());
    TWI0_WriteRead(VEML_I2C_ADDR, &write_cmd, 1, read_data, 2);
    color[1] = (read_data[1] << 8) | read_data[0];
    
    // read B_LSB and B_MSB registers
    write_cmd = VEML_BLU_CMD_REG;
    while(TWI0_IsBusy());
    TWI0_WriteRead(VEML_I2C_ADDR, &write_cmd, 1, read_data, 2);
    color[2] = (read_data[1] << 8) | read_data[0];
}