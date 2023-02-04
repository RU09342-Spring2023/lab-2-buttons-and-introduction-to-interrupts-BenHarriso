/*
 * OccupancyDetector.c
 *
 *  Created on: Feb 1, 2023
 *      Author: Ben Harrison
 *      Version 2/4/2023
 */

#include <msp430.h>

#include "GPIO_Driver.h"


int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               //stop watchdog timer

    //initialize states
    #define ARMED_STATE 0
    #define WARNING_STATE 1
    #define ALERT_STATE 2

    gpioInit(1, 5, 0);          //set pin 1.5 as an input
    gpioInit(4, 1, 0);          //set button 4.1 as input
    gpioInit(1, 0, 1);          //set 1.0 as output
    gpioInit(6, 6, 1);          //set 6.6 as output

    PM5CTL0 &= ~LOCKLPM5;       // Disable the GPIO power-on default high-impedance mode
                                // to activate previously configured port settings

    gpioWrite(1, 0, 0);         // Set Pin 1.0 to 0 initially
    gpioWrite(6, 6, 0);         // Set Pin 6.6 to 0 initially

    char LEDState = 0x00;       //char to hold state off the LED as on or off

    char state = ARMED_STATE;   //state of the security system, armed, warning or alert

    char secCount = 0;           //char to count the seconds in warning state before setting off alarm


    while(1)
    {
      //char to see if there is movement detected
      char detect = gpioRead(1, 5);

      switch (state) {

          //if no person detected
          case ARMED_STATE:

              //Check to see if sensor picks up something
              if(!detect){
                  //blink green
                  gpioWrite(6, 6, LEDState);
              }
              //if motion is registered
              else{
                  //force off green LED
                  gpioWrite(6, 6, 0);

                  //set state to warning
                  state = WARNING_STATE;
              }

              //1.5s delay, 3 sec total for green light to blink on and off
              __delay_cycles(1500000);
              break;

        //if person detected
        case WARNING_STATE:

            gpioWrite(1, 0, LEDState);

            //check if motion is still detected and if second counter has reached 10 seconds (20 half seconds)
            if(detect && secCount == 20){

                //set the state to alert
                state = ALERT_STATE;

                //turn off red LED
                gpioWrite(1, 0, 0);

                //reset second counter
                secCount = 0;
            }

            //if nothing is detected and if second counter has reached 10 seconds (20 half seconds)
            else if(!detect && secCount == 20){

                //set the state to armed
                state = ARMED_STATE;

                //reset second counter
                secCount = 0;
            }

            //add to the second counter
            secCount = secCount + 1;

            //0.5s delay, 1 sec total to blink red light on and off
            __delay_cycles(500000);
            break;

        //case where alarm is set off and
        case ALERT_STATE:
            //set LED to be red until disarmed
            gpioWrite(1, 0, LEDState);

            break;
      }



      LEDState ^= 0x01;   // Toggle LED State

      //disarm if button pressed
      if(!gpioRead(4, 1)){
          //reset the state
          state = ARMED_STATE;

          //turn off LEDs
          gpioWrite(1, 0, 0);
          gpioWrite(6, 6, 0);

          //pause detection while button is pressed
          while(!gpioRead(4, 1));

      }
    }





}
