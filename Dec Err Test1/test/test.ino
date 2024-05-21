#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CANListener listener;

static CAN_message_t rxmsg, txmsg;
int upperspeedByte, lowerspeedByte, accByte, dirByte, relAxisByte1, relAxisByte2, relAxisByte3; //speed

void setup() 
{
  Serial.begin(921600);
  delay(1000);
  Serial.println("CAN Setup Start");

  Can0.begin();
  Can0.setBaudRate(1000000);

  //Can0.attachObj(&listener);
  //listener.attachGeneralHandler();
  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(FIFO, canSniff);
  Can0.setFIFOFilter(REJECT_ALL);
  Can0.setFIFOFilterRange(0, 0x100, 0x108, STD);
  Can0.enhanceFilter(FIFO);

  txmsg.seq = 1;
  rxmsg.seq = 1;
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
volatile int speeds = 500;
volatile int i;
void loop() 
{
  if (Serial.available()) 
  {
    String input = Serial.readString();
    input.trim();

    if(input == "run speeds mode")
    {
      Serial.println("~~~~~~~~~~Run Speed Mode~~~~~~~~~~");
      while(1)
      {
        upperspeedByte = (speeds >> 8) & 0xFF;
        lowerspeedByte = speeds & 0xFF;
        accByte = 255;
        dirByte = 0;
        txmsg.id = 5;
        txmsg.len = 5;
        txmsg.buf[0] = 0xF6;
        txmsg.buf[1] = dirByte + upperspeedByte;
        txmsg.buf[2] = lowerspeedByte;
        txmsg.buf[3] = accByte;
        txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3]) & 0xFF;

        Serial.printf("\nSpeeds: %d", speeds);        
        Can0.write(txmsg);
        speeds -= 1;
        if(speeds == 0) break;
        //delayMicroseconds(500);
        delay(100);
      }
      Serial.println("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~done");
      /*
      Serial.println("**********Stop Speed Mode**********");
      speeds = 500;
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
      */     
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
      speeds = 500;
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

