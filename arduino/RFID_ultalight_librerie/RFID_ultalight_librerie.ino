#include <Keyboard.h>
#include <SPI.h>
#include <MFRC522.h>
#include <string.h>
#define RST_PIN    5         
#define SS_PIN    10 
// alla linea 112 sostituire i caratteri F F con quelli che verranno usati per codificare i tag

 byte buffer[18];  //data transfer buffer (16+2 bytes data+CRC)
  byte size = sizeof(buffer);
 char string[18];
 uint8_t pageAddr = 0x06;  //In this example we will write/read 16 bytes (page 6,7,8 and 9).
                            //Ultraligth mem = 16 pages. 4 bytes per page. 
                            //Pages 0 to 4 are for special functions.       



MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

 
void setup(){
  //Serial.begin(9600);                                           // Initialize serial communications with the PC
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init(); 
  Keyboard.begin();
 

}
//uint8_t buf[10]= {};
MFRC522::Uid id;
MFRC522::Uid id2;
bool is_card_present = false;
uint8_t control = 0x00;
void PrintHex(uint8_t *data, uint8_t length) // prints 8-bit data in hex with leading zeroes
{
     char tmp[16];
       for (int i=0; i<length; i++) { 
         sprintf(tmp, "0x%.2X",data[i]); 
         //Serial.print(tmp); Serial.print(" ");
       }
}
 
//*****************************************************************************************//
 
void cpid(MFRC522::Uid *id){
  memset(id, 0, sizeof(MFRC522::Uid));
  memcpy(id->uidByte, mfrc522.uid.uidByte, mfrc522.uid.size);
  id->size = mfrc522.uid.size;
  id->sak = mfrc522.uid.sak;
}
 
void loop(){
 

  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  MFRC522::StatusCode status;
 
    // Look for new cards
  if ( !mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if ( !mfrc522.PICC_ReadCardSerial()) {
    return;
  }
 
  //bool result = true;
 //uint8_t buf_len=4;
  
  //Serial.print("NewCard ");
  PrintHex(id.uidByte, id.size);
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : "");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : ""));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
 //check codice key e invia carattere
  //Serial.println();
  //Serial.print("Message : ");
  content.toUpperCase();
  //Serial.println(content);
 

   // Read data ***************************************************
  //Serial.println(F("Reading data ... "));
  //data in 4 block is readed at once.
  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(pageAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
     size = sizeof(buffer);
    //Serial.print(F("MIFARE_Read() failed: "));
    //Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //Serial.print(F("Readed data: "));
  //Dump a byte array to Serial
  for (uint8_t i = 1; i < 7; i++) {
    if(buffer[i]){
      //Serial.write(buffer[i]);
      string[i-1]=buffer[i];
      
    }
    
  }
  //Serial.println();

  
    char* ptr=strtok(string, "_");  
    if(ptr[0] == 'L' && ptr[1] == 'L') {//sostituire i caratteri L L con quelli che verranno usati per codificare i tag
      ptr = strtok(0, "_");
      int ascii = atoi(ptr);
      //Serial.println(ascii);
      Keyboard.write(ascii);
     } else {
        //Serial.println("tag non riconosciuto");
     }


   
  while(true){
    
    
    control=0;
    for(int i=0; i<3; i++){
      if(!mfrc522.PICC_IsNewCardPresent()){
        if(mfrc522.PICC_ReadCardSerial()){
          //Serial.print('a');
          control |= 0x16;
        }
        if(mfrc522.PICC_ReadCardSerial()){
          //Serial.print('b');
          control |= 0x16;
        }
        //Serial.print('c');
          control += 0x1;
      }
      //Serial.print('d');
      control += 0x4;
    }
     
    //Serial.println(control);
    if(control == 13 || control == 14){
      //card is still there
    } else {
      break;
    }
  }
  //Serial.println("no");
  Keyboard.write(32);

  delay(500); //change value if you want to read cards faster
 
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
   
}
