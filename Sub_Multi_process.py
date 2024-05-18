from multiprocessing import Process, Value
import tensorflow as tf
import tensorflow_hub as hub
import cv2 as cv
import cv2
import numpy as np
import pickle
import time
import pygame
import serial
import socket
import argparse
import os
import sys
import math
import struct
import threading
from dataclasses import dataclass


class click_data:
    Left_or_right:int = 3
    X:int = 0
    Y:int = 0
Click = click_data()

C_LR = Value('i', 3)
C_X = Value('i', 0)
C_Y = Value('i', 0)
RGB_Com_X = Value('i', 0)
RGB_Com_Y = Value('i', 0)

IR_Com_X = Value('i', 0)
IR_Com_Y = Value('i', 0)

################################################################################
def RGB_pro(C_LR_, C_X_, C_Y_, RGB_Com_X_, RGB_Com_Y_):
    max_length = 65000
    UDP_host_IP = "10.254.1.20"
    UDP_host_port = 9000
    UDP_Client_IP = "10.254.2.172"
    UDP_Client_port = 8000

    UDP = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    UDP.bind((UDP_host_IP, UDP_host_port))
    
    cap1 = cv2.VideoCapture(0)
    cap1.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    cap1.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    cap1.set(cv2.CAP_PROP_FPS, 30)

    model = hub.load('https://tfhub.dev/google/movenet/multipose/lightning/1')
    movenet = model.signatures['serving_default']

    def draw_bounding_box(frame, keypoints, confidence_threshold):
        y, x, c = frame.shape
        shaped = np.squeeze(np.multiply(keypoints, [y, x, 1]))
        valid_points = [kp for kp in shaped if kp[2] > confidence_threshold]
        if not valid_points:
            return None

        min_x = min([kp[1] for kp in valid_points])
        min_y = min([kp[0] for kp in valid_points])
        max_x = max([kp[1] for kp in valid_points])
        max_y = max([kp[0] for kp in valid_points])

        cv2.rectangle(frame, (int(min_x), int(min_y)), (int(max_x), int(max_y)), (255, 0, 0), 2)
        return (min_x, min_y, max_x, max_y)

    def loop_through_people(frame, keypoints_with_scores, confidence_threshold):
        rectangles = []
        for person in keypoints_with_scores:
            # 트래커가 활성화되지 않았을 때만 바운딩 박스를 그립니다.
            if tracker is None:
                rect = draw_bounding_box(frame, person, confidence_threshold)
                if rect is not None:
                    rectangles.append(rect)
        return rectangles

    # Tracker 초기화
    tracker = None

    def mouse_callback(event, x, y, flags, param):
        if event == cv2.EVENT_LBUTTONDOWN:
            for rect in rectangles_info:
                min_x, min_y, max_x, max_y = rect
                if min_x <= x <= max_x and min_y <= y <= max_y:
                    tracker = cv2.TrackerCSRT_create()
                    bbox = (int(min_x), int(min_y), int(max_x - min_x), int(max_y - min_y))
                    tracker.init(frame1, bbox)
                    break
        elif event == cv2.EVENT_RBUTTONDOWN:
            tracker = None


    gpus = tf.config.list_physical_devices('GPU')
    if gpus:
      # 텐서플로가 첫 번째 GPU만 사용하도록 제한
      try:
        tf.config.set_visible_devices(gpus[0], 'GPU')
      except RuntimeError as e:
        # 프로그램 시작시에 접근 가능한 장치가 설정되어야만 합니다
        print(e)

    with open("RGB_calibration.pkl", "rb") as f:
        RGB_cameraMatrix, RGB_dist = pickle.load(f)

    cv2.namedWindow("Movenet Multipose")
    cv2.setMouseCallback("Movenet Multipose", mouse_callback)

    while cap1.isOpened():
        success1, frame1 = cap1.read()
    
        if success1:
            frame1 = cv.undistort(frame1, RGB_cameraMatrix, RGB_dist, None)

            if C_LR_.value == 2:
                tracker = None
                C_LR_.value = 3
                C_X_.value = 0
                C_Y_.value = 0

            if tracker is None:
                img = frame1.copy()
                img = tf.image.resize_with_pad(tf.expand_dims(img, axis=0), 480, 640)
                input_img = tf.cast(img, dtype=tf.int32)
         
                results = movenet(input_img)
         
                keypoints_with_scores = results['output_0'].numpy()[:,:,:51].reshape((6,17,3))
       
                rectangles_info = loop_through_people(frame1, keypoints_with_scores, 0.5)
            
                if C_LR_.value == 1:
                    for rect in rectangles_info:
                        min_x, min_y, max_x, max_y = rect
                        if min_x <= C_X_.value <= max_x and min_y <= C_Y_.value <= max_y:
                            tracker = cv2.TrackerCSRT_create()
                            bbox = (int(min_x), int(min_y), int(max_x - min_x), int(max_y - min_y))
                            C_LR_.value = 3
                            C_X_.value = 0
                            C_Y_.value = 0
                            success1, frame1 = cap1.read()
                            tracker.init(frame1, bbox)
                            break
            elif tracker is not None:
                ret, bbox = tracker.update(frame1)
                if ret:
                    x, y, w, h = [int(v) for v in bbox]
                    cv2.rectangle(frame1, (x, y), (x + w, y + h), (0, 255, 0), 2)
                    #print(((x + x + w) / 2) - 320, ', ', 240 - ((y + y + h) / 2))
                    RGB_Com_X_.value = int(((x + x + w) / 2) - 320)
                    RGB_Com_Y_.value = 240 - int(((y + y + h) / 2))
                else:
                    # 트래킹 실패 시 트래커 리셋
                    tracker = None
    
            cv2.imshow('Movenet Multipose', frame1)
        retval, buffer = cv2.imencode(".jpg", frame1)
        if retval:
            buffer = buffer.tobytes()
            buffer_size = len(buffer)

            num_of_packs = 1
            if buffer_size > max_length:
                num_of_packs = math.ceil(buffer_size/max_length)

            frame_info = {"packs":num_of_packs}

            left = 0
            right = max_length

            for i in range(num_of_packs):
                data = buffer[left:right]
                left = right
                right += max_length
                UDP.sendto(data, (UDP_Client_IP, UDP_Client_port))
        
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap1.release()
    cv2.destroyAllWindows()
