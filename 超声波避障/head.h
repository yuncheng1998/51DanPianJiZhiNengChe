#include <AT89X52.h>
#include <intrins.h>

#define TX P2_1
#define RX P2_0

sbit L293D_IN1=P1^2;
sbit L293D_IN2=P1^3;
sbit L293D_IN3=P1^4;
sbit L293D_IN4=P1^5;
sbit L293D_EN1=P1^6;
sbit L293D_EN2=P1^7;

sbit BUZZ=P2^3;  //蜂鸣器

unsigned char disbuff[4]={0,0,0,0}; //距离

unsigned int time = 0;
unsigned long S = 0;
bit flag = 0;
bit turn_right_flag;

#define Left_moto_pwm	  P1_6	 //PWM信号端
#define Right_moto_pwm	  P1_7

/********   运动    ***********/
#define Left_moto_go      {P1_2=1,P1_3=0;}  //左电机向前走
#define Left_moto_back    {P1_2=0,P1_3=1;} 	//向后转
#define Left_moto_stop    {P1_2=0,P1_3=0;}  //停转
#define Right_moto_go     {P1_4=1,P1_5=0;}	//右边电机向前走
#define Right_moto_back   {P1_4=0,P1_5=1;}	//向后走
#define Right_moto_stop   {P1_4=0,P1_5=0;}  //停转

unsigned char push_val_left =0;// 左电机占空比N/20
unsigned char push_val_right=0;// 右电机占空比N/20
unsigned char Left_Speed = 0; //速度调节
unsigned char Right_Speed = 0;

bit Left_stop = 1;
bit Right_stop = 1;

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
/**********************************/

/*****   PWM   *********/

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
/****************************/

/****     延时          ***********/
void Delay1ms(unsigned int i){
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

void Delay10us(unsigned char i){ //10us延时
  unsigned char j;
  do{
    j = 10;
    do{
      _nop_();
    }while(--j);
  }while(--i);
}
/***************************/

/****** 计算距离 ***********/
void Count(void){
  time = TH1*256 + TL1;
  TH1 = 0;
  TL1 = 0;
  S = time*2;
  S = S*0.17;
  if(S <= 200){
    if(turn_right_flag != 1){
      stop();
      Delay1ms(5);    //保护程序
    }
    turn_right_flag = 1;
    P2_3 = 0;
    Delay1ms(50);
    P2_3 = 1;
    backRun();
    Delay1ms(300);
    turnLeft();
    Delay1ms(250);
  }
  else{
    turn_right_flag = 0;
    frontRun();
  }
  if((S >= 5000)||flag == 1){
    flag = 0;
  }
  else{
    disbuff[0] = S%10;
    disbuff[1] = S/10%10;
    disbuff[2] = S/100%10;
    disbuff[3] = S/1000;
  }
}
/****************************/

/****  T0中断测距   ***********/
void zd0() interrupt 3{
  flag = 1;
  RX = 0;
}
/********************/

/*******   计数测距启动  ********/
void Timer_Count(){
  TR1 = 1;
  while(RX);
  TR1 = 0;
  Count();
}
/****************************/

/*******  启动   ***********/
void StartModule(){
  TX = 1;
  Delay10us(2);
  TX = 0;
}
/**************************/

/*TIMER0中断服务子函数产生PWM信号*/
void timer0()interrupt 1 using 2{
  TH0=0XFc;	  //1Ms定时
	TL0=0X18;
	time++;
	Left_Speed++;
	Right_Speed++;
	pwm_out_left_moto();
	pwm_out_right_moto();
}
