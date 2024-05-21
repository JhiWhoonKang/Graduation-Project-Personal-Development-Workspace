import pygame
import serial
import time
from dataclasses import dataclass
import serial
import struct

try:
    teensy = serial.Serial('COM3', 500000)
except IOError as e:
    print(e)
    print("Teensy undetect")
    exit()
print("Teensy hi")

def init_gamepad():
    pygame.init()
    pygame.joystick.init()
    joystick_count = pygame.joystick.get_count()
    if joystick_count == 0:
        #print("게임 패드가 연결되어 있지 않습니다.")
        return None

    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    #print(f"{joystick.get_name()} 게임 패드가 연결되었습니다.")
    return joystick

class joy_data:
    axisX:int = 0
    axisY:int = 0
    axisT:int = 0
    button:int = 0xfc000004
joy = joy_data()

ACC_Z = 220
PREV_LEFT = 0
PREV_RIGHT = 0
PREV_UP = 0
PREV_DOWN = 0
pulse = 0
def get_gamepad_input(joystick):
    global joy
    global PREV_DOWN, PREV_LEFT, PREV_RIGHT, PREV_UP, pulse
    for event in pygame.event.get():
        if event.type == pygame.JOYBUTTONUP:
            if event.button == 2: # 3번 - go home
                go_home(4)
                go_home(5)
            if event.button == 3: # 4번 - set axis 0
                set_current_axis_to_zero(5)
            if event.button == 4: # 5번 - set axis 0
                position_control(5, 1, 30, 50, 18062)
                pulse = 18602
            if event.button == 5: # 6번 - read encoder
                read_encoder(5)
            if event.button == 11:
                position_control(5, 0, 100, 200, 100) # 0: CC2
                pulse -=100
                print("pulse: ", pulse)
            if event.button == 10:
                position_control(5, 1, 100, 200, 100) # 1: CW
                pulse +=100
                print("pulse: ", pulse)
            if event.button == 9:
                position_control(5, 0, 100, 200, 10)
                pulse -=10
                print("pulse: ", pulse)
            if event.button == 8:
                position_control(5, 1, 100, 200, 10)
                pulse +=10
                print("pulse: ", pulse)
            if event.button == 7:
                position_control(5, 0, 100, 200, 1)
                pulse -=1
                print("pulse: ", pulse)
            if event.button == 6:
                position_control(5, 1, 100, 200, 1)
                pulse +=1
                print("pulse: ", pulse)
            if event.button == 5: # optic zero space
                position_control(4, 1, 50, 100, 18062)
                position_control(5, 1, 50, 100, 8190)

def read_encoder(canid):
    byte1 = 0x31
    crcbyte = (canid + byte1) & 0xFF
    packet = [canid, 2, byte1, crcbyte]
    teensy.write(bytearray(packet))    
    
def go_home(canid):
    byte1 = 0x91
    crcbyte = (canid + byte1) & 0xFF
    packet = [canid, 2, byte1, crcbyte]
    teensy.write(bytearray(packet))

def set_current_axis_to_zero(canid):
    byte1 = 0x92
    crcbyte = (canid + byte1) & 0xFF
    packet = [canid, 2, byte1, crcbyte]
    teensy.write(bytearray(packet))


def position_control(canid, dir, speed, acc,  pulses):
    upper_speed = (speed >> 8) & 0x0F
    lower_speed = speed & 0xFF
    byte1 = 0xFD
    byte2 = (dir << 7) | upper_speed
    byte3 = lower_speed
    byte4 = acc
    byte5 = (pulses >> 16) & 0xFF
    byte6 = (pulses >> 8) & 0xFF
    byte7 = pulses & 0xFF
    byte8 = (canid + 0xFD + byte2 + byte3 + byte4 + byte5 + byte6 +byte7) & 0xFF
    packet = [canid, 8, byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8]
    teensy.write(bytearray(packet))
    hex_packet = [format(byte, '02X') for byte in packet]
    print(hex_packet)      

while(True):
        gamepad = init_gamepad()  
        if gamepad:
            get_gamepad_input(gamepad)
            
# class Gun:
#     def __init__(self):
#         self.__gun_ID = 0x07
#         self.__MODEMASK = 0x80
#         self.__DEVICEMASK = 0x40
#         self.__CAMMANMASK = 0x3F
#         self.__AHRS = 0x40
#         self.__DEVICE = 0x00
        
#         self.ack = False
        
