#ifndef _LED_H_
#define _LED_H_

#define Left_1_led P3_7  //循迹模块
#define Right_1_led P3_6

#define Left_moto_go      {P1_2=1,P1_3=0;}  //左电机向前走
#define Left_moto_back    {P1_2=0,P1_3=1;} 	//向后转
#define Left_moto_Stop    {P1_2=0,P1_3=0;}  //停转
#define Right_moto_go     {P1_4=1,P1_5=0;}	//右边电机向前走
#define Right_moto_back   {P1_4=0,P1_5=1;}	//向后走
#define Right_moto_Stop   {P1_4=0,P1_5=0;}  //停转

unsigned char Left_Speed = 0; //速度调节
unsigned char Right_Speed = 0;

sbit IN1 = P1^2; //L289N驱动的定义
sbit IN2 = P1^3;
sbit IN3 = P1^4;
sbit IN4 = P1^5;
sbit EN1 = P1^6;
sbit EN2 = P1^7;

sbit BUZZ = P2^3;//蜂鸣器

void delay(unsigned int k){//延时k ms
  unsigned int i;
  unsigned char j;
  for(i = 0;i < k; i++){
    for(j = 0;j < 200; j++);
    for(j = 0;j < 102; j++);
  }
}
void frontRun() {
  Left_Speed = 12;
  Left_Speed = 12;
  Left_moto_go;
  Right_moto_go;
}
void backRun(){
  Left_Speed = 12;
  Left_Speed = 12;
  Left_moto_back;
  Right_moto_back;
}
void turnLeft(){  //左拐 右前左后
  Left_Speed = 5;
  Right_Speed = 15;
  Left_moto_back;
  Right_moto_go;
}
void turnRight(){
  Right_Speed = 5;
  Left_Speed = 15;
  Right_moto_back;
  Left_moto_go;
}
void stop(){
  Right_moto_Stop;
  Left_moto_Stop;
}
