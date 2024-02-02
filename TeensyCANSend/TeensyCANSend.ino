// -------------------------------------------------------------
// CANtest for Teensy 4.0 using CAN2 and CAN2 bus
#include <FlexCAN_T4.h>

#define debug(msg) Serial.print("["); Serial.print(__FILE__); Serial.print("::"); Serial.print(__LINE__);  Serial.print("::"); Serial.print(msg); Serial.println("]");
void debug_pause(void)
{
  Serial.print("Paused...");
  while (!Serial.available());
  while (Serial.available()) Serial.read();
  Serial.println("Restarted.");
}

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;
FlexCAN_T4<CAN2, RX_SIZE_256, TX_SIZE_16> Can2;

static CAN_message_t msg;
static uint8_t hex[17] = "0123456789abcdef";

// -------------------------------------------------------------
static void hexDump(uint8_t dumpLen, uint8_t *bytePtr)
{
  uint8_t working;
  while( dumpLen-- ) {
    working = *bytePtr++;
    Serial.write( hex[ working>>4 ] );
    Serial.write( hex[ working&15 ] );
  }
  Serial.write('\r');
  Serial.write('\n');
}


// -------------------------------------------------------------
void setup(void)
{
  Serial.begin(115200);
  int iSerialTimeout = 1000000;
  delay(100);
  while (!Serial && (iSerialTimeout-- != 0));  
  debug (F("start setup"));

  Can1.begin();  
  Can2.begin();

  pinMode(0, INPUT);
  pinMode(1, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, INPUT);



  // t4 missing msg.ext = 0;
  msg.id = 0x100;
  msg.len = 8;
  msg.flags.extended = 0;
  msg.flags.remote   = 0;
  msg.flags.overrun  = 0;
  msg.flags.reserved = 0;
  msg.buf[0] = 10;
  msg.buf[1] = 20;
  msg.buf[2] = 0;
  msg.buf[3] = 100;
  msg.buf[4] = 128;
  msg.buf[5] = 64;
  msg.buf[6] = 32;
  msg.buf[7] = 16;
  debug (F("setup complete"));
  //debug_pause();
}


// -------------------------------------------------------------
void loop(void)
{
  Serial.println("T4.0cantest - Repeat: Read bus2, Write bus1");
  CAN_message_t inMsg;
  while (Can2.read(inMsg)!=0) 
  {
    Serial.print("W RD bus 2: "); hexDump(8, inMsg.buf);
  }
  msg.buf[0]++;
  Can1.write(msg);
  msg.buf[0]++;
  Can1.write(msg);
  msg.buf[0]++;
  Can1.write(msg);
  msg.buf[0]++;
  Can1.write(msg);
  msg.buf[0]++;
  Can1.write(msg);  
  delay(20);
}