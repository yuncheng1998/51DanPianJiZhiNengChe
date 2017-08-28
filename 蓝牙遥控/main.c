#include <AT89x51.h>
#define up 'A'
#define down 'B'
#define left 'C'
#define right 'D'
#define stop 'F'

#define uint unsigned int
#define uchar unsigned char
#define ShowPort P0
char code str[] = "up"
char code str[] = "back"
char code str[] = "left"
char code str[] = "right"
char code str[] = "stop"

bit flag_REC = 0;
bit flag = 0;
uchar i = 0;
uchar dat = 0;
uchar buff[5] = 0;
uchar code LedShowData[] = {0x03,0x9F,0x25,0x0D,0x99, //定义数码管显示数据
                            0x49,0x41,0x1F,0x01,0x19}

void delay(unsigned int k){
  unsigned int x,y;
  for(x = 0; x < k; x++)
  for(y = 0; y < 2000; y++);
}
