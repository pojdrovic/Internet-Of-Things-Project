#include <msp430g2553.h>
#include <stdio.h>

// Variable definitions

unsigned char temperature = 'F';
unsigned char system_state = 'f';

/*
void InitializeUART(void)
{
	P1SEL |= RXD + TXD;  // P1.1 = RXD, P1.2 = TXD
	P1SEL2 |= RXD + TXD;  // P1.1 = RXD, P1.2 = TXD

	UCA0CTL1 |= UCSSEL_2;  // Use system Master Clock at 1MHz
	UCA0BR0 = 104;  // (1 MHz)/(9600 bps)
	UCA0BR1 = 0;
	UCA0MCTL = UCBRS0;  // modulation UCBRSx = 1 found on pg 424 of datasheet
	UCA0CTL1 &= ~UCSWRST;  // ** initialize USCI state machine **
	IE2 |= UCA0RXIE;  // Enable USCI_A0 RX interrupt
}
*/

unsigned char uartSend(unsigned char *pucData, unsigned char ucLength)
{
	while(ucLength--)
	{
		// Wait for TX buffer to be ready for new data
		while(!(UCA1FG & UCTXIFG));

		// Push data to TX buffer
		UCA1TXBUF = * pucData;

		// Update Variables

		ucLength--;
		pucData++;
	}

	// Wait until the last byte is completely seng
	while(UCA1STAT & UCBUSY);
}

int main(void)
{
d
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


  while (1) {
		  	switch (temperature){

			if (temperature < 70){
				if (temperature > 65 && system_state == 'f'){


					TA0CCTL0 &= ~CCIE;

					P1SEL &= ~BIT6;
					P1SEL &= ~BIT5;
					P1SEL &= ~BIT3;
					P1SEL &= ~BIT0;

					P1OUT |= BIT5;
					P1OUT &= ~BIT0;
					P1OUT &= ~BIT6;	
					P1OUT &= ~BIT3;
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

					P1OUT |= BIT5;
					P1OUT &= ~BIT0;
					P1OUT &= ~BIT6;	
					P1OUT &= ~BIT3;
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


					}
				}
			} // End of switch statement
  } // End of while loop 
} // End of main function



#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{
	Rx_Data = UCA0RXBUF;					// Assign received byte to Rx_Data
	__bic_SR_register_on_exit(LPM0_bits);	// Wake-up CPU
}



#pragma vector=TIMER0_A0_VECTOR     // Timer0 A0 interrupt service routine
   __interrupt void Timer0_A0 (void) {

	   count++;
	   if (count == 10)
		   {
		   P1OUT ^= BIT0 + BIT6;					// P1.0 Toggle (Red LED)
		   count =0;
		   }
}