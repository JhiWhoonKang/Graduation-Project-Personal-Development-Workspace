#include <FlexCAN_T4.h>

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;
CANListener listener;

static CAN_message_t rxmsg, txmsg;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("CAN Setup Start");

  Can0.begin();
  Can0.setBaudRate(500000);
  Can0.attachObj(&listener);
  listener.attachGeneralHandler();

  txmsg.id = 1;
  txmsg.len = 2;
  txmsg.buf[0] = 49;
  txmsg.buf[1] = 50;
  Serial.println("CAN Rx Setup Ready");
  Serial.println("CAN Tx Setup Ready");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    input.trim();

    Serial.println("---------------------------tx");
    if (input == "send") {
      Serial.printf("%02X", txmsg.id);
      for (byte i = 0; i < 8; i++) {          
        Serial.printf(" %02X", txmsg.buf[i]);
      }
      Serial.printf(" | time:%d \n\r", millis());

      Can0.write(txmsg);
      Serial.println(" Message sent");
    }
    Serial.println("---------------------------tx_");
  }

  if (Can0.read(rxmsg)) {
    Serial.println("---------------------------rx");
    Serial.printf("%02X", rxmsg.id);
    for (byte i = 0; i < 8; i++) {  
      Serial.printf(" %02X", rxmsg.buf[i]);
    }
    Serial.printf(" | time:%d \n\r", millis());
    Serial.println("---------------------------rx_");
  }
}