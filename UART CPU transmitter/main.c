#include "LED_Branch.h"

#define SIZE 22
/* Pattern , which use with function : next_pattern()*/
int pattern[SIZE] = 
{
11,12,13,14,15,
16,17,18,19,20,
21,-22,-21,-20,-19,
-18,-17,-16,-15,-14,
-13,-12  
//11,-12,11,-12,11,-12,12,-13,11,-12,12,-13,70
};
int pattern_delay[SIZE] = 
{
2,2,2,2,2,
2,2,2,2,2,
2,2,2,2,2,
2,2,2,2,2,
2,2
};
/* store the number of one transmition */
int package = 8;
/* every 0.5 sec , each change ; first byte => start up 
signal_store : for one signal instruction from piano
local_signal : for one signal instruction by autoplay (src : pattern[]) ;
*/
int signal_store[8] = {30,0,0,0,0,0,0,0};
/* Retain status , 0 for autoplay and 1 for piano */
int status = 0;
/* For TA1 , if when piano : 1 , autoplay = 0 */
int check_result = 0;
/* Function :
check_status() : check is it time to change to autoplay ? or have piano input recently.
GPIO_IE_UP() : enabled GPIO interrupt
next_pattern(int select) : modulize the pattern show
*/
void check_status();
void GPIO_IE_UP();

