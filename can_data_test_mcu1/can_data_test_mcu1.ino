// ******************************************************************************
// Speed range 0 ~ 3000
// Acc 0 ~ 255
// relAxis range -8388607 ~ 8388607
// Dir 0(CCW), 1(CW)
// CRC = (ID + byte1 + … + byte(n) ) & 0xFF
// CAN ID 3 = Weapon
// CAN ID 4 = Optical TILT
// CAN ID 5 = Body PAN
// ******************************************************************************
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CANListener listener;

static CAN_message_t rxmsg, txmsg;
uint16_t speeds;
uint8_t upperspeedByte, lowerspeedByte, accByte, dirByte, relAxisByte1, relAxisByte2, relAxisByte3; //speed
long relAxisByte;

void setup() 
{
  Serial.begin(115200);
  delay(2000);
  Serial.println("CAN Setup Start");

  Can0.begin();
  Can0.setBaudRate(1000000);
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

    if(input == "1")
    {
      dirByte = 0;
      accByte = 3;
      txmsg.id = 5;
      txmsg.len = 5;
      txmsg.buf[0] = 0xF6;
      txmsg.buf[3] = accByte;
      speeds = 500;
      Serial.println("==============================");
      while(speeds != 0)
      {
        upperspeedByte = (speeds >> 8) & 0xFF;
        lowerspeedByte = speeds & 0xFF;        
        txmsg.buf[1] = dirByte + upperspeedByte;
        txmsg.buf[2] = lowerspeedByte;        
        txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3]) & 0xFF;
        Can0.write(txmsg);
        speeds--;
        Serial.println("==============================");
      }
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