/**
 * A source file generated by TWI0 I2C host driver.
 *
 * @file twi0.c
 *
 * @ingroup i2c_host_interrupt
 *
 * @brief This file contains the API implementation for TWI0 driver.
 *
 * @version TWI0 Driver Version 2.1.4
 * 
 * @version TWI0 Package Version 8.2.0
 */

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

/**
 * @misradeviation {@advisory,2.5} False positive - A few macros in this file 
 * are used as arguments but are not getting recognized by the tool.
 * This rule ID has been disabled at the project level due to numerous 
 * instances across various files.
 * Consequently, in the application project, this rule ID must be disabled
 * in the MPLAB-X IDE by navigating to Tools>Options>Embedded>MISRA Check.
 */

#include "../twi0.h"
#include <stdbool.h>
#include <stdlib.h>
#include "../../system/utils/compiler.h"

static void TWI0_Close(void);
static void TWI0_ReadStart(void);
static void TWI0_WriteStart(void);
static void TWI0_EventHandler(void);
static void TWI0_ErrorEventHandler(void);

static i2c_event_states_t I2C_EVENT_IDLE(void);
static i2c_event_states_t I2C_EVENT_SEND_RD_ADDR(void);
static i2c_event_states_t I2C_EVENT_SEND_WR_ADDR(void);
static i2c_event_states_t I2C_EVENT_TX(void);
static i2c_event_states_t I2C_EVENT_RX(void);
static i2c_event_states_t I2C_EVENT_NACK(void);
static i2c_event_states_t I2C_EVENT_ERROR(void);
static i2c_event_states_t I2C_EVENT_STOP(void);
static i2c_event_states_t I2C_EVENT_RESET(void);

static inline void TWI0_CommandUpdate(TWI_MCMD_t cmd);
static void (*TWI0_Callback)(void);
volatile i2c_event_status_t twi0_Status = {0};

const i2c_host_interface_t I2C0_Host = 
{
    .Initialize = TWI0_Initialize,
    .Deinitialize = TWI0_Deinitialize,
    .Write = TWI0_Write,
    .Read = TWI0_Read,
    .WriteRead = TWI0_WriteRead,
    .TransferSetup = NULL,
    .ErrorGet = TWI0_ErrorGet,
    .IsBusy = TWI0_IsBusy,
    .CallbackRegister = TWI0_CallbackRegister,
    .Tasks = NULL
};

const twi0eventHandler twi0_eventTable[] = 
{
    I2C_EVENT_IDLE,
    I2C_EVENT_SEND_RD_ADDR,
    I2C_EVENT_SEND_WR_ADDR,
    I2C_EVENT_TX,
    I2C_EVENT_RX,
    I2C_EVENT_NACK,
    I2C_EVENT_ERROR,
    I2C_EVENT_STOP,
    I2C_EVENT_RESET
};

void TWI0_Initialize(void)
{
    
    // Disable the peripheral
    TWI0.MCTRLA &= ~(1 << TWI_ENABLE_bp);

    // FMPEN OFF; INPUTLVL I2C; SDAHOLD OFF; SDASETUP 4CYC; 
    TWI0.CTRLA = 0x0;

    // Debug Run
    TWI0.DBGCTRL = 0x0;

    // Host Baud Rate Control
    TWI0.MBAUD = (uint8_t)TWI0_BAUD(104166, 0.1);

    // Host Address
    TWI0.MADDR = 0x0;

    // Host Data
    TWI0.MDATA = 0x0;
   
    // ARBLOST disabled; BUSERR disabled; BUSSTATE UNKNOWN; CLKHOLD disabled; RIF disabled; WIF disabled; 
    TWI0.MSTATUS = 0x0;

    // ACKACT ACK; FLUSH disabled; MCMD NOACT; 
    TWI0.MCTRLB = 0x0;
  
    // ENABLE enabled; QCEN disabled; RIEN enabled; SMEN disabled; TIMEOUT DISABLED; WIEN enabled; 
    TWI0.MCTRLA = 0xC1;

    // Force bus to go in idle state
    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc; 

    TWI0_Callback = NULL;
}

