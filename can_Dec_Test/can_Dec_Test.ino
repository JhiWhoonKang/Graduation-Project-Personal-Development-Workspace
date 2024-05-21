// ******************************************************************************
// Speed range 0 ~ 3000
// Acc 0 ~ 255
// relAxis range -8388607 ~ 8388607
// Dir 0(CCW), 1(CW)
// CRC = (ID + byte1 + … + byte(n) ) & 0xFF
// ******************************************************************************
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CANListener listener;

static CAN_message_t rxmsg, txmsg;
boolean speedFlag, positionFlag;
int speedIndex, accIndex, dirIndex, relAxisIndex; //index
int speed;
int upperspeedByte, lowerspeedByte, accByte, dirByte, relAxisByte1, relAxisByte2, relAxisByte3; //speed
long relAxisByte, Pulse;
byte pulsebyte1, pulsebyte2, pulsebyte3;


void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("CAN Setup Start");

  speedFlag = false;
  positionFlag = false;

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
volatile int speedss = 500;
void loop() 
{
  if (Serial.available()) 
  {
    String input = Serial.readString();
    input.trim();

    Serial.println("---------------------------tx");

    if(input == "speed mode status")
    {
      Serial.println("==========Speed Mode Configuration==========");

      txmsg.len = 5;
      Serial.println("CAN DLC SET");
      txmsg.buf[0] = 0xF6;
      txmsg.buf[1] = dirByte + upperspeedByte;
      txmsg.buf[2] = lowerspeedByte;
      txmsg.buf[3] = accByte;
      txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3]) & 0xFF;

      Serial.printf("CAN DATA FORMAT: ");
      Serial.printf("%02X %02X %02X %02X %02X %02X", txmsg.id, txmsg.buf[0],  txmsg.buf[1], txmsg.buf[2], txmsg.buf[3], txmsg.buf[4]);
      Serial.println("\n============================================");
    }

    if(input == "run speed mode")
    {
      Serial.println("\n~asdfasdfasdf~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"); 
      Can0.write(txmsg);
      Serial.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    if(input == "run speeds mode")
    {
      volatile int speeds = 500;
      Serial.println("~~~~~~~~~~Run Speed Mode~~~~~~~~~~");
      while(speeds!=0)
      {
        upperspeedByte = (speeds >> 8) & 0xFF;
        lowerspeedByte = speeds & 0xFF;
        accByte = 3;
        txmsg.id = 5;
        txmsg.len = 5;
        Serial.println("CAN DLC SET");
        txmsg.buf[0] = 0xF6;
        txmsg.buf[1] = dirByte + upperspeedByte;
        txmsg.buf[2] = lowerspeedByte;
        txmsg.buf[3] = accByte;
        txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3]) & 0xFF;

        Serial.printf("Speeds: %d", speeds);        
        Can0.write(txmsg);
        speeds--;
      }
      
      Serial.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    if(input == "1")
    {
      
      Serial.println("~~~~~~~~~~Run Speed Mode~~~~~~~~~~");
      upperspeedByte = (speedss >> 8) & 0xFF;
      lowerspeedByte = speedss & 0xFF;
      accByte = 3;
      txmsg.id = 5;
      txmsg.len = 5;
      Serial.println("CAN DLC SET");
      txmsg.buf[0] = 0xF6;
      txmsg.buf[1] = dirByte + upperspeedByte;
      txmsg.buf[2] = lowerspeedByte;
      txmsg.buf[3] = accByte;
      txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3]) & 0xFF;

      Serial.printf("Speeds: %d", speedss);        
      Can0.write(txmsg);
      speedss -= 10;
      if(speedss == 0) speedss=500;
      Serial.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    if(input == "run 500rpm")
    {      
      Serial.println("~~~~~~~~~~Run Speed Mode~~~~~~~~~~");
      dirByte = 0;
      upperspeedByte = (500 >> 8) & 0xFF;
      lowerspeedByte = 500 & 0xFF;
      accByte = 3;
      txmsg.id = 5;
      txmsg.len = 5;
      Serial.println("CAN DLC SET");
      txmsg.buf[0] = 0xF6;
      txmsg.buf[1] = dirByte + upperspeedByte;
      txmsg.buf[2] = lowerspeedByte;
      txmsg.buf[3] = 3;
      txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3]) & 0xFF;

      Can0.write(txmsg);
      Serial.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    if(input == "stop speed mode")
    {
      Serial.println("**********Stop Speed Mode**********");
      speedss = 500;
      accByte = 3;
      txmsg.buf[0] = 0xF6;
      txmsg.buf[1] = 0x00;
      txmsg.buf[2] = 0x00;
      txmsg.buf[3] = accByte;
      txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[3]) & 0xFF;

      Serial.printf("CAN DATA FORMAT: ");
      Serial.printf("%02X %02X %02X %02X %02X %02X", txmsg.id, txmsg.buf[0],  txmsg.buf[1], txmsg.buf[2], txmsg.buf[3], txmsg.buf[4]);

      Can0.write(txmsg);
      Serial.println("\n***********************************");
    }
    if(input == "2")
    {
      Serial.println("2");
    }

    
    if(input == "position mode status")
    {
      Serial.println("==========Position Mode Configuration==========");
      positionFlag = true;
      Serial.println("FLAG SET");

      txmsg.len = 8;
      Serial.println("CAN DLC SET");
      txmsg.buf[0] = 0xF4;
      txmsg.buf[1] = upperspeedByte;
      txmsg.buf[2] = lowerspeedByte;
      txmsg.buf[3] = accByte;
      txmsg.buf[4] = relAxisByte1;
      txmsg.buf[5] = relAxisByte2;
      txmsg.buf[6] = relAxisByte3;
      txmsg.buf[7] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3] + txmsg.buf[4] + txmsg.buf[5] + txmsg.buf[6]) & 0xFF;

      Serial.printf("CAN DATA FORMAT: ");
      Serial.printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X", txmsg.id, txmsg.buf[0],  txmsg.buf[1], txmsg.buf[2], txmsg.buf[3], txmsg.buf[4], txmsg.buf[5], txmsg.buf[6], txmsg.buf[7]);
      Serial.println("\n============================================");
    }

    if(input == "run position mode")
    {
      Serial.println("~~~~~~~~~~Run Position Mode~~~~~~~~~~");
      Can0.write(txmsg);
      Serial.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    if(input == "stop position mode")
    {
      Serial.println("**********Stop Position Mode**********");
      txmsg.buf[0] = 0xF4;
      txmsg.buf[1] = 0;
      txmsg.buf[2] = 0;
      txmsg.buf[3] = accByte;
      txmsg.buf[4] = 0;
      txmsg.buf[5] = 0;
      txmsg.buf[6] = 0;
      txmsg.buf[7] = (txmsg.id + txmsg.buf[0] + txmsg.buf[3]) & 0xFF;

      Serial.printf("CAN DATA FORMAT: ");
      Serial.printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X", txmsg.id, txmsg.buf[0],  txmsg.buf[1], txmsg.buf[2], txmsg.buf[3], txmsg.buf[4], txmsg.buf[5], txmsg.buf[6], txmsg.buf[7]);

      Can0.write(txmsg);
      Serial.println("\n**************************************");
    }

    if(input == "position mode2 status")
    {
      Serial.println("==========Position Mode2 Configuration==========");
      positionFlag = true;
      Serial.println("FLAG SET");

      txmsg.len = 8;
      Serial.println("CAN DLC SET");
      txmsg.buf[0] = 0xFD;
      txmsg.buf[1] = upperspeedByte;
      txmsg.buf[2] = lowerspeedByte;
      txmsg.buf[3] = accByte;
      txmsg.buf[4] = pulsebyte1;
      txmsg.buf[5] = pulsebyte2;
      txmsg.buf[6] = pulsebyte3;
      txmsg.buf[7] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3] + txmsg.buf[4] + txmsg.buf[5] + txmsg.buf[6]) & 0xFF;

      Serial.printf("CAN DATA FORMAT: ");
      Serial.printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X", txmsg.id, txmsg.buf[0],  txmsg.buf[1], txmsg.buf[2], txmsg.buf[3], txmsg.buf[4], txmsg.buf[5], txmsg.buf[6], txmsg.buf[7]);
      Serial.println("\n============================================");
    }

    if(input == "stop position2 mode")
    {
      Serial.println("**********Stop Position Mode**********");
      txmsg.buf[0] = 0xFD;
      txmsg.buf[1] = 0;
      txmsg.buf[2] = 0;
      txmsg.buf[3] = accByte;
      txmsg.buf[4] = 0;
      txmsg.buf[5] = 0;
      txmsg.buf[6] = 0;
      txmsg.buf[7] = (txmsg.id + txmsg.buf[0] + txmsg.buf[3]) & 0xFF;

      Serial.printf("CAN DATA FORMAT: ");
      Serial.printf("%02X %02X %02X %02X %02X %02X %02X %02X %02X", txmsg.id, txmsg.buf[0],  txmsg.buf[1], txmsg.buf[2], txmsg.buf[3], txmsg.buf[4], txmsg.buf[5], txmsg.buf[6], txmsg.buf[7]);

      Can0.write(txmsg);
      Serial.println("\n**************************************");
    }

    if(input == "run position mode")
    {
      Serial.println("~~~~~~~~~~Run Position Mode~~~~~~~~~~");
      Can0.write(txmsg);
      Serial.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    if(input == "run position2 mode")
    {
      Serial.println("~~~~~~~~~~Run Position2 Mode~~~~~~~~~~");
      Can0.write(txmsg);
      Serial.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    }

    if(input == "go home")
    {
      Serial.println("---------------------------go home");
      txmsg.len = 2;
      txmsg.buf[0] = 0x91;
      txmsg.buf[1] = (txmsg.id + txmsg.buf[0]) & 0xFF;
      
      Can0.write(txmsg);
      Serial.println("---------------------------go home_");
    }

    if(input == "set current axis to zero")
    {
      Serial.println("---------------------------set current axis to zero");
      txmsg.len = 2;
      txmsg.buf[0] = 0x92;
      txmsg.buf[1] = (txmsg.id + txmsg.buf[0]) & 0xFF;
      
      Can0.write(txmsg);
      Serial.println("---------------------------set current axis to zero_");
    }

    if(input.indexOf("canID") != -1)
    {
      Serial.println("---------------------------canID setup");
      int idIndex = input.indexOf("canID");
      String idStr = input.substring(idIndex + 6).trim();
      txmsg.id = strtol(idStr.c_str(), NULL, 10);
      Serial.printf("CAN ID set to: %02X\n", txmsg.id);
      Serial.println("---------------------------canID_");
    }

    if(input.indexOf("Pulse") != -1)
    {
      Serial.println("---------------------------Pulse setup");
      int idIndex = input.indexOf("Pulse");
      String Pulsestr = input.substring(idIndex + 6).trim();
      Pulse = strtol(Pulsestr.c_str(), NULL, 10);

      if(Pulse >= 0 && Pulse <= 16777215)
      {
        pulsebyte1 = (Pulse >> 16) & 0xFF;
        pulsebyte2 = (Pulse >> 8) & 0xFF;
        pulsebyte3 = (Pulse) & 0xFF;
        Serial.printf("Pulse in hexadecimal: %02X, %02X, %02X\n", pulsebyte1, pulsebyte2, pulsebyte3);
      }

      else
      {
        Serial.println("Error: Pulse value must be between 0 and 16777215");
      }

      Serial.println("---------------------------Pulse_");
    }

    if(input.indexOf("Speed") != -1)
    {
      Serial.println("---------------------------Speed setup");
      speedIndex = input.indexOf("Speed");
      String speedStr = input.substring(speedIndex + 6).trim();
      speed = strtol(speedStr.c_str(), NULL, 10);      

      if(speed >= 0 && speed <= 3000)
      {
        upperspeedByte = (speed >> 8) & 0xFF;
        lowerspeedByte = speed & 0xFF;

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

    if(input.indexOf("relAxis") != -1)
    {
      Serial.println("---------------------------relAxis setup");
      relAxisIndex = input.indexOf("relAxis");
      String relAxisStr = input.substring(accIndex + 8).trim();
      relAxisByte = strtol(relAxisStr.c_str(), NULL, 10);

      if (relAxisByte >= -8388607 && relAxisByte <= 8388607)
      {
        relAxisByte1 = (relAxisByte >> 16) & 0xFF;
        relAxisByte2 = (relAxisByte >> 8) & 0xFF;
        relAxisByte3 = relAxisByte & 0xFF;

        Serial.printf("RelAxis in hexadecimal: %02X %02X %02X\n", relAxisByte1, relAxisByte2, relAxisByte3);
      } 
      else 
      {
        Serial.println("Error: relAxis value must be between -8388607 and +8388607");
      }
      Serial.println("---------------------------relAxis_");
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