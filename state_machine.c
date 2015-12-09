#include <msp430g2553.h>
#include <stdio.h>


// Two pieces of hardware
// The heating and cooling unit
// Window limit switch.
/*
	Window sensor open or closed (reed switch)
	window turns on/off the temperature control unit. 

	Send rain flag to bluetooth unit
		Triggers alarm

	Temperature controller turns a fan on or off

	Feed in temperature data to system from the internet

	Heating/Cooling unit

	Tasks - Weather Controller
		Temp, simple weather
	Bluetooth,
	State machine for temperature. 
	

*/


// State variables
volatile unsigned char state = 'I'; // Fan on or off. I is off, O is on. 
volatile unsigned char mode = 'C'; // States for heating and cooling. C is cool, H is heat
volatile unsigned char weather = 'S'; // Weather which is sent to the MSP


// Definitions
#define ROOM_TEMPERATURE 70


// Initialization function
void init_button(void);
void init_WDT(void);

// control handlers
void temperature_controller(unsigned int temperature);

int main(void){

	// 1 Mhz calibration for SMCLK clock
	BCSCTL1 = CALBC1_1MHZ;
    DCOCTL  = CALDCO_1MHZ;

    init_WDT();
    init_button();

    // turn off CPU and enable interrupts
    _bis_SR_register(GIE+LPM0_bits);
}




void temperature_controller(unsigned int temperature) {

		if (64 < temp < 70){
			state = 'I';
			mode = 'H'
		}
		else if (temp < 64){
			state = 'O';
			mode = 'H';
		}
		else if (70 < temp < 76){
			sate = 'I';
			mode = 'C';
		}
		else if (temp >= 76){
			state = 'O';
			mode = 'C';
		}


		

}



