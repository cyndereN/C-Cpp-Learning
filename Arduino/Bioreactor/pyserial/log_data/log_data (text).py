import time
import serial
ser = serial.Serial(
    port='COM3',                   
    baudrate=9600,
    parity=serial.PARITY_ODD,      
    stopbits=serial.STOPBITS_TWO,  
    bytesize=serial.SEVENBITS      
)
data = ''

while 1:
    data = ser.readline()
    t = time.time()
    ct = time.ctime(t)
    print(ct, ':')
    print(data) 
    f = open('D:/test.txt', 'a') #can be changed
    f.writelines(ct)
    f.writelines(':\n')
    f.writelines(data.decode('utf-8'))
    f.close()