#         self.trigger_status = 0 # open 0 , ready 2, on 3
#         self.trigger_open_degree = 110
#         self.trigger_single_time = 100
#         self.trigger_ready_degree = 78
#         self.trigger_on_degree = 60
        
#         self.voltage = 0
#         self.temperature = 0
#         self.accel = [0,0,0]
#         self.gyro = [0,0,0]
#         self.mag = [0,0,0]
#         self.euler = [0,0,0]
#         self.quatanion = [0,0,0,0]
                    
#     def __read_int_from_bytes(self,data):
#         # 바이트 데이터를 정수로 변환
#         return struct.unpack('<I', data)[0] 
    
#     def __DeviceData(self, data):
#         if ((data[0] & self.__MODEMASK) >> 7) == 0x00:           # 읽기 모드
#             com = data[0] & self.__CAMMANMASK
#             if com == 0x00:        # 장치 확인 완료
#                 if data[1] == self.__gun_ID:
#                     self.ack = True
#                     print("[INFO] GUN::Gun Ack")
#             elif com == 0x01:
#                 if data[1] == 0x00:
#                     print("[INFO] GUN::Gun POWER Off")
#                 elif data[1] == 0x01:
#                     print("[INFO] GUN::Gun POWER On")
#             elif com == 0x10:
#                 if data[1] == 0x00:
#                     self.trigger_status = 0
#                     print("[INFO] GUN::Trigger Open")
#                 elif data[1] == 0x02:
#                     self.trigger_status = 2
#                     print("[INFO] GUN::Trigger Ready")
#                 elif data[1] == 0x03:
#                     self.trigger_status = 3
#                     print("[INFO] GUN::Trigger On")
#             elif com == 0x14:
#                 self.trigger_open_degree = data[1]
#                 print("[INFO] GUN::Open Degree : ", self.trigger_open_degree)
#             elif com == 0x15:
#                 self.trigger_single_time = self.__int_from_bytes(data[1])
#                 print("[INFO] GUN::Single time : ", self.trigger_single_time)
#             elif com == 0x16:
#                 self.trigger_on_degree = data[1]
#                 print("[INFO] GUN::Single time : ", self.trigger_on_degree)
#             elif com == 0x17:
#                 self.trigger_ready_degree = data[1]
#                 print("[INFO] GUN::Ready Degree : ", self.trigger_ready_degree)
                
#     def __AHRSData(self, data):
#         if ((data[0] & self.__MODEMASK) >> 7) == 0x00:           # 읽기 모드
#             index = (data[0] & self.__CAMMANMASK)
#             if (data[1] == 0xE6): # "p + v"
#                 self.voltage = self.__float_from_bytes(data[2:])
#                 print("[INFO] GUN::Voltage : ", self.voltage)
#             if (data[1] == 0x74): # "t"
#                 self.temperature = self.__float_from_bytes(data[2:])
#                 print("[INFO] GUN::Temperature : ", self.temperature)
#             elif data[1] == 0x61: # "a"
#                 self.accel[index] = self.__float_from_bytes(data[2:])
#                 if index == 2:
#                     print("[INFO] GUN::Accel : ", self.accel)
#             elif data[1] == 0x67: # "g"
#                 self.gyro[index] = self.__float_from_bytes(data[2:])
#                 if index == 2:
#                     print("[INFO] GUN::Gyro : ", self.gyro)
#             elif data[1] == 0x6D: # "m"
#                 self.mag[index] = self.__float_from_bytes(data[2:])
#                 if index == 2:
#                     print("[INFO] GUN::Mag : ", self.mag)
#             elif data[1] == 0x65: # "e"
#                 self.euler[index] = self.__float_from_bytes(data[2:])
#                 if index == 2:
#                     print("[INFO] GUN::Euler : ", self.euler)
#             elif data[1] == 0x71: # "q"
#                 self.quatanion[index] = self.__float_from_bytes(data[2:])
#                 if index == 3:
#                     print("[INFO] GUN::Quatanion : ", self.quatanion)
                                            
#     def CheckPacket(self, data):
#         if data[0] != self.__gun_ID:
#             return
#         length = data[1]
#         if ((data[2][0] & self.__DEVICEMASK) >> 6) == 0x00:     # 장치
#             self.__DeviceData(data[2])
#         elif ((data[2][0] & self.__DEVICEMASK) >> 6) == 0x01:     # AHRS
#             self.__AHRSData(data[2])
    