int main( void )
{
  // Stop watchdog timer to prevent time out rese
  WDTCTL = WDTPW + WDTHOLD;
  // Enable the special purpose TX:3.3 RX:3.4
  P3SEL = BIT3 + BIT4;
  UCA0CTL1 |= UCSWRST;
  UCA0CTL1 |= UCSSEL_2;
  // Baud Rate => 9600
  UCA0BR0 = 109;
  UCA0BR1 = 0;
  UCA0MCTL = 4;
  
  UCA0CTL1 &= ~UCSWRST;
  UCA0IE |= UCRXIE;
  // Enabled 8 pin GPIO to Get signal from Piano => port 2 : 5,4,3,2 ; port 1 : 5,4,3,2 ;
  GPIO_IE_UP();
  // Setting Timer - For delay interrupt => 0.5 sec
  TA1CTL |= TASSEL_1 + MC_1 + TACLR;
  TA1CCR0 = 32768;
  TA1CCTL0 = CCIE;
  // Setting Timer - For delay interrupt and check for every 4 sec , TA0R / 4 , so set the TA0CCR0 = original 1 sec
  TA0CTL |= TASSEL_1 + ID_3 + MC_1 + TACLR;
  TA0CCR0 = 32768;
  TA0CCTL0 = CCIE;
  
  __bis_SR_register(GIE);
  while(1){};
  return 0;
}
/*===========================================
TIMER A1 ISR (TA1CCIFG0)
===========================================*/
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void){
  // read signal_store[] , and then convert to uart signal
  int i,j;
  // check_result == 1 => piano
  if(check_result==1){
    // deliver the signal (Using UCA0TXBUF) => for 8 byte // 
    for(i = 0 ; i < package ; i++){
      // Deliver for 8 times , i for times
      UCA0IE = 0x02;
        // store_signal
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = signal_store[i];
        if(i != 0){
        signal_store[i] = 0;
        }
      UCA0IE = 0x00;
    }
  }
  else{
    // check_result == 0 => autoplay
    // local_signal
    int size = SIZE;
    for(i=0;i<size;i++){
      next_pattern(pattern[i]);
      for(j = 0 ; j < package ; j++){
      // Deliver for 8 times , i for times
      UCA0IE = 0x02;
        // store_signal
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = local_signal[j];
        //if(j!=0){  
        //local_signal[j] = 0;
        //}
      UCA0IE = 0x00;
      }
      // Setting Timer Delay here ; Disable TA1CCTL0 = ~CCIE; and Enable TA2 To do the Delay you want
      unsigned long count = 0;
      while(count< (5000 * pattern_delay[i])){count++;}
    }
  }
}
/*===========================================
TIMER A0 ISR (TA0CCIFG0)
===========================================*/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void){
  /* When this timer interrupt happened
  Means its time to switch pattern , from piano to autoplay
  change status to 0
  */
  status = 0;
  check_result = 0;
}
/*===========================================
PORT2 ISR
===========================================*/
#pragma vector=PORT2_VECTOR
__interrupt void P2_ISR(void){
  // start , disable interrupt
  P2IE = 0x00;
  if(P2IFG & BIT2){
    // when pin 2.2 triggered
    // Switch Type
  }
  if(P2IFG & BIT3){
    // when pin 2.3 triggered - Si
    // LED1
    signal_store[1] |= (BIT7 | BIT4);
    signal_store[2] |= (BIT5);
    // LED2
    signal_store[3] |= (BIT3 | BIT2);
    //Branch-R
    signal_store[4] |= (BIT0);
    signal_store[5] |= (BIT7);
    //Branch-G
    signal_store[6] |= (BIT5 | BIT4);
    //Branch-B
    signal_store[7] |= (BIT2 | BIT1);
  }
  if(P2IFG & BIT4){
    // when pin 2.4 triggered - So
    // LED1
    signal_store[1] |= (BIT7 | BIT5);
    signal_store[2] |= (BIT7);
    // LED2
    signal_store[3] |= BIT5;
    // R
    signal_store[4] |= BIT2;
    // G
    signal_store[6] |= BIT7;
    // B
    signal_store[7] |= BIT4;
  }
  if(P2IFG & BIT5){
    // when pin 2.5 triggered - La
    // LED1
    signal_store[1] |= (BIT7 | BIT4);
    signal_store[2] |= BIT6;
    // LED2
    signal_store[3] |= BIT4;
    // R
    signal_store[4] |= BIT1;
    // G
    signal_store[6] |= BIT6;
    // B
    signal_store[7] |= BIT3;
  }
  status = 1;
  // Clear the TA0
  TA0CCTL0 = CCIE;
  TA0R = 0;
  // Check the status
  check_status();
  P2IFG = 0x00;
  P2IE = 60; // Enable all interrupt : 0011 1110
}
/*===========================================
PORT1 ISR
===========================================*/
#pragma vector=PORT1_VECTOR
__interrupt void P1_ISR(void){
  // start , disable interrupt
  P1IE = 0x00;
  if(P1IFG & BIT2){
    // when pin1.2 triggered - Do
    // LED1 
    signal_store[1] = (BIT7 | BIT6 | BIT3);
    // LED2
    signal_store[2] |= (BIT4 | BIT3);
    // R 
    signal_store[3] |= (BIT0 | BIT1);
    // G
    signal_store[5] |= (BIT6 | BIT5);
    // B 
    signal_store[6] |= (BIT3 | BIT2);
  }
  if(P1IFG & BIT3){
    // when pin 1.3 triggered - Re
    // LED1
    signal_store[1] |= (BIT7 | BIT6 | BIT2);
    // LED2
    signal_store[2] |= BIT2;
    // R
    signal_store[4] |= BIT7;
    // G
    signal_store[5] |= BIT4;
    // B
    signal_store[6] |= BIT1;
  }
  if(P1IFG & BIT4){
    // when pin 1.4 triggered - Mi
    // LED1
    signal_store[1] |= (BIT7 | BIT5 | BIT1);
    // LED2
    signal_store[2] |= BIT1;
    // R
    signal_store[4] |= BIT6;
    // G
    signal_store[5] |= BIT3;
    // B
    signal_store[6] |= BIT0;
  }
  if(P1IFG & BIT5){
    // when pin 1.5 triggered - Fa
    // LED1
    signal_store[1] |= (BIT7 | BIT5 | BIT0);
    // LED2
    signal_store[2] |= BIT0;
    signal_store[3] |= (BIT7 | BIT6);
    // R
    signal_store[4] |= (BIT5 | BIT4 | BIT3);
    // G
    signal_store[5] |= (BIT2 | BIT1 | BIT0);
    // B
    signal_store[7] |= (BIT7 | BIT6 | BIT5);
  }
  status = 1;
  // Clear the TA0
  TA0CCTL0 = CCIE;
  TA0R = 0;
  // Check the status
  check_status();
  P1IFG = 0x00;
  P1IE = 60; // Enable all interrupt : 0011 1100
}
/*===========================================
User define function
===========================================*/
void GPIO_IE_UP(){
  // Enabled 8 pin GPIO => port 2 : 5,4,3,2 ; port 1 : 5,4,3,2 
  // Port 2
  P2SEL &= (~BIT5 & ~BIT4 & ~BIT3 & ~BIT2);
  P2DIR &=(~BIT5 & ~BIT4 & ~BIT3 & ~BIT2);
  P2REN |= (BIT5 | BIT4 | BIT3 | BIT2);
  P2OUT |= (BIT5 | BIT4 | BIT3 | BIT2);
  P2IES |= (BIT5 | BIT4 | BIT3 | BIT2);
  P2IE |= (BIT5 | BIT4 | BIT3 | BIT2);
  P2IFG = 0x00;
  // Port 1
  P1SEL &= (~BIT5 & ~BIT4 & ~BIT3 & ~BIT2);
  P1DIR &= (~BIT5 & ~BIT4 & ~BIT3 & ~BIT2);
  P1REN |= (BIT5 | BIT4 | BIT3 | BIT2);
  P1OUT |= (BIT5 | BIT4 | BIT3 | BIT2);
  P1IES |= (BIT5 | BIT4 | BIT3 | BIT2);
  P1IE |= (BIT5 | BIT4 | BIT3 | BIT2);
  P1IFG = 0x00;
}

void check_status(){
  // if status = 0 , do autoplay , stop the store_signal output , and start to broadcast autoplay
  // if status = 1 , Enable piano's pattern
  switch(status){
  case 0:
    check_result = 0;
    break;
  case 1:
    check_result = 1;
    break;
  default:
    break;
  }
}