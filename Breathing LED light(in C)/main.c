
#include "io430.h"
/* light */
unsigned long upper = 110;
unsigned long start = 100;
/* light */
/* Step */
unsigned long step = 1;
/* Step */
/* Delay */
unsigned long delay = 500;
/* Delay */
/* Change the direction , and change the light */
int increase = 1;

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;

  /* Setting Pin 1.4 */
  P1DIR &= ~BIT4;
  P1REN |= BIT4;
  P1OUT &= ~BIT4;
  P1IFG = 0x0;
  P1IE |= BIT4;
  
  //Enable general interrupt
  __bis_SR_register(GIE + CPUOFF);

  return 0;
}
/*===========================================
Port 1
===========================================*/
#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
{
   P1IE &= ~BIT4;
    /* Pin 1.0  */
    P1OUT &= ~BIT0;
    P1DIR |= BIT0;
    /* Pin 1.2  */
    P1OUT &= ~BIT2;
    P1DIR |= BIT2;
    
    // Setting light
    TA0CTL |= TASSEL_1 + MC_1 + TACLR;
    TA0CCR0 = upper;
    TA0CCR1 = start;
    TA0CCTL0 = CCIE;
    
    // Setting checker
    TA1CTL |= TASSEL_1 + MC_1 + TACLR;
    TA1CCR0 = step;
    TA1CCTL0 = CCIE;
    
    // Setting 
    TA2CTL |= TASSEL_1 + MC_1 + TACLR;
    TA2CCR0 = delay;
    TA2CCTL0 = CCIE;
   P1IFG &= ~BIT4;
   P1IE |= BIT4;
}

/*===========================================
TIMER A0 ISR (TA0CCIFG0) // Setting light
===========================================*/
#pragma vector = TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
  // Back to start
  TA0R = 0x0;
}


/*===========================================
TIMER A1 ISR (TA1CCIFG0) // Setting check 
===========================================*/
#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
  if(TA0R < TA0CCR1 ){
    // Turn off the light
    P1OUT &= ~BIT0;
    P1OUT &= ~BIT2;
  }
  else{
    // Turn on the light
    P1OUT |= BIT0;
    P1OUT |= BIT2;
  }
}

/*===========================================
TIMER A2 ISR (TA2CCIFG0) // Setting TA0CCR1 value -> adjust the light
===========================================*/
#pragma vector = TIMER2_A0_VECTOR
__interrupt void TIMER2_A0_ISR(void)
{
  if(increase == 1){
    // from 100 to 0
    if(TA0CCR1 > 0)
      TA0CCR1 -= 1;
    else{
      increase = 0;
    }
  }
  else{
    // from 0 to 100
    if(TA0CCR1 <= 100)
      TA0CCR1 += 1;
    else{
      increase = 1;
    }
  }
}
