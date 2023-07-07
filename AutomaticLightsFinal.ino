const int pirPin= 4;
const int ledPin= 5;

int pirState = LOW;
int ledState= LOW;
int ledTime=0;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);
}

void loop(){
   pirState= digitalRead(pirPin);  

    if (pirState==HIGH ) 
    {
        if(ledState==LOW)
        {
            digitalWrite(ledPin, HIGH);
            ledState=HIGH;
            Serial.print("LED on for 5s minimum \n");
            delay(10000);
            ledTime=ledTime+5;
        }
        else
        {
            Serial.print("Exiting bathroom\n");
            delay(2000);
            digitalWrite(ledPin,LOW);
            ledState=LOW;
            Serial.print("LED off\n");
            delay(2000);
            ledTime=0;
        }
    }
    else
    {
        digitalWrite(ledPin, ledState);
        delay(1000);
        ledTime=ledTime+ledState;
    }

    if(ledTime==30*60*60) {
        digitalWrite(ledPin,LOW);
        ledState=LOW;
        ledTime=0;
        delay(1000);
    }
      Serial.print("LED State: ");
      Serial.print(ledState);
      Serial.print("  Timer:");
      Serial.print(ledTime);
      Serial.print("\n");

}