################################################################################


################################################################################
def IR_pro(IR_Com_X_, IR_Com_Y_):
    with open("IR_calibration.pkl", "rb") as f:
        IR_cameraMatrix, IR_dist = pickle.load(f)

    cap2 = cv2.VideoCapture(2)
    cap2.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
    cap2.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)
    cap2.set(cv2.CAP_PROP_FPS, 30)

    kernel = np.ones((3, 3))/3**2 #블러치리할 영역(), 나눌 숫자

    array = np.array([[1, 1, 1, 1],[1, 1, 1, 1],[1, 1, 1, 1],[1, 1, 1, 1]]) #침식 범위
    #array = np.array([[1, 1, 1, 1, 1],[1, 1, 1, 1, 1],[1, 1, 1, 1, 1],[1, 1, 1, 1, 1],[1, 1, 1, 1, 1]]) #침식 범위
    #array = np.array([[1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1],[1, 1, 1, 1, 1, 1],[1, 1, 1, 1, 1, 1],[1, 1, 1, 1, 1, 1],[1, 1, 1, 1, 1, 1]]) #침식 범위

    while cap2.isOpened():
        success2, frame2 = cap2.read()
        if success2:
            frame2 = cv.undistort(frame2, IR_cameraMatrix, IR_dist, None)
    
            frame2_gray = cv2.cvtColor(frame2, cv2.COLOR_BGR2GRAY)

            blured = cv2.filter2D(frame2_gray, -1, kernel) #블러처리

            ret_set_binary, set_binary = cv2.threshold(blured, 200, 255, cv2.THRESH_BINARY) #이진화
        
            erode = cv2.erode(set_binary, array) #침식
            dilate = cv2.dilate(erode, array) #팽창

            cv2.imshow('Camera Window1', dilate)
            cv2.imshow('Camera Window2', frame2)
        
            white_pixel_coordinates = np.column_stack(np.nonzero(dilate))

            if len(white_pixel_coordinates) > 0:
                center = np.mean(white_pixel_coordinates, axis=0)
                center = tuple(map(int, center))  # 정수형으로 변환
                IR_Com_X_.value = int(240 - center[0])
                IR_Com_Y_.value = int(center[1] - 320)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
 
    cap2.release()
    cv2.destroyAllWindows()
