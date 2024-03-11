import serial

# 시리얼 포트 설정
ser = serial.Serial('COM13', 9600)

try:
    while True:
        if ser.in_waiting > 0:
            received_data = ser.readline().decode().strip()
            print("Received from Teensy:", received_data)
except KeyboardInterrupt:
    ser.close()  # 프로그램 종료 시 시리얼 포트 닫기
