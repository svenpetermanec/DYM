#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <MFRC522.h>
#include<Wire.h>
 
#define SS_PIN 53
#define RST_PIN 5
#define irled1 40
#define irled2 41
#define irled3 42
#define irled4 43
#define irled5 44
#define irled6 45
#define irled7 46
#define irled8 47

MFRC522 mfrc522(SS_PIN, RST_PIN);
Servo myservo;
String car;

int ir1;
int ir2;
int ir3;
int ir4;
int allow=0;
int spots[]={1,1,1,1};

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x02};
IPAddress ip(192, 168, 137, 9);
IPAddress serv(192, 168, 5, 18);
EthernetClient cliente;

void setup() {
  Serial.begin(9600);
  SPI.begin();     
  mfrc522.PCD_Init();
  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);

  digitalWrite(8,0);
  digitalWrite(4,0);
  digitalWrite(7,0);

  pinMode(31, INPUT);
  pinMode(33, INPUT);
  pinMode(32, INPUT);
  pinMode(30, INPUT);
  pinMode(40, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(44, OUTPUT);
  pinMode(45, OUTPUT);
  pinMode(46, OUTPUT);
  pinMode(47, OUTPUT);

  pinMode(22, OUTPUT);
  pinMode(24, OUTPUT);
  
  myservo.attach(9); 
  Serial.println("Put your card to the reader...");
  Serial.println();
  Ethernet.begin(mac, ip);
  delay(2000);
  myservo.write(0);
}

void statusCheck(int ir, int spot, int port1, int port2){
      if((ir)==LOW){
        delay(1000);
        if((ir)==LOW){
         digitalWrite(port1, HIGH);
         digitalWrite(port2, LOW);
         spots[spot]=0;
      }}
      else{
         digitalWrite(port2, HIGH);
         digitalWrite(port1, LOW);
         spots[spot]=1;
        }
}

void loop() {
  
    ir1=digitalRead(31);
    ir2=digitalRead(33);
    ir3=digitalRead(32);
    ir4=digitalRead(30);

   statusCheck(ir1, spot[0], irled1, irled2);
   statusCheck(ir2, spot[1], irled3, irled4);
   statusCheck(ir3, spot[2], irled5, irled6);
   statusCheck(ir4, spot[3], irled7, irled8);

  if(spots[0]==1){
      digitalWrite(6,1);
   }else{
      digitalWrite(6,0);
   }
   
   if(spots[1]==1){
      digitalWrite(10,1);
   }else{
      digitalWrite(10,0);
   }
   
   if(spots[2]==1){
      digitalWrite(2,1);
   }else{
      digitalWrite(2,0);
   }

   if(spots[3]==1){
      digitalWrite(11,1);
   }else{
      digitalWrite(11,0);
   }
  
  if(spots[0]==0 && spots[1]==0 && spots[2]==0 && spots[3]==0){
    digitalWrite(takenCounter,HIGH);
    digitalWrite(freeCounter,LOW);
    }else{
      digitalWrite(takenCounter,LOW);
      digitalWrite(freeCounter,HIGH);
  }
  
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "07 C8 A8 5F")
  {
    Serial.println("Authorized access");
    Serial.println();
    myservo.write(90);
    delay(2000);
    myservo.write(0);
    car="ZG-5534-FR";
    allow=1;
  }else if(content.substring(1) == "5A F7 84 07"){
    Serial.println("Authorized access");
    Serial.println();
    myservo.write(90);
    delay(2000);
    myservo.write(0);
    car="OS-1348-C";
    allow=1;
    }else if(content.substring(1) == "9B 02 AC 21"){
    Serial.println("Authorized access");
    Serial.println();
    myservo.write(90);
    delay(2000);
    myservo.write(0);
    car="SP-309-RB";
    allow=1;
      }
 
else{
    Serial.println(" Access denied");
    allow=0;
  }
  
if(allow==1){
    if(cliente.connect(serv, 80)){
      cliente.print("GET /ethernet/dht/data.php?");
    cliente.print("Vozilo="); 
    cliente.print(car);
    cliente.println(" HTTP/1.1"); 
    cliente.println("Host: 192.168.5.18"); 
    cliente.println("Connection: close");
    cliente.println(); 
    cliente.println(); 
    cliente.stop(); 
    Serial.println(car);
    Serial.println("connected");
    }else{
        Serial.println("Failed");
     }
  }
}
.