#include <Servo.h>

Servo motor2;
Servo motor3;
Servo motor4;
Servo motor5;
Servo motor6;
Servo motor7;

int pos=0;

/* const int sensorPin=A0;

int val=0;
int threshold=256;
*/

int thumbsUpInput=0;
int grabInput=0;

int thumbsUpState=0;
int grabState=0;

void setup() {
  // put your setup code here, to run once:
  // pinMode(sensorPin,INPUT);
  pinMode(10,INPUT);
  pinMode(11,INPUT);

  Serial.begin(9600);

  motor2.attach(2);
  motor3.attach(3);
  motor4.attach(4);
  motor5.attach(5);
  motor6.attach(6);
  motor7.attach(7);

  motor2.write(pos);
  motor3.write(pos);
  motor4.write(pos);
  motor5.write(pos);
  motor6.write(pos);
  motor7.write(pos);
}

void loop() {
  Serial.println("Loop Starts");

  thumbsUpInput=digitalRead(10);
  grabInput=digitalRead(11);

  if(grabInput==1 && grabState==0)
  {
    grab();
    grabState=1;
  }
  else if(grabInput==0 && grabState==1)
  {
    UnGrab();
    grabState=0;
  }

  if(thumbsUpInput==1 && thumbsUpState==0)
  {
    thumbsUp();
    thumbsUpState=1;
  }
  else if(thumbsUpInput==0 && thumbsUpState==1)
  {
    UnThumbsUp();
    thumbsUpState=0;
  }

  delay(500);

}

void grab()
{
  if(thumbsUpState==1)
  {
    UnThumbsUp();
  }
    Serial.println("Grab starts"); 
    for (pos = 0;pos <= 90; pos++)
    {
      motor2.write(pos);
      motor3.write(pos);
      motor4.write(pos);
      motor5.write(pos);
      motor6.write(pos);
      motor7.write(pos);
      delay(10); 
    }
    Serial.println("Grabbed");
    delay(500);
}

void thumbsUp()
{
  if(grabState==1)
  {
    UnGrab();
  }
  Serial.println("Thumbs Up Starts"); 
    for (pos = 0;pos <= 180; pos++)
    {
      //motor2.write(pos);
      motor3.write(pos);
      motor4.write(pos);
      motor5.write(pos);
      motor6.write(pos);
      motor7.write(pos);
      delay(10); 
    }
  Serial.println("Thumbs Upped");
  delay(500);
}

void UnGrab()
{
  Serial.println("Ungrabbing");
  for (pos = 90;pos >=0; pos--)
  {
    motor2.write(pos);
    motor3.write(pos);
    motor4.write(pos);
    motor5.write(pos);
    motor6.write(pos);
    motor7.write(pos);
    delay(10); 
  }
  Serial.println("Hand returned to normal position");
  delay(500);
}

void UnThumbsUp()
{
  Serial.println("UnThumbsUpping");
  for (pos = 180;pos >=0; pos--)
  {
    //motor2.write(pos);
    motor3.write(pos);
    motor4.write(pos);
    motor5.write(pos);
    motor6.write(pos);
    motor7.write(pos);
    delay(10); 
  }
  Serial.println("Hand returned to normal position");
  delay(500);
}

