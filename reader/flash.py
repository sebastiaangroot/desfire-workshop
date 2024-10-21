import RPi.GPIO as GPIO
import sys
import time

if len(sys.argv) < 2:
    print(f'usage: {sys.argv[0]} <BCM pin 1> .. <BCM pin N>')
    sys.exit(1)

pins = []
for i in range(len(sys.argv)-1):
    pins.append(int(sys.argv[i+1]))

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

for pin in pins:
    GPIO.setup(pin, GPIO.OUT)

for pin in pins:
    GPIO.output(pin, GPIO.HIGH)

time.sleep(2)

for pin in pins:
    GPIO.output(pin, GPIO.LOW)

