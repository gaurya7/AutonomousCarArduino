//Required header files.....
#include <SoftwareSerial.h>
#include <Servo.h>
#include <String.h>
// Variables.......
char data = "";
String source = "0";
String destination = "0";
String temp[5];
int mode = 0; // change to blank after finalization
int i=0;
int echo1 = 22;
int trig1 = 23;
int echo2 = 24;
int trig2 = 25;
int echo3 = 26;
int trig3 = 27;
int echo4 = 28;
int trig4 = 29;
int echo5 = 30;
int trig5 = 31;
int echo6 = 32;
int trig6 = 33;
Servo servoangle;
int angle = 60; //change later
int carspeed = 0;
int lanekeep = 0;
int wait=0; //counter for waiting behind the car.
int calibrationTime = 30;
long unsigned int lowIn;
long unsigned int pause = 5000;
boolean lockLow = true;
boolean takeLowTime;
int pirPin = 50;
int pedestrian = 0;
int motor11 = 44;  //used for motor
int motor12 = 45; //used for motor
int motor21 = 46;
int motor22 = 47;
int mcontrol1 = 11; //used for motor speed control
int mcontrol2 = 10; //used for motor speed control
int ld = 52; //pin no of left lane detector.
int rd = 53; //pin no of right lane detector.
int lca=1; // lane change assist variable..... 1: enable     0: disable
int m = 4;
int backlight1=42;
int backlight2=43;
int leftindicator=38;
int rightindicator=39;
int buzz=7;
int headlamp1=40;
int headlamp2=41;
int ldr=A0; 
int backlight=0;
int horn=0;
int hwl=0;
int ldrvalue=0;
int n; //to store the accepted values from the bluetooth
//default arrays
int a12[25] = {60,0,60,60,60,120,60,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999};
int a13[25] = {1,3,1,2,1};
int a14[25] = {1,3,1,2,1,2,3,3,2,1};
int a15[25] = {1,3,1,2,1,1,2,3,3,3,2,1};
int a16[25] = {1,3,1,1,1,2,1,1,1,3,1};
int a21[25] = {1,2,1};
int a23[25] = {2,1,2,2};
int a24[25] = {2,1,2,3,3,2,1};
int a25[25] = {2,1};
int a26[25] = {1,1,3,1};
int a31[25] = {};
int a32[25] = {};
int a34[25] = {};
int a35[25] = {};
int a36[25] = {};
int a41[25] = {};
int a42[25] = {};
int a43[25] = {};
int a45[25] = {};
int a46[25] = {};
int a51[25] = {};
int a52[25] = {};
int a53[25] = {};
int a54[25] = {};
int a56[25] = {};
int a61[25] = {};
int a62[25] = {};
int a63[25] = {};
int a64[25] = {};
int a65[25] = {};
int f[25] = {60,0,60,60,60,120,60,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999,999};
int cmd=0;
int arr=0;
int start=0;
void setup() 
{
 Serial.begin(115200);
 Serial3.begin(9600);
 pinMode(echo1, INPUT);
 pinMode(trig1, OUTPUT);
pinMode(echo2, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo3, INPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo4,INPUT);
  pinMode(trig4,OUTPUT);
  pinMode(echo5,INPUT);
  pinMode(trig5,OUTPUT);
  pinMode(echo6,INPUT);
  pinMode(trig6,OUTPUT);
  pinMode(motor11, OUTPUT);
  pinMode(motor12, OUTPUT);
  pinMode(motor21, OUTPUT);
  pinMode(motor22, OUTPUT);
  pinMode(mcontrol1, OUTPUT);
  pinMode(mcontrol2, OUTPUT);
  pinMode(ld, INPUT);
  pinMode(rd, INPUT);
  pinMode(backlight1,OUTPUT);
  pinMode(backlight2,OUTPUT);
  pinMode(leftindicator,OUTPUT);
  pinMode(rightindicator,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(headlamp1,OUTPUT);
  pinMode(headlamp2,OUTPUT);
  pinMode(ldr,INPUT);
  servoangle.attach(13);
 digitalWrite(buzz,LOW);
  digitalWrite(backlight1,LOW);
  digitalWrite(backlight2,LOW);
  digitalWrite(leftindicator,LOW);
  digitalWrite(rightindicator,LOW);
  digitalWrite(headlamp1,LOW);
  digitalWrite(headlamp2,LOW);
  Serial.println("Initializing");
  servoangle.write(120);
  delay(3000);
  servoangle.write(0);
  delay(3000);
  servoangle.write(60);
  //servoangle.detach();
  // iterate over the notes of the melody:
  /*for (int thisNote = 0; thisNote < 8; thisNote++) 
  {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(buzz, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzz);
  }*/
}
void loop() 
{
  if(start==1)
  {
    goforward();
    checkLanes();
  }
// put your main code here, to run repeatedly:
  while(Serial3.available())
  {
    data=Serial3.read();
    Serial.println(data);
    if((data=="A")||(data=="B")||(data=="C")||(data=="D")||(data=="E"))
    {
      if(data=="A")
      {
        goforward();
      }
      else if(data=="B")
      {
        goreverse();
      }
     else if(data=="C")
      {
        turnleft();
      }
      else if(data=="D")
      {
        turnright();
      }
      else if(data=="S")
      {
        //turn off all the motors
      }
    }
    else
    {     
      if(i<2)
      {
        temp[i]=data;
        i=i+1;
      }
    }
  }
  if(start==0)
  {
      if(i==2)
      {
          Serial.print("temp[0]:");
        Serial.println(temp[0]);
        Serial.print("temp[1]:");
        Serial.println(temp[1]);
        source=temp[0];
        destination=temp[1]; 
        if((temp[0]=="1") && (temp[1]=="2"))
        {
          Serial.println("array12 selected");          
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a12[arr];
          }
        }
        else if((temp[0]=="1") && (temp[1]=="3"))
        {
          Serial.println("array13 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a13[arr];
          }
        }
        else if((temp[0]=="1") && (temp[1]=="4"))
        {
          Serial.println("array14 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a14[arr];
          }
        }
        else if((temp[0]=="1") && (temp[1]=="5"))
        {
          Serial.println("array15 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a15[arr];
          }
        }
        else if((temp[0]=="1") && (temp[1]=="6"))
        {
          Serial.println("array16 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a16[arr];
          }
        }
        else if((temp[0]=="2") && (temp[1]=="1"))
        {
          Serial.println("array21 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a21[arr];
          }
        }
        else if((temp[0]=="2") && (temp[1]=="3"))
        {
          Serial.println("array23 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a23[arr];
          }
        }
        else if((temp[0]=="2") && (temp[1]=="4"))
        {
          Serial.println("array24 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a24[arr];
          }
        }
        else if((temp[0]=="2") && (temp[1]=="5"))
        {
          Serial.println("array25 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a25[arr];
          }
        }
        else if((temp[0]=="2") && (temp[1]=="6"))
        {
          Serial.println("array26 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a26[arr];
          }
        }
        else if((temp[0]=="3") && (temp[1]=="1"))
        {
          Serial.println("array31 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a31[arr];
          }
        }
        else if((temp[0]=="3") && (temp[1]=="2"))
        {
          Serial.println("array32 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a32[arr];
          }
        }
        else if((temp[0]=="3") && (temp[1]=="4"))
        {
          Serial.println("array34 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a34[arr];
          }
        }
        else if((temp[0]=="3") && (temp[1]=="5"))
        {
          Serial.println("array35 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a35[arr];
          }
        }
        else if((temp[0]=="3") && (temp[1]=="6"))
        {
          Serial.println("array36 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a36[arr];
          }
        }
        else if((temp[0]=="4") && (temp[1]=="1"))
        {
          Serial.println("array41 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a41[arr];
          }
        }
        else if((temp[0]=="4") && (temp[1]=="2"))
        {
          Serial.println("array42 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a42[arr];
          }
        }
        else if((temp[0]=="4") && (temp[1]=="3"))
        {
          Serial.println("array43 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a43[arr];
          }
        }
        else if((temp[0]=="4") && (temp[1]=="5"))
        {
          Serial.println("array45 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a45[arr];
          }
        }
        else if((temp[0]=="4") && (temp[1]=="6"))
        {
          Serial.println("array46 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a46[arr];
          }
        }
        else if((temp[0]=="5") && (temp[1]=="1"))
        {
          Serial.println("array51 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a51[arr];
          }
        }
        else if((temp[0]=="5") && (temp[1]=="2"))
        {
          Serial.println("array52 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a52[arr];
          }
        }
        else if((temp[0]=="5") && (temp[1]=="3"))
        {
          Serial.println("array53 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a53[arr];
          }
        }
        else if((temp[0]=="5") && (temp[1]=="4"))
        {
          Serial.println("array54 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a54[arr];
          }
        }
        else if((temp[0]=="5") && (temp[1]=="6"))
        {
          Serial.println("array56 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a56[arr];
          }
        }
        else if((temp[0]=="6") && (temp[1]=="1"))
        {
          Serial.println("array61 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a61[arr];
          }
        }
        else if((temp[0]=="6") && (temp[1]=="2"))
        {
          Serial.println("array62 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a62[arr];
          }
        }
        else if((temp[0]=="6") && (temp[1]=="3"))
        {
          Serial.println("array63 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a63[arr];
          }
        }
        else if((temp[0]=="6") && (temp[1]=="4"))
        {
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a64[arr];
          }
        }
        else if((temp[0]=="6") && (temp[1]=="5"))
        {
          Serial.println("array65 selected");
          for(arr=0;arr<25;arr++)
          {
            f[arr]=a65[arr];
          }
        } 
        for(arr=0;arr<25;arr++)
          {
            Serial.println(f[arr]);
          }
          cmd=f[0];
          arr=1;
          start=1;
      }
      temp[0]="";
      temp[1]="";
      //i=0; 
    }
}  
void goforward()
{
  getfrontdist();
  if (carspeed == 0)
  {
    digitalWrite(motor11, LOW);
    digitalWrite(motor12, LOW);
    digitalWrite(motor21, LOW);
    digitalWrite(motor22, LOW);
    //taillampon();
  }
  else
  {
    //taillampoff();
    //turn the pin high to go forward
    digitalWrite(motor11, LOW);
    digitalWrite(motor12, HIGH);
    digitalWrite(motor21, LOW);
    digitalWrite(motor22, HIGH);
  }
}
void goreverse()
  {
  if (carspeed == 0) {
    digitalWrite(motor11, LOW);
    digitalWrite(motor12, LOW);
    digitalWrite(motor21, LOW);
    digitalWrite(motor22, LOW);
  }
  else
  {
    digitalWrite(motor11, HIGH);
    digitalWrite(motor12, LOW);
    digitalWrite(motor21, HIGH);
    digitalWrite(motor22, LOW);
  }
}
void checkLanes()
{
  int leftline=digitalRead(ld);
  int rightline=digitalRead(rd);
  Serial.println("************");
  Serial.println(leftline);
  Serial.println(rightline);
  if(lca==1)
    {    
      /*Serial.print("LD=");
      Serial.println(leftline);
      Serial.print("RD=");
      Serial.println(rightline);*/
      if ((leftline==0)&&(leftline!=rightline))
      {                
        turnright();
        digitalWrite(motor11, LOW);
        digitalWrite(motor12, HIGH);
        digitalWrite(motor21, LOW);
        digitalWrite(motor22, HIGH);
        delay(300);
        digitalWrite(motor11, LOW);
        digitalWrite(motor12, LOW);
        digitalWrite(motor21, LOW);
        digitalWrite(motor22, LOW);
        turnleft();
      }
      if ((rightline==0)&&(rightline!=leftline))
      {
        turnleft();
        digitalWrite(motor11, LOW);
        digitalWrite(motor12, HIGH);
        digitalWrite(motor21, LOW);
        digitalWrite(motor22, HIGH);
        delay(500);
        digitalWrite(motor11, LOW);
        digitalWrite(motor12, LOW);
        digitalWrite(motor21, LOW);
        digitalWrite(motor22, LOW);
        turnright();
      }
    }
    if ((leftline==0)&&(rightline==0))
    {
      cmd=f[arr];
      //Serial.println(cmd);
      arr=arr+1;
      Serial.println("Command Changed");
      if(cmd==999)
      {
        digitalWrite(motor11, LOW);
        digitalWrite(motor12, LOW);
        digitalWrite(motor21, LOW);
        digitalWrite(motor22, LOW);
        start=0;
      }
      else if((cmd<999)&&(start==1))
      {
        servoangle.write(cmd);
      }
      goforward();
      delay(300);
      goforward();
    }
}
void turnleft()
{
  Serial.println("Turning left");
  Serial.println(angle);
  //servoangle.attach(6);
  if((angle==0) || (angle==30) || (angle==60) || (angle==90))
  {
    angle=angle+30;
    servoangle.write(angle);
  }
  else
  {
    Serial.println("Servo at its maximum permissible limit towards left");
  }
  Serial.println(angle);
  //servoangle.detach();
}
void turnright()
{
  Serial.println("Turning right");
  Serial.println(angle);
  //servoangle.attach(6);
  if((angle==120) || (angle==90) || (angle==60) || (angle==30))
  {
    angle=angle-30;
    servoangle.write(angle);
  }
  else
  {
    Serial.println("Servo at its maximum permissible limit towards right");
  }
  Serial.println(angle);
  //servoangle.detach();
}
void getfrontdist()
{
  int distfrontleft = getfrontleft();
  int distfront = getfront();
  int distfrontright = getfrontright();
 // int left = getleft();
  //int right = getright();
  /*Serial.println("******************");
  Serial.println(distfrontleft);
  Serial.println(distfront);
  Serial.println(distfrontright);*/
  //Serial.println(right);
  //Serial.println(left);
  if ((distfrontleft < 7 || distfrontright < 7) && distfront > 0)
  {
    carspeed = 0;
    analogWrite(mcontrol1,0);
    analogWrite(mcontrol2,0);
    digitalWrite(motor11, LOW);
    digitalWrite(motor12, LOW);
    digitalWrite(motor21, LOW);
    digitalWrite(motor22, LOW);
  }
  else if ((distfrontleft > 0 || distfrontright > 0) && distfront < 7)
  {
    carspeed = 0;
    analogWrite(mcontrol1,0);
    analogWrite(mcontrol2,0);
    digitalWrite(motor11, LOW);
    digitalWrite(motor12, LOW);
    digitalWrite(motor21, LOW);
    digitalWrite(motor22, LOW);
    //overtake();
  }
  else if (((distfrontleft > 9 && distfrontleft < 10) || (distfrontright > 9 && distfrontright < 10)) && distfront > 7)
  {
    carspeed = 20;
    analogWrite(mcontrol1,110);
    analogWrite(mcontrol2,130);
  }
  else if (((distfrontleft > 9 && distfrontleft < 10) || (distfrontright > 9 && distfrontright < 10)) && distfront < 7)
  {
    carspeed = 0;
    analogWrite(mcontrol1,0);
    analogWrite(mcontrol2,0);
    digitalWrite(motor11, LOW);
    digitalWrite(motor12, LOW);
    digitalWrite(motor21, LOW);
    digitalWrite(motor22, LOW);
    //overtake();
  }
  else if ((distfrontleft > 9 && distfrontright > 9) && (distfront > 7 && distfront < 10))
  {
    carspeed = 20;
    analogWrite(mcontrol1,110);
    analogWrite(mcontrol2,130);
  }
  else if ((distfrontleft > 9 && distfrontright > 9) && distfront < 7)
  {
    carspeed = 0;
    analogWrite(mcontrol1,0);
    analogWrite(mcontrol2,0);
    digitalWrite(motor11, LOW);
    digitalWrite(motor12, LOW);
    digitalWrite(motor21, LOW);
    digitalWrite(motor22, LOW);
    //overtake();                                              
  }
  else if ((distfrontleft > 9 && distfrontright > 9) && (distfront > 10 && distfront < 15))
  {
    carspeed = 40;
    analogWrite(mcontrol1,130);
    analogWrite(mcontrol2,150);
  }
  else if ((distfrontleft > 9 && distfrontright > 9) && (distfront > 15 && distfront < 20))
  {
    carspeed = 60;
    analogWrite(mcontrol1,160);
    analogWrite(mcontrol2,180);
  }
  else if ((distfrontleft > 9 && distfrontright > 9) && (distfront > 20 && distfront < 25))
  {
    carspeed = 80;
    analogWrite(mcontrol1,180);
    analogWrite(mcontrol2,200);
  }
  else if ((distfrontleft > 9 && distfrontright > 9) && distfront > 25)
  {
    carspeed = 100;
    analogWrite(mcontrol1,230);
    analogWrite(mcontrol2,250);
  }
  Serial.print("Carspeed= ");
  Serial.println(carspeed);
}
int getfrontleft()
{
  long duration;
  int distance;
  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  duration = pulseIn(echo1, HIGH);
  distance = duration * 0.034 / 2;
  //Serial.println(distance);
  return (distance);
} int getfront()
{ long duration;
  int distance;
  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  duration = pulseIn(echo2, HIGH);
  distance = duration * 0.034 / 2;
  //Serial.println(distance);
  return (distance);
}
int getfrontright()
{
  long duration;
  int distance;
  digitalWrite(trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);
  duration = pulseIn(echo3, HIGH);
  distance = duration * 0.034 / 2;
  //Serial.println(distance);
  return (distance);
}
