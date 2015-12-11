#include "stdio.h"
#include "io430.h"
int DFS(int level,int A[],int B[]);

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  // input a complete binary tree
  int A[7] = {15,10,20,8,12,16,25};
  int B[7] = {0,0,0,0,0,0,0};
  // calla for DFS
  DFS(3,A,B);
  int i;
  for(i=0;i<7;i++){
      printf("%d ",B[i]);
  }
  // Because the program will crash without infinite loop
  while(1){}

  return 0;
}
