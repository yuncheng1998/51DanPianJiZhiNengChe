#include <AT89X52.h>
#include <head.h>
void main() {
  unsigned char i;
  unsigned int a;
  Delay1ms(5);
  TMOD = TMOD|0x10;
  EA = 1;
  TH1 = 0;
  TL1 = 0;
  ET1 = 1;
  turn_right_flag = 0;
  B: for(i = 0; i < 50; i++){
    Delay1ms(1);
    if(P3_2 != 0)
    goto B;
  }
  BUZZ = 0;
  Delay1ms(50);
  BUZZ = 1;
  while (1) {
    RX = 1;
    StartModule();
    for(a = 951; a > 0; a--){
      if(RX == 1){
        Timer_Count();
      }
    }
  }

}
