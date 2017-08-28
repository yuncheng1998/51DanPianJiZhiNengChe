#include <AT89X52.H>
#include <head.h>
void main(){
        while(1) {
                if(Left_1_led == 0&&Right_1_led == 0) frontRun();
                else if(Left_1_led == 1&&Right_1_led == 0) turnLeft();
                else if(Right_1_led == 1&&Left_1_led == 0) turnRight();
                else if(Right_1_led ==  1&&Left_1_led == 1) stop();
        }
}
