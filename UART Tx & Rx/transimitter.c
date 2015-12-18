#include <msp430.h>
int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  // Enable the special purpose TX:3.3 RX:3.4
  P3SEL = BIT3 + BIT4;
  UCA0CTL1 |= UCSWRST;
  UCA0CTL1 |= UCSSEL_2;
  
  UCA0BR0 = 109;
  UCA0BR1 = 0;
  UCA0MCTL = 4;
  
  UCA0CTL1 &= ~UCSWRST;
  UCA0IE |= UCRXIE;
  
  // Enabled P2.1
  P2SEL &= ~BIT1;
  P2DIR &= ~BIT1;
  P2REN |= BIT1;
  P2OUT |= BIT1;
  P2IES |= BIT1;
  P2IE |= BIT1;
  P2IFG = 0;
  
  __bis_SR_register(GIE);
  while(1);
  return 0;
}

#pragma vector=PORT2_VECTOR
__interrupt void P2_ISR(void){
  // start , disable interrupt
  P2IE &= ~BIT1;
  UCA0IE = 0x02;
  // Giving the Test bit
  while (!(UCA0IFG&UCTXIFG));
  UCA0TXBUF = 255; // 00000010
  UCA0IE = 0x00;
  P2IFG &= ~BIT1;
  P2IE |= BIT1;
}