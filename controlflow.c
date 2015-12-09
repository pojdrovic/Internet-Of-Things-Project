


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

}