import socket
import threading
import sys

def receive_messages(sock):
    """서버로부터 메시지를 받아 출력하는 함수"""
    while True:
        try:
            data = sock.recv(1024).decode('utf-8') # 서버로부터 데이터 받기
            if data:
                print("Received:", data)
            else:
                # 연결이 종료되었을 경우
                print("Connection closed by the server")
                break
        except:
            print("An error occurred.")
            sock.close()
            break

def main(server_ip, port):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.connect((server_ip, port)) # 서버에 연결
        except Exception as e:
            print(f"Cannot connect to server: {e}")
            sys.exit()

        print("Connected to the server.")
        
        # 서버로부터 메시지를 받는 스레드 시작
        thread = threading.Thread(target=receive_messages, args=(s,))
        thread.start()

        try:
            # 사용자 입력을 받아 서버에 메시지 보내기
            while True:
                message = input()
                if message:
                    s.sendall(message.encode('utf-8'))
        except KeyboardInterrupt:
            print("Client terminated.")
            s.close()

if __name__ == "__main__":
    server_ip = '172.16.3.87' # Teensy 서버의 IP 주소
    port = 23 # Teensy 서버의 포트 번호
    main(server_ip, port)
