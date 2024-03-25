#include <NativeEthernet.h>
#include <NativeEthernetUdp.h>

EthernetServer server(23); // 23번 포트를 사용합니다. 필요하다면 변경 가능합니다.

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // 시리얼 포트가 준비될 때까지 대기합니다.
  }

  // 이더넷 설정: IP 주소를 설정합니다. 네트워크에 맞게 적절히 조정이 필요합니다.
  IPAddress ip(172, 16, 3, 87); // 예시 IP, 실제 네트워크 환경에 맞게 조정해야 합니다.
  Ethernet.begin(ip);

  server.begin(); // 서버 시작
  Serial.print("서버 시작, IP 주소: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  EthernetClient client = server.available(); // 클라이언트 연결을 확인합니다.
  if (client) {
    Serial.println("클라이언트 연결됨");
    while (client.connected()) {
      if (client.available()) {
        char c = client.read(); // 클라이언트로부터 데이터를 읽습니다.
        Serial.write(c); // 시리얼 모니터에 출력합니다.
        client.write(c); // 클라이언트에게 데이터를 되돌려 보냅니다.
      }
    }
    client.stop(); // 클라이언트 연결을 종료합니다.
    Serial.println("클라이언트 연결 종료");
  }
}
