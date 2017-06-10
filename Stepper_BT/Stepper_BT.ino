#include <SoftwareSerial.h>
#include <Stepper.h>
#define STEPS 200  //定義步進馬達每圈的步數

//steps:代表馬達轉完一圈需要多少步數。如果馬達上有標示每步的度數，
//將360除以這個角度，就可以得到所需要的步數(例如：360/3.6=100)。(int)

Stepper stepper(STEPS, 7, 6, 5, 4);

SoftwareSerial BT(10,11); // 10: Rx ---> connect to BT's Tx; 11: TX---> connect to BT's Rx


int value=0;
int angle=0;
int times=0;
void setup() {

  stepper.setSpeed(30);     // 將馬達的速度設定成140RPM 最大  150~160

  Serial.begin(9600);
  BT.begin(9600);


}

// the loop function runs over and over again forever
void loop() {

  
  

  
  if (BT.available()){
      value=BT.read();
      Serial.println(value);

      angle=round(value/16)*6;
      times=value%16;
    
      Serial.println(angle);
      Serial.println(times);
      steppermove(times,angle);
  }
}


void steppermove(int times,int angle){
   for (int i=0; i<times ; i++)
   {
       stepper.step(round(angle/1.8)*4);//正半圈
       delay(1000);
       stepper.step(-round(angle/1.8)*4);//反半圈
       delay(1000);
    }
}



