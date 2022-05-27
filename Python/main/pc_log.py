#!/usr/bin/python

import serial
import time
import sys
# from cobs import cobs
import matplotlib.pyplot as plt
import array
import numpy as np
import tkinter

# NOTE:  Should install matplotlib, tkinter

PRINTLOG = False
PRINTSOURCE = False
NUMBER =10_000 #10000
data = array.array('I')

def printLog(a):
    if( PRINTLOG ):
        print(a)

def main(arg):
    global PRINTLOG
    global PRINTSOURCE
    global NUMBER
    if(len(arg)==1):
        print("try format for run:")
        print("python3 main.py <PORT>[<NUMBER=1000>] [<PRINTSOURCE=False>] [<PRINTLOG=False>]")
        return
    if(len(arg) > 1):
        PORT = arg[1]
        if(len(arg) > 2):
            NUMBER = int(arg[2])
            if(len(arg)>3):
                PRINTSOURCE = bool(arg[3])
                if(len(arg)>4):
                    PRINTLOG = bool(arg[4])

    ser = serial.Serial()
    ser.baudrate = 115200
    ser.port = PORT # "/dev/ttyUSB1" #'COM12'
#    ser.set_buffer_size(rx_size = 12800, tx_size = 12800)
    print(ser)
    ser.open()

    buf = bytearray()
    count = 0 #-1 # if count<0 then non-stop, if count=0 stop after NUMBER readingconda
    print("***********************************************************************")
    time_1 = time.time()
    print(time_1)
    print("***********************************************************************")
    
    bwords = bytearray()
    iword = 0
    word_i = 0
    while True:
#        byte = bytearray()
        byte = ser.read(1)
        if byte != None:
            if(count >=0): 
                count = count + 1
            ibyte = int.from_bytes(byte, byteorder='big')
            if(ibyte == 32):
                # iword = int.from_bytes(bwords, byteorder='big')
                ii = word_i
                for bb in bwords:
                    ii = ii -1
                    iword = iword + bb*(10**ii)
                    # print(f'\r bb={bb} word_i={word_i} ii={ii} iword={iword} ',  flush=True)
                print(f'\r         extend data={iword} count={count} ',  flush=True)
                if iword > 1000:
                    iword = 0
                data.append(iword)
                del bwords[0:word_i]  
                iword = 0
                word_i = 0
            else:
                bwords.extend((abs(ibyte - 48)).to_bytes(1, byteorder='big') )
                # print(f'\r         ibyte={ibyte-48} ',  flush=True)
                # print(f'\r         word_i={word_i} ',  flush=True)
                word_i = word_i + 1
            if(count > NUMBER):
                break
    print(f'\r         FINISH data.size={len(data)}',  flush=True)
    plt.plot(data)
    plt.show()
                # plt.plot(data)

                # x = np.arange(0, data.buffer_info()[1], 1)
                # size = data.buffer_info()[1]
                # print(f'\nSIZE={size}')
                # plt.plot(x,data)
                # plt.plot(data)               
                # time_2 = time.time()
                # time_interval = time_2 - time_1
                # print(time_interval)
                # plt.show()
                # plt.savefig("mygraph.png")
#            print(f'     byte BUFF LENGTH={len(byte)}')
            # buf.extend(byte)
        
            # del buf[0:bytes_to_drop]  

    
if __name__ == '__main__':
    main(sys.argv)    