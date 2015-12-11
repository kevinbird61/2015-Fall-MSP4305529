
#include "io430.h"
#define DELAY 30000
/*
Direction : Pin x.x y.y ( Left or up -> x.x Right or down -> y.y )
*/
void Top_both();
void Top_left();
void Top_right();

void Left_both();
void Left_up();
void Left_down();

void Right_both();
void Right_up();
void Right_down();

void Down_both();
void Down_left();
void Down_right();

void cent_h_both();
void cent_h_left();
void cent_h_right();

void cent_v_both();
void cent_v_up();
void cent_v_down();

void curv_right_both();
void curv_right_up();
void curv_right_down();

void curv_left_both();
void curv_left_up();
void curv_left_down();

void H();
void A();
void P();
void Y();
void B();
void I();
void R();
void T();
void D();
void J();
void _V();
void _N();
// Clear
void Clear();

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  H();
  unsigned long i = 30000;
  while(i){i--;}
  A();
  i = 30000;
  while(i){i--;}
  P();
  i = 30000;
  while(i){i--;}
  P();
  i = 30000;
  while(i){i--;}
  Y();
  i = 300000;
  while(i){i--;}
  
  B();
  i = 30000;
  while(i){i--;}
  I();
  i = 30000;
  while(i){i--;}
  R();
  i = 30000;
  while(i){i--;}
  T();
  i = 30000;
  while(i){i--;}
  H();
  i = 30000;
  while(i){i--;}
  D();
  i = 30000;
  while(i){i--;}
  A();
  i = 30000;
  while(i){i--;}
  Y();
  i = 300000;
  while(i){i--;}
  
  // Jarvan
  J();
  i = 30000;
  while(i){i--;}
  A();
  i = 30000;
  while(i){i--;}
  R();
  i = 30000;
  while(i){i--;}
  _V();
  i = 30000;
  while(i){i--;}
  A();
  i = 30000;
  while(i){i--;}
  _N();
  i = 30000;
  while(i){i--;}
  
  
  while(1);
}

void H(){
  unsigned long i = DELAY;
  while(i){
    Left_both();
    Right_both();
    cent_h_both();
    i--;
  }
  Clear();
}
void A(){
  unsigned long i = DELAY;
  while(i){
    Left_both();
    Right_both();
    cent_h_both();
    Top_both();
    i--;
  }
  Clear();
}
void P(){
  unsigned long i = DELAY;
  while(i){
    Left_both();
    Right_up();
    cent_h_both();
    Top_both();
    i--;
  }
  Clear();
}
void Y(){
  unsigned long i = DELAY;
  while(i){
    Left_up();
    Right_up();
    cent_h_both();
    cent_v_down();
    i--;
  }
  Clear();
}
void B(){
  unsigned long i = DELAY;
  while(i){
    Left_both();
    Right_both();
    cent_h_both();
    Top_both();
    Down_both();
    i--;
  }
  Clear();
}
void I(){
  unsigned long i = DELAY;
  while(i){
    Top_both();
    Down_both();
    cent_v_both();
    i--;
  }
  Clear();
}
void R(){
  unsigned long i = DELAY;
  while(i){
    Left_both();
    Top_both();
    Right_up();
    cent_h_both();
    cent_v_down();
    Down_right();
    i--;
  }
  Clear();
}
void T(){
  unsigned long i = DELAY;
  while(i+10000){
    Top_both();
    cent_v_both();
    i--;
  }
  Clear();
}
void D(){
  unsigned long i = DELAY;
  while(i){
    Left_both();
    Top_left();
    curv_right_both();
    Down_left();
    i--;
  }
  Clear();
}
void J(){
  unsigned long i = DELAY;
  while(i+10000){
    Top_both();
    cent_v_both();
    Down_left();
    Left_down();
    i--;
  }
  Clear();
}
void _V(){
  unsigned long i = DELAY;
  while(i+10000){
    Right_up();
    Left_up();
    curv_left_down();
    curv_right_down();
    i--;
  }
  Clear();
}

