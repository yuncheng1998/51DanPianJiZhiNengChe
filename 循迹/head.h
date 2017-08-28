#ifndef _LED_H_
#define _LED_H_

#define Left_1_led P3_7  //循迹模块
#define Right_1_led P3_6

#define Left_moto_pwm     P1_6   //PWM信号端
#define Right_moto_pwm    P1_7

#define Left_moto_go      {P1_2=1,P1_3=0;}  //左电机向前走
#define Left_moto_back    {P1_2=0,P1_3=1;}  //向后转
#define Left_moto_Stop    {P1_2=0,P1_3=0;}  //停转
#define Right_moto_go     {P1_4=1,P1_5=0;}  //右边电机向前走
#define Right_moto_back   {P1_4=0,P1_5=1;}  //向后走
#define Right_moto_Stop   {P1_4=0,P1_5=0;}  //停转

unsigned char Left_Speed = 0; //规定速度
unsigned char Right_Speed = 0;
unsigned char push_val_left =0;// PWM调速，速度循环
unsigned char push_val_right=0;// 右电机占空比N/20
unsigned int time=0;   //PWM时间循环
bit Left_stop = 1;
bit Right_stop = 1;

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
        for(i = 0; i < k; i++) {
                for(j = 0; j < 200; j++) ;
                for(j = 0; j < 102; j++) ;
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
        Left_Speed = 12;
        Right_Speed = 15;
        Left_moto_back;
        Right_moto_go;
}
void turnRight(){
        Right_Speed = 12;
        Left_Speed = 15;
        Right_moto_back;
        Left_moto_go;
}
void stop(){
        Right_moto_Stop;
        Left_moto_Stop;
}

void pwm_out_left_moto(){
        if(Left_stop) {
                if(Left_Speed<=push_val_left) {
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
        if(Right_stop) {
                if(Right_Speed<=push_val_right) {
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
void timer0() interrupt 1   using 2 {
        TH0=0XFc; //1Ms定时
        TL0=0X18;
        time++;
        Left_Speed++;
        Right_Speed++;
        pwm_out_left_moto();
        pwm_out_right_moto();
}
