#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CANListener listener;

static CAN_message_t rxmsg;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Can0.begin();
  Can0.setBaudRate(500000);
  Can0.attachObj(&listener);
  listener.attachGeneralHandler();

  Serial.println("CAN Setup Ready");
}

void loop() {
  if (Can0.read(rxmsg)) {
    Serial.printf("%08X", rxmsg.id);
    for (byte i = 0; i < 8; i++) {
      Serial.printf(" %02X", rxmsg.buf[i]);
    }
    Serial.printf(" time:%d \n\r", millis());
  }
  Can0.events();
}