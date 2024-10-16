#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10

int UID[4], i;

int ID1[4] = {202, 169, 31, 100}; 
int led1=4;
int led2=5;
 
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() 
{

    Serial.begin(9600);   

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    
    SPI.begin();    
    mfrc522.PCD_Init();

}

void loop() 
{

  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  { 
    return; 
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {  
    return;  
  }
  
  Serial.print("UID của thẻ: ");   
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  { 
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");   
    UID[i] = mfrc522.uid.uidByte[i];
    Serial.print(UID[i]);
  }

  Serial.println("   ");
  
  if (UID[i] == ID1[i])
  {
    
    Serial.println("Correct Card !!! ");
    
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
       
  }
  
  else
  {
    Serial.println("Incorrect Card ........");
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }

  mfrc522.PICC_HaltA();  
  mfrc522.PCD_StopCrypto1();

}

