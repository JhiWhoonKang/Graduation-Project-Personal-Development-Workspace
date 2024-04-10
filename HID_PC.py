import hid
import time
#from pynput import keyboard
import pygame
import numpy as np
from dataclasses import dataclass
import serial
import struct
import pickle

VID = 0x16C0
PID = 0x0486

Xflag = 0
Yflag = 0

try:
    device = hid.device()
    device.open(VID, PID)
    print("Teensy 잡았")
except IOError as e:
    print(e)
    print("Teensy 어디")
    exit()

up = 0
down = 0
right = 0
left = 0
dir = 0
Acc = 255

def HID(data):
    print("transmit")
    global device
    report = [0] + data
    report += [0] * (64 - len(report))
    #report = struct.pack('64B', report[0], report[1], report[2], report[3], report[4], report[5], report[6], report[7], report[8], report[9], report[10], report[11], report[12], report[13], report[14], report[15], report[16], report[17], report[18], report[19], report[20], report[21], report[22], report[23], report[24], report[25], report[26], report[27], report[28], report[29], report[30], report[31], report[32], report[33], report[34], report[35], report[36], report[37], report[38], report[39], report[40], report[41], report[42], report[43], report[44], report[45], report[46], report[47], report[48], report[49], report[50], report[51], report[52], report[53], report[54], report[55], report[56], report[57], report[58], report[59], report[60], report[61], report[62], report[63])
    
    #print(time.time() - pre_time)
    #pre_time = time.time()
    device.write(report)
    time.sleep(0.1)
    if report[5] == 0:
        while(True):
            print("ACC 0")
            exit()

class joy_data:
    axisX:int = 0
    axisY:int = 0
    axisT:int = 0
    button:int = 0xfc000004
joy = joy_data()


def init_gamepad():
    # pygame 초기화
    pygame.init()

    # 게임 패드 초기화
    pygame.joystick.init()

    # 연결된 게임 패드의 수
    joystick_count = pygame.joystick.get_count()

    if joystick_count == 0:
        print("게임 패드가 연결되어 있지 않습니다.")
        return None

    # 첫 번째 게임 패드 얻기
    joystick = pygame.joystick.Joystick(0)

    # 게임 패드 초기화
    joystick.init()

    print(f"{joystick.get_name()} 게임 패드가 연결되었습니다.")
    return joystick
count = 0

def get_gamepad_input(joystick):
    # 이벤트 처리
    global up
    global down
    global right
    global left
    global dir
    global Acc
    global joy
    global Xflag, Yflag
    global count
    for event in pygame.event.get():
        if event.type == pygame.JOYAXISMOTION:
            if event.axis == 0 :                
                if event.value > -0.2 and event.value < 0.2:
                    # joystick - center
                    joy.axisX = int(0)
                    right = 0
                    left = 0
                    CRCBYTE = (0x5 + 0xF6 + Acc) & 0xFF
                    if Xflag == 1:
                        print("{} 정지 {}", count, left)
                        HID([5, 0xF6, 0, 0, Acc, CRCBYTE])
                        count +=1 
                    Xflag = 0
                else:
                    # joystick - 기울어짐
                    Xflag = 1
                    if event.value > 0 :
                        joy.axisX = int(event.value * 10)
                        #joy.axisX = 10
                        if (right != joy.axisX and joy.axisX != 0) :
                            
                            right = joy.axisX*6
                            dir = 0
                            upper_speed = (right >> 4) & 0x0F
                            lower_speed = right & 0x0F
                            BYTE2 = (dir << 7) | upper_speed
                            CRCBYTE = (0x5 + 0xF6 + BYTE2 + lower_speed + Acc) & 0xFF
                            print("{} 우키 {}",count, right)
                            
                            HID([5, 0xF6, BYTE2, lower_speed, Acc, CRCBYTE])
                            count += 1
                    elif event.value < 0 :
                        joy.axisX = abs(int(event.value * 10))
                        if (left != joy.axisX and joy.axisX != 0):
                            left = abs(joy.axisX)*6
                            dir = 1
                            upper_speed = (left >> 4) & 0x0F
                            lower_speed = left & 0x0F
                            BYTE2 = (dir << 7) | upper_speed
                            CRCBYTE = (0x5 + 0xF6 + BYTE2 + lower_speed + Acc) & 0xFF
                            print("{} 왼키 {}", count, left)
                            HID([5, 0xF6, BYTE2, lower_speed, Acc, CRCBYTE])
                            count += 1

                    elif event.type == pygame.JOYBUTTONDOWN:
                        if event.button == 0:
                            CRCBYTE = (0x5 + 0xF6 + Acc) & 0xFF
                            HID([5, 0xF6, 0, 0, Acc, CRCBYTE])
                        if event.button == 1:
                            right = 30
                            dir = 0
                            upper_speed = (right >> 4) & 0x0F
                            lower_speed = right & 0x0F
                            BYTE2 = (dir << 7) | upper_speed
                            CRCBYTE = (0x5 + 0xF6 + BYTE2 + lower_speed + Acc) & 0xFF
                            #print("우키")
                            HID([5, 0xF6, BYTE2, lower_speed, Acc, CRCBYTE])
                        if event.button == 2:
                            left = 30
                            dir = 1
                            upper_speed = (left >> 4) & 0x0F
                            lower_speed = left & 0x0F
                            BYTE2 = (dir << 7) | upper_speed
                            CRCBYTE = (0x5 + 0xF6 + BYTE2 + lower_speed + Acc) & 0xFF
                            #print("왼키")
                            HID([5, 0xF6, BYTE2, lower_speed, Acc, CRCBYTE])

gamepad = init_gamepad()

while True:
    if gamepad:
        get_gamepad_input(gamepad)   
device.close()