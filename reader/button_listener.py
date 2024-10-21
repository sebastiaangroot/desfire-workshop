#!/usr/bin/env python

import RPi.GPIO as GPIO
import subprocess
import time

def button_callback(ch):
    print('Button pressed')
    subprocess.run('./ctf_leds.sh', shell=True)

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(21, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

GPIO.add_event_detect(21, GPIO.RISING, callback=button_callback)
while True:
    time.sleep(360)
