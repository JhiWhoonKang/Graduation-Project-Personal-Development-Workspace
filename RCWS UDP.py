import cv2
import socket
import math
import pickle
import sys
from dataclasses import dataclass
import struct

max_length = 65000
host = "127.0.0.1"
#host = "172.16.2.249"
port = 9000

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((host, port))

cap = cv2.VideoCapture(1)
ret, frame = cap.read()

while True:
    # compress frame
    # data_ = sock.recvfrom(max_length)
    # print(data_)

    ret, frame = cap.read()
    if ret:
        retval, buffer = cv2.imencode(".jpg", frame)
        if retval:
            buffer = buffer.tobytes()
            buffer_size = len(buffer) #buffer 사이즈 확인.

            num_of_packs = 1
            if buffer_size > max_length: # 65,000보다 크면
                num_of_packs = math.ceil(buffer_size/max_length)

            left = 0
            right = max_length

            for i in range(num_of_packs):
                data = buffer[left:right]
                left = right
                right += max_length

                sock.sendto(data, (host, 8000))