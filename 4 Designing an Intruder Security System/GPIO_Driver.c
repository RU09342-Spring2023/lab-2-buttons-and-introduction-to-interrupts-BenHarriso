/*
 * GPIO_Driver.c
 *
 *  Created on: Jan 6, 2023
 *      Author: (Modified by) Ben Harrison
 *      Version: 1/28/2023
 */



#include "GPIO_Driver.h"
#include <msp430.h>


/**
 * gpioInit(char Port, char Pin, char Direction)
 * Used to configure a single GPIO pin as an input or output.
 *
 * char Port: takes values from 1-6
 * char Pin: takes values from 0-7
 * char Direction: 0 for Input, 1 for Output
 *
 * Example: Setting pin 1.0 to an output
 * gpioInit(1, 0, 1);
 */

//check if input or output
void gpioInit(char Port, char Pin, char Direction){
    //right shift to match bit
    unsigned char PinNumber = 0x01 << Pin;

    //if init as an output
    if(Direction){
        //switch statement to determine and assign the port as an output
        switch(Port){
            // (Port Directory) -> (Or function to set as an output and assign Directory as off)
            // -> (Use correct Bit value with PinNumber)
            case 1:
                P1DIR |= PinNumber;
                break;
            case 2:
                P2DIR |= PinNumber;
                break;
            case 3:
                P3DIR |= PinNumber;
                break;
            case 4:
                P4DIR |= PinNumber;
                break;
            case 5:
                P5DIR |= PinNumber;
                break;
            case 6:
                P6DIR |= PinNumber;
                break;
        }
    }
    else{
        //switch statement to determine and assign the port as an input
        switch(Port){
            // (Port Output) -> (Or function to set as an input and to assign Directory as off)
            //-> (Use correct Bit value with PinNumber)
            case 1:
                P1DIR &= ~PinNumber;
                P1REN |= PinNumber;
                P1OUT |= PinNumber;
                break;
            case 2:
                P2DIR &= ~PinNumber;
                P2REN |= PinNumber;
                P2OUT |= PinNumber;
                break;
            case 3:
                P3DIR &= ~PinNumber;
                P3REN |= PinNumber;
                P3OUT |= PinNumber;
                break;
            case 4:
                P4DIR &= ~PinNumber;
                P4REN |= PinNumber;
                P4OUT |= PinNumber;
                break;
            case 5:
                P5DIR &= ~PinNumber;
                P5REN |= PinNumber;
                P5OUT |= PinNumber;
                break;
            case 6:
                P6DIR &= ~PinNumber;
                P6REN |= PinNumber;
                P6OUT |= PinNumber;
                break;
            }
        }
    }


/**
 * gpioWrite(char Port, char Pin, char Value)
 * Used to write a 1 or 0 to a Pin which has already been declared as an output.
 *
 * char Port: takes values from 1-6
 * char Pin: takes values from 0-7
 * char Value: 0 or 1
 *
 * Example: Setting pin 1.0 to a 1
 * gpioWrite(1, 0, 1);
 */

//check if writing 0 or 1
void gpioWrite(char Port, char Pin, char Value){
    //right shift to match bit
    unsigned char PinNumber = 0x01 << Pin;

        //if write as 1
        if(Value){
            //switch statement to determine and assign the port as an output
            switch(Port){
                // (Port Directory) -> (OR to nondestructively set Bit On) -> (Use correct Bit value with PinNumber)
                case 1:
                    P1OUT |= PinNumber;
                    break;
                case 2:
                    P2OUT |= PinNumber;
                    break;
                case 3:
                    P3OUT |= PinNumber;
                    break;
                case 4:
                    P4OUT |= PinNumber;
                    break;
                case 5:
                    P5OUT |= PinNumber;
                    break;
                case 6:
                    P6OUT |= PinNumber;
                    break;
            }
        }
        else{
            //switch statement to determine and assign the port as an input
            switch(Port){
                // (Port Directory) -> (Or function with tilde to bitmask the chosen bit to off) ->
                //(Use correct Bit value with PinNumber)
                case 1:
                    P1OUT &= ~PinNumber;
                    break;
                case 2:
                    P2OUT &= ~PinNumber;
                    break;
                case 3:
                    P3OUT &= ~PinNumber;
                    break;
                case 4:
                    P4OUT &= ~PinNumber;
                    break;
                case 5:
                    P5OUT &= ~PinNumber;
                    break;
                case 6:
                    P6OUT &= ~PinNumber;
                    break;
            }
        }
}


/**
 * gpioRead(char Port, char Pin, char Value)
 * Used to Read from a pin which has been declared as an input.
 * Returns a 1 or 0 based on pin value.
 *
 * char Port: takes values from 1-6
 * char Pin: takes values from 0-7
 *
 * Example: Reading Pin 1.1
 * unsigned char PinState = gpioRead(1, 1);
 */

char gpioRead(char Port, char Pin){
    //right shift to match bit
    unsigned char PinNumber = 0x01 << Pin;
    //temp variable to hold the returned value
    char readVal;

    //switch statement to determine the port and assign a temp variable either 1 or 0 based off if the bit is on or off
    switch(Port){
    // (Port Directory) -> (And function to set all numbers from directory to 0 except the original bit)
    // -> (Use correct Bit value with PinNumber)
        case 1:
            readVal = P1IN & PinNumber;
            break;
        case 2:
            readVal = P2IN & PinNumber;
            break;
        case 3:
            readVal = P3IN & PinNumber;
            break;
        case 4:
            readVal = P4IN & PinNumber;
            break;
        case 5:
            readVal = P5IN & PinNumber;
            break;
        case 6:
            readVal = P6IN & PinNumber;
            break;
    }
    return readVal;
}



