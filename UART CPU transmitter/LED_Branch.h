#include <msp430.h>

int local_signal[8] = {30,0,0,0,0,0,0,0};
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

void next_pattern(int select){
  // Enable using integer to control LED pattern
  switch(select){
    // 0~21 : LED on ; 22 ~ 32 : Branch-R ; 33 ~ 43 : Branch-G ; 44 ~ 54 : Branch-B ; 54 ~ ? Special Color
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
    case 55:
       // LED1 Turn all on
      LED0(1);
      LED1(1);
      LED2(1);
      LED3(1);
      LED4(1);
      LED5(1);
      LED6(1);
      LED7(1);
      LED8(1);
      LED9(1);
      LED10(1);
    break;
    case 56:
      // LED2 Turn all on
      LED11(1);
      LED12(1);
      LED13(1);
      LED14(1);
      LED15(1);
      LED16(1);
      LED17(1);
      LED18(1);
      LED19(1);
      LED20(1);
      LED21(1);
      break;
    case 57:
      // All Branch Turn Red
      Branch0(0);
      Branch1(0);
      Branch2(0);
      Branch3(0);
      Branch4(0);
      Branch5(0);
      Branch6(0);
      Branch7(0);
      Branch8(0);
      Branch9(0);
      Branch10(0);
      break;
    case 58:
      // All Branch Turn Green
      Branch0(1);
      Branch1(1);
      Branch2(1);
      Branch3(1);
      Branch4(1);
      Branch5(1);
      Branch6(1);
      Branch7(1);
      Branch8(1);
      Branch9(1);
      Branch10(1);
      break;
    case 59:
      // All Branch Turn Blue
      Branch0(2);
      Branch1(2);
      Branch2(2);
      Branch3(2);
      Branch4(2);
      Branch5(2);
      Branch6(2);
      Branch7(2);
      Branch8(2);
      Branch9(2);
      Branch10(2);
      break;
    // flash on
    case 60:
      // Special pattern - flash 1
      LED0(1);
      LED1(1);
      LED4(1);
      LED11(1);
      LED12(1);
      Branch0(2);
      Branch1(2);
      break;
    case 61:
      // flash 2
      LED0(1);
      LED1(1);
      LED5(1);
      LED13(1);
      Branch2(2);
      break;
    case 62:
      // flash 3
      LED0(1);
      LED2(1);
      LED6(1);
      LED14(1);
      Branch3(2);
      break;
    case 63:
      // flash 4
      LED0(1);
      LED2(1);
      LED7(1);
      LED15(1);
      LED16(1);
      LED17(1);
      Branch4(2);
      Branch5(2);
      Branch6(2);
      break;
    case 64:
      // flash 5
      LED0(1);
      LED2(1);
      LED8(1);
      LED18(1);
      Branch7(2);
      break;
    case 65:
      // flash 6
      LED0(1);
      LED3(1);
      LED9(1);
      LED19(1);
      Branch8(2);
      break;
    case 66:
      // flash 7
      LED0(1);
      LED3(1);
      LED10(1);
      LED20(1);
      LED21(1);
      Branch9(2);
      Branch10(2);
      break;
    case 70:
      // turn off all
      LED0(0);
      LED1(0);
      LED2(0);
      LED3(0);
      LED4(0);
      LED5(0);
      LED6(0);
      LED7(0);
      LED8(0);
      LED9(0);
      LED10(0);
      LED11(0);
      LED12(0);
      LED13(0);
      LED14(0);
      LED15(0);
      LED16(0);
      LED17(0);
      LED18(0);
      LED19(0);
      LED20(0);
      LED21(0);
      Branch0(6);
      Branch1(6);
      Branch2(6);
      Branch3(6);
      Branch4(6);
      Branch5(6);
      Branch6(6);
      Branch7(6);
      Branch8(6);
      Branch9(6);
      Branch10(6);
    case 71:
      Branch0(6);
      Branch1(6);
      Branch2(6);
      Branch3(6);
      Branch4(6);
      Branch5(6);
      Branch6(6);
      Branch7(6);
      Branch8(6);
      Branch9(6);
      Branch10(6);
      break;
    // Turn off - (-1~-22 : LED off ; -23 ~ -33 : Branch off)
    case 80:  
      // second layer
      LED1(1);
      LED2(1);
      LED3(1);
      break;
    case 81:
      // third layer
      LED4(1);
      LED5(1);
      LED6(1);
      LED7(1);
      LED8(1);
      LED9(1);
      LED10(1);
      break;
    case 82:
      // last layer
      LED11(1);
      LED12(1);
      LED13(1);
      LED14(1);
      LED15(1);
      LED16(1);
      LED17(1);
      LED18(1);
      LED19(1);
      LED20(1);
      LED21(1);
      break;
    
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
    // flash off 
    case -60:
      // Special pattern - flash 1
      LED0(0);
      LED1(0);
      LED4(0);
      LED11(0);
      LED12(0);
      Branch0(6);
      Branch1(6);
      break;
    case -61:
      // flash 2
      LED0(0);
      LED1(0);
      LED5(0);
      LED13(0);
      Branch2(6);
      break;
    case -62:
      // flash 3
      LED0(0);
      LED2(0);
      LED6(0);
      LED14(0);
      Branch3(6);
      break;
    case -63:
      // flash 4
      LED0(0);
      LED2(0);
      LED7(0);
      LED15(0);
      LED16(0);
      LED17(0);
      Branch4(6);
      Branch5(6);
      Branch6(6);
      break;
    case -64:
      // flash 5
      LED0(0);
      LED2(0);
      LED8(0);
      LED18(0);
      Branch7(6);
      break;
    case -65:
      // flash 6
      LED0(0);
      LED3(0);
      LED9(0);
      LED19(0);
      Branch8(6);
      break;
    case -66:
      // flash 7
      LED0(0);
      LED3(0);
      LED10(0);
      LED20(0);
      LED21(0);
      Branch9(6);
      Branch10(6);
      break;
    case -80:  
      // second layer
      LED1(0);
      LED2(0);
      LED3(0);
      break;
    case -81:
      // third layer
      LED4(0);
      LED5(0);
      LED6(0);
      LED7(0);
      LED8(0);
      LED9(0);
      LED10(0);
      break;
    case -82:
      // last layer
      LED11(0);
      LED12(0);
      LED13(0);
      LED14(0);
      LED15(0);
      LED16(0);
      LED17(0);
      LED18(0);
      LED19(0);
      LED20(0);
      LED21(0);
      break;
  }
}