#     def __CHECKACK(self):
#         if not self.ack:
#             print("[WARN] GUN::Didn't Check the Device")
#             return True
#         return False
    
#     def ReadGunPower(self):
#         if self.__CHECKACK == True:
#             return self.ACK()
#         packet = [self.__gun_ID, 1, 0x01]
#         return bytearray(packet)
        
#     def ReadTriggerStatus(self):
#         if self.__CHECKACK == True:
#             return self.ACK()
#         packet = [self.__gun_ID, 1, 0x10]
#         return bytearray(packet)
    
#     def ReadOpenDegree(self):
#         if self.__CHECKACK == True:
#             return self.ACK()
#         packet = [self.__gun_ID, 1, 0x14]
#         return bytearray(packet)
    
#     def ReadSingleTime(self):
#         if self.__CHECKACK == True:
#             return self.ACK()
#         packet = [self.__gun_ID, 1, 0x15]
#         return bytearray(packet)
    
#     def ReadOnDegree(self):
#         if self.__CHECKACK == True:
#             return self.ACK()
#         packet = [self.__gun_ID, 1, 0x16]
#         return bytearray(packet)
    
#     def ReadReadyDegree(self):
#         if self.__CHECKACK == True:
#             return self.ACK()
#         packet = [self.__gun_ID, 1, 0x17]
#         return bytearray(packet)
    
#     def ReadAHRS(self, name):
#         if self.__CHECKACK == True:
#             return self.ACK()
        
#         byte_data = name.encode('utf-8')
#         if name == "pv":
#             byte_data = byte_data[0] + byte_data[1]
#         else:
#             byte_data = int.from_bytes(byte_data, 'big')
#         packet = [self.__gun_ID, 2, self.__AHRS, byte_data]
#         return bytearray(packet)

        
            
#     def __int_from_bytes(self,data):
#         # 바이트 데이터를 정수로 변환
#         return struct.unpack('<I', data)[0] 
    
#     def __float_from_bytes(self,data):
#         # 바이트 데이터를 정수로 변환
#         return struct.unpack('<f', data)[0] 
        
#     def ACK(self):
#         self.ack = False
#         packet = [self.__gun_ID, 0x01, 0x00]
#         return bytearray(packet)
    
#     def Reset(self):
#         packet = [self.__gun_ID, 0x01, 0xFF]
#         return bytearray(packet)
                      
# SendData = list()

# def Read(mcu:serial.Serial):
#     if mcu.in_waiting > 3:
#         id = int.from_bytes(mcu.read(1), 'big')
#         len = int.from_bytes(mcu.read(1), 'big')
#         data = mcu.read(len)
#         return [id, len, data]
#     return [0,0,0]

# def WaitData(mcu:serial.Serial):
#     while(True):
#         if mcu.in_waiting > 3:
#             break
        
# def Write(mcu:serial.Serial):
#     while(True):
#         if len(SendData) == 0:
#             break
#         mcu.write(SendData[0])
#         SendData.pop(0)
        

        
# if __name__=="__main__":
#     try:
#         teensy = serial.Serial('COM3', 500000)
#     except IOError as e:
#         print(e)
#         print("Teensy undetect")
#         exit()
#     print("Teensy open")
#     gun = Gun()
    
#     # 장치 인식
#     SendData.append(gun.ACK())          # 전송 목록에 데이터 추가 (bytearray)
#     Write(teensy)                       # 전송 데이터 모두 처리
    
#     ## Apply to all data processing
#     WaitData(teensy)                    # 데이터가 올 때까지 대기 (예제 용)
#     packet = Read(teensy)               # 데이터를 받아서 처리하기 편한 packet으로 변경 [id(int), len(int), data(bytearray)]   
#     ##-----------------------------     # 데이터가 없는 경우 [0,0,0]반환
#     gun.CheckPacket(packet)             # 데이터 처리 / 해당 데이터가 아닌 경우 return
        
    
    # while(True):
    #     gamepad = init_gamepad()  
    #     if gamepad:
    #         get_gamepad_input(gamepad)
        # time.sleep(1)
        # SendData.append(gun.ReadAHRS("e")) # 전송 목록에 데이터 추가 (bytearray)
        # Write(teensy)                       # 전송 데이터 모두 처리
        # packet = Read(teensy)
        # gun.CheckPacket(packet)
        # packet = Read(teensy)
        # gun.CheckPacket(packet)
        # packet = Read(teensy)
        # gun.CheckPacket(packet)