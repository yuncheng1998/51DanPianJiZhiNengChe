#include<AT89X52.H>
#include<intrins.h>
#include<head.h>

unsigned char RunFlag=0;
bit EnableLight=0;

sbit S1=P3^2; //按键
sbit LeftLed=P2^0;

/*************完成红外探头端口定义***********/
sbit M1A = P1^2;                                        //定义电机1正向端口
sbit M1B = P1^3;                                        //定义电机1反向端口
sbit M2A = P1^6;                                        //定义电机2正向端口
sbit M2B = P1^7;                                        //定义电机2反向端口

sbit IRIN=P3^3;//红外接收端口
#define ShowPort P0//定义数码管显示端口

unsigned char code  RecvData[]={0x19,0x46,0x15,0x44,0x43,0x40,0x0D,0x0E,0x00,0x0F};

unsigned char IRCOM[7];

void Delay(){   //定义延时子程序
  unsigned int DelayTime=30000;  //定义延时时间变量
  while(DelayTime--);  //开始进行延时循环
  return; //子程序返回
}

extern void ControlCar(unsigned char ConType){
  stop();
  switch (ConType) {
    case 1: //前进
      stop();
      delay1ms(240);
      LeftLed = 0;
      frontRun();
      ShowPort = ShowDirect[0];
      break;
    case 2:
      stop();
      delay1ms(240);
      LeftLed = 1;
      backRun();
      ShowPort = ShowDirect[1];
      break;
    case 3:
      stop();
      delay1ms(240);
      turnLeft();
      ShowPort = ShowDirect[2];
      break;
    case 4:
      stop();
      delay1ms(240);
      turnRight();
      ShowPort = ShowDirect[3];
      break;
    case 5:
      stop();
      ShowPort = ShowDirect[4];
      break;
  }
}

void IR_IN() interrupt 2 using 0{
  unsigned char j,k,N = 0;
  EX1 = 0;
  delayms(210);//NEC协议 0:0.56+0.56;1:0.56+1.68 ms
  if(IRIN == 1){  //红外接收 IRIN == 1 低电平 寻找高电平进入中断
    EX1 = 1;      //允许外部中断
    return;       //取消中断
  }
  while (!IRIN)   //红外接收 高电平  即进入 9ms 引导脉冲
    delayms(14);//延时跳过 9ms引导
  for(j = 0; j < 4; j++){ //接收 4 个字节 4*8 位
    for(k = 0; k < 8; k++){
      while(IRIN)  // 等待低电平 0.14ms 进入 4.5ms 空闲
        delayms(14);  //延时跳过4.5ms空闲
      while (!IRIN) // 进入高电平
        delayms(14);//延时跳过
      while (IRIN){ //低电平 0.14 ms
        delayms(14);//0.14ms延时并计数
        N++;        // 计数器 比特值 0
        if(N >= 30){//低电平时间过长则说明此信号有误则中断
          EX1 = 1;
          return;
        }
      }
      IRCOM[j] = IRCOM[j] >> 1;//右移一位，最高位为0

      if (N >= 8){  //如果 n>8 则为 1
        IRCOM[j] = IRCOM[j]|0x80; //右移后最高为 0; |0x80 最高位为 1
      }
      N = 0; // 计数位 清 0
    }
  }
  if(IRCOM[2] != ~IRCOM[3]){ //判断两个数据码是否相同
    EX1=1;  //打开外部中断
    return;
  }
  for(j = 0; j < 10; j++){
    if(IRCOM[2]==RecvData[j])
      ControlCar(j);
  }
  EX1 = 1;
}
void main()                                       //主程序入口
{
 bit ExeFlag=0;                                       //定义可执行位变量
 EX1=1;                                               //同意开启外部中断1
 IT1=1;                                               //设定外部中断1，下降沿控制终端
 EA=1;      //允许中断
 TMOD=0X01;
 TH0= 0XFc;		  //1ms定时
 TL0= 0X18;
 TR0= 1;
  ET0= 1;
 ShowPort=ShowDirect[4];
 PX1 = 1;                            //数码管显示数字0
while(1)                                              //程序主循环
 {
   Delay();                                           //延时
 }
}







/***/