void TWI0_Deinitialize(void)
{
    // FMPEN OFF; INPUTLVL I2C; SDAHOLD OFF; SDASETUP 4CYC; 
    TWI0.CTRLA = 0x00;
    
    // Debug Run
    TWI0.DBGCTRL = 0x00;
    
    // Host Baud Rate Control
    TWI0.MBAUD = (uint8_t)TWI0_BAUD(104166, 0.1);
    
    // ENABLE enabled; QCEN disabled; RIEN enabled; SMEN disabled; TIMEOUT DISABLED; WIEN enabled; 
    TWI0.MCTRLA = 0x00;
    
    // ARBLOST disabled; BUSERR disabled; BUSSTATE UNKNOWN; CLKHOLD disabled; RIF disabled; WIF disabled; 
    TWI0.MSTATUS = 0x00;

    // Host Address
    TWI0.MADDR = 0x00;
    
    // ACKACT ACK; FLUSH disabled; MCMD NOACT; 
    TWI0.MCTRLB = 0x00;
    
    // Host Data
    TWI0.MDATA = 0x00;

    TWI0.MCTRLA &= ~(1 << TWI_ENABLE_bp);
    // Force bus to go in idle state
    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
    
}

bool TWI0_Write(uint16_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    
    if (!TWI0_IsBusy())
    {
        twi0_Status.busy = true;
        twi0_Status.address = address;
        twi0_Status.switchToRead = false;
        twi0_Status.writePtr = data;
        twi0_Status.writeLength = dataLength;
        twi0_Status.readPtr = NULL;
        twi0_Status.readLength = 0;
        twi0_Status.errorState = I2C_ERROR_NONE;
        TWI0_WriteStart();
        retStatus = true;
    }
    
    return retStatus;
}

bool TWI0_Read(uint16_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    
    if (!TWI0_IsBusy())
    {
        twi0_Status.busy = true;
        twi0_Status.address = address;
        twi0_Status.switchToRead = false;
        twi0_Status.readPtr = data;
        twi0_Status.readLength = dataLength;
        twi0_Status.writePtr = NULL;
        twi0_Status.writeLength = 0;
        twi0_Status.errorState = I2C_ERROR_NONE;
        TWI0_ReadStart();
        retStatus = true;
    }
    
    return retStatus;
}

bool TWI0_WriteRead(uint16_t address, uint8_t *writeData, size_t writeLength, uint8_t *readData, size_t readLength)
{
    bool retStatus = false;
    
    if (!TWI0_IsBusy())
    {
        twi0_Status.busy = true;
        twi0_Status.address = address;
        twi0_Status.switchToRead = true;
        twi0_Status.writePtr = writeData;
        twi0_Status.writeLength = writeLength;
        twi0_Status.readPtr = readData;
        twi0_Status.readLength = readLength;
        twi0_Status.errorState = I2C_ERROR_NONE;
        TWI0_WriteStart();
        retStatus = true;
    }
    
    return retStatus;
}

i2c_host_error_t TWI0_ErrorGet(void)
{
    i2c_host_error_t retErrorState = twi0_Status.errorState;
    twi0_Status.errorState = I2C_ERROR_NONE;
    
    return retErrorState;
}

bool TWI0_IsBusy(void)
{
    return (twi0_Status.busy || ((TWI0.MSTATUS & TWI_BUSSTATE_gm) != TWI_BUSSTATE_IDLE_gc));
}

void TWI0_CallbackRegister(void (*callbackHandler)(void))
{
    if (callbackHandler != NULL)
    {
        TWI0_Callback = callbackHandler;
    }
}

