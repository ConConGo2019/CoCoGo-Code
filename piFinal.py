#This is the same code as rainTest.py, but it is a bit cleaner (unneeded comments were removed)

import gps
import serial
import RPi.GPIO as GPIO
import os 
import sys
from subprocess import Popen
from time import sleep
from graphics import *


v1 = True
ser = serial.Serial('/dev/ttyACM0', 115200)

movie1 = ("/home/pi/Desktop/newInitial.mp4")
v2 = True



movie3 = ("/home/pi/Desktop/Bill.mp4")
v3 = True



os.system('killall omxplayer.bin')


os.system('killall omxplayer.bin')


while 1:
    first = ser.readline()
    #print(first)
    
    if (b'Start' in first and v2 ==True) :
        v2 = False
        os.system('killall omxplayer.bin')
        omxc = Popen(['omxplayer', '-o', "local", movie1])
        

    elif (b'Bill' in first and v3 ==True) :
        v3 = False
        os.system('killall omxplayer.bin')
        omxc = Popen(['omxplayer', '-o', "local", movie3])
        

    

