/**
 * SPI0 Generated Driver File
 *
 * @file spi0.c
 *
 * @ingroup spi0
 *
 * @brief This file contains the driver code for the SPI0 module.
 *
 * @version SPI0 Driver Version 3.1.0
 *  
 * @version SPI0 Package Version 5.1.0
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


#include "../spi0.h"
#include "../spi_polling_types.h"

const struct SPI_INTERFACE SPI0_Host = 
{
    .Initialize = SPI0_Initialize,
    .Deinitialize = SPI0_Deinitialize,
    .Open = SPI0_Open,
    .Close = SPI0_Close,
    .Transfer = SPI0_Transfer,
    .BufferExchange = SPI0_BufferExchange,
    .BufferWrite = SPI0_BufferWrite,
    .BufferRead = SPI0_BufferRead,	
    .ByteExchange = SPI0_ByteExchange,
    .ByteWrite = SPI0_ByteWrite,
    .ByteRead = SPI0_ByteRead,
    .IsTxReady = SPI0_IsTxReady,
    .IsRxReady = SPI0_IsRxReady,
    .RxCompleteCallbackRegister = NULL,
    .TxCompleteCallbackRegister = NULL
};

static const spi_configuration_t spi0_configuration[] =
{
    { 0x33, 0xc4 },
    { 0x34, 0xC4 }
};

void SPI0_Initialize(void)
{
    SPI0.CTRLA &= ~SPI_ENABLE_bm;
    SPI0.CTRLA = (1 << SPI_CLK2X_bp)                /* CLK2X (enabled) */
				|(0 << SPI_DORD_bp)                 /* DORD (disabled) */
				|(0 << SPI_ENABLE_bp)               /* ENABLE (disabled) */
				|(1 << SPI_MASTER_bp)               /* MASTER (enabled) */
				|(SPI_PRESC_DIV64_gc);              /* PRESC (DIV64) */
    SPI0.CTRLB = (1 << SPI_BUFEN_bp)                /* BUFEN (enabled) */
				|(1 << SPI_BUFWR_bp)                /* BUFWR (enabled) */
				|(SPI_MODE_0_gc)                    /* MODE (0) */
				|(1 << SPI_SSD_bp);                 /* SSD (enabled) */
}

void SPI0_Deinitialize(void)
{
    SPI0.CTRLA = 0x0;
    SPI0.CTRLB = 0x0;
    SPI0.INTCTRL = 0x0;
}

bool SPI0_Open(uint8_t spiConfigIndex)
{
    bool returnValue = false;
    if (0 == (SPI0.CTRLA & SPI_ENABLE_bm)) 
    {
        SPI0.CTRLB = spi0_configuration[spiConfigIndex].ctrlb;
        SPI0.CTRLA = spi0_configuration[spiConfigIndex].ctrla;
        SPI0.CTRLA |= SPI_ENABLE_bm;
        returnValue = true;
    } 
    else 
    {
        returnValue = false;
    }
    return returnValue;
}

void SPI0_Close(void)
{
    SPI0.CTRLA &= ~SPI_ENABLE_bm;
}

uint8_t SPI0_ByteExchange(uint8_t byteData)
{
    uint8_t readData = 0;
    SPI0.DATA = byteData;
    while (0 == (SPI0.INTFLAGS & SPI_RXCIF_bm))
    { 
        ; // Wait until ongoing SPI transfer is completed
    }
    readData = SPI0.DATA;
    return readData;
}

void SPI0_ByteWrite(uint8_t byteData)
{
    SPI0.DATA = byteData;
}

uint8_t SPI0_ByteRead(void)
{
    return SPI0.DATA;
}

void SPI0_Transfer(const void *txBuffer, void *rxBuffer, size_t bufferSize)
{
    const uint8_t *bufferTransmit = (const uint8_t *)txBuffer;
    uint8_t *bufferReceive = (uint8_t *)rxBuffer;
	size_t bufferInputSize = bufferSize;
    while(0U != bufferInputSize) 
    {
        SPI0.DATA = *bufferTransmit;
        while (0 == (SPI0.INTFLAGS & SPI_RXCIF_bm))
        {
            ; // Wait until ongoing SPI transfer is completed
        }
        *bufferReceive = SPI0.DATA;
        bufferTransmit++;
        bufferReceive++;  
        bufferInputSize--;
    }
}

void SPI0_BufferExchange(void *bufferData, size_t bufferSize)
{
    uint8_t *buffer = (uint8_t *)bufferData;
	size_t bufferInputSize = bufferSize;
    while(0U != bufferInputSize) 
    {
        SPI0.DATA = *buffer;
        while (0 == (SPI0.INTFLAGS & SPI_RXCIF_bm))
        {
            ; // Wait until ongoing SPI transfer is completed
        }
        *buffer = SPI0.DATA;
        buffer++;
        bufferInputSize--;
    }
}

void SPI0_BufferWrite(void *bufferData, size_t bufferSize)
{
    uint8_t *buffer = (uint8_t *)bufferData;
    uint8_t  readData = 0;
	size_t bufferInputSize = bufferSize;
    while(0U != bufferInputSize) 
    {
        SPI0.DATA = *buffer;
        while(0 == (SPI0.INTFLAGS & SPI_RXCIF_bm))
        {
            ; // Wait until ongoing SPI transfer is completed
        }        
        readData = SPI0.DATA;
        (void) readData;
        buffer++;
        bufferInputSize--;
    }
}

void SPI0_BufferRead(void *bufferData, size_t bufferSize)
{
    uint8_t *buffer = (uint8_t *)bufferData;
	size_t bufferInputSize = bufferSize;
    while(0U != bufferInputSize) 
    {
        SPI0.DATA = 0;
        while (0 == (SPI0.INTFLAGS & SPI_RXCIF_bm))
            {
                ; // Wait until ongoing SPI transfer is completed
            }
        *buffer = SPI0.DATA;
        buffer++;
        bufferInputSize--;
    }
}

bool SPI0_IsTxReady(void)
{
    bool returnValue = false;
    if(0 != (SPI0.CTRLA & SPI_ENABLE_bm))
    {
        if(0 != (SPI0.INTFLAGS & SPI_DREIF_bm))
        {
            returnValue = true;
        }
        else
        {
           returnValue = false; 
        }
    }
    else
    {
        returnValue = false;
    }
    return returnValue;
}

bool SPI0_IsRxReady(void)
{
    bool returnValue = false;
    if(0 != (SPI0.CTRLA & SPI_ENABLE_bm))
    {
        if(0 != (SPI0.INTFLAGS & SPI_RXCIF_bm))
        {
            returnValue = true;
        }
        else
        {
           returnValue = false; 
        }
    }
    else
    {
        returnValue = false;
    }
    return returnValue;
}