################################################################################
    
    
################################################################################
def init_gamepad():
    pygame.init()
    pygame.joystick.init()
    joystick_count = pygame.joystick.get_count()
    if joystick_count == 0:
        print("게임 패드가 연결되어 있지 않습니다.")
        return None

    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    print(f"{joystick.get_name()} 게임 패드가 연결되었습니다.")
    return joystick

start_up_3 = 0

ACC3 = 210

pre_3_Speed = 0

M3_state_dir = 0

M3_Stop = b'\x03\x03\xf6\x02\xfb'
M3_Move = b'\x03\x03\xf6\x01\xfa'
M3_state = b'\x03\x03\xf6\x02\xfb'
M3_error = b'\x03\x03\xf6\x00\xf9'

CRCBYTE3 = (0x3 + 0xF6 + ACC3) & 0xFF
packet3 = [3, 5, 0xF6, 0, 0, ACC3, CRCBYTE3]


start_up_4 = 0

ACC4 = 100

pre_4_Speed = 0

M4_state_dir = 0

M4_Stop = b'\x04\x03\xf6\x02\xfc'
M4_Move = b'\x04\x03\xf6\x01\xfb'
M4_state = b'\x04\x03\xf6\x02\xfc'
M4_error = b'\x04\x03\xf6\x00\xfa'

CRCBYTE4 = (0x4 + 0xF6 + ACC4) & 0xFF
packet4 = [4, 5, 0xF6, 0, 0, ACC4, CRCBYTE4]

class joy_data:
    axisX:int = 0
    axisY:int = 0
    axisT:int = 0
    button:int = 0xfc000004
joy = joy_data()

try:
    teensy = serial.Serial('/dev/ttyACM0', 500000, timeout = 0)
except IOError as e:
    print(e)
    print("Teensy 어디")
    exit()
    
def read_encoder2(canid):
    byte1 = 0x31
    crcbyte = (canid + byte1) & 0xFF
    packet = [canid, 2, byte1, crcbyte]
    teensy.write(bytearray(packet))
    """if teensy.in_waiting > 0:
        data = teensy.read(teensy.in_waiting)
        print("Origin Data: ", data.hex())
        for i in range(len(data)):
            if data[i:i+pattern_length] == pattern:
                filtered_data = data[i:i+data_length]
                filtered_data_hex = filtered_data.hex()
                weapon_encoder_data = filtered_data_hex[4:-2]
                print("Filtered Data: ", weapon_encoder_data)"""
    
def Go_to_Speed_Zero_3():
    global ACC3, CRCBYTE3, packet3
    CRCBYTE3 = (0x3 + 0xF6 + ACC3) & 0xFF
    packet3 = [3, 5, 0xF6, 0, 0, ACC3, CRCBYTE3]
    
def Go_to_target_Speed_3(Speed):
    global ACC3, CRCBYTE3, packet3
    if Speed > 0:
        DIR = 0
        upper_speed = (Speed >> 8) & 0x0F
        lower_speed = Speed & 0xFF
        BYTE2 = (DIR << 7) | upper_speed
        CRCBYTE3 = (0x3 + 0xF6 + BYTE2 + lower_speed + ACC3) & 0xFF
        packet3 = [3, 5, 0xF6, BYTE2, lower_speed, ACC3, CRCBYTE3]
    elif Speed < 0:
        DIR = 1
        upper_speed = (abs(Speed) >> 8) & 0x0F
        lower_speed = abs(Speed) & 0xFF
        BYTE2 = (DIR << 7) | upper_speed
        CRCBYTE3 = (0x3 + 0xF6 + BYTE2 + lower_speed + ACC3) & 0xFF
        packet3 = [3, 5, 0xF6, BYTE2, lower_speed, ACC3, CRCBYTE3]