void _N(){
  unsigned long i = DELAY;
  while(i){
    Right_both();
    curv_left_up();
    cent_h_left();
    cent_v_down();
    curv_right_down();
    Left_both();
    i--;
  }
  Clear();
}

void Top_both(){
  P2DIR = BIT6;
  P7DIR = BIT4;
  
  P2OUT = BIT6;
  P7OUT = 0x0;
  P7OUT = BIT4;
  P2OUT = 0x0;
}

void Top_left(){
  P2DIR = BIT6;
  P7DIR = BIT4;
  
  P2OUT = BIT6;
  P7OUT = 0x0;
}
void Top_right(){
  P2DIR = BIT6;
  P7DIR = BIT4;
  
  P7OUT = BIT4;
  P2OUT = 0x0;
}

void Left_both(){
  P2DIR = BIT0 | BIT2 ; 
  P2OUT = BIT0;
  P2OUT = BIT2;
}
void Left_up(){
  P2DIR = BIT0 | BIT2 ; 
  P2OUT = BIT0;
}
void Left_down(){
  P2DIR = BIT0 | BIT2 ; 
  P2OUT = BIT2;
}

void Right_both(){
  P2DIR = BIT3 ;
  P8DIR = BIT1 ;
  
  P2OUT = BIT3;
  P2OUT = 0x0;
  P8OUT = BIT1 ; 
  P8OUT = 0x0;
}
void Right_up(){
  P2DIR = BIT3 ;
  P8DIR = BIT1 ;
  
  P8OUT = 0x0;
  P2OUT = BIT3;
}
void Right_down();

void Down_both(){
  P2DIR = BIT7;
  P1DIR = BIT6;
  
  P2OUT = BIT7;
  P1OUT = 0x0;
  P1OUT = BIT6;
  P2OUT = 0x0;
}
void Down_left(){
  P2DIR = BIT7;
  P1DIR = BIT6;
  
  P1OUT = BIT6;
  P2OUT = 0x0;
}
void Down_right(){
  P2DIR = BIT7;
  P1DIR = BIT6;
  
  P2OUT = BIT7;
  P1OUT = 0x0;
}

void cent_h_both(){
  P1DIR = BIT3 | BIT2;
  
  P1OUT = BIT3;
  P1OUT = BIT2;
}
void cent_h_left(){
  P1DIR = BIT3 | BIT2;
  P1OUT = BIT2;
}
void cent_h_right(){
  P1DIR = BIT3 | BIT2;
  P1OUT = BIT3;
}

void cent_v_both(){
  P1DIR = BIT4 | BIT5;
  P1OUT = BIT5;
  P1OUT = BIT4;
}
void cent_v_up(){
  P1DIR = BIT4 | BIT5;
  P1OUT = BIT4;
}
void cent_v_down(){
  P1DIR = BIT4 | BIT5;
  P1OUT = BIT5;
}

void curv_right_both(){
    P4DIR = BIT0 | BIT3;
    P4OUT = BIT0;
    P4OUT = BIT3;
}

void curv_right_up(){
  P4DIR = BIT0 | BIT3;
  P4OUT = BIT0;
}
void curv_right_down(){
  P4DIR = BIT0 | BIT3;
  P4OUT = BIT3;
}

void curv_left_both(){
  P2DIR = BIT4 | BIT5;
  P2OUT = BIT4;
  P2OUT = BIT5;  
}
void curv_left_up(){
  P2DIR = BIT4 | BIT5;
  P2OUT = BIT4;
}
void curv_left_down(){
  P2DIR = BIT4 | BIT5;
  P2OUT = BIT5;
}

void Clear(){
    P2OUT = 0x0 ;
    P1OUT = 0x0 ;
    P4OUT = 0x0 ;
    P8OUT = 0x0 ;
    P7OUT = 0x0 ;
}