import serial

serialPort = "COM3"  # port we connected to gui
baudRate = 9600  # baud rate
ser = serial.Serial(serialPort, baudRate, timeout=0.5)
print("Configutration：Port=%s ，Baud rate=%d" % (serialPort, baudRate))

demo1 = b"1"     # Convert 0 to ASCII
demo2 = b"2"
demo3 = b"3"

while 1:
    print("Please input:")
    print("1.New RPM")
    print("2.New Temperature")
    c = input("3.New pH\n")

    c = ord(c)    # Convert c to UTF-8
    if(c==49):
        ser.write(demo1)   #ser.write to write data to port
    if(c==50):
        ser.write(demo2)
    if(c==51):
        ser.write(demo3)
    
