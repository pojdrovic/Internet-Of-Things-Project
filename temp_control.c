


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














