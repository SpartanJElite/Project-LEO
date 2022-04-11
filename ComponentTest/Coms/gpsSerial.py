
import serial

arduinoData = serial.Serial('com3',115200)
while True:
    cmd = input('Enter your long and lat:')
    cmd = cmd + '\r'
    arduinoData.write(cmd.encode())




