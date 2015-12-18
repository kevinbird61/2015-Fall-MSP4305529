#include "io430.h"

void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
  P3SEL |= BIT4;                         // P4.4,5 = USCI_A1 TXD/RXD
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL1 |= UCSSEL_2;                    // CLK = SMCLK
  P1DIR |= BIT0;
  P1OUT &= ~BIT0; 
//===========set the baud-rate register====
  UCA0BR0 = 109;
  UCA0BR1 = 0;
  UCA0MCTL = 4;
//=========================================  
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A1 RX interrupt

  __bis_SR_register(GIE);       // Enter LPM3, interrupts enabled       
  __no_operation();
  while(1);
// For debugger
}
// Echo back RXed character, confirm TX buffer is ready first
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void)
{
  switch(__even_in_range(UCA0IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
    //while (!(UCA0IFG&UCTXIFG));             // USCI_A1 TX buffer ready?   
      P1OUT ^= BIT0; 
      UCA0IFG &= ~UCRXIFG;
      //char data =UCA0RXBUF;// TX -> RXed character
     break;        
  case 4:break;                             // Vector 4 - TXIFG
  default: break;  
  }
}