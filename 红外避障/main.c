#include<AT89X52.H>
#include<head.h>

void main(){
  unsigned char i;
  P1 = 0x00;  //关电机
B:  for(i = 0; i <50; i++){  //判断按键是否按下
    delay(100);
    if(P3_2!=0)
    goto B;
  }
  BUZZ = 0;
  delay(1000);

  BUZZ = 1;

  TMOD=0X01;
  TH0= 0XFc;		  //1ms定时
	TL0= 0X18;
  TR0= 1;
  ET0= 1;
  EA = 1;		     //开总中断
  while (1) {
    /* 有信号为 0，没有信号为 1 */
    if(Avoid_Right_led == 1&&Avoid_Left_led == 1) frontRun();
    else if(Avoid_Right_led == 1&&Avoid_Left_led == 0) {
      turnRight();
      delay(1000);
    }
    else if(Avoid_Right_led == 0&&Avoid_Left_led == 1) {
      turnLeft();
      delay(1000);
    }
    else if(Avoid_Right_led == 0&&Avoid_Left_led == 0){
      backRun();
      delay(1000);
      turnRight();
      delay(2000);
    }
  }
}