def Active_Motor_3(Speed):
    global ACC3, pre_3_Speed, M3_state_dir, M3_state, M3_Stop, M3_Move, CRCBYTE3, packet3, start_up_3
    if Speed != pre_3_Speed or (Speed != 0 and M3_state == M3_Stop):
        start_up_3 = 1
        read_encoder2(3)
        if Speed == 0:
            Go_to_Speed_Zero_3()
        elif Speed > 15:
            if (M3_state == M3_Stop) or M3_state_dir == 1:
                Go_to_target_Speed_3(Speed)
                M3_state_dir = 1
            elif M3_state_dir == -1:
                Go_to_Speed_Zero_3()
        elif Speed > 0 and Speed <= 15:
            if (pre_3_Speed > 15) or (M3_state_dir == -1):
                Go_to_Speed_Zero_3()
            elif M3_state == M3_Stop:
                Go_to_target_Speed_3(Speed)
                M3_state_dir = 1
        elif Speed < -15:
            if (M3_state == M3_Stop) or M3_state_dir == -1:
                Go_to_target_Speed_3(Speed)
                M3_state_dir = -1
            elif (M3_state_dir == 1):
                Go_to_Speed_Zero_3()
        elif Speed < 0 and Speed >= -15:
            if (pre_3_Speed < -15) or (M3_state_dir == 1):
                Go_to_Speed_Zero_3()
            elif M3_state == M3_Stop:
                Go_to_target_Speed_3(Speed)
                M3_state_dir = -1
        M3_state = M3_Move
        teensy.write(bytearray(packet3))
        pre_3_Speed = Speed
    elif Speed == 0 and M3_state == M3_Move and start_up_3 == 1:
        read_encoder2(3)
        Go_to_Speed_Zero_3()
        teensy.write(bytearray(packet3))
        start_up_3 = 0
            
       
def Go_to_Speed_Zero_4():
    global ACC4, CRCBYTE4, packet4
    CRCBYTE4 = (0x4 + 0xF6 + ACC4) & 0xFF
    packet4 = [4, 5, 0xF6, 0, 0, ACC4, CRCBYTE4]
    
def Go_to_target_Speed_4(Speed):
    global ACC4, CRCBYTE4, packet4
    if Speed > 0:
        DIR = 0
        upper_speed = (Speed >> 8) & 0x0F
        lower_speed = Speed & 0xFF
        BYTE2 = (DIR << 7) | upper_speed
        CRCBYTE4 = (0x4 + 0xF6 + BYTE2 + lower_speed + ACC4) & 0xFF
        packet4 = [4, 5, 0xF6, BYTE2, lower_speed, ACC4, CRCBYTE4]
    elif Speed < 0:
        DIR = 1
        upper_speed = (abs(Speed) >> 8) & 0x0F
        lower_speed = abs(Speed) & 0xFF
        BYTE2 = (DIR << 7) | upper_speed
        CRCBYTE4 = (0x4 + 0xF6 + BYTE2 + lower_speed + ACC4) & 0xFF
        packet4 = [4, 5, 0xF6, BYTE2, lower_speed, ACC4, CRCBYTE4]

def Active_Motor_4(Speed):
    global ACC4, pre_4_Speed, M4_state_dir, M4_state, M4_Stop, M4_Move, CRCBYTE4, packet4, start_up_4
    if Speed != pre_4_Speed or (Speed != 0 and M4_state == M4_Stop):
        start_up_4 = 1
        read_encoder2(4)
        if Speed == 0:
            Go_to_Speed_Zero_4()
        elif Speed > 15:
            if (M4_state == M4_Stop) or (M4_state_dir == 1):
                Go_to_target_Speed_4(Speed)
                M4_state_dir = 1
            elif (M4_state_dir == -1):
                Go_to_Speed_Zero_4()
        elif Speed > 0 and Speed <= 15:
            if (pre_4_Speed > 15) or (M4_state_dir == -1):
                Go_to_Speed_Zero_4()
            elif M4_state == M4_Stop:
                Go_to_target_Speed_4(Speed)
                M4_state_dir = 1
        elif Speed < -15:
            if (M4_state == M4_Stop) or (M4_state_dir == -1):
                Go_to_target_Speed_4(Speed)
                M4_state_dir = -1
            elif (M4_state_dir == 1):
                Go_to_Speed_Zero_4()
        elif Speed < 0 and Speed >= -15:
            if (pre_4_Speed < -15) or (M4_state_dir == 1):
                Go_to_Speed_Zero_4()
            elif (M4_state == M4_Stop):
                Go_to_target_Speed_4(Speed)
                M4_state_dir = -1
        M4_state = M4_Move
        teensy.write(bytearray(packet4))
        pre_4_Speed = Speed
    elif Speed == 0 and M4_state == M4_Move and start_up_4 == 1:
        Go_to_Speed_Zero_4()
        teensy.write(bytearray(packet4))
        start_up_4 = 0
        read_encoder2(4)
        

