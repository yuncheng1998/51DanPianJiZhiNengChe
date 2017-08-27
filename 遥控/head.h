#include<intrins.h>
#ifndef _LED_H_
#define _LED_H_

#define Avoid_Left_led P3_4//红外避障
#define Avoid_Right_led P3_5

#define Find_Left_led P3_7  //循迹模块
#define Find_Right_led P3_6

#define Left_moto_pwm	  P1_6	 //PWM信号端
#define Right_moto_pwm	  P1_7

#define Left_moto_go      {P1_2=1,P1_3=0;}  //左电机向前走
#define Left_moto_back    {P1_2=0,P1_3=1;} 	//向后转
#define Left_moto_stop    {P1_2=0,P1_3=0;}  //停转
#define Right_moto_go     {P1_4=1,P1_5=0;}	//右边电机向前走
#define Right_moto_back   {P1_4=0,P1_5=1;}	//向后走
#define Right_moto_stop   {P1_4=0,P1_5=0;}  //停转


unsigned char Left_Speed = 0; //速度调节
unsigned char Right_Speed = 0;
unsigned char push_val_left =0;// 左电机占空比N/20
unsigned char push_val_right=0;// 右电机占空比N/20

bit Left_stop = 1;
bit Right_stop = 1;

unsigned char code ShowNumber[] = {0x03,0x9F,0x25,0x0D,0x99,0x49,0x41,0x1F,0x01,0x19};
// 0 到 9，加了code的数组是把这个数组保存到程序区，程序运行过程中是无法修改的
unsigned char code ShowDirect[] = {0x3B,0xC7,0xF1,0x9D,0x03};
unsigned  int  time=0;

sbit IN1 = P1^2; //L289N驱动的定义
sbit IN2 = P1^3;
sbit IN3 = P1^4;
sbit IN4 = P1^5;
sbit EN1 = P1^6;
sbit EN2 = P1^7;

sbit BUZZ = P2^3;//蜂鸣器
#define ShowPort P0//定义数码管显示端口

void delay(unsigned int k){//延时 k ms
  unsigned int i;
  unsigned char j;
  for(i = 0;i < k; i++){
    for(j = 0;j < 201; j++);
    for(j = 0;j < 101; j++);
  }
}
void micro_delay(unsigned int k){//延时 0.0k ms
  unsigned char i;
  for(i = 0; i < k-1; i++);
}
/*********/
void delayms(unsigned char k)                         //0.01mS延时程序
{
  unsigned char j = 1;
  unsigned char i;                                    //定义临时变量
  while(j--)                                          //延时时间循环
  {
    for (i = 0; i<k-1; i++) {}                         //14mS延时
  }
}
/*************/
void delay1ms(unsigned int i){  //  4ms
  unsigned char j,k;
  do{
    j = 10;
    do{
      k = 50;
      do{
        _nop_();
      }while(--k);
    }while(--j);
  }while(--i);
}
void frontRun() {
  push_val_left = 12;
  push_val_right = 12;
  Left_moto_go;
  Right_moto_go;
}
void backRun(){
  push_val_left = 12;
  push_val_right = 12;
  Left_moto_back;
  Right_moto_back;
}
void turnLeft(){  //左拐 右前左后
  push_val_left = 12;
  push_val_right = 12;
  Left_moto_back;
  Right_moto_go;
}
void turnRight(){
  push_val_left = 12;
  push_val_right = 12;
  Right_moto_back;
  Left_moto_go;
}
void stop(){
  Right_moto_stop;
  Left_moto_stop;
}

void pwm_out_left_moto(){
  if(Left_stop){
     if(Left_Speed<=push_val_left){
       Left_moto_pwm=1;
		 }
	   else{
	       Left_moto_pwm=0;
		 }
     if(Left_Speed>=20)
	   Left_Speed=0;
   }
   else{
     Left_moto_pwm=0;
	  }
}

   void pwm_out_right_moto(){
     if(Right_stop){
       if(Right_Speed<=push_val_right){
         Right_moto_pwm=1;
		   }
       else{
         Right_moto_pwm=0;
       }
       if(Right_Speed>=20)
         Right_Speed=0;
       }
       else{
         Right_moto_pwm=0;
	     }
     }

///*TIMER0中断服务子函数产生PWM信号*/
 	void timer0()interrupt 1   using 2{
   TH0=0XFc;	  //1Ms定时
	 TL0=0X18;
	 time++;
	 Left_Speed++;
	 Right_Speed++;
	 pwm_out_left_moto();
	 pwm_out_right_moto();
 }
#endif
