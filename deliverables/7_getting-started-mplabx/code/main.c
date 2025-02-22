/*
 * File:   main.c
 * Author: bobm
 *
 * Created on January 27, 2025, 6:47 PM
 */



#define F_CPU 4000000UL

#include <xc.h>
#include <util/delay.h>


#define USR_LED 5
// #define USR_LED (1 << 5)




void main(void)
{

    // PORTF.DIR = (1 << USR_LED);
    PORTF.DIRSET = (1 << USR_LED);
    PORTF.OUTSET = (1 << USR_LED);
    
    
    while(1)
        
    {
        
        PORTF.OUTCLR = ( 1 << USR_LED);
        _delay_ms(100);
        PORTF.OUTSET = ( 1 << USR_LED);
        _delay_ms(900);    
        
    }
    
    


    return;
}
