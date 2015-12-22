#include <msp430.h>

#define SIZE 2
/* Pattern , which use with function : next_pattern()*/
int pattern[SIZE] = {1,2};
/* store the number of one transmition */
int package = 8;
/* every 0.5 sec , each change ; first byte => start up 
signal_store : for one signal instruction from piano
local_signal : for one signal instruction by autoplay (src : pattern[]) ;
*/
int signal_store[8] = {255,0,0,0,0,0,0,0};
int local_signal[8] = {255,0,0,0,0,0,0,0};
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
void next_pattern(int select); // read array
/*LED light
mode: 0 -> turn off ; 1 -> light up
*/
void LED0(int mode);
void LED1(int mode);
void LED2(int mode);
void LED3(int mode);
void LED4(int mode);
void LED5(int mode);
void LED6(int mode);
void LED7(int mode);
void LED8(int mode);
void LED9(int mode);
void LED10(int mode);
void LED11(int mode);
void LED12(int mode);
void LED13(int mode);
void LED14(int mode);
void LED15(int mode);
void LED16(int mode);
void LED17(int mode);
void LED18(int mode);
void LED19(int mode);
void LED20(int mode);
void LED21(int mode);
/* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b , 6 -> off*/
void Branch0(int color);
void Branch1(int color);
void Branch2(int color);
void Branch3(int color);
void Branch4(int color);
void Branch5(int color);
void Branch6(int color);
void Branch7(int color);
void Branch8(int color);
void Branch9(int color);
void Branch10(int color);


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
  TA1CCR0 = 16384;
  TA1CCTL0 = CCIE;
  // Setting Timer - For delay interrupt and check for every 4 sec , TA0R / 4 , so set the TA0CCR0 = original 1 sec
  TA0CTL |= TASSEL_1 + ID_2 + MC_1 + TACLR;
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
  int i;
  // check_result == 1 => piano
  if(check_result==1){
    // deliver the signal (Using UCA0TXBUF) => for 8 byte // 
    for(i = 0 ; i < package ; i++){
      // Deliver for 8 times , i for times
      UCA0IE = 0x02;
        // store_signal
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = signal_store[i];
      signal_store[i] = 0;
      UCA0IE = 0x00;
    }
  }
  else{
    // check_result == 0 => autoplay
    // local_signal
    int size = SIZE;
    for(i=0;i<size;i++){
      next_pattern(pattern[i]);
      for(i = 0 ; i < package ; i++){
      // Deliver for 8 times , i for times
      UCA0IE = 0x02;
        // store_signal
        while (!(UCA0IFG&UCTXIFG));
        UCA0TXBUF = local_signal[i];
      local_signal[i] = 0;
      UCA0IE = 0x00;
      }
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
  TA0R = 0;
  // Check the status
  check_status();
  P2IFG = 0x00;
  P2IE = 0x60; // Enable all interrupt : 0011 1110
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
  TA0R = 0;
  // Check the status
  check_status();
  P1IFG = 0x00;
  P1IE = 0x60; // Enable all interrupt : 0011 1100
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

void next_pattern(int select){
  // Enable using integer to control LED pattern
  switch(select){
    // 0~21 : LED on ; 22 ~ 32 : Branch-R ; 33 ~ 43 : Branch-G ; 44 ~ 55 : Branch-B
    case 0:
      LED0(1);
      break;
    case 1:
      LED1(1);
      break;
    case 2:
      LED2(1);
      break;
    case 3:
      LED3(1);
      break;
    case 4:
      LED4(1);
      break;
    case 5:
      LED5(1);
      break;
    case 6:
      LED6(1);
      break;
    case 7:
      LED7(1);
    break;
    case 8:
      LED8(1);
    break;
    case 9:
      LED9(1);
    break;
    case 10:
      LED10(1);
    break;
    case 11:
      LED11(1);
    break;
    case 12:
      LED12(1);
    break;
    case 13:
      LED13(1);
    break;
    case 14:
      LED14(1);
    break;
    case 15:
      LED15(1);
    break;
    case 16:
      LED16(1);
    break;
    case 17:
      LED17(1);
    break;
    case 18:
      LED18(1);
    break;
    case 19:
      LED19(1);
    break;
    case 20:
      LED20(1);
    break;
    case 21:
      LED21(1);
    break;
    // R
    case 22:
      Branch0(0);
    break;
    case 23:
      Branch1(0);
    break;
    case 24:
      Branch2(0);
    break;
    case 25:
      Branch3(0);
    break;
    case 26:
      Branch4(0);
    break;
    case 27:
      Branch5(0);
    break;
    case 28:
      Branch6(0);
    break;
    case 29:
      Branch7(0);
    break;
    case 30:
      Branch8(0);
    break;
    case 31:
      Branch9(0);
    break;
    case 32:
      Branch10(0);
    break;
    // G
    case 33:
      Branch0(1);
      break;
    case 34:
      Branch1(1);  
      break;
    case 35:
      Branch2(1);  
    break;
    case 36:
      Branch3(1);  
    break; 
    case 37:
      Branch4(1);  
    break; 
    case 38:
      Branch5(1);  
    break; 
    case 39:
      Branch6(1);  
    break; 
    case 40:
      Branch7(1);  
    break; 
    case 41:
      Branch8(1);  
    break; 
    case 42:
      Branch9(1);  
    break; 
    case 43:
      Branch10(1);  
    break; 
    // B
    case 44:
      Branch0(2);  
    break; 
    case 45:
      Branch1(2);  
    break; 
    case 46:
      Branch2(2);  
    break; 
    case 47:
      Branch3(2);  
    break; 
    case 48:
      Branch4(2);  
    break; 
    case 49:
      Branch5(2);  
    break; 
    case 50:
      Branch6(2);  
    break; 
    case 51:
      Branch7(2);  
    break; 
    case 52:
      Branch8(2);  
    break; 
    case 53:
      Branch9(2);  
    break; 
    case 54:
      Branch10(2);  
    break; 
    // Other Color change - add later
    
    // Turn off - (-1~-22 : LED off ; -23 ~ -33 : Branch off)
    case -1:
      LED0(0);
    break;
    case -2:
      LED1(0);
    break;
    case -3:
      LED2(0);
    break;
    case -4:
      LED3(0);
    break;
    case -5:
      LED4(0);
    break;
    case -6:
      LED5(0);
    break;
    case -7:
      LED6(0);
    break;
    case -8:
      LED7(0);
    break;
    case -9:
      LED8(0);
    break;
    case -10:
      LED9(0);
    break;
    case -11:
      LED10(0);
    break;
    case -12:
      LED11(0);
    break;
    case -13:
      LED12(0);
    break;
    case -14:
      LED13(0);
    break;
    case -15:
      LED14(0);
    break;
    case -16:
      LED15(0);
    break;
    case -17:
      LED16(0);
    break;
    case -18:
      LED17(0);
    break;
    case -19:
      LED18(0);
    break;
    case -20:
      LED19(0);
    break;
    case -21:
      LED20(0);
    break;
    case -22:
      LED21(0);
    break;
    // Branch
    case -23:
      Branch0(6);
    break;
    case -24:
      Branch1(6);
    break;
    case -25:
      Branch2(6);
    break;
    case -26:
      Branch3(6);
    break;
    case -27:
      Branch4(6);
    break;
    case -28:
      Branch5(6);
    break;
    case -29:
      Branch6(6);
    break;
    case -30:
      Branch7(6);
    break;
    case -31:
      Branch8(6);
    break;
    case -32:
      Branch9(6);
    break;
    case -33:
      Branch10(6);
    break;
  }
}

/*LED light*/
void LED0(int mode){
  // set local_signal
  local_signal[1] |= BIT7;
  if(mode == 0){
    local_signal[1] &= ~BIT7;
  }
}
void LED1(int mode){
  // set local_signal
  local_signal[1] |= BIT6;
  if(mode == 0){
    local_signal[1] &= ~BIT6;
  }
}
void LED2(int mode){
  // set local_signal
  local_signal[1] |= BIT5;
  if(mode == 0){
    local_signal[1] &= ~BIT5;
  }
}
void LED3(int mode){
  // set local_signal
  local_signal[1] |= BIT4;
  if(mode == 0){
    local_signal[1] &= ~BIT4;
  }
}
void LED4(int mode){
  // set local_signal
  local_signal[1] |= BIT3;
  if(mode == 0){
    local_signal[1] &= ~BIT3;
  }
}
void LED5(int mode){
  // set local_signal
  local_signal[1] |= BIT2;
  if(mode == 0){
    local_signal[1] &= ~BIT2;
  }
}
void LED6(int mode){
  // set local_signal
  local_signal[1] |= BIT1;
  if(mode == 0){
    local_signal[1] &= ~BIT1;
  }
}
void LED7(int mode){
  // set local_signal
  local_signal[1] |= BIT0;
  if(mode == 0){
    local_signal[1] &= ~BIT0;
  }
}
void LED8(int mode){
  // set local_signal
  local_signal[2] |= BIT7;
  if(mode == 0){
    local_signal[2] &= ~BIT7;
  }
}
void LED9(int mode){
  // set local_signal
  local_signal[2] |= BIT6;
  if(mode == 0){
    local_signal[2] &= ~BIT6;
  }
}
void LED10(int mode){
  // set local_signal
  local_signal[2] |= BIT5;
  if(mode == 0){
    local_signal[2] &= ~BIT5;
  }
}
void LED11(int mode){
  // set local_signal
  local_signal[2] |= BIT4;
  if(mode == 0){
    local_signal[2] &= ~BIT4;
  }
}
void LED12(int mode){
  // set local_signal
  local_signal[2] |= BIT3;
  if(mode == 0){
    local_signal[2] &= ~BIT3;
  }
}
void LED13(int mode){
  // set local_signal
  local_signal[2] |= BIT2;
  if(mode == 0){
    local_signal[2] &= ~BIT2;
  }
}
void LED14(int mode){
  // set local_signal
  local_signal[2] |= BIT1;
  if(mode == 0){
    local_signal[2] &= ~BIT1;
  }
}
void LED15(int mode){
  // set local_signal
  local_signal[2] |= BIT0;
  if(mode == 0){
    local_signal[2] &= ~BIT0;
  }
}
void LED16(int mode){
  // set local_signal
  local_signal[3] |= BIT7;
  if(mode == 0){
    local_signal[3] &= ~BIT7;
  }
}
void LED17(int mode){
  // set local_signal
  local_signal[3] |= BIT6;
  if(mode == 0){
    local_signal[3] &= ~BIT6;
  }
}
void LED18(int mode){
  // set local_signal
  local_signal[3] |= BIT5;
  if(mode == 0){
    local_signal[3] &= ~BIT5;
  }
}
void LED19(int mode){
  // set local_signal
  local_signal[3] |= BIT4;
  if(mode == 0){
    local_signal[3] &= ~BIT4;
  }
}
void LED20(int mode){
  // set local_signal
  local_signal[3] |= BIT3;
  if(mode == 0){
    local_signal[3] &= ~BIT3;
  }
}
void LED21(int mode){
  // set local_signal
  local_signal[3] |= BIT2;
  if(mode == 0){
    local_signal[3] &= ~BIT2;
  }
}
/* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
void Branch0(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[3] |= BIT1;
    break;
  case 1:
    local_signal[5] |= BIT6;
    break;
  case 2:
    local_signal[6] |= BIT3;
    break;
  case 3:
    local_signal[3] |= BIT1;
    local_signal[5] |= BIT6;
    break;
  case 4:
    local_signal[3] |= BIT1;
    local_signal[6] |= BIT3;
    break;
  case 5:
    local_signal[5] |= BIT6;
    local_signal[6] |= BIT3;
    break;
  case 6:
    local_signal[3] &= ~BIT1;
    local_signal[5] &= ~BIT6;
    local_signal[6] &= ~BIT3;
    break;
  }  
}
void Branch1(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[3] |= BIT0;
    break;
  case 1:
    local_signal[5] |= BIT5;
    break;
  case 2:
    local_signal[6] |= BIT2;
    break;
  case 3:
    local_signal[3] |= BIT0;
    local_signal[5] |= BIT5;
    break;
  case 4:
    local_signal[3] |= BIT0;
    local_signal[6] |= BIT2;
    break;
  case 5:
    local_signal[5] |= BIT5;
    local_signal[6] |= BIT2;
    break;
  case 6:
    local_signal[3] &= ~BIT0;
    local_signal[5] &= ~BIT5;
    local_signal[6] &= ~BIT2;
    break;
  }
}
void Branch2(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[4] |= BIT7;
    break;
  case 1:
    local_signal[5] |= BIT4;
    break;
  case 2:
    local_signal[6] |= BIT1;
    break;
  case 3:
    local_signal[4] |= BIT7;
    local_signal[5] |= BIT4;
    break;
  case 4:
    local_signal[4] |= BIT7;
    local_signal[6] |= BIT1;
    break;
  case 5:
    local_signal[5] |= BIT4;
    local_signal[6] |= BIT1;
    break;
  case 6:
    local_signal[4] &= ~BIT7;
    local_signal[5] &= ~BIT4;
    local_signal[6] &= ~BIT1;
    break;
  }
}
void Branch3(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[4] |= BIT6;
    break;
  case 1:
    local_signal[5] |= BIT3;
    break;
  case 2:
    local_signal[6] |= BIT0;
    break;
  case 3:
    local_signal[4] |= BIT6;
    local_signal[5] |= BIT3;
    break;
  case 4:
    local_signal[4] |= BIT6;
    local_signal[6] |= BIT0;
    break;
  case 5:
    local_signal[5] |= BIT3;
    local_signal[6] |= BIT0;
    break;
  case 6:
    local_signal[4] &= ~BIT6;
    local_signal[5] &= ~BIT3;
    local_signal[6] &= ~BIT0;
    break;
  }
}
void Branch4(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[4] |= BIT5;
    break;
  case 1:
    local_signal[5] |= BIT2;
    break;
  case 2:
    local_signal[7] |= BIT7;
    break;
  case 3:
    local_signal[4] |= BIT5;
    local_signal[5] |= BIT2;
    break;
  case 4:
    local_signal[4] |= BIT5;
    local_signal[7] |= BIT7;
    break;
  case 5:
    local_signal[5] |= BIT2;
    local_signal[7] |= BIT7;
    break;
  case 6:
    local_signal[4] &= ~BIT5;
    local_signal[5] &= ~BIT2;
    local_signal[7] &= ~BIT7;
    break;
  }
}
void Branch5(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[4] |= BIT4;
    break;
  case 1:
    local_signal[5] |= BIT1;
    break;
  case 2:
    local_signal[7] |= BIT6;
    break;
  case 3:
    local_signal[4] |= BIT4;
    local_signal[5] |= BIT1;
    break;
  case 4:
    local_signal[4] |= BIT4;
    local_signal[7] |= BIT6;
    break;
  case 5:
    local_signal[5] |= BIT1;
    local_signal[7] |= BIT6;
    break;
  case 6:
    local_signal[4] &= ~BIT4;
    local_signal[5] &= ~BIT1;
    local_signal[7] &= ~BIT6;
    break;
  }
}
void Branch6(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[4] |= BIT3;
    break;
  case 1:
    local_signal[5] |= BIT0;
    break;
  case 2:
    local_signal[7] |= BIT5;
    break;
  case 3:
    local_signal[4] |= BIT3;
    local_signal[5] |= BIT0;
    break;
  case 4:
    local_signal[4] |= BIT3;
    local_signal[7] |= BIT5;
    break;
  case 5:
    local_signal[5] |= BIT0;
    local_signal[7] |= BIT5;
    break;
  case 6:
    local_signal[4] &= ~BIT3;
    local_signal[5] &= ~BIT0;
    local_signal[7] &= ~BIT5;
    break;
  }
}
void Branch7(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[4] |= BIT2;
    break;
  case 1:
    local_signal[6] |= BIT7;
    break;
  case 2:
    local_signal[7] |= BIT4;
    break;
  case 3:
    local_signal[4] |= BIT2;
    local_signal[6] |= BIT7;
    break;
  case 4:
    local_signal[4] |= BIT2;
    local_signal[7] |= BIT4;
    break;
  case 5:
    local_signal[6] |= BIT7;
    local_signal[7] |= BIT4;
    break;
  case 6:
    local_signal[4] &= ~BIT2;
    local_signal[6] &= ~BIT7;
    local_signal[7] &= ~BIT4;
    break;
  }
}
void Branch8(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[4] |= BIT1;
    break;
  case 1:
    local_signal[6] |= BIT6;
    break;
  case 2:
    local_signal[7] |= BIT3;
    break;
  case 3:
    local_signal[4] |= BIT1;
    local_signal[6] |= BIT6;
    break;
  case 4:
    local_signal[4] |= BIT1;
    local_signal[7] |= BIT3;
    break;
  case 5:
    local_signal[6] |= BIT6;
    local_signal[7] |= BIT3;
    break;
  case 6:
    local_signal[4] &= ~BIT1;
    local_signal[6] &= ~BIT6;
    local_signal[7] &= ~BIT3;
    break;
  }
}
void Branch9(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[4] |= BIT0;
    break;
  case 1:
    local_signal[6] |= BIT5;
    break;
  case 2:
    local_signal[7] |= BIT2;
    break;
  case 3:
    local_signal[4] |= BIT0;
    local_signal[6] |= BIT5;
    break;
  case 4:
    local_signal[4] |= BIT0;
    local_signal[7] |= BIT2;
    break;
  case 5:
    local_signal[6] |= BIT5;
    local_signal[7] |= BIT2;
    break;
  case 6:
    local_signal[4] &= ~BIT0;
    local_signal[6] &= ~BIT5;
    local_signal[7] &= ~BIT2;
    break;
  }
}
void Branch10(int color){
  /* Branch color : 0 -> red , 1 -> green , 2 -> blue , 3 -> r+g , 4 -> r+b , 5 -> g+b */
  switch(color){
  case 0:
    local_signal[5] |= BIT7;
    break;
  case 1:
    local_signal[6] |= BIT4;
    break;
  case 2:
    local_signal[7] |= BIT1;
    break;
  case 3:
    local_signal[5] |= BIT7;
    local_signal[6] |= BIT4;
    break;
  case 4:
    local_signal[5] |= BIT7;
    local_signal[7] |= BIT1;
    break;
  case 5:
    local_signal[6] |= BIT4;
    local_signal[7] |= BIT1;
    break;
  case 6:
    local_signal[5] &= ~BIT7;
    local_signal[6] &= ~BIT4;
    local_signal[7] &= ~BIT1;
    break;
  }
}