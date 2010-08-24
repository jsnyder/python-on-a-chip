#!/usr/bin/python

# This file was written by Andrew Pullin
# This file obtained from: http://bmi.berkeley.edu/~pullin/red-bsl.py
# No copyright or licensing is claimed
# Permission to use this file was granted via correspondence


import serial
from struct import pack,unpack
import os
import sys
import time
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-f", "--file", dest="filename",
                  help="binary file to program", metavar="FILE")
parser.add_option("-t", "--target", dest="target",
                  help="serial device to send to, default /dev/tty.usbserial-000030FDB",
                  default="/dev/tty.usbserial-000030FDB'",
                  metavar="TARGET")
parser.add_option("-s", "--flash", dest="flashprog", action="store_true",
                  help="write program to flash using libmc1322x flasher", 
                  default=False,
                  metavar="FLASHPROG")
parser.add_option("-S", "--SSL", dest="SSL_flashprog", action="store_true",
                  help="write program to flash using SSL flasher", default=False,
                  metavar="SSLFLASHPROG")
parser.add_option("-b", "--baudrate", dest="baudrate",
                  help="baudrate for serial device, default 115200", default=115200,
                  metavar="BAUDRATE")

(options, args) = parser.parse_args()

ZEROCHAR = chr(0)
SOF = chr(0x55)

engReadReq      = 0x01
engReadResp     = 0x02
engWriteReq     = 0x03
engCommitReq    = 0x04
engEraseReq     = 0x05
engCmdCnf       = 0xF0

gEngValidReq	= 0x0
gEngInvalidReq	= 0x1
gEngSuccessOp	= 0x2
gEngWriteError	= 0x3
gEngReadError	= 0x4
gEngCRCError	= 0x5
gEngCommError	= 0x6
gEngExecError	= 0x7
gEngNoConfirm	= 0x8

engSecured    = 0xC3
engUnsecured  = 0x3C

ENG_BUFFER_SIZE = 0x200
FLASH_IMAGE_HEADER = 0x8;

### Helper functions, should be moved to a different class or module later:
def simpleCRC(bytes):
	crc = 0;
	return sum([ord(b) for b in bytes]) & 255;

def SendCommand(command):
	ser.write(SOF)
	ser.write((Int16AsBytes(len(command))))
	ser.write(command)
	ser.write(chr(simpleCRC(command)))
	#print "SOF: ",SOF.encode("hex")
	#print "LEN: ",len(command)
	#print "PAY: ",command.encode("hex")
	#print "CRC: %x" % simpleCRC(command)


def ENG_Erase(address):
	print "Erasing address 0x%08x" % address
	command = chr(engEraseReq) + Int32AsBytes(address)
	SendCommand(command)
	return WaitForConfirm()

def ENG_Write(address, data):
	if len(data) > ENG_BUFFER_SIZE:
	  return gEngInvalidReq

	#print "Writing ",len(data),"B to 0x%08x" % address
	#data is a list, so list->str is required for concat
	command = chr(engWriteReq) + Int32AsBytes(address) + Int16AsBytes(len(data)) + ''.join(data)
	SendCommand(command)
	return WaitForConfirm()

def ENG_Commit(length, secure):
	command = chr(engCommitReq) + Int32AsBytes(length)
	if secure:
		command += chr(engSecured)
	else:
		command += chr(engUnsecured)
	SendCommand(command)
	return WaitForConfirm()


def WaitForConfirm():
	recvd = ser.read(1)
	while(recvd != SOF):
	  recvd = ser.read(1)
	lenStr = ser.read(2)
	len = unpack("H",lenStr)[0]
	command = ser.read(len)
	crcIn = ord(ser.read(1))
	if crcIn != simpleCRC(command):
	  print "CRC error"
	  return gEngCRCError
	if ord(command[0]) != engCmdCnf:
	  print "Confirm error"
	  return gEngNoConfirm
	else:
	  return ord(command[1])

def Int32AsBytes(val):
	#For sanity, value is wrapped to unsigned 32-bit
	val &= 0xffffffff
	return pack('I',val)

def Int16AsBytes(val):
	#For sanity, value is wrapped to unsigned 16-bit
	val &= 0xffff
	return pack('H',val)

def EraseFlash():
	status = ENG_Erase(0xffffffff)
	if status != gEngSuccessOp:
	  print "Error erasing flash: ",status
	else:
	  print "Flash erased..."

