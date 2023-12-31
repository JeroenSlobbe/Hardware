# The goal of this script is to get a better understanding of the SPI protocol.
# It takes the hex formatted export file from the Kings Virtual Instruments Studio (https://www.qdkingst.com/en/download) as an input
# The scripts Format is: Time [s],Packet ID,MOSI,MISO. For the script to correctly work, plz remove this line :)
# Based on very interesting paper: http://elm-chan.org/docs/mmc/mmc_e.html and: http://www.rjhcoding.com/avrc-sd-interface-4.php
# Interesting thing to play around with, Aruidno lib only implemented 13 out of the at least 63 commands: https://github.com/dilshan/sdfatlib/blob/main/sddriver/sdcmd.h
# SD.begin triggers (line 353) card.init, volume.init and root.init https://github.com/arduino-libraries/SD/blob/master/src/SD.cpp
# Wondering why, CMD17 isn't actually transmitting the filename, because (line 474), its using a cache to determine actual blocknumber to request as read parameter: https://github.com/arduino-libraries/SD/blob/master/src/utility/SdFile.cpp

commandLookupArray = ["GO_IDLE_STATE", "SEND_OP_COND", "ALL_SEND_CID", "SET_RELATIVE_ADDR", "SET_DSR", "SLEEP_AWAKE", "SWITCH", "SELECT_CARD","SEND_EXT_CSD", "SEND_CSD", "SEND_CID", "obsolete", "STOP_TRANSMISSION","SEND_STATUS", "BUSTEST_R", "GO_INACTIVE_STATE", "SET_BLOCKLEN", "READ_SINGLE_BLOCK", "READ_MULTIPLE_BLOCK", "BUSTEST_W","obsolete", "SEND_TUNING_BLOCK", "reserved","SET_BLOCK_COUNT","WRITE_BLOCK", "WRITE_MULTIPLE_BLOCK","PROGRAM_CID","PROGRAM_CSD", "SET_WRITE_PROT", "CLR_WRITE_PROT", "SEND_WRITE_PROT", "SEND_WRITE_PROT_TYPE", "32UNKNOWN", "33UNKNOWN", "34UNKNOWN", "ERASE_GROUP_START","ERASE_GROUP_END", "37UNKNOWN", "ERASE", "FAST_IO", "GO_IRQ_STATE", "41UNKNOWN", "LOCK_UNLOCK", "43UNKNOWN", "QUEUED_TASK_PARAMS","QUEUED_TASK_ADDRESS","EXECUTE_READ_TASK","EXECUTE_WRITE_TASK","CMDQ_TASK_MGMT", "SET_TIME", "50UNKNOWN", "51UNKNOWN", "52UNKNOWN", "PROTOCOL_RD", "PROTOCOL_WR", "APP_CMD","GEN_CMD","57UNKNOWN", "58UNKNOWN", "59UNKNOWN", "60UNKNOWN", "61UNKNOWN", "62UNKNOWN", "63UNKNOWN"]

def printGreen(txtGreen, txtNormal):
	print(f'\033[92m{txtGreen}\033[00m' + txtNormal)
	
def printBlue(txtBlue, txtNormal):
	print(f"\033[96m{txtBlue}\033[00m" + txtNormal)
	
def interpretCommand(command):
	commandArray = command.split(" ")
	#	Note that 0x40 -> 01000000 in binary. Given that the command is only 6 bits and the first two bits are the preamble, we need to remove them
	# Result of bin, will return 0b<binvalue>. For the argument we would like to remove the preabmle (01), hence starting from position 4
	# Note int("STRING",2") converts binary to decimal
	commandNumber = int(str(bin(int(commandArray[0]))[4:]),2)
	return (command + " | " + commandLookupArray[commandNumber] + " (" + str(commandNumber) + ")")

def fixBytePadding(input):
	output = ""
	output = input
	if(len(input) == 3):
		output = " " + input
	return output

started = False
mosiCMD = ""
mosiByteCounter = 0
misoByteCounter = 0
charactersPerLine = 10
misoHex = ""
misoAscii = ""
misoLine = ""

# Both, or one of the channels should be listening, checking this to feel comfortable
with open("hex_output.txt","r") as f:
	for line in f:
		row = line.rstrip('\n').split(",")
		if((int(row[2],16)) != 255) and (int(row[3],16)!=255):
			print("Something weird is going on, as both channels are sending at the same time")


# Disecting, focussing on MOSI arguments
with open("hex_output.txt","r") as f:
	for line in f:
		row = line.rstrip('\n').split(",")
		# Search for RESET/initialisation command: 0x40, 0x00, 0x00, 0x00, 0x95, and ignore anything before
		if(int(row[2],16) == int("40",16)):
			started = True
			
		if(started):
			# Lets ignore the command response time
			if((int(row[2],16)) == 255) and (int(row[3],16)==255):
				x = "do nothing"
			
			# Lets also ignore all the R1 response bytes, that indicate no errors are present (0x00) and the time listening (0xff)
			elif(((int(row[2],16)) == 255)):
				if((int(row[3],16)) != 0):
					misoHex = misoHex + " " + fixBytePadding(hex(int(row[3],16)))
					misoAscii = misoAscii + chr(int(row[3],16))
					
					misoByteCounter = misoByteCounter + 1
					if(misoByteCounter == charactersPerLine):
						misoLine = misoHex + "     " + misoAscii.replace('\n','').replace('\r','')
						printBlue("MISO: ", misoLine)
						misoLine = ""
						misoHex = ""
						misoAscii = ""
						misoByteCounter = 0

			else:
				if(misoByteCounter != 0):
					padding = (charactersPerLine - (len(misoAscii)))*"     "
					misoLine = misoHex + padding + "     " + misoAscii.replace('\n','').replace('\r','')
					printBlue("MISO: ", misoLine)
					misoLine = ""
					misoHex = ""
					misoAscii = ""
					misoByteCounter = 0				
				mosiCMD = mosiCMD + str(int(row[2],16)) + " "
				mosiByteCounter = mosiByteCounter + 1
				if(mosiByteCounter == 6):
					printGreen("MOSI: ", interpretCommand(mosiCMD))
					mosiCMD = ""
					mosiByteCounter = 0

