Embedded Lab Part 4 - Security System
Author: Benjamin Harrison
Verison: 2/4/2023
Purpose: Have an TI MSP-430 function as a basic security alarm using a HC-SR501 PIR Sensor
Functionality:


The board uses two inputs and two outputs
----------------------------------------------------------------------------------------------------------------------
Inputs:
	Port 1.5 - Input pin to get a signal from motion sensor
	Port 4.1 - Input button to reset state of alarm system

Outputs:
	Port 1.0 - Output as a red LED to set on and off
	Port 6.6 - Output as a green LED to set on and off
----------------------------------------------------------------------------------------------------------------------



The alarm system has 3 states
----------------------------------------------------------------------------------------------------------------------
ARMED:
	Green LED blinks on and off every 3 seconds
	If the sensor picks up on motion the state changes to WARNING and forces the green LED off

WARNING:
	Red LED blinks on and off every 1 second
	A counter will count up in WARNING state up to 10 seconds
	If 10 seconds are reached and no motion is detected, red LED is forced off and state is switched to ARMED
	If 10 seconds are reached and motion is detected, state changes to ALERT

ALERT:
	Red LED is left on indefinitely and state will not change automatically
----------------------------------------------------------------------------------------------------------------------

Additionally button 4.1 has the functionality of resetting each LED to off as well as being able to set the state of
the alarm system to ARMED regardless of current state
