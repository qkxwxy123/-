#include <RfidDb.h>
#include <MFRC522.h>
#include <SPI.h>
#include <Servo.h>
#define Buzzer 4

Servo myservo;    //创建一个伺服电机对象
unsigned char serNum[5];

void setup()
{
  Serial.begin(9600);
  Serial.println("welcome to use!");
  SPI.begin();
  pinMode(chipSelectPin, OUTPUT);
  digitalWrite(chipSelectPin, LOW);
  pinMode(NRSTPD, OUTPUT);
  myservo.attach(8);
  MFRC522_Init();
  myservo.write(0);
  pinMode(8, OUTPUT);
  pinMode(4, OUTPUT);
}

int time = 0;
void loop()
{
  myservo.write(0);
  unsigned char status;
  unsigned char str[MAX_LEN];
  status = MFRC522_Request(PICC_REQIDL, str);
  if(status == MI_OK)
  {
    memcpy(serNum, str, 5);
    Serial.print("ID:");
    ShowCardID(serNum);
    unsigned char* id = serNum;
    if( id[0] == 0x** && id[1] == 0x** && id[2] == 0x** && id[3] == 0x**)
    {
      myservo.write(90);
      Serial.println("The host 1!");
      delay(1300);
      myservo.write(0);
    }
    else
    {
      Serial.println("Stranger!");
      for(int a = 0; a < 3; a++)
      {
        for(int i = 0; i < 1000; i++)
        {
          digitalWrite(Buzzer, HIGH);
          delayMicroseconds(100);
          digitalWrite(Buzzer, LOW);
          delayMicroseconds(100);
        }
        delay(200);
      }
      delay(2000);
    }
  } 
  MFRC522_Halt();
  delay(100);
}