def get_gamepad_input(joystick):
    # 이벤트 처리
    for event in pygame.event.get():
        if event.type == pygame.JOYAXISMOTION:
            if event.axis == 0:                
                if event.value > -0.2025 and event.value < 0.2025:
                    joy.axisX = int(0)
                else:
                    if event.value >= 0.2025:
                        joy.axisX = int(event.value * 400 - 80)
                    elif event.value <= -0.2025:
                        joy.axisX = int(event.value * 400 + 80)
            if event.axis == 1:                
                if event.value > -0.22 and event.value < 0.22:
                    joy.axisY = int(0)
                else:
                    if event.value > 0.22 :
                        joy.axisY = int(event.value * 50 - 10)
                    elif event.value < -0.22 :
                        joy.axisY = int(event.value * 50 + 10)
        if event.type == pygame.JOYBUTTONDOWN:
            if event.button == 0:
                read_encoder2(3)
                print("BB")
            

gamepad = init_gamepad()
################################################################################
    
    
################################################################################
TCP_host_IP = "10.254.1.20"
TCP_host_port = 7000

TCP = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
TCP.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 0)

TCP.bind((TCP_host_IP, TCP_host_port))

TCP.listen(2)

def Get_Joystick(client_socket, addr):
    global joy
    while 1:    
        data = client_socket.recv(16)
        ds = struct.unpack('3iI', data)
        if ds[3] & 0xfc000000 == 4227858432:
            joy.axisX = ds[0]
            joy.axisY = ds[1]
            joy.axisT = ds[2]
            joy.button = ds[3]
            
        time.sleep(0.001)
        
def Get_Clickdata(client_socket, addr):
    global Click
    while 1:
        data = client_socket.recv(12)
        ds = struct.unpack('3i', data)
        
        if ds[0] == 1 or ds[0] == 2:
            C_LR.value = ds[0]
            C_X.value = ds[1]
            C_Y.value = ds[2]
            
        time.sleep(0.001)
################################################################################

    
if __name__ == '__main__':
    p1 = Process(target=RGB_pro, args=(C_LR, C_X, C_Y, RGB_Com_X, RGB_Com_Y,))
    p2 = Process(target=IR_pro, args=(IR_Com_X, IR_Com_Y,))
    
    p1.start()
    p2.start()
    
    client_socket1, addr1 = TCP.accept()
    print("success1")
    client_socket2, addr2 = TCP.accept()
    print("success2")
    
    
    t1= threading.Thread(target=Get_Clickdata, args=(client_socket1, addr1))

    t1.daemon = True

    t1.start() 
    
    t2 = threading.Thread(target=Get_Joystick, args=(client_socket2, addr2))

    t2.daemon = True

    t2.start() 
    
    while 1:
        print(IR_Com_X.value, IR_Com_Y.value)
        #if gamepad:
        #    get_gamepad_input(gamepad)
        data1 = teensy.read(2)
        if len(data1) > 1:
            if data1[0] == 3 and data1[1] == 3:
                data2 = teensy.read(3)
                if data2 == b'\xf6\x02\xfb' or data2 == b'\xf6\x00\xf9':
                    M3_state = M3_Stop
                    M3_state_dir = 0
            elif data1[0] == 4 and data1[1] == 3:
                data2 = teensy.read(3)
                if data2 == b'\xf6\x02\xfc' or data2 == b'\xf6\x00\xfa':
                    M4_state = M4_Stop
                    M4_state_dir = 0
            elif data1[0] == 3 and data1[1] == 8:
                data2 = teensy.read(7)
                #print(data2)
            elif data1[0] == 4 and data1[1] == 8:
                data2 = teensy.read(7)
                #print(data2)
                
        Active_Motor_3(joy.axisX)
        Active_Motor_4(joy.axisY)
    
device.close() 
