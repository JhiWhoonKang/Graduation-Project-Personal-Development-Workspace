// ******************************************************************************
// Speed range 0 ~ 3000
// Acc 0 ~ 255
// relAxis range -8388607 ~ 8388607
// Dir 0(CCW), 1(CW)
// CRC = (ID + byte1 + … + byte(n) ) & 0xFF
// CAN ID 3 = Body PAN
// CAN ID 4 = Optical TILT
// CAN ID 5 = Weapon
// ******************************************************************************

#include <usb_rawhid.h>
#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CANListener listener;

static CAN_message_t rxmsg, txmsg;
int speedIndex, accIndex, dirIndex, relAxisIndex; //index
int speed;
int upperspeedByte, lowerspeedByte, accByte, dirByte, relAxisByte1, relAxisByte2, relAxisByte3; //speed
long relAxisByte;
volatile bool dataFlag = false;
volatile int panValue = 0;
volatile int tiltValue = 0;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("CAN Setup Start");

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
  uint8_t receiveBuffer[64];
  uint8_t sendBuffer[64];
  int recvSize;

  recvSize = RawHID.recv(receiveBuffer, 0);
  if(recvSize > 0)
  {
    Serial.println("Received Data:");
    for(int i = 0; i < recvSize; i++)
    {
      Serial.print(receiveBuffer[i], HEX);
      Serial.print(" ");
    }
 
    if(receiveBuffer[0] == 1)
    {
      Serial.println("canID 1 data");
    }
    if(receiveBuffer[0] == 2)
    {
      Serial.println("canID 2 data");
    }

    // Speed Mode
    if(receiveBuffer[0] == 3)
    {
      Serial.println("canID 3 data");
      txmsg.len = 5;    
      txmsg.buf[0] = receiveBuffer[1];
      txmsg.buf[1] = receiveBuffer[2];
      txmsg.buf[2] = receiveBuffer[3];
      txmsg.buf[3] = receiveBuffer[4];
      txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3]) & 0xFF;
      Serial.println("==========RCWS Body Speed Mode Configuration==========");

      Can0.write(txmsg);
      Serial.println("==========RCWS Body Speed Mode Run==========");
    }

    // Speed Mode
    if(receiveBuffer[0] == 4)
    {
      Serial.println("canID 4 data");
      txmsg.len = 5;    
      txmsg.buf[0] = receiveBuffer[1];
      txmsg.buf[1] = receiveBuffer[2];
      txmsg.buf[2] = receiveBuffer[3];
      txmsg.buf[3] = receiveBuffer[4];
      txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3]) & 0xFF;
      Serial.println("==========RCWS Optical Speed Mode Configuration==========");

      Can0.write(txmsg);
      Serial.println("==========RCWS Optical Speed Mode Run==========");
    }

    // Position Mode
    if(receiveBuffer[0] == 5)
    {
      Serial.println("canID 5 data");
      txmsg.len = 8;
      txmsg.buf[0] = receiveBuffer[1];
      txmsg.buf[1] = receiveBuffer[2];
      txmsg.buf[2] = receiveBuffer[3];
      txmsg.buf[3] = receiveBuffer[4];
      txmsg.buf[4] = receiveBuffer[5];
      txmsg.buf[5] = receiveBuffer[6];
      txmsg.buf[6] = receiveBuffer[7];
      txmsg.buf[7] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3] + txmsg.buf[4] + txmsg.buf[5] + txmsg.buf[6]) & 0xFF;
    }
    Serial.println();

    memset(sendBuffer, 1, sizeof(sendBuffer));

    RawHID.send(sendBuffer, 100);
  }
  delay(100);
}
