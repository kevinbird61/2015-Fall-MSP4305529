
#include "io430.h"
#include "intrinsics.h"

#define unit 16
#define dot unit
#define dash unit*3
#define part_space unit
#define letter_space unit*3
#define word_space unit*7

/* decode mode :
0000 - 0000
dash,dot,dash,dot - dash,dot,dash,dot
*/
int filter = 1;
int string_index = 0;
int index = 0;
int count = 0;
char change = 0;
int leng = 0;
char progress_line[5] = {0,0,0,0,0};
int progress_line_len[5] = {0,0,0,0,0};
int progress_line_index = 0;

static unsigned char table[26] = 
{
  0x60,0xD4,0xF0,0xD0,0x40,
  0x5C,0xB0,0x55,0x50,0x6A,
  0xE0,0x74,0xA0,0xC0,0xA8,
  0x6C,0xB8,0x70,0x54,0x80,
  0x58,0x56,0x68,0xD8,0xE8,
  0xB4
};
static unsigned int len_table[26] = 
{
  2,4,4,3,1,
  4,3,4,2,4,
  3,4,2,2,3,
  4,4,3,3,1,
  3,4,3,4,4,
  4
};
int compare[8] = {128,64,32,16,8,4,2,1};

void setChar(char ch){
  switch(ch){
  case 'A':
    // 0110-0000
    change = table[0];
    leng = len_table[0];
    break;
  case 'B':
    // 1101 - 0100
    change = table[1];
    leng = len_table[1];
    break;
  case 'C':
    // 1111 - 0000
    change = table[2];
    leng = len_table[2];
    break;
  case 'D':
    // 1101 - 0000
    change = table[3];
    leng = len_table[3];
    break;
  case 'E':
    // 0100 - 0000
    change = table[4];
    leng = len_table[4];
    break;
  case 'F':
    // 0101 - 1100
    change = table[5];
    leng = len_table[5];
    break;
  case 'G':
    // 1011 - 0000
    change = table[6];
    leng = len_table[6];
    break;
  case 'H':
    // 0101 - 0101
    change = table[7];
    leng = len_table[7];
    break;
  case 'I':
    // 0101 - 0000
    change = table[8];
    leng = len_table[8];
    break;
  case 'J':
    // 0110 - 1010
    change = table[9];
    leng = len_table[9];
    break;
  case 'K':
    // 1110 - 0000
    change = table[10];
    leng = len_table[10];
    break;
  case 'L':
    // 0111 - 0100
    change = table[11];
    leng = len_table[11];
    break;
  case 'M':
    // 1010 - 0000
    change = table[12];
    leng = len_table[12];
    break;
  case 'N':
    // 1100 - 0000
    change = table[13];
    leng = len_table[13];
    break;  
  case 'O':
    // 1010 - 1000
    change = table[14];
    leng = len_table[14];
    break;
  case 'P':
    // 0110 - 1100
    change = table[15];
    leng = len_table[15];
    break;
  case 'Q':
    // 1011 - 1000
    change = table[16];
    leng = len_table[16];
    break;
  case 'R':
    // 0111 - 0000
    change = table[17];
    leng = len_table[17];
    break;
  case 'S':
    // 0101 - 0100
    change = table[18];
    leng = len_table[18];
    break;
  case 'T':
    // 1000 - 0000
    change = table[19];
    leng = len_table[19];
    break;
  case 'U':
    // 0101 - 1000
    change = table[20];
    leng = len_table[20];
    break;
  case 'V':
    // 0101 - 0110
    change = table[21];
    leng = len_table[21];
    break;
  case 'W':
    // 0110 - 1000
    change = table[22];
    leng = len_table[22];
    break;
  case 'X':
    // 1101 - 1000
    change = table[23];
    leng = len_table[23];
    break;
  case 'Y':
    // 1110 - 1000
    change = table[24];
    leng = len_table[24];
    break;
  case 'Z':
    // 1011 - 0100
    change = table[25];
    leng = len_table[25];
    break;
  }
  progress_line[progress_line_index] = change;
  progress_line_len[progress_line_index] = leng;
  progress_line_index++;
}
void setString(const char *str){
  // initialize timerB
  while(str[string_index]){
      setChar(str[string_index]);
      string_index++;
      filter = 0;
  }
  string_index = 0;
}


#pragma vector=TIMER0_B1_VECTOR
__interrupt void TIMER0_B1_ISR(){
  //int i = TBIV;
  switch(__even_in_range(TBIV,14)){
  case 0:
    break;
  case 2:
    break;
  case 4:
    break;
  case 6:
    break;
  case 8:
    break;
  case 10:
    break;
  case 12:
    break;
  case 14:
    // In TB
    // Turn on led
    // Judge what's bit it is
    if(progress_line[progress_line_index] & compare[index]){
      P4OUT |= BIT7;
      if(index%2 == 0){
        // even => dash
        TA0CTL |= TASSEL_1 + MC_1 + TACLR;
        TA0CCR0 = 3000;
        TA0CCTL0 = CCIE;
      }
      else{
        // odd => dot
        TA0CTL |= TASSEL_1 + MC_1 + TACLR;
        TA0CCR0 = 1000;
        TA0CCTL0 = CCIE;
      }
      count++;
    }
    else{
      // not compare
      P4OUT &= ~BIT7;
      TA0CTL |= TASSEL_1 + MC_1 + TACLR;
      TA0CCR0 = 1000;
      TA0CCTL0 = CCIE;
    }
    if(count == progress_line_len[progress_line_index]){
      count = 0;
      index = 0;
      progress_line_index++;
      //TA0CTL |= TASSEL_1 + MC_1 + TACLR;
      //TA0CCR0 = 5000;
      //TA0CCTL0 = CCIE;
      //printf("%c " ,);
    }
    if(progress_line_index == 5){
      // do not thing
    }
    index++;
    TBCTL &= ~TBIE;
    break;
  }
}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void){
  // turn on LED
  P4OUT &= ~BIT7;
  TBCTL |= TBIE;
  TA0CCTL0 = ~CCIE;
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW+WDTHOLD; // Stop watchdog timer
  P4DIR |= BIT7;
  P4OUT &= ~BIT7;
  UCSCTL5 |= DIVA_5; //ACLK = 32768/32 Hz
  TBCTL = CNTL_3|TBSSEL_1|ID_1|MC_2|TBCLR|TBIE|TBIFG;
  TBEX0 = TBIDEX_7;//TimerB 8-bit continuous mode, ACLK/8/8

  //setChar('B');

  setString("HELLO");
  progress_line_index = 0;
  __bis_SR_register(GIE|LPM3_bits); // CPU off, enable interrupts
  return 0;
}