def DownloadBinary():
	flashFile = open(options.filename)
	filesize = os.path.getsize(options.filename)
	print "Writing ",options.filename," to flash... (%dB)" % filesize
	#load entire BIN into an array. Images are < 128KB, so this isn't too terrible
	flashBytes = [i for i in flashFile.read()]
	flashIndex = 0
	currentWriteAddress = FLASH_IMAGE_HEADER
	binRemainder = filesize

	starttime = time.time()

	#Write
	while binRemainder != 0:
		if binRemainder > ENG_BUFFER_SIZE:
		    sendSize = ENG_BUFFER_SIZE
		else:
		    sendSize = binRemainder
		binRemainder -= sendSize
		status = ENG_Write(currentWriteAddress, flashBytes[flashIndex:(flashIndex+sendSize)])
		if status != gEngSuccessOp:
		    print "Error trying to write to Flash: ",status
		    sys.exit(-1)
		currentWriteAddress += sendSize;
		flashIndex += sendSize;
		#print ".",

	#Commit
	status = ENG_Commit(filesize, False)
	if status != gEngSuccessOp:
		print "Error executing commit: ",status
		sys.exit(-1)

	endtime = time.time()
	print "Speed: %.2f KBps" % (filesize/(endtime-starttime)/1000)

#######################################


if options.filename == None:
	print "No binary file specified."
	parser.print_help()
	sys.exit(-1)

if options.SSL_flashprog and options.flashprog:
	print "You can only use one flasher binary! -s and -S are mutually exclusive."
	sys.exit(-1)

ser = serial.Serial(port=options.target,baudrate=options.baudrate,timeout=0.25,rtscts=1)
if ser.isOpen():
	ser.flushInput()
	ser.flushOutput()
	ser.setRTS()

connected = 0
print "Press RESET now..."

while True:
	ser.write(ZEROCHAR)
	response = ser.read(100)
	if response == "\x00CONNECT" or response=="CONNECT":
		print "Connected!"
		break

if options.SSL_flashprog:
	infile = open("ssl.bin")
	filesize = os.path.getsize("ssl.bin")
	print "Sending SSL flasher... (%dB)" % filesize
elif options.flashprog:
	infile = open("flasher.bin")
	filesize = os.path.getsize("flasher.bin")
	print "Sending libmc1322x flasher... (%dB)" % filesize
else:
	infile = open(options.filename)
	filesize = os.path.getsize(options.filename)
	print "Sending binary file to RAM... (%dB)" % filesize


#ser.write(chr(filesize & 255))
#ser.write(chr((filesize >> 8)&255))
#ser.write(chr((filesize >> 16)&255))
#ser.write(chr((filesize >> 24)&255))
fileSizeBytes = pack('I',filesize)
ser.write(fileSizeBytes)


#bytes = [i for i in infile.read()]
bytes = infile.read()

starttime = time.time()
#ser.write(bytes)
for byte in bytes:
	ser.write(byte)

#Make sure all bytes are sent
while 1:
	if ser.inWaiting() == 0:
	  break


endtime = time.time()

print "Speed: %.2f KBps" % (filesize/(endtime-starttime)/1000)

#SSL section for sending binary
if options.SSL_flashprog:
	print "Waiting for flasher to start..."
	for tries in range(100):
		time.sleep(0.010)
		if tries==99:
			print "No response from flasher utility. Erase flash with jumpers and try again."
			sys.exit(0)
		if ser.readline().strip() == "READY":
			print "Entering Second Stage Loader..."
			break
	EraseFlash()
	DownloadBinary()
#Section for libmc1322x flasher
elif options.flashprog:
	print "Waiting for flasher to start..."
	for tries in range(100):
		time.sleep(0.010)
		if tries==99:
			print "No response from flasher utility. Erase flash with jumpers and try again."
			sys.exit(0)
		if ser.readline().strip() == "ready":
			break

	flashfile = open(options.filename)
	filesize = os.path.getsize(options.filename)
	print "Writing to flash... (%dB)" % filesize
	flashbytes = [i for i in flashfile.read()]
	ser.write(chr(filesize & 255))
	ser.write(chr(filesize >> 8))
	ser.write(chr(filesize >> 16))
	ser.write(chr(filesize >> 24))
	starttime = time.time()
	for byte in flashbytes:
		ser.write(byte)
		time.sleep(0.0005)
	endtime = time.time()
	print "Speed: %.2f KBps" % (filesize/(endtime-starttime)/1000)

print "Done."

ser.close()


