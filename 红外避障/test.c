#include<AT89X52.H>
unsigned int i;
unsigned char j;
void delay(unsigned int k){//延时k ms
  unsigned int i;
  unsigned char j;
  for(i = 0;i < k; i++){
    for(j = 0;j < 201; j++);
    for(j = 0;j < 101; j++);
  }
}
void main(){
	delay(10);
	unsigned int x,y;
	 for(x=0;x<k;x++)
	   for(y=0;y<2000;y++);
	
}