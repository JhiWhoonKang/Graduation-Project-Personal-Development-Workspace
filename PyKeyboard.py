import serial
import keyboard

# 시리얼 포트 설정
ser = serial.Serial('COM13', 9600)

try:
    while True:
        # 키보드 입력 감지
        if keyboard.is_pressed('w'):  
            ser.write(b'w')  # Teensy로 'w' 전송
        elif keyboard.is_pressed('s'):
            ser.write(b's')
        elif keyboard.is_pressed('a'):
            ser.write(b'a')
        elif keyboard.is_pressed('d'):
            ser.write(b'd')
except KeyboardInterrupt:
    ser.close()  # 프로그램 종료 시 시리얼 포트 닫기
