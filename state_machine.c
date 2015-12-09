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

    //init_WDT();
    //init_button();

    // turn off CPU and enable interrupts
    _bis_SR_register(GIE+LPM0_bits);
}

int main(void)
{
	/*** Set-up system clocks ***/
	WDTCTL = WDTPW + WDTHOLD;				// Stop WDT
	if (CALBC1_1MHZ == 0xFF)				// If calibration constant erased
			{
			while (1);						// do not load, trap CPU!
			}
	DCOCTL = 0;								// Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_1MHZ;					// Set DCO
	DCOCTL = CALDCO_1MHZ;
	/*** Set-up GPIO ***/
	P1SEL = BIT1 + BIT2;					// P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2;					// P1.1 = RXD, P1.2=TXD
	P1DIR |= BIT6 + BIT0;					// P1.6 set as output
	P1OUT &= ~(BIT6 + BIT0);				// P1.6 set low
	/*** Set-up USCI A ***/
	UCA0CTL1 |= UCSSEL_2;					// SMCLK
	UCA0BR0 = 104;							// 1MHz 9600
	UCA0BR1 = 0;							// 1MHz 9600
	UCA0MCTL = UCBRS0;						// Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;					// Initialize USCI state machine
	IE2 |= UCA0RXIE;						// Enable USCI_A0 RX interrupt
	__bis_SR_register(LPM0_bits + GIE);		// Enter LPM0, interrupts enabled


/*
  while(1)
  {
	  				switch (Rx_Data)
	  				{
	  					case 0x41:							// ON Command
	  						//while (!(IFG2&UCA0TXIFG));	// USCI_A0 TX buffer ready?
	  						//UCA0TXBUF = 0x41;				// Send 8-bit character
	  					    TA0CCTL0 &= ~CCIE;				// Disable Timer0_A interrupts
	  					    P1SEL &= ~BIT6;					// P1.6 selected as GPIO
	  						P1OUT |= BIT6 + BIT0;			// P1.0 and P1.6 set high

	  						break;

	  					case 0x42:							// OFF Command
	  						//while (!(IFG2&UCA0TXIFG));	// USCI_A0 TX buffer ready?
	  						//UCA0TXBUF = 0x42;				// Send 8-bit character
	  					    TA0CCTL0 &= ~CCIE;				// Disable Timer0_A interrupts
	  					    P1SEL &= ~BIT6;					// P1.6 selected as GPIO
	  						P1OUT &= ~(BIT6 + BIT0);		// P1.0 and P1.6 set low
	  						break;

	  					case 0x46:							// FLASH Command
	  						//while (!(IFG2&UCA0TXIFG));	// USCI_A0 TX buffer ready?
	  						//UCA0TXBUF = 0x46;				// Send 8-bit character
	  						// Timer0_A Set-Up /
	  					    TA0CCR0 |= 10000-1;				// Counter value
	  					    TA0CCTL0 |= CCIE;				// Enable Timer0_A interrupts
	  					    TA0CTL |= TASSEL_2 + MC_1;		// ACLK, Up Mode (Counts to TA0CCR0)
	  					    // Timer0_A Set-Up
	  						break;

	  					case 0x3E:							// INCREASE Command
	  						break;

	  					case 0x3C:							// DECREASE Command
	  						break;

	  					case 0x31:							// 1 Command
	  						break;

	  					case 0x32:							// 2 Command
	  						break;

	  					case 0x33:							// 3 Command
	  						break;

	  					case 0x34:							// 4 Command
							break;

	  					case 0x35:							// 5 Command
	  						break;

	  					default: break;
	  				}
						 __bis_SR_register(LPM0_bits);	// Enter LPM0, interrupts enabled
  }

  */

  while (1) {

		switch (state)
		{
			if (state == 'o'){
				P1OUT |= BIT4;

					switch (temperature)
					{
					    case 0x3c:
					        P1OUT |= BIT6;
					        P1OUT &= ~BIT0;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					        break;

					    case 0x3d:
					    	P1OUT |= BIT6;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x3e:
					    	P1OUT |= BIT6;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x3f:
					    	P1OUT |= BIT6;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x40:
					    	P1OUT |= BIT6;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x41:
					    	P1OUT |= BIT6;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x42:
					    	P1OUT |= BIT5;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT6;
					        P1OUT &= ~BIT3;

					    	break;

					    case 0x43:
					    	P1OUT |= BIT5;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT6;	
					        P1OUT &= ~BIT3;

					    	break;

					    case 0x44:
					    	P1OUT |= BIT5;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT6;
					        P1OUT &= ~BIT3;	

					    	break;

					    case 0x45:
					    	P1OUT |= BIT5;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT6;
					        P1OUT &= ~BIT3;	

					    	break;

					    case 0x46:
					    	P1OUT |= BIT5;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT6;
					        P1OUT &= ~BIT3;	

					    	break;

					    case 0x4b:
					    	P1OUT |= BIT5;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT6;
					        P1OUT &= ~BIT3;	

					    	break;


					    case 0x48:
					    	P1OUT |= BIT5;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT6;
					        P1OUT &= ~BIT3;	

					    	break;

					    case 0x49:
					    	P1OUT |= BIT5;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT6;	
					        P1OUT &= ~BIT3;

					    	break;

					    case 0x4a:
					    	P1OUT |= BIT5;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT6;
					        P1OUT &= ~BIT3;	

					    	break;

					    case 0x4b:
					    	P1OUT |= BIT5;
					    	P1OUT &= ~BIT0;
					        P1OUT &= ~BIT6;	
					        P1OUT &= ~BIT3;

					    	break;

					    case 0x4c:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x4d:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;
					        P1OUT |= BIT3;	

					    	break;

					    case 0x4e:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;
					        P1OUT |= BIT3;	

					    	break;


					    case 0x4f:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;
					        P1OUT |= BIT3;	

					    	break;

					    case 0x50:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;
					        P1OUT |= BIT3;	

					    	break;

					    case 0x51:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;
					        P1OUT |= BIT3;	

					    	break;

					    case 0x52:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x53:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x54:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x55:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x56:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x57:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x59:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;

					    case 0x60:
					    	P1OUT |= BIT0;
					    	P1OUT &= ~BIT6;
					        P1OUT &= ~BIT5;	
					        P1OUT |= BIT3;

					    	break;
						} // End of case statement 

					}

					else if (state == 'f'){
						P1OUT &= ~BIT0;
						P1OUT &= ~BIT3;
						P1OUT &= ~BIT4;
						P1OUT &= ~BIT5;
						P1OUT &= ~BIT6;
			}
		}
	}
}


/*
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
*/

// lolololol



