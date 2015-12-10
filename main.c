#include <msp430g2253.h>

unsigned char temperature = 'A';                    // Byte received via UART
unsigned int count = 0;                             // Used for the flashing LED
unsigned char system_state = 'f';                   // Global System ON vs OFF

/*****
 *  BIT0 = COOLING
 *  BIT3 = SYSTEM
 *  BIT5 = STEADY
 *  BIT6 = HEATING
 */
int main(void)
{
	/*** Set-up system clocks ***/
	WDTCTL = WDTPW + WDTHOLD;                       // No WDT
	if (CALBC1_1MHZ == 0xFF)                        // If calibration constant erased
	{
		while (1);                                  // do not load, trap CPU! (Thanks StackExchange :-] )
	}
	DCOCTL = 0;                                     // Select lowest DCOx and MODx settings
	BCSCTL1 = CALBC1_1MHZ;                          // Set DCO
	DCOCTL = CALDCO_1MHZ;
	/*** Set-up GPIO ***/
	P1SEL = BIT1 + BIT2;                            // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2;                           // P1.1 = RXD, P1.2=TXD
	P1DIR |= (BIT0 + BIT3 + BIT5 + BIT6);			// P1.0,3,5,6 set as output

	P1OUT &= ~(BIT0 + BIT3 + BIT5 + BIT6);			// P1.0,3,5,6 set low

	temperature = 'A';                              // Byte received via UART
	count = 0;                                      // Used for the flashing LED demonstration
	system_state = 'f';                             // Global System ON vs OFF

	/*** Set-up USCI A ***/
	UCA0CTL1 |= UCSSEL_2;                           // SMCLK
	UCA0BR0 = 104;                                  // 1MHz 9600
	UCA0BR1 = 0;                                    // 1MHz 9600
	UCA0MCTL = UCBRS0;                              // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;                           // Initialize USCI state machine
	IE2 |= UCA0RXIE;                                // Enable USCI_A0 RX interrupt
	__bis_SR_register(LPM0_bits + GIE);             // Enter LPM0, interrupts enabled


	while (1) {


		switch (temperature){

			default:
			{
				while (!(IFG2&UCA0TXIFG));				// USCI_A0 TX buffer ready?
				UCA0TXBUF = temperature;				// Send 16-bit character


				if (temperature < 70){
						if (temperature > 65 && system_state == 'f'){

							TA0CCTL0 &= ~CCIE;

							P1SEL &= ~BIT6;
							P1SEL &= ~BIT5;
							P1SEL &= ~BIT3;
							P1SEL &= ~BIT0;

							TA0CCR0 |= 10000-1;				// Counter value
							TA0CCTL0 |= CCIE;				// Enable Timer0_A interrupts
							TA0CTL |= TASSEL_2 + MC_1;		// ACLK, Up Mode (Counts to TA0CCR0)

							P1OUT &= ~BIT0;
							P1OUT &= ~BIT6;
							P1OUT &= ~BIT3;

							__delay_cycles(1000000);        // SW Delay of 1000000 cycles at 1Mhz

							break;
						}
						else {
							system_state = 'o';


							TA0CCTL0 &= ~CCIE;

							P1SEL &= ~BIT6;
							P1SEL &= ~BIT5;
							P1SEL &= ~BIT3;
							P1SEL &= ~BIT0;

							P1OUT |= BIT6;
							P1OUT &= ~BIT0;
							P1OUT &= ~BIT5;
							P1OUT |= BIT3;
							temperature += 1;

							__delay_cycles(1000000);        // SW Delay of 1000000 cycles at 1Mhz

							break;

						}
					}

					else if (temperature > 70){
						if (temperature < 75 && system_state == 'f'){


							TA0CCTL0 &= ~CCIE;

							P1SEL &= ~BIT6;
							P1SEL &= ~BIT5;
							P1SEL &= ~BIT3;
							P1SEL &= ~BIT0;

							//STEADY STATE
							TA0CCR0 |= 10000-1;				// Counter value
							TA0CCTL0 |= CCIE;				// Enable Timer0_A interrupts
							TA0CTL |= TASSEL_2 + MC_1;		// ACLK, Up Mode (Counts to TA0CCR0)

							//P1OUT |= BIT5;   //steady
							P1OUT &= ~BIT0;    //cooling
							P1OUT &= ~BIT6;    //heating
							P1OUT &= ~BIT3;    //system

							__delay_cycles(1000000);        // SW Delay of 1000000 cycles at 1Mhz

							break;
						}

						else {

							TA0CCTL0 &= ~CCIE;

							system_state = 'o';

							P1SEL &= ~BIT6;
							P1SEL &= ~BIT5;
							P1SEL &= ~BIT3;
							P1SEL &= ~BIT0;

							P1OUT |= BIT0;
							P1OUT &= ~BIT6;
							P1OUT &= ~BIT5;
							P1OUT |= BIT3;
							temperature -= 1;


							__delay_cycles(1000000);        // SW Delay of 1000000 cycles at 1Mhz
							break;
						}
					}
					else if (temperature == 70){
							TA0CCTL0 &= ~CCIE;

							system_state = 'f';

							P1SEL &= ~BIT6;
							P1SEL &= ~BIT5;
							P1SEL &= ~BIT3;
							P1SEL &= ~BIT0;

							//STEADY STATE
							TA0CCR0 |= 10000-1;				// Counter value
							TA0CCTL0 |= CCIE;				// Enable Timer0_A interrupts
							TA0CTL |= TASSEL_2 + MC_1;		// ACLK, Up Mode (Counts to TA0CCR0)

							P1OUT &= ~BIT0;  //cooling
							P1OUT &= ~BIT6;  //heating
							P1OUT &= ~BIT3;  //system

							__delay_cycles(1000000);        // SW Delay of 1000000 cycles at 1Mhz

							break;
					}
			}
		} // End of switch statement
	} // End of while loop
} // End of main function

//  USCI A interrupt handler
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
	temperature = UCA0RXBUF;                        // Assign received byte to temperature data
	__bic_SR_register_on_exit(LPM0_bits);           // Wake-up CPU
}

#pragma vector=TIMER0_A0_VECTOR                     // Timer0 A0 interrupt
   __interrupt void Timer0_A0 (void) {

	   count++;
	   if (count == 10)
		   {
		   P1OUT ^= BIT5;                           // P1.5 Steady State Toggle
		   count =0;
		   }
}
