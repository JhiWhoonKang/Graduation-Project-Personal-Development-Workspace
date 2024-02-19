#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CANListener listener;

static CAN_message_t rxmsg, txmsg;
boolean speedFlag;
int speedIndex, accIndex, dirIndex; //index
int speed;
int upperspeedByte, lowerspeedByte, accByte, dirByte; //speed

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("CAN Setup Start");

  speedFlag = false;
  Can0.begin();
  Can0.setBaudRate(500000);
  Can0.attachObj(&listener);
  listener.attachGeneralHandler();

  txmsg.id = 1;
  txmsg.len = 5;
  txmsg.buf[0] = 00;
  txmsg.buf[1] = 00;
  txmsg.buf[2] = 00;
  txmsg.buf[3] = 00;
  txmsg.buf[4] = 00;
  txmsg.buf[5] = 00;
  txmsg.buf[6] = 00;
  txmsg.buf[7] = 00;

  Serial.println("CAN Rx Setup Ready");
  Serial.println("CAN Tx Setup Ready");
  Serial.println("==============================setup()");
}

void loop() 
{
  if (Serial.available()) 
  {
    String input = Serial.readString();
    input.trim();

    Serial.println("---------------------------tx");

    if(input == "speedmode status")
    {
      Serial.println("==========Speed Mode Configuration==========");
      speedFlag = true;
      Serial.println("FLAG SET");

      txmsg.len = 5;
      Serial.println("CAN DLC SET");
      txmsg.buf[0] = 0xF6;
      txmsg.buf[1] = dirByte + upperspeedByte;
      txmsg.buf[2] = lowerspeedByte;
      txmsg.buf[3] = accByte;
      txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3]) & 0xFF;
      Serial.printf("%02X %02X %02X %02X %02X %02X", txmsg.id, txmsg.buf[0],  txmsg.buf[1], txmsg.buf[2], txmsg.buf[3], txmsg.buf[4]);
      Serial.println("\n============================================");
    }

    if(input == "run speedMode")
    {

    }

    if(input.indexOf("canID") != -1)\
    {
      Serial.println("---------------------------canID setup");
      int idIndex = input.indexOf("canID");
      String idStr = input.substring(idIndex + 6).trim();
      txmsg.id = strtol(idStr.c_str(), NULL, 10);
      Serial.printf("CAN ID set to: %02X\n", txmsg.id);
      Serial.println("---------------------------canID_");
    }

    if(input.indexOf("Speed") != -1)
    {
      Serial.println("---------------------------Speed setup");
      speedIndex = input.indexOf("Speed");
      String speedStr = input.substring(speedIndex + 6).trim();
      speed = strtol(speedStr.c_str(), NULL, 10);
      upperspeedByte = (speed >> 8) & 0xFF;
      lowerspeedByte = speed & 0xFF;

      if(speed >= 0 && speed <= 3000)
      {
        Serial.printf("Speed in hexadecimal: %02X, %02X\n", upperspeedByte, lowerspeedByte);
      }
      else
      {
        Serial.println("Error: Speed value must be between 0 and 3000");
      }
      Serial.println("---------------------------Speed_");
    }

    if(input.indexOf("Acc") != -1)
    {
      Serial.println("---------------------------Acc setup");
      accIndex = input.indexOf("Acc");
      String accStr = input.substring(accIndex + 4).trim();
      accByte = strtol(accStr.c_str(), NULL, 10);

      if (accByte >= 0 && accByte <= 255)
      {
        Serial.printf("Acc in hexadecimal: %02X\n", accByte);
      } 
      else 
      {
        Serial.println("Error: Acc value must be between 0 and 255");
      }
      Serial.println("---------------------------Acc_");
    }

    if(input.indexOf("Dir") != -1)
    {
      Serial.println("---------------------------Dir setup");
      dirIndex = input.indexOf("Dir");
      String dirStr = input.substring(dirIndex + 4).trim();
      dirByte = strtol(dirStr.c_str(), NULL, 10);

      if (dirByte == 0 || dirByte == 1)
      {
        if(dirByte == 0)
        {
          Serial.printf("CCW, Dir in hexadecimal: %02X\n", dirByte);
        }
        else 
        {
          Serial.printf("CW, Dir in hexadecimal: %02X\n", dirByte);        
        }        
      } 
      else
      {
        Serial.println("Error: Dir value must be  0(CCW) or 1(CW)");
      }
      Serial.println("---------------------------Dir_");
    }

    if(speedFlag == true)
    {
      
    }

    if (input.indexOf("FD") != -1) 
    {
      Serial.println("DATA: FD");


    } 

    if (input == "send") 
    {
      Serial.printf("%02X", txmsg.id);
      for (byte i = 0; i < 8; i++) 
      {          
        Serial.printf(" %02X", txmsg.buf[i]);
      }
      Serial.printf(" | time:%d \n\r", millis());

      Can0.write(txmsg);
      Serial.println(" Message sent");
    }
    Serial.println("---------------------------tx_");
  }

  if (Can0.read(rxmsg)) 
  {
    Serial.println("---------------------------rx");
    Serial.printf("%02X", rxmsg.id);
    for (byte i = 0; i < 8; i++) 
    {  
      Serial.printf(" %02X", rxmsg.buf[i]);
    }
    Serial.printf(" | time:%d \n\r", millis());
    Serial.println("---------------------------rx_");
  }
}