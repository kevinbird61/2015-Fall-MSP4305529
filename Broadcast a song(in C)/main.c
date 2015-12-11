
#include "io430.h"
#define END 42

void changeSound(int filter);
int sheet[42] = {1,1,5,5,6,6,5,4,4,3,3,2,2,1
                 ,5,5,4,4,3,3,2,5,5,4,4,3,3,2,
                 1,1,5,5,6,6,5,4,4,3,3,2,2,1};
int time[42] = { 1,1,1,1,1,1,2,1,1,1,1,1,1,2,
                1,1,1,1,1,1,2,1,1,1,1,1,1,2,
                1,1,1,1,1,1,2,1,1,1,1,1,1,2};
int pause = 0;
int pause_p2_1 = 0;
int start = 0;
int index = 0;

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  // P1.2
  P1DIR = BIT2; 
  P1SEL = BIT2;
  // P1.1
  P1SEL &= ~BIT1;
  P1DIR &= ~BIT1;
  P1REN |= BIT1;
  P1OUT |= BIT1;
  P1IES |= BIT1;
  P1IE |= BIT1;
  // P2.1
  P2SEL &= ~BIT1;
  P2DIR &= ~BIT1;
  P2REN |= BIT1;
  P2OUT |= BIT1;
  P2IES |= BIT1;
  P2IE |= BIT1;
  
  // TEST PIN : P1.1 -> P 1.5
  P1DIR |= BIT5;
  P1OUT |= BIT5;
  
  // TEST PIN : P2.1 -> P 1.4
  P1DIR |= BIT4;
  P1OUT |= BIT4;
  
  __bis_SR_register(GIE + CPUOFF);
  
  while(1);
  return 0;
}

void changeSound(int filter){
  switch(filter){
  case 1:
    // Do
    TA0CCR0 = 1912;
    TA0CCR1 = 956;
    break;
  case 2:
    // Re 
    TA0CCR0 = 1704;
    TA0CCR1 = 852;
    break;
  case 3:
    // Mi 
    TA0CCR0 = 1518;
    TA0CCR1 = 759;
    break;
  case 4:
    // Fa
    TA0CCR0 = 1432;
    TA0CCR1 = 716;
    break;
  case 5:
    // So 
    TA0CCR0 = 1276;
    TA0CCR1 = 638;
    break;
  case 6:
    // La
    TA0CCR0 = 1136;
    TA0CCR1 = 568;
    break;
  case 7:
    // Si
    TA0CCR0 = 1012;
    TA0CCR1 = 506;
    break;
  case 8:
    // Do_2
    TA0CCR0 = 956;
    TA0CCR1 = 478;
    break;
  }
  if(index>=END){
    TA0CCR0 = 0;
    TA0CCR1 = 0;
  }
  index++;
}

/*===========================================
TIMER A1 ISR (TA1CCIFG0)
===========================================*/
#pragma vector = TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
  if(pause == 0){
    // Pause is false
    if(time[index]==1){
      TA1CCR0 = 16384;
      changeSound(sheet[index]);
    }
    else{
      TA1CCR0 = 32767;
      changeSound(sheet[index]);
    }
  }
  else{
    // Pause is true
    TA0CCR0 = 0;
    TA0CCR1 = 0;
    TA1CCR0 = 2000;
  }
  pause = 1 - pause;
}

#pragma vector=PORT1_VECTOR
__interrupt void P1_ISR(void)
{
  P1IE &= ~BIT1;
  // For gitlab test pin
  P1OUT |= BIT5;
  
  index = 0;
  pause = 0;
  pause_p2_1 = 0;
  start = 0;

  TA0CCR0 = 0;
  TA0CCR1 = 0;
  
  TA0CTL |= TACLR;
  TA1CTL |= TACLR;
  
  TA1CCTL0 &= ~CCIE;
  
  // For gitlab test pin
  P1OUT &= ~BIT5;
  
  P1IFG &= ~BIT1;
  P1IE |= BIT1;
}

#pragma vector=PORT2_VECTOR
__interrupt void P2_ISR(void)
{
  // Start and Pause
  P2IE &= ~BIT1;
  
  // For gitlab test pin 
  P1OUT |= BIT4;
    
  if(start == 0){
    // start
    // Setting Timer - For melody
    TA0CCR0 = 0;
    TA0CCR1 = 0;
    TA0CCTL1 |= OUTMOD_3;
    TA0CTL |= TASSEL_2 + MC_1 + TACLR;
    // Setting Timer - For delay interrupt => 0.5 sec
    TA1CTL |= TASSEL_1 + MC_1 + TACLR;
    TA1CCR0 = 16384;
    TA1CCTL0 = CCIE;
    
    start++;
  }
  else{
    // Pause or restart
    if(pause_p2_1 == 0){
      TA0CCR0 = 0;
      TA0CCR1 = 0;
      TA1CCTL0 &= ~CCIE;
    }
    else{
      TA1CCTL0 |= CCIE;
    }
    pause_p2_1 = 1 - pause_p2_1;
  }
  // For gitlab test pin 
  P1OUT &= ~BIT4;
  
  P2IFG &= ~BIT1;
  P2IE |= BIT1;
}
