#!/usr/bin/python3

import sys
import os
import time
import pty
import termios
import tty

count = 0
if len(sys.argv) < 2:
  print("Usage: <prog_name> <input_file_name>")
  sys.exit()

try:
  file = open(sys.argv[1], "rb")
except FileNotFoundError:
  msg = "File: " + sys.argv[1] + " does not exist"
  print(msg)
  sys.exit()

(fd, fd1) = pty.openpty()  
tty.setraw(fd)  
print("other end pseudoterminal name is " + str(os.ttyname(fd1)))
time.sleep(1)

all_data = file.read()
print(all_data)

while True:
  for data_byte in all_data:
    if data_byte == 36:
      count += 1
      print("sending new message:" + str(count))
    #print("byte %x" % data_byte)
    os.write(fd, data_byte.to_bytes(1,"little"))
    #os.write(fd, b"")#uncomment this line if it has issues
    time.sleep(0.01)
    # res = os.read(fd,10000)
    # print (res.decode())
    # os.write(fd, res)