static void TWI0_Close(void)
{
    twi0_Status.busy = false;
    twi0_Status.address = 0xFF;
    twi0_Status.writePtr = NULL;
    twi0_Status.readPtr = NULL;
    twi0_Status.state = I2C_STATE_IDLE;
    // Clear interrupt status
    TWI0.MSTATUS = (TWI_RIF_bm | TWI_WIF_bm);
    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
}

static void TWI0_ReadStart(void)
{
    twi0_Status.state = I2C_EVENT_SEND_RD_ADDR();
}

static void TWI0_WriteStart(void)
{
    twi0_Status.state = I2C_EVENT_SEND_WR_ADDR();
}

static void TWI0_EventHandler(void)
{
    twi0_Status.state = twi0_eventTable[twi0_Status.state]();
}

static void TWI0_ErrorEventHandler(void)
{
    // Check the bus error
    if ((TWI0.MSTATUS & TWI_BUSERR_bm) || (TWI0.MSTATUS & TWI_ARBLOST_bm))
    {
        twi0_Status.state = I2C_STATE_ERROR;
        twi0_Status.errorState = I2C_ERROR_BUS_COLLISION;
        
        // Clear the error flags
        TWI0.MSTATUS = (TWI_BUSERR_bm | TWI_ARBLOST_bm);
    }
    // Check if address NAK
    else if ((TWI0.MADDR) && (TWI0.MSTATUS & TWI_RXACK_bm))
    {
        twi0_Status.state = I2C_STATE_NACK;
        twi0_Status.errorState = I2C_ERROR_ADDR_NACK;
    }
    // Check if data NAK
    else if ((TWI0.MDATA) && (TWI0.MSTATUS & TWI_RXACK_bm))
    {
        twi0_Status.state = I2C_STATE_NACK;
        twi0_Status.errorState = I2C_ERROR_DATA_NACK;
    }
    else
    {
        // No action required
    }
    
    twi0_Status.state = twi0_eventTable[twi0_Status.state]();
    
    if(twi0_Status.errorState != I2C_ERROR_NONE)
    {
        if (TWI0_Callback != NULL)
        {
            TWI0_Callback();
        }
    }
}

/* I2C Event interfaces */
static i2c_event_states_t I2C_EVENT_IDLE(void)
{
    twi0_Status.busy = false;
    // Force bus to go in idle state
    TWI0.MSTATUS = TWI_BUSSTATE_IDLE_gc;
    
    return I2C_STATE_RESET;
}

static i2c_event_states_t I2C_EVENT_SEND_RD_ADDR(void)
{
    TWI0.MADDR = (uint8_t) ((twi0_Status.address << 1) | 1U);
    return I2C_STATE_RX;
}

static i2c_event_states_t I2C_EVENT_SEND_WR_ADDR(void)
{
    TWI0.MADDR = (uint8_t) (twi0_Status.address << 1);
    
    return I2C_STATE_TX;
}

static i2c_event_states_t I2C_EVENT_TX(void)
{
    i2c_event_states_t retEventState = I2C_STATE_TX;

        if (0U != twi0_Status.writeLength)
        {
            twi0_Status.writeLength--;
            TWI0.MDATA = *twi0_Status.writePtr;
            twi0_Status.writePtr++;
            retEventState = I2C_STATE_TX;
        }
        else
        {
            if (twi0_Status.switchToRead)
            {
                twi0_Status.switchToRead = false;
                retEventState = I2C_STATE_SEND_RD_ADDR;
            }
            else
            {
                retEventState = I2C_EVENT_STOP();
            }
        }

    return retEventState;
}

