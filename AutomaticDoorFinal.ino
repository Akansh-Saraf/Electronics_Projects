#include <Stepper.h>

const int stepsPerRevolution = 200;
const int maxStepLevel=800;
const int stepSize=20;
 
const int inputPin= 2; 
const int in1 = 3;
const int in2 = 4;
const int in3 = 5;
const int in4 = 6;
const int ena = 9;
const int enb = 10;

int stepLevel=0;
int pirState=0;
Stepper motor(stepsPerRevolution, in1, in2, in3, in4);

void setup() 
{
  pinMode(inputPin, INPUT); 
  const int in1 = 3;
  const int in2 = 4;
  const int in3 = 5;
  const int in4 = 6;
  const int ena = 9;
  const int enb = 10;
  Serial.begin(9600);

  motor.setSpeed(200); // Set the motor speed (0-255)
  digitalWrite(ena, HIGH); // Enable motor A
  digitalWrite(enb, HIGH); // Enable motor B
}
 
void loop()
{

  pirState = digitalRead(inputPin);
  Serial.print("pirState: ");
  Serial.print(pirState);
  Serial.print("\n");
  if(pirState==HIGH && stepLevel!=maxStepLevel)
  {
  	openDoor();
  } 
  if(pirState==LOW && stepLevel==maxStepLevel)
  {
  	closeDoor();
  } 
  Serial.print("\nLoop end\n");
  delay(1000);
}

void openDoor()
{
  Serial.print("\nDoor opening\n");
  Serial.print(stepLevel);
	while(stepLevel<maxStepLevel)
    {
      motor.step(stepSize);
      delay(20);
      stepLevel=stepLevel+stepSize;
      Serial.print(stepLevel);
      Serial.print(" ");
    }
  Serial.print("\nDoor opened\n");
  delay(4000);
}

void closeDoor()
{
  Serial.print("\nDoor closing\n");
  Serial.print(stepLevel);
  Serial.print(" ");
  while(stepLevel>0)
  {
   pirState = digitalRead(inputPin); 
    if(pirState==HIGH)
      {
      	delay(10);
      	openDoor();
        return;
      }
    motor.step(-stepSize);
    delay(40);
    stepLevel=stepLevel-stepSize;
    Serial.print(stepLevel);
    Serial.print(" ");
  }
  Serial.print("\nDoor closed\n");
}

