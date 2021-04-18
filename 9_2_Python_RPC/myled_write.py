import serial
import time
serdev = '/dev/ttyACM0'                # use the device name you get from `ls /dev/ttyACM*`
s = serial.Serial(serdev, 9600)

s.write(bytes("/myled/write 1\r", 'UTF-8'))
line=s.readline() # Read an echo string from mbed terminated with '\n' (putc())
print(line.decode(encoding='utf-8'))
line=s.readline() # Read an echo string from mbed terminated with '\n' (RPC reply)
print(line.decode(encoding='utf-8'))
time.sleep(1)

s.write(bytes("/myled/write 0\r", 'UTF-8'))
line=s.readline() # Read an echo string from mbed terminated with '\n' (putc())
print(line.decode(encoding='utf-8'))
line=s.readline() # Read an echo string from mbed terminated with '\n' (RPC reply)
print(line.decode(encoding='utf-8'))
s.close()