static i2c_event_states_t I2C_EVENT_RX(void)
{
    i2c_event_states_t retEventState = I2C_STATE_RX;

    if (twi0_Status.readLength == 1U)
    {
        // Next byte will be last to be received, setup NACK
        TWI0.MCTRLB |= TWI_ACKACT_bm;
    }
    else
    {
        // More bytes to receive, setup ACK
        TWI0.MCTRLB &= ~TWI_ACKACT_bm;
    }

    if (0U != --twi0_Status.readLength)
    {
        *twi0_Status.readPtr = TWI0.MDATA;
        twi0_Status.readPtr++;
        // Execute Acknowledge Action followed by a byte read operation
        TWI0_CommandUpdate(TWI_MCMD_RECVTRANS_gc);
        retEventState = I2C_STATE_RX;
    }
    else
    {
        *twi0_Status.readPtr = TWI0.MDATA;
        twi0_Status.readPtr++;
        // Next byte will be last to be received, setup NACK
        TWI0.MCTRLB |= TWI_ACKACT_bm;
        retEventState = I2C_EVENT_STOP();
    }

    return retEventState;
}

static i2c_event_states_t I2C_EVENT_NACK(void)
{
    i2c_event_states_t retEventState = I2C_STATE_NACK;
    retEventState = I2C_EVENT_STOP();
    
    return retEventState;
}

static i2c_event_states_t I2C_EVENT_ERROR(void)
{
    // Clear bus collision status flag
    i2c_event_states_t retEventState = I2C_STATE_ERROR;
    // Clear interrupt status
    TWI0.MSTATUS = (TWI_RIF_bm | TWI_WIF_bm);
    retEventState = I2C_EVENT_RESET();
    
    return retEventState;
}

static i2c_event_states_t I2C_EVENT_STOP(void)
{
    // Send stop
    TWI0_CommandUpdate(TWI_MCMD_STOP_gc);
    TWI0_Close();
    
    return I2C_STATE_IDLE;
}

static i2c_event_states_t I2C_EVENT_RESET(void)
{
    // Reset the bus
    TWI0.MCTRLA &= ~(1 << TWI_ENABLE_bp);
    TWI0.MCTRLA |= 1 << TWI_ENABLE_bp;

    twi0_Status.busy = false;
    
    return I2C_STATE_IDLE;
}

static inline void TWI0_CommandUpdate(TWI_MCMD_t cmd)
{
    TWI0.MCTRLB = (TWI0.MCTRLB & ~TWI_MCMD_gm) | cmd;  
}

/** 
 * @misradeviation{@advisory,2.7} False positive - ISR is a pre-processor macro, 
 * defined in interrupt., and is wrongly treated as a function by the CPP Checker.
 * 
 * @misradeviation{@required,8.2,@required,8.4} False positive - ISR is a pre-processor macro 
 * defined in interrupt.h. The CPP Checker wrongly treats ISR as a function and expects 
 * a declaration to be available.
 *
 * @misradeviation{@required,5.5} False positive - ISR is a pre-processor macro, 
 * defined in interrupt.h file provided by XC8 compiler and is redefined in utils/interrupt_avr.h 
 * this file is out of scope for the MISRA check here but is considered by CPP Checker.
 */
/* cppcheck-suppress misra-c2012-2.7 */
/* cppcheck-suppress misra-c2012-8.2 */
/* cppcheck-suppress misra-c2012-8.4 */
/**
 * @ingroup i2c_host
 * @brief Common Interrupt Service Routine (ISR) for all TWI0 interrupts. 
 * Initialize TWI0 with TWI0_Initialize() before calling this API. \n
 * This API calls the TWI0_ErrorEventHandler() if an error flag is set, otherwise it calls
 * TWI0_EventHandler() for other TWI transmit and receive events.
 * @param None.
 * @return None. \n
 */
ISR(TWI0_TWIM_vect)
{/* cppcheck-suppress misra-c2012-5.5 */
   if (0U != (TWI0.MSTATUS & (TWI_RXACK_bm | TWI_BUSERR_bm | TWI_ARBLOST_bm)))
   {
    TWI0_ErrorEventHandler();
   }
   else if (0U != (TWI0.MSTATUS & (TWI_RIF_bm | TWI_WIF_bm | TWI_CLKHOLD_bm)))
   {
    TWI0_EventHandler();
   }
   else
   {
       // No action required
   }
}

