import xlwt
import time
import serial

#set excel style
def set_style(name,height,bold=False):
    style = xlwt.XFStyle()
    font = xlwt.Font()
    font.name = name
    font.bold = bold
    font.color_index = 4
    font.height = height
    style.font = font
    return style

#write Excel
def write_excel():
    if serial.isOpen():
        print ('Serial is open.\n')
    f = xlwt.Workbook()
    sheet1 = f.add_sheet('arduino_data',cell_overwrite_ok=True)
    row0 = ["RPM","Temperature","pH"]
    time1=time.localtime(time.time())
    
    #first row
    for i in range(len(row0)):
        sheet1.write(0,i,row0[i],set_style('Times New Roman',220,True))
    i=1
    time.sleep(5)
    serial.flushInput() 
    while True:
        try:
            size = serial.inWaiting()
            if size != 0:
                response = serial.read(size)        #read and input
                s=response.decode('utf-8').rstrip('\r\n').split('\t')
                if len(s)!=3:
                    serial.flushInput()
                    continue
                else:
                    try:
                        for j in range(len(s)):
                            sheet1.write(i,j,int(s[j]),set_style('Times New Roman',220,False))
                        print(s)
                        serial.flushInput()                 
                        i = i+1
                        time.sleep(0.5)
                    except ValueError:
                        serial.flushInput()
                        continue
        except KeyboardInterrupt:
            time2=time.localtime(time.time())
            f.save(r'C:\Users\zhang\Desktop\arduino_data\{0}.{1}_{2:0>2d}.{3:0>2d}.{4:0>2d}-{5}.{6}_{7:0>2d}.{8:0>2d}.{9:0>2d}.xls'.format\
                    (time1[1],time1[2],time1[3],time1[4],time1[5],
                     time2[1],time2[2],time2[3],time2[4],time2[5]))
                      #location can be changed
            serial.close()
            print(time1)
            print(time2)
            quit()
     
if __name__ == '__main__':
    serial = serial.Serial('COM3', 9600, timeout=2)
    write_excel()

