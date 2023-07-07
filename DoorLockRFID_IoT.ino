/*

*/

#include "thingProperties.h"

#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

byte readCard[4];
String MasterTag = "21B26A1D";	// REPLACE this Tag ID with your Tag ID!!!
String tagID = "";

// Create instances
MFRC522 mfrc522(SS_PIN, RST_PIN);

const int outputPin=2;
const int buttonPin=4;
int buttonState=0;

void setup()
{
  Serial.begin(9600);
  delay(1500);
  
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
  
   SPI.begin(); // SPI bus
  mfrc522.PCD_Init(); // MFRC522
  Serial.begin(9600);

  pinMode(outputPin,OUTPUT);
  pinMode(buttonPin,INPUT);
}

void loop() {
   buttonState=digitalRead(buttonPin);
  if(buttonState==HIGH)
  {
    digitalWrite(outputPin,HIGH);
    Serial.println("Door Unlocked");
  }
  else
  {
    digitalWrite(outputPin,LOW);
    Serial.println("Door Locked");
  }
  
  //Wait until new tag is available
  
  
  while (getID()) 
  {
    Serial.println("Scan Card");
    Serial.print("MasterTag: ");
    Serial.println(MasterTag);
    Serial.print("Tag ID: ");
    Serial.println(tagID);
    if (tagID == MasterTag) 
    {
      
      Serial.println(" Access Granted!");
      digitalWrite(outputPin,HIGH);
      Serial.println("Door unlocked");
      
    }
    else
    {
      Serial.println(" Access Denied!");
    }
    delay(1000);

    
  }
}

boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! mfrc522.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(mfrc522.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA(); // Stop reading
  return true;
}