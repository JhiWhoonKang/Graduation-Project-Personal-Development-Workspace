#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CANListener listener;

static CAN_message_t rxmsg, txmsg;
int upperspeedByte, lowerspeedByte, accByte, dirByte, relAxisByte1, relAxisByte2, relAxisByte3; //speed
int16_t CurSpeed, ReadSpeed, TempSpeed;
void setup() 
{
  Serial.begin(921600);
  delay(1000);

  Can0.begin();
  Can0.setBaudRate(1000000);

  Can0.enableFIFO();
  Can0.enableFIFOInterrupt();
  Can0.onReceive(FIFO, CANRecv);
  Can0.setFIFOFilter(REJECT_ALL);
  Can0.setFIFOFilterRange(0, 0x001, 0x005, STD);
  Can0.enhanceFilter(FIFO);
  Serial.println("==============================setup()");
}

void loop() 
{
  Can0.events();
  if (Serial.available()) 
  {
    String input = Serial.readString();
    if(input == "run")
    {      
      RUN(10, 0, 3);
    }

    if(input == "stop")
    {
      accByte = 3;
      txmsg.id = 5;
      txmsg.len = 5;
      txmsg.buf[0] = 0xF6;
      txmsg.buf[1] = 0x00;
      txmsg.buf[2] = 0x00;
      txmsg.buf[3] = accByte;
      txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[3]) & 0xFF;

      Can0.write(txmsg);
      Serial.println("==============================STOP");
    }
  }
}

void CANRecv(const CAN_message_t &msg) 
{
  Serial.print("Interrupted ->");
  Serial.print("MB ");
  Serial.print(msg.mb);
  Serial.print(" OVERRUN: ");
  Serial.print(msg.flags.overrun);
  Serial.print(" LEN: ");
  Serial.print(msg.len);
  Serial.print(" EXT: ");
  Serial.print(msg.flags.extended);
  Serial.print(" TS: ");
  Serial.print(msg.timestamp);
  Serial.print(" ID: ");
  Serial.print(msg.id, HEX);
  Serial.print(" Buffer: ");
  for ( uint8_t i = 0; i < msg.len; i++ ) 
  {
    Serial.print(msg.buf[i], HEX);
    Serial.print(" ");    
  }
  Serial.println();

  printf("\n%d", TempSpeed);
  if(msg.buf[0] == 0x32)
  {
    Serial.println("read speed data");
    ReadSpeed = (msg.buf[1] << 8) | msg.buf[2];
    Serial.printf("%d\n", abs(ReadSpeed));
    if(abs(ReadSpeed) == TempSpeed)
    {
      Serial.println("correct");
      TempSpeed -= 1;
      DecreaseSpeed(TempSpeed);
    }
  }
}

void RUN(uint16_t targetspeed, int dir, int acc)
{
  TempSpeed = targetspeed;
  printf("%d\n", TempSpeed);
  dirByte = dir;
  upperspeedByte = (10 >> 8) & 0xFF;
  lowerspeedByte = 10 & 0xFF;
  accByte = acc;
  txmsg.id = 5;
  txmsg.len = 5;
  txmsg.buf[0] = 0xF6;
  txmsg.buf[1] = dirByte + upperspeedByte;
  txmsg.buf[2] = lowerspeedByte;
  txmsg.buf[3] = 3;
  txmsg.buf[4] = (txmsg.id + txmsg.buf[0] + txmsg.buf[1] + txmsg.buf[2] + txmsg.buf[3]) & 0xFF;

  Can0.write(txmsg);
  Serial.println("==============================RUN");
  RTSpeed();
}

void RTSpeed(void)
{
  txmsg.id = 5;
  txmsg.len = 2;
  txmsg.buf[0] = 0x32;
  txmsg.buf[1] = 0x37;
  Can0.write(txmsg);